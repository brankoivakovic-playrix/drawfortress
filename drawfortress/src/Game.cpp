
#include "Game.h"
#include "World/World.h"
#include <windows.h>
#include "Input/ConsoleInputManager.h"
#include "Render/Render.h"


unique_ptr<Game> g_Game;

mutex mtx;

#undef DrawText

Game::Game() : _serializer(new Serializer), _world(new World({150, 100}, *_serializer.get()))
{
	Render::Instance().ViewSize({80, 30});
	Render::Instance().Clear();
	_world->Draw(Render::Instance());
	Render::Instance().Flush();

}


Game& Game::Instance()
{
	if (!g_Game)
	{
		mtx.lock();

		if (!g_Game)
		{
			g_Game = unique_ptr<Game>(new Game());
		}

		mtx.unlock();
	}
	return *(g_Game.get());
}

int Game::Loop()
{
	while (true)
	{
		const auto currentTime = chrono::steady_clock::now();
		
		const auto deltaTime = chrono::duration_cast<chrono::milliseconds>(currentTime - _startTime).count();

		ConsoleInputManager::Instance().Update();

		_world->Update(deltaTime);

		
		 
		this_thread::sleep_for(1ms);
	}
}


void Game::Serialize()
{
	
}

void Game::Draw()
{
	Render::Instance().SetClipRect({{0, 0}, {0, 0}});
	Render::Instance().Clear();
	_world->Draw(Render::Instance());
	Render::Instance().Flush();
}

World& Game::GetWorld() const
{
	return *(_world.get());
}
