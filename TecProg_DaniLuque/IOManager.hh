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
#include <map>
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
		levelData.VInit = atof(node->first_node("VInit")->value());
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

	
	//checks if file exists
	static bool FileExists(const std::string& filename)
	{
		struct stat buf;
		if (stat(filename.c_str(), &buf) != -1)
		{
			return true;
		}
		return false;
	}

	//manages the ranking (loading/saving & sorting)
	static void ManageRanking(int gameDif, int score) {
		
		std::string filename = "cfg/";
		
		typedef struct { int puntuacion; char nombre[10]; } Data;
		
		Data read_ranking_list[11];

		bool create;
		
		score = 5500;

		//ESCOGEMOS EL ARCHIVO QUE QUEREMOS ABRIR (SEGUN DIFICULTAD)
		//SI NO EXISTE LO INICIALIZAMOS CON SCORE: 0 NAME: " - "
		switch (gameDif) {
		case EASY:
			filename += "Ranking_EASY.bin";
			if (FileExists(RESOURCE_FILE(filename))) {
				std::cout << "ABRIENDO Ranking_EASY" << std::endl;
				create = false;
			}
			else {
				create = true;
			}
			break;
		case MEDIUM:
			filename += "Ranking_MEDIUM.bin";
			if (FileExists(RESOURCE_FILE(filename))) {
				std::cout << "ABRIENDO Ranking_MEDIUM" << std::endl;
				create = false;
			}
			else {
				create = true;
			}
			break;
		case HARD:
			filename += "Ranking_HARD.bin";
			if (FileExists(RESOURCE_FILE(filename))) {
				std::cout << "ABRIENDO RANKING_HARD" << std::endl;
				create = false;
			}
			else {
				create = true;
			}
			break;
		}

		//si el archivo no existe, creamos uno vacio
		if (create) {
			Data ranking_list[11];
			string tmp = " - ";

			cout << "----------------------------CREANDO NUEVO FICHERO-----------------------------" << endl;

			for (int i = 0; i < 11; i++) {
				strcpy(ranking_list[i].nombre, tmp.c_str());
				ranking_list[i].puntuacion = 0;
			}

			ofstream createFile(RESOURCE_FILE(filename), std::ios::out | std::ios::binary);

			if (!createFile.is_open()) {
				throw std::exception("[RankingFile] System was not able to open the file");
			}

			createFile.write(reinterpret_cast<char *>(&ranking_list), sizeof(ranking_list));

			createFile.close();
		}
		
		//leemos el archivo
		ifstream myInputFile(RESOURCE_FILE(filename), std::ios::in | std::ios::binary);

		myInputFile.read(reinterpret_cast<char *>(&read_ranking_list), sizeof(read_ranking_list));

		myInputFile.close();

		cout << "--------------------------------------------------------------------" << endl;

		for (int i = 0; i < 10; i++) {
			cout << "Nombre: " << read_ranking_list[i].nombre << endl;
			cout << "Score: " << read_ranking_list[i].puntuacion << endl;
		}

		//añadimos la score y nombre del jugador
		//Como está ordenado el ranking, substituimos la nueva score por la numero 11
		//esta score numero 11 siempre estará ahi, pero no se mostrará nunca

		cout << "Insert your name: (MAX 10 CHARACTERS!)";
		
		std::string name;
		getline(cin, name);

		//insertamos nombre
		strcpy(read_ranking_list[10].nombre, name.c_str());
		//insertamos score
		read_ranking_list[10].puntuacion = score;

		//ORDENAMOS EL ARRAY DE MAYOR A MENOR

		Data temp;
		for (int i = 0; i < 11 - 1; i++) {
			for (int j = i + 1; j < 11; j++) {
				if (read_ranking_list[i].puntuacion < read_ranking_list[j].puntuacion) {
					temp = read_ranking_list[i];
					read_ranking_list[i] = read_ranking_list[j];
					read_ranking_list[j] = temp;
				}
			}
		}
		
		
		cout << "--------------------------------------------------------------------" << endl;

		for (int i = 0; i < 10; i++) {
			cout << "Nombre: " << read_ranking_list[i].nombre << endl;
			cout << "Score: " << read_ranking_list[i].puntuacion << endl;
		}

		//GUARDAMOS EL ARRAY

		ofstream saveFile(RESOURCE_FILE(filename), std::ios::out | std::ios::binary);

		if (!saveFile.is_open()) {
			throw std::exception("[RankingFile] System was not able to open the file");
		}

		saveFile.write(reinterpret_cast<char *>(&read_ranking_list), sizeof(read_ranking_list));

		saveFile.close();
		

//		LEEMOS EL CONTENIDO DEL ARCHIVO


		//ifstream myInputFile(RESOURCE_FILE(filename), std::ios::in | std::ios::binary);


		/*for (auto it = --(list_rank.end()); it != --(list_rank.begin()); it--) {
			std::cout << "Score: " << it->first << " Name: " << it->second << std::endl;
		}*/

		//list_rank.clear();

		//myInputFile.read(reinterpret_cast<char *>(&list_rank), sizeof(list_rank.size()));

		//myInputFile.close();
	
		//std::cout << "-----------------------RANKING-----------------------" << std::endl;
		//
		//for (auto it = --(list_rank.end()); it != --(list_rank.begin()); it--) {
		//	std::cout << "Score: " << it->first << " Name: " << it->second << std::endl;
		//}
		//
		////__________________________________________

		//cout << "What's your name?";
		//
		//std::string name;
		//getline(cin, name);

		//list_rank.insert(std::pair<int, std::string>(score, { name }));

		//

		////borramos el primer elemento ya que se almacenan en orden descendente
		//
		//for (auto it = --(list_rank.end()); it != --(list_rank.begin()); it--) {
		//	std::cout << "Score: " << (*it).>first << " Name: " << (*it).second << std::endl;
		//}
		////PrintRanking(prueba);
	
		//system("pause");
		//cout << "HOLAAAAAAA -------------->" << list_rank.begin()->first << endl;
	
	
		////std::multimap<int, string>::iterator it = prueba.list_rank.begin();
		//
		////auto it = prueba.list_rank.begin();

		////Make a copy of the current iterator, then increment the real one.
		//
		////_mEntity.erase(tmp);

		////minheap.erase(std::prev(minheap.end()));
		//list_rank.erase(list_rank.begin());

		//

		////PRINTEAMOS SU CONTENIDO

		//std::cout << "-----------------------RANKING CAMBIADO-----------------------" << std::endl;

		//for (auto it = --(list_rank.end()); it != --(list_rank.begin()); it--) {
		//	std::cout << "Score: " << it->first << " Name: " << it->second << std::endl;
		//}

		//ofstream myOutputFile2(RESOURCE_FILE(filename), std::ios::out | std::ios::binary);

		//if (!myOutputFile2.is_open()) {
		//	throw std::exception("[RankingFile] System was not able to open the file");
		//}

		//myOutputFile2.write(reinterpret_cast<char *>(&list_rank), sizeof(std::multimap<int, std::string>));

		//std::cout << "-----------------------RANKING CAMBIADO 2-----------------------" << std::endl;

		//for (auto it = --(list_rank.end()); it != --(list_rank.begin()); it--) {
		//	std::cout << "Score: " << it->first << " Name: " << it->second << std::endl;
		//}

		//myOutputFile2.close();

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
	}
}