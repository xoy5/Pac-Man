/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include <assert.h>
#include <algorithm>

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),

	playerController(&wnd.kbd, PlayerController::KeyboardControll::WSAD),
	secondPlayerController(&wnd.kbd, PlayerController::KeyboardControll::ARROWS),
	pacMan(maze, &playerController),

	botController1(BotController::Behavior::Pursuit, &maze, &pacMan),
	ghostBlinky(Ghost::Identity::Blinky, maze, &secondPlayerController /*&botController1*/, &pacMan),

	botController2(BotController::Behavior::Pursuit, &maze, &pacMan),
	ghostPinky(Ghost::Identity::Pinky, maze, &botController2, &pacMan),

	botController3(BotController::Behavior::Wander, &maze, &pacMan),
	ghostInky(Ghost::Identity::Inky, maze, &botController3, &pacMan),

	botController4(BotController::Behavior::Wander, &maze, &pacMan),
	ghostClyde(Ghost::Identity::Clyde, maze, &botController4, &pacMan)
{
	myMessageBox.SetButtons(MyMessageBox::Buttons::Ok);
	myMessageBox.SetText("Error");
}

void Game::Go()
{
	gfx.BeginFrame();
	ProcessInput();
	const float elapsedTime = ft.Mark();
	float time = elapsedTime;
	while (time > 0.0f) {
		const float dt = std::min(precision, time);
		UpdateModel(dt);
		time -= dt;
	}
	numberOfFrames++;
	timeSecond += elapsedTime;
	if (timeSecond >= 1.0f) {
		timeSecond -= 1.0f;
		FPS = numberOfFrames;
		numberOfFrames = 0;
	}

	ComposeFrame();
	gfx.EndFrame();
}

void Game::ProcessInput()
{
	////////////// KEYBOARD ///////////////
	/////////////// TYPING ////////////////
	// Keys
	while (!wnd.kbd.KeyIsEmpty())
	{
		const Keyboard::Event keyPressed = wnd.kbd.ReadKey();
		if (keyPressed.IsValid() && keyPressed.IsPress())
		{

		}
	}
	// Characters
	while (!wnd.kbd.CharIsEmpty())
	{
		const char character = wnd.kbd.ReadChar();
	}

	///////////////////////////////////////
	/////////////// MOVEMENT //////////////
	if (flagGameEnd == false)
	{
		pacMan.SetMoveDirection(maze);
		ghostBlinky.SetMoveDirection(maze);
		ghostPinky.SetMoveDirection(maze);
		ghostInky.SetMoveDirection(maze);
		ghostPinky.SetMoveDirection(maze);
	}
	///////////////////////////////////////
	///////////////////////////////////////



	//////////////// MOUSE ////////////////
	while (!wnd.mouse.IsEmpty())
	{
		const auto e = wnd.mouse.Read();
		if (flagGameEnd)
		{
			MyMessageBox::ValueButton value = myMessageBox.ProcessMouse(e);

			switch (value)
			{
				case MyMessageBox::ValueButton::Ok:
					flagGameEnd = false;
					
			}
		
		}
	}
	///////////////////////////////////////
}

void Game::UpdateModel(float dt)
{
	if (flagGameEnd == false)
	{
		pacMan.Update(dt, maze);
		ghostBlinky.Update(dt, maze);
		ghostPinky.Update(dt, maze);
		ghostInky.Update(dt, maze);
		ghostClyde.Update(dt, maze);
	}
}

void Game::ComposeFrame()
{
	maze.Draw(gfx);
	pacMan.Draw(gfx);
	ghostBlinky.Draw(gfx);
	ghostPinky.Draw(gfx);
	ghostInky.Draw(gfx);
	ghostClyde.Draw(gfx);

	// Draw FPS
	const std::string fpsText = "FPS: " + std::to_string(FPS);
	fontXs.DrawText(fpsText, Vei2{ 10, 10 }, Colors::White, gfx);
}