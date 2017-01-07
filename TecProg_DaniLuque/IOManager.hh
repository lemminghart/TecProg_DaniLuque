/******************************************************************
* Copyright (C) 2016 Jordi Serrano Berbel <jsberbel95@gmail.com> *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#pragma once
#include "ID.hh"
#include <fstream>
#include <sstream>
#include <ios>
#include <iterator>
#include "Logger.hh"
#include "Assert.hh"
#include "Resource.hh"
#include "XML/rapidxml.hpp"
#include "XML/rapidxml_utils.hpp"
#include "GameMenu.hh"
#include "Score.h"
#include "Snake.h"

using namespace Logger;

namespace IOManager {

	//swap 2 scores
	static void Swap(Score &a, Score &b) {
		Score t;
		t = a;
		a = b;
		b = t;
	}

	static int CompareScore(int leftValue, int rightValue) {
		if (leftValue < rightValue)
			return 1;
		if (leftValue > rightValue)
			return -1;
		return 0;
	}


	//Function that shows the content of the LEVEL XML file
	static void PrintData(rapidxml::xml_node<> * parent_node) {
		//prints the content of the selected level
		for (rapidxml::xml_node<> *node_I = parent_node->first_node(); node_I; node_I = node_I->next_sibling()) {
			std::cout << node_I->name() << " : " << node_I->value() << "\n";
		}
	}

	static void AssignData(rapidxml::xml_node<> * node, LevelData &levelData) {

		//Rows: 
		levelData.rows = atoi(node->first_node("rows")->value());
		//Columns: 
		levelData.columns = atoi(node->first_node("columns")->value());
		//Time:
		levelData.time = atoi(node->first_node("time")->value());
		//Initial snake speed: 
		levelData.VInit = atoi(node->first_node("VInit")->value());
		//Initial food:
		levelData.NumFoodInit = atoi(node->first_node("NumFoodInit")->value());
		//Food increment:
		levelData.NumFoodIncr = atoi(node->first_node("NumFoodIncr")->value());

		Println(levelData.rows, " : ", levelData.columns, " : ", levelData.time, " : ", levelData.VInit,
			" : ", levelData.NumFoodInit, " : ", levelData.NumFoodIncr);
		std::cout << "Values properly assigned" << std::endl;

	}


	// Function for loading the level data
	static LevelData LoadLevelData(std::string &&filename, GameDifficulty difficulty, LevelData &levelData) {
		rapidxml::file<> xmlFile(RESOURCE_FILE(filename));
		rapidxml::xml_document<> doc;
		doc.parse<0>(xmlFile.data());
		rapidxml::xml_node<> *root_node = doc.first_node("document");
		rapidxml::xml_node<> * node;
		switch (difficulty) {
		case GameDifficulty::EASY:
			node = root_node->first_node("easy");
			PrintData(node);
			AssignData(node, levelData);
			break;
		case GameDifficulty::MEDIUM:
			node = root_node->first_node("medium");
			PrintData(node);
			AssignData(node, levelData);
			break;
		case GameDifficulty::HARD:
			node = root_node->first_node("hard");
			PrintData(node);
			AssignData(node, levelData);
			break;
		}
		return levelData;
	}

	static Score SetScores(int gameDif, int sizeOfList, int score) {
		std::string filename = "cfg/";
		Score s;
		s.askPersonName();
		s.setScore(score);
		int sizeScore = sizeof(Score);
		std::ofstream myInputFile;
		

		switch (gameDif) {
		case EASY:
			std::cout << "ABRIENDO RANKING_EASY" << std::endl;
			filename += "Ranking_EASY.dat";
			break;
		case MEDIUM:
			std::cout << "ABRIENDO RANKING_MEDIUM" << std::endl;
			filename += "Ranking_MEDIUM.dat";
			break;
		case HARD:
			std::cout << "ABRIENDO RANKING_HARD" << std::endl;
			filename += "Ranking_HARD.dat";
			break;
		}

		myInputFile.open(RESOURCE_FILE(filename), std::ios::out | std::ios::binary | std::ios::ate);

		if (!myInputFile.is_open()) {
			throw std::exception("[RankingFile] System was not able to open the file");
		}

		myInputFile.write(reinterpret_cast<char *>(&s), sizeScore);

		//myInputFile.clear();

		myInputFile.close();
		std::cout << "DOC CERRADO" << std::endl;
	}

	static void ReadAndPrintScores(int gameDif, int score) {
		std::string filename = "cfg/";
		std::ifstream myFile;

		std::streampos fileSize;
		Score s;
		s.askPersonName();
		s.setScore(score);
		int sizeScore = sizeof(Score);

		switch (gameDif) {
		case EASY:
			std::cout << "ABRIENDO RANKING_EASY" << std::endl;
			filename += "Ranking_EASY.dat";
			break;
		case MEDIUM:
			std::cout << "ABRIENDO RANKING_MEDIUM" << std::endl;
			filename += "Ranking_MEDIUM.dat";
			break;
		case HARD:
			std::cout << "ABRIENDO RANKING_HARD" << std::endl;
			filename += "Ranking_HARD.dat";
			break;
		}


		//Read the file
		myFile.open(RESOURCE_FILE(filename), std::ios::in | std::ios::binary);
		if (!myFile.is_open()) {
			throw std::exception("[ReadAndPrintScores] System was not able to open the file");
		}

		//-----------------------------
		Score totalScores[11];

		//fullfill the totalScores with empty scores
		for (int i = 0; i < 11; i++) {
			totalScores[i].setName("-");
			totalScores[i].setScore(0);
		}
		for (int i = 0; i < 10; i++) {
			myFile.read(reinterpret_cast<char *>(&totalScores[i]), sizeScore);
			//std::cout << totalScores[i] << std::endl;
		}

		//close the file
		myFile.close();


		//SORTING ALGORITHM
		totalScores[10] = s;

		int top = 10;
		int index;
		int swaps = 1;

		// sort the scores 
		while (top != 0 && swaps != 0) {
			// set the swap variable to 0, because we haven't made any swaps yet.
			swaps = 0;

			// perform one iteration
			for (index = 0; index < top; index++) {
				// swap the indexes if necessary
				if (CompareScore(totalScores[index].getScore(), totalScores[index + 1].getScore()) > 0) {
					Swap(totalScores[index], totalScores[index + 1]);
					swaps++;
				}
			}
			top--;
		}

		//--------------------------------------------------------------
		std::ofstream myInputFile;

		myInputFile.open(RESOURCE_FILE(filename), std::ios::in | std::ios::binary);

		if (!myInputFile.is_open()) {
			throw std::exception("[RankingFile] System was not able to open the file");
		}

		for (int i = 0; i < 10; i++) {
			std::cout << totalScores[i] << std::endl;
			myInputFile.write(reinterpret_cast<char *>(&totalScores[i]), sizeScore);			
		}
		
		myInputFile.close();

		//WTF?
		/*for (int i = 0; i < 10; i++) {
			myFile.read(reinterpret_cast<char *>(&totalScores[i]), sizeScore);
			std::cout << totalScores[i] << std::endl;
		}*/

		////open again the file to save the ranking
		//myFile.open(RESOURCE_FILE(filename), std::ios::in | std::ios::binary);
		//if (!myFile.is_open()) {
		//	throw std::exception("[ReadAndPrintScores] System was not able to open the file");
		//}

		////save the sorted scores
		//for (int i = 0; i < 11; i++) {
		//	myFile.write(reinterpret_cast<char *>(&totalScores[i]), sizeScore);
		//	std::cout << totalScores[i] << std::endl;
		//}

		
	}
}