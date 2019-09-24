#pragma once

#include "Common.h"
#include "ConsoleInputHandler.h"


class ConsoleInputManager
{
	struct PermissionToken{ explicit PermissionToken(int){}; };
public:
	explicit ConsoleInputManager(PermissionToken&&);
	
	static ConsoleInputManager& Instance();

	void AddEventHandler(std::weak_ptr<IConsoleInputHandler> handler);

	void Update();

	~ConsoleInputManager();
private:
	
	static void InputThread();

	std::map< ConsoleInput::Type, std::queue< ConsoleInput* > > _events;
	
	std::map< ConsoleInput::Type, std::list< std::weak_ptr< IConsoleInputHandler > > > _handlers;

	std::thread* _inputThread;


};
