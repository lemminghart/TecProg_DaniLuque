/******************************************************************
* Copyright (C) 2016 Jordi Serrano Berbel <jsberbel95@gmail.com> *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#pragma once
#include "ID.hh"
#include <fstream>
#include <sstream>
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

	// Base test function for XML purposes (TODO)
	/*static void LoadLevel(std::string &&filename) {
		rapidxml::file<> xmlFile(RESOURCE_FILE(filename));
		rapidxml::xml_document<> doc;
		doc.parse<0>(xmlFile.data());
		rapidxml::xml_node<> *root_node = doc.first_node("document");
		for (rapidxml::xml_node<> * node = root_node->first_node("node"); node; node = node->next_sibling()) {
			Println("Node: ", 
				  node->first_attribute("att1")->value(),
				  " - ",
				  node->first_attribute("att2")->value());
		}
	}*/

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
	

	static void SetScores(std::string &&filename, int sizeOfList) {
		Score s;
		int sizeScore = sizeof(Score);
		std::ofstream myOutputFile;

		myOutputFile.open(RESOURCE_FILE(filename), std::ios::out | std::ios::trunc | std::ios::binary);

		if (!myOutputFile.is_open()) {
			throw std::exception("[CreateAPopulationFile] System was not able to open the file");
		}
		for (int id = 0; id < sizeOfList; id++) {
			myOutputFile.write((char *)(&s), sizeScore);
		}
		myOutputFile.close();
	}

	static void ReadAndPrintScores(std::string &&filename) {
		std::ifstream myInputFile;
		std::streampos fileSize;
		Score s;
		int sizeScore = sizeof(Score);

		//Read the file
		myInputFile.open(RESOURCE_FILE(filename), std::ios::in | std::ios::binary);
		if (!myInputFile.is_open()) {
			throw std::exception("[ReadAndPrintScores] System was not able to open the file");
		}

		//Compute the filesize
		myInputFile.seekg(0, std::ios::end);
		fileSize = myInputFile.tellg();
		myInputFile.seekg(0, std::ios::beg);

		//Read the content
		int numElements = fileSize / sizeScore;
		for (int i = 0; i < numElements; i++) {
			myInputFile.read((char *)(&s), sizeScore);
			std::cout << s << std::endl;

		}
		myInputFile.close();
	}

		//rows="50" columns="50" time="400" VInit="1" NumFoodInit="5" NumFoodIncr="1"


	//TestXML("level_1.xml");
	/*
	<impresora peso="50" type="blanc.negro">
		<tinta>rj3847</tinta>
	</impresora>

	array=(a="z", b="x");
	*/

	//// Loader function that takes level info for a grid
	//static std::vector<std::vector<ObjectID>> LoadLevel(std::string &&filename, int &rows, int &cols) {
	//	std::ifstream fileData(RESOURCE_FILE(filename));
	//	ASSERT(fileData.good());
	//	std::vector<std::vector<ObjectID>> lvlData;
	//	std::string line;
	//	while (std::getline(fileData, line)) {
	//		std::istringstream strData(std::move(line));
	//		lvlData.emplace_back(std::istream_iterator<ObjectID>(std::move(strData)), std::istream_iterator<ObjectID>());
	//	}
	//	rows = int(lvlData.size()); cols = int(lvlData[0].size());
	//	fileData.close();
	//	#pragma region DEBUG_DATA
	//		Println("Level: ", filename);
	//		for (auto &r : lvlData) {
	//			for (auto &c : r) Print(c, ' ');
	//			Endln();
	//		}
	//	#pragma endregion
	//	return std::move(lvlData);
	//}

}