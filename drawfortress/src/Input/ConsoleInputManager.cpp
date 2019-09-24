#include <windows.h>

#include "ConsoleInputManager.h"


static std::mutex _consoleLock;

static std::unique_ptr<ConsoleInputManager> _consoleInputInstance;


ConsoleInputManager& ConsoleInputManager::Instance()
{
	if(!_consoleInputInstance)
	{
		_consoleLock.lock();

		if(!_consoleInputInstance)
		{
			_consoleInputInstance = std::make_unique<ConsoleInputManager>(PermissionToken{0});
		}

		_consoleLock.unlock();
	}

	return *(_consoleInputInstance.get());
}

void ConsoleInputManager::InputThread()
{
	const auto inputHandle = GetStdHandle(STD_INPUT_HANDLE);
	

	SetConsoleMode(inputHandle, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);

	INPUT_RECORD irInBuf[128];

	Vector2di lastMousePos;
	auto isLeftButtonPressed  = false;
	auto isRightButtonPressed = false;
	auto isDragStarted        = false;
	
	while(true)
	{
		DWORD  readCount;
		ReadConsoleInput(inputHandle, irInBuf, 128, &readCount);

		_consoleLock.lock();
		
		for (size_t i = 0; i < readCount; i++) 
        {
			auto& input = irInBuf[i];
			auto& evt   = input.Event;

			if(input.EventType == KEY_EVENT)
			{
				if(evt.KeyEvent.bKeyDown)
				{
						Instance()._events[ConsoleInput::Type::KeyDown].push(
							new ConsoleInput
							{
								ConsoleInput::Type::KeyDown,
								static_cast<unsigned short>(evt.KeyEvent.wVirtualKeyCode),
								evt.KeyEvent.uChar.AsciiChar,
								static_cast<bool>(evt.KeyEvent.dwControlKeyState & 2),
								static_cast<bool>(evt.KeyEvent.dwControlKeyState & 8),
								static_cast<bool>(evt.KeyEvent.dwControlKeyState & 16),
								lastMousePos,
								lastMousePos
							}
						);
				}
			}
			
			if(irInBuf[i].EventType == MOUSE_EVENT)
			{
				

				
				auto& ev = irInBuf[i].Event;
				
				Vector2di  mousePos { ev.MouseEvent.dwMousePosition.X, ev.MouseEvent.dwMousePosition.Y};
				
				const auto mouseMoved = mousePos != lastMousePos;
				
				if(ev.MouseEvent.dwButtonState & 1)
				{
					if(mouseMoved)
					{
						if(isLeftButtonPressed && !isDragStarted)
						{
							//drag start
							isDragStarted = true;
						}
						else if(isDragStarted)
						{
							//drag
						}
					}
					else if(!isLeftButtonPressed)
					{
						// left button down
					}
					isLeftButtonPressed = true;
				}
				else if(isDragStarted)
				{
					// drag end
					isDragStarted = false;
				}
				else if(isLeftButtonPressed)
				{
					// left button up
				}

				if(ev.MouseEvent.dwButtonState & 2)
				{
					if(!isRightButtonPressed)
					{
						// right click
					}
					isRightButtonPressed = true;
				}
				else if(isRightButtonPressed)
				{
					// right button up
				}
				
				if(mouseMoved)
				{
					if(!isDragStarted)
					{
						// mouse move
					}
					lastMousePos = mousePos;
				}
			}
		}

		_consoleLock.unlock();
	}
}



ConsoleInputManager::ConsoleInputManager(PermissionToken&&) : _inputThread(new std::thread(InputThread))
{
}

ConsoleInputManager::~ConsoleInputManager()
{
	if(_inputThread)
	{
		_inputThread->join();
		delete _inputThread;
		_inputThread = nullptr;
	}
}


void ConsoleInputManager::AddEventHandler(std::weak_ptr<IConsoleInputHandler> handler)
{
	_handlers[handler.lock()->Type()].push_back(handler);
}

void ConsoleInputManager::Update()
{
	_consoleLock.lock();
		// brisanje unistenih handlera
	for(auto& handlersMap : _handlers)
	{
		auto& handlers = handlersMap.second;

		for(auto it = handlers.begin(); it != handlers.end(); ++it)
		{
			if(it->expired())
			{
				handlers.erase(it--);
			}
		}
	}
	
	for(auto& eventsByTypeMapItem : _events)
	{
		const auto eventType = eventsByTypeMapItem.first;
		
		auto& eventsByType = eventsByTypeMapItem.second;
		
		for( ; !eventsByType.empty(); eventsByType.pop())
		{
			const auto* e = eventsByType.front();
			
			for(auto& handlerWeakPtr : _handlers[eventType])
			{
				if(!handlerWeakPtr.expired())
				{
					handlerWeakPtr.lock()->Invoke(e);
				}
			}

			delete e;
		}
	}

	_consoleLock.unlock();
}

