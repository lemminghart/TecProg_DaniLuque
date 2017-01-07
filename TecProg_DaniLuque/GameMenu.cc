/******************************************************************
* Copyright (C) 2016 Jordi Serrano Berbel <jsberbel95@gmail.com> *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "GameMenu.hh"
#include "Scene_Playing.h"
#pragma region TODO



using namespace Logger;

#define CELL_WIDTH 80
#define CELL_HEIGHT 80

GameMenu::GameMenu(void) {
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 };
	*gameDifficulty = DF;
}

GameMenu::~GameMenu(void){
}

void GameMenu::OnEntry(void) {
	selector = false;
}

void GameMenu::OnExit(void) {

	Println("LEAVING_main_menu");
	SetState<SceneState::EXIT>();

}

void GameMenu::Update(void) {
	static MouseCoords mouseCoords(0,0);
	/*if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
		Println("===============");
		Println("mxp: ", mouseCoords);
		mouseCoords = IM.GetMouseCoords();

	}*/
	if (!selector) {
		if (IM.IsMouseUp<MOUSE_BUTTON_LEFT>()) {
			Println("mxn: ", IM.GetMouseCoords());

			if (mouseCoords.x > 350 && mouseCoords.x < 450 && mouseCoords.y > 340 && mouseCoords.y < 375) {
				Println("PLAY");
				selector = true;
			}
			if (mouseCoords.x > 350 && mouseCoords.x < 450 && mouseCoords.y > 460 && mouseCoords.y < 495) {
				Println("EXIT");
				OnExit();
			}
		}

		if (IM.IsKeyUp<KEY_BUTTON_ESCAPE>()) {
			Println("GOING BACK");
			GameMenu::OnExit();
		}
	}
	else {
		/////
		if (IM.IsMouseUp<MOUSE_BUTTON_LEFT>()) {
			Println("mxn: ", IM.GetMouseCoords());

			if (mouseCoords.x > 347 && mouseCoords.x < 455 && mouseCoords.y > 100 && mouseCoords.y < 135) {
				Println("EASY");
				*gameDifficulty = EASY;
				SM.SetCurScene <GamePlaying>();

			}
			if (mouseCoords.x > 320 && mouseCoords.x < 480 && mouseCoords.y > 222 && mouseCoords.y < 254) {
				Println("MEDIUM");
				*gameDifficulty = MEDIUM;
				SM.SetCurScene <GamePlaying>();

			}
			if (mouseCoords.x > 343 && mouseCoords.x < 460 && mouseCoords.y > 340 && mouseCoords.y < 374) {
				Println("HARD");
				*gameDifficulty = HARD;
				SM.SetCurScene <GamePlaying>();

			}
			if (mouseCoords.x > 345 && mouseCoords.x < 460 && mouseCoords.y > 462 && mouseCoords.y < 495) {
				Println("BACK");
				selector = false;
				//GO BACK TO MAIN MENU
			}
		}
	}



}

void GameMenu::Draw(void) {
	m_background.Draw(); 
	
	if (!selector) {
		GUI::DrawTextShaded<FontID::ARIAL>("SNAKE",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.1f), 1, 1 },
		{ 0, 255, 0 }, { 0, 0, 0 });
		GUI::DrawTextBlended<FontID::ARIAL>("PLAY",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.6f), 1, 1 },
		{ 115, 0, 180 });
		GUI::DrawTextBlended<FontID::ARIAL>("EXIT",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.8f), 1, 1 },
		{ 255, 0, 0 });
	}
	else {
		GUI::DrawTextBlended<FontID::ARIAL>("EASY",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.2f), 1, 1 },
		{ 115, 0, 180 });
		GUI::DrawTextBlended<FontID::ARIAL>("MEDIUM",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.4f), 1, 1 },
		{ 115, 0, 180 });
		GUI::DrawTextBlended<FontID::ARIAL>("HARD",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.6f), 1, 1 },
		{ 115, 0, 180 });

		GUI::DrawTextBlended<FontID::ARIAL>("BACK",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.8f), 1, 1 },
		{ 255, 0, 0 });
	}
}



/*GUI::DrawTextBlended<FontID::ARIAL>("Easy",
{ W.GetWidth() >> 1, int(W.GetHeight()*.3f), 1, 1 },
{ 115, 0, 180 });
GUI::DrawTextBlended<FontID::ARIAL>("Medium",
{ W.GetWidth() >> 1, int(W.GetHeight()*.5f), 1, 1 },
{ 115, 0, 180 });
GUI::DrawTextBlended<FontID::ARIAL>("Hard",
{ W.GetWidth() >> 1, int(W.GetHeight()*.7f), 1, 1 },
{ 115, 0, 180 });*/