

#include <thread> 
#include <mutex>

#include "Game.h"
#include "World/World.h"


Game::Game():
	_world(new World())
{
}



std::unique_ptr<Game> g_Game;

std::mutex mtx;

Game* Game::instance()
{
	if (!g_Game)
	{
		mtx.lock();

		if (!g_Game)
		{
			g_Game = std::move(std::unique_ptr<Game>(new Game()));
		}

		mtx.unlock();
	}
	return g_Game.get();
}

int Game::Loop()
{
	while (true)
	{
		
		std::this_thread::sleep_for(1ms);
	}
}

void Game::Pause()
{
}

void Game::Resume()
{
}

void Game::Serialize()
{
}
