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
#include "Ranking_list.h"
#include "Score.h"
#include "Snake.h"

using namespace Logger;
using namespace std;

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

	static void ReadRanking(Ranking_list &rank) {
		std::string filename = "cfg/";
		std::ifstream myInputFile;

		myInputFile.open(RESOURCE_FILE(filename), std::ios::in);
		//myInputFile.open(RESOURCE_FILE(filename), std::ios::in | std::ios::binary);

		if (!myInputFile.is_open()) {
			throw std::exception("[RankingFile] System was not able to open the file");
		}

		myInputFile.read(reinterpret_cast<char *>(&rank.list_rank), sizeof(rank.list_rank));

		myInputFile.close();
	}

	static void PrintRanking(Ranking_list &rank) {
		
		std::cout << "-----------------------RANKING-----------------------" << std::endl;

		for (auto it = rank.list_rank.rbegin(); it != rank.list_rank.rend(); ++it) {
			std::cout << "Score: " << it->first << " Name: " << it->second << std::endl;
		}
		
	}

	static void WriteRanking(Ranking_list &rank) {
		std::string filename = "cfg/";
		std::ofstream myOutputFile;

		myOutputFile.open(RESOURCE_FILE(filename), std::ios::out);
		//myOutputFile.open(RESOURCE_FILE(filename), std::ios::out | std::ios::binary);
		
		if (!myOutputFile.is_open()) {
			throw std::exception("[RankingFile] System was not able to open the file");
		}

		myOutputFile.write(reinterpret_cast<char *>(&rank.list_rank), sizeof(rank.list_rank));

		myOutputFile.close();

	}

	static bool FileExists(const std::string& filename)
	{
		struct stat buf;
		if (stat(filename.c_str(), &buf) != -1)
		{
			return true;
		}
		return false;
	}

	static void ManageRanking(int gameDif, int score) {
		std::string filename = "cfg/";
		Ranking_list rank(false); //lista rara
		Ranking_list blank_rank(true); //lista vacia 0 & " - "
		Ranking_list prueba;



		bool create;
		//rank.askPersonName();

		score = 4300;

		//ESCOGEMOS EL ARCHIVO QUE QUEREMOS ABRIR (SEGUN DIFICULTAD)
		//SI NO EXISTE LO INICIALIZAMOS CON SCORE: 0 NAME: " - "
		switch (gameDif) {
		case EASY:
			filename += "Ranking_EASY.dat";
			if (FileExists(RESOURCE_FILE(filename))) {
				std::cout << "ABRIENDO Ranking_EASY" << std::endl;
			}
			else {
				create = true;
			}
			break;
		case MEDIUM:
			filename += "Ranking_MEDIUM.dat";
			if (FileExists(RESOURCE_FILE(filename))) {
				std::cout << "ABRIENDO Ranking_MEDIUM" << std::endl;
			}
			else {
				create = true;
			}
			break;
		case HARD:
			filename += "Ranking_HARD.dat";
			if (FileExists(RESOURCE_FILE(filename))) {
				std::cout << "ABRIENDO RANKING_HARD" << std::endl;
			}
			else {
				create = true;
			}
			break;
		}

		//si el archivo no existe, creamos uno vacio
		if (create = true) {
			/*cout << "trampa!" << endl;
			system("pause");*/
			ofstream createFile(RESOURCE_FILE(filename), std::ios::out | std::ios::binary);

			if (!createFile.is_open()) {
				throw std::exception("[RankingFile] System was not able to open the file");
			}

			createFile.write(reinterpret_cast<char *>(&rank.list_rank), sizeof(rank.list_rank));

			createFile.close();
		}
		
		
//		LEEMOS EL CONTENIDO DEL ARCHIVO


		ifstream myInputFile(RESOURCE_FILE(filename), std::ios::in | std::ios::binary);

		if (!myInputFile.is_open()) {
			throw std::exception("[RankingFile] System was not able to open the file");
		}

		if (myInputFile.good()) {
			cout << "all good" << endl;
		}
		else {
			cout << "no va" << endl;
			if (myInputFile.fail()) cout << "bit fail activo" << endl;
			if (myInputFile.eof()) cout << "bit eof activo" << endl;
			if (myInputFile.bad()) cout << "bit bad activo" << endl;
		}

		myInputFile.read(reinterpret_cast<char *>(&prueba.list_rank), sizeof(blank_rank.list_rank));

		myInputFile.close();
	
		std::cout << "-----------------------RANKING-----------------------" << std::endl;

		for (auto it = prueba.list_rank.rbegin(); it != prueba.list_rank.rend(); ++it) {
			std::cout << "Score: " << it->first << " Name: " << it->second << std::endl;
		}
		
		//__________________________________________

		blank_rank.askPersonName();

		prueba.list_rank.insert(std::pair<int, std::string>(score, { blank_rank.getName() }));

		//borramos el primer elemento ya que se almacenan en orden descendente
		
		for (auto it = prueba.list_rank.rbegin(); it != prueba.list_rank.rend(); ++it) {
			std::cout << "Score: " << it->first << " Name: " << it->second << std::endl;
		}

	
		system("pause");
		cout << "HOLAAAAAAA -------------->" << prueba.list_rank.begin()->first << endl;
	

		prueba.list_rank.erase(666);

		//PRINTEAMOS SU CONTENIDO

		std::cout << "-----------------------RANKING-----------------------" << std::endl;

		for (auto it = prueba.list_rank.rbegin(); it != prueba.list_rank.rend(); ++it) {
			std::cout << "Score: " << it->first << " Name: " << it->second << std::endl;
		}

		ofstream myOutputFile2(RESOURCE_FILE(filename), std::ios::out | std::ios::binary);

		if (!myOutputFile2.is_open()) {
			throw std::exception("[RankingFile] System was not able to open the file");
		}

		myOutputFile2.write(reinterpret_cast<char *>(&prueba.list_rank), sizeof(prueba.list_rank));

		myOutputFile2.close();

		////LEER DE NUEVO
		//myInputFile.open(RESOURCE_FILE(filename), std::ios::in | std::ios::binary);

		//if (!myInputFile.is_open()) {
		//	throw std::exception("[RankingFile] System was not able to open the file");
		//}

		//if (myInputFile.good()) {
		//	cout << "all good" << endl;
		//}
		//else {
		//	cout << "no va" << endl;
		//	if (myInputFile.fail()) cout << "bit fail activo" << endl;
		//	if (myInputFile.eof()) cout << "bit eof activo" << endl;
		//	if (myInputFile.bad()) cout << "bit bad activo" << endl;
		//}

		//myInputFile.read(reinterpret_cast<char *>(&prueba.list_rank), sizeof(blank_rank.list_rank));

		//myInputFile.close();

		//std::cout << "-----------------------RANKING2-----------------------" << std::endl;

		//for (auto it = prueba.list_rank.rbegin(); it != prueba.list_rank.rend(); ++it) {
		//	std::cout << "Score: " << it->first << " Name: " << it->second << std::endl;
		//}


		//------------------------------------------------------------



		/*myOutputFile.open(RESOURCE_FILE(filename), std::ios::out | std::ios::binary);

		myOutputFile.write(reinterpret_cast<char *>(&rank.list_rank), sizeof(rank.list_rank));

		myOutputFile.close();

		myInputFile.open(RESOURCE_FILE(filename), std::ios::in | std::ios::binary);

		if (!myInputFile.is_open()) {
			throw std::exception("[RankingFile] System was not able to open the file");
		}

		myInputFile.read(reinterpret_cast<char *>(&rank2.list_rank), sizeof(rank2.list_rank));

		myInputFile.close();

		for (auto it = rank2.list_rank.rbegin(); it != rank2.list_rank.rend(); ++it) {
			std::cout << "Score: " << it->first << " Name: " << it->second << std::endl;
		}

		std::cout << "---------------------------------------------------------" << std::endl;*/

		//rank.list_rank.insert(std::pair<int, std::string>(score, { rank.getName() }));

		////borramos el primer elemento ya que se almacenan en orden descendente
		//rank.list_rank.erase(rank.list_rank.begin()->first);

		////printamos los elementos en orden ascendente
		//for (auto it = rank.list_rank.rbegin(); it != rank.list_rank.rend(); ++it) {
		//	std::cout << "Score: " << it->first << " Name: " << it->second << std::endl;
		//}
		//
		//myOutputFile.open(RESOURCE_FILE(filename), std::ios::out | std::ios::binary);

		//myOutputFile.write(reinterpret_cast<char *>(&rank.list_rank), sizeof(rank.list_rank));

		//myOutputFile.close();

		////---

		//myInputFile.open(RESOURCE_FILE(filename), std::ios::in | std::ios::binary | std::ios::ate);

		//if (!myInputFile.is_open()) {
		//	throw std::exception("[RankingFile] System was not able to open the file");
		//}

		//myInputFile.read(reinterpret_cast<char *>(&rank2.list_rank), sizeof(rank2.list_rank));

		//myInputFile.close();

		//for (auto it = rank2.list_rank.rbegin(); it != rank2.list_rank.rend(); ++it) {
		//	std::cout << "Score: " << it->first << " Name: " << it->second << std::endl;
		//}

		system("pause");

	}
}