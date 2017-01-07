/******************************************************************
* Copyright (C) 2016 Jordi Serrano Berbel <jsberbel95@gmail.com> *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#pragma once
#include "System.hh"
#include <iostream>

#pragma region GAME_SCENES
#include "GameMenu.hh"
#include "GameScene.h"
#include "Scene_Dif_Selector.h"
#include "Scene_Playing.h"
#include "Scene_Ranking.h"
#pragma endregion TODO

//! Initializes game needs and controls the game loop
namespace GameEngine {
	//! Loads main resources such as game images and fonts
	void LoadMedia(void) {
		R.LoadFont<FontID::ARIAL>("fnt/arial.ttf", 40);
		R.LoadFont<FontID::CANDY>("fnt/candy.ttf", 50);
		R.LoadFont<FontID::FACTORY>("fnt/candsb.ttf", 80);
		
		R.LoadTexture<ObjectID::BG_00>("gfx/bg.png");

		R.LoadTexture<ObjectID::SNAKE_HEAD>("gfx/Snake/Snake_head.png");
		R.LoadTexture<ObjectID::SNAKE_BODY>("gfx/Snake/Snake_body.png");
		R.LoadTexture<ObjectID::SNAKE_TAIL>("gfx/Snake/Snake_tail.png");
		R.LoadTexture<ObjectID::FOOD_APPLE>("gfx/Snake/Food_apple.png");

		R.LoadTexture<ObjectID::CELL_EMPTY>("gfx/empty.png");
		R.LoadTexture<ObjectID::CELL_WALL>("gfx/wall.png");
	}
	//! Adds the game scenes into the Scene Manager and decides which is the first screen
	void AddScenes(void) {
		SM.AddScene<GameMenu>();
		SM.AddScene<GameScene>();
		SM.AddScene<DifSelector>();
		SM.AddScene<GamePlaying>();
		SM.AddScene<Ranking>();
		
		SM.SetCurScene<GameMenu>();
	}
	/** 
	 * Runs the game specifying the window's name and dimensions
	 * @tparam screenWidth Determines the window's width
	 * @tparam screenHeight Determines the window's height
	 * @param name Determines the window's title
	 */
	template<int screenWidth, int screenHeight>
	void Run(std::string &&name) {
		Window::Instance(std::move(name), screenWidth, screenHeight); // Initialize window Singleton instance for the first time
		LoadMedia(); // Loads the resource assets
		AddScenes(); // Loads the scenes
		bool m_isRunning{ true }; // Decides if the game loop is running
		Scene *&m_curScene(SM.GetCurScene()); // Defines a reference to a pointer that points to the current scene pointer (mindblown)
		while (!IM.HasQuit() && m_isRunning) { // Checks while game's still playable
#pragma region GAME_UPDATE
			TM.Update([&] {
				switch (m_curScene->GetState()) { // Check for the state of the screen
				case SceneState::RUNNING:	IM.Update(); m_curScene->Update(); break; // Updates the InputManager and the current scene
				case SceneState::EXIT:	m_isRunning = false; break; // Triggers an end of the game looping
				case SceneState::SLEEP: default:;
				}});
#pragma endregion
#pragma region GAME_DRAW
			if (m_curScene->CheckState<SceneState::RUNNING>()) { // If screen object exists and its state is running
				R.Clear();	// Clear the screen buffer
				m_curScene->Draw(); // Call the draw method of the scene
				R.Render();	// Update the screen buffer with all sprites that were pushed
			}
#pragma endregion
		}
	}
}