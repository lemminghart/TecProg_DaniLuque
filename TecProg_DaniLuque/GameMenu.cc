/******************************************************************
* Copyright (C) 2016 Jordi Serrano Berbel <jsberbel95@gmail.com> *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "GameMenu.hh"
#include "Scene_Dif_Selector.h"
#pragma region TODO



using namespace Logger;

#define CELL_WIDTH 80
#define CELL_HEIGHT 80

GameMenu::GameMenu(void) {
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 };
}

GameMenu::~GameMenu(void){
}

void GameMenu::OnEntry(void) {
}

void GameMenu::OnExit(void) {

	Println("LEAVING_main_menu");
	SetState<SceneState::EXIT>();

}

void GameMenu::Update(void) {
	static MouseCoords mouseCoords(0,0);
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
		Println("===============");
		Println("mxp: ", mouseCoords);
		mouseCoords = IM.GetMouseCoords();

	} else if (IM.IsMouseUp<MOUSE_BUTTON_LEFT>()) {
		Println("mxn: ", IM.GetMouseCoords());

		if (mouseCoords.x > 350 && mouseCoords.x < 450 && mouseCoords.y > 340 && mouseCoords.y < 375) {
			Println("PLAY");
			SM.SetCurScene <DifSelector>();
		}
		if (mouseCoords.x > 350 && mouseCoords.x < 450 && mouseCoords.y > 460 && mouseCoords.y < 495) {
			Println("EXIT");
			OnExit();
		}	
	}
	
	// Test InputManager key methods
	if (IM.IsKeyHold<'a'>()) Println("a hold");
	if (IM.IsKeyDown<'0'>()) Println("0 down");
	if (IM.IsKeyUp<KEY_BUTTON_DOWN>()) Println("down arrow up");
	if (IM.IsKeyUp<KEY_BUTTON_ESCAPE>()) {
		Println("GOING BACK");
		GameMenu::OnExit();
	}
}

void GameMenu::Draw(void) {
	m_background.Draw(); 
	
	GUI::DrawTextShaded<FontID::ARIAL>("SNAKE",
										{ W.GetWidth() >> 1, int(W.GetHeight()*.1f), 1, 1 }, 
										{ 0, 255, 0}, { 0, 0, 0 }); 
	GUI::DrawTextBlended<FontID::ARIAL>("PLAY",
										{ W.GetWidth() >> 1, int(W.GetHeight()*.6f), 1, 1 },
										{ 115, 0, 180 });

	/*GUI::DrawTextBlended<FontID::ARIAL>("Easy",
										{ W.GetWidth() >> 1, int(W.GetHeight()*.3f), 1, 1 }, 
										{ 115, 0, 180 }); 
	GUI::DrawTextBlended<FontID::ARIAL>("Medium",
										{ W.GetWidth() >> 1, int(W.GetHeight()*.5f), 1, 1 },
										{ 115, 0, 180 });
	GUI::DrawTextBlended<FontID::ARIAL>("Hard",
										{ W.GetWidth() >> 1, int(W.GetHeight()*.7f), 1, 1 },
										{ 115, 0, 180 });*/

	GUI::DrawTextBlended<FontID::ARIAL>("EXIT",
										{ W.GetWidth() >> 1, int(W.GetHeight()*.8f), 1, 1 },
										{ 255, 0, 0 });
}
