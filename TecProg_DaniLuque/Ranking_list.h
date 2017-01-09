#pragma once

#include <map>
#include <iostream>
#include <iostream>
#include <string>
#include <sstream>


class Ranking_list {
	int _score;
	std::string _name;



public:
	Ranking_list();
	~Ranking_list();

	std::map<int, std::string> list_rank;


	//Get and Set methods for getting and setting the attribute values
	int getScore();
	void setScore(int age);
	std::string getName();
	void setName(std::string name);

	//In and output methods
	void printScore();
	void askPersonName();

};