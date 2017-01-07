#pragma once

#include <string>
#include <exception>			//Management of exceptions
#include <iostream>				//Management of cin and cout
#include <stdlib.h>				//Management of random numbers: srand, rand 
#include <cstdlib>				//Management of system functions such as pause
#include <fstream>				//Management of files

/*
* This class represent a person with the following data: age, sex and name
*/
class Score {
	int _score;
	char _name[100];
public:
	//Default constructor
	Score();
	//Overload constructor
	Score(Score & p);
	//Copy constructor
	Score(std::string name, int score);
	//Destructor
	~Score();

	//Get and Set methods for getting and setting the attribute values
	int getScore();
	void setScore(int age);
	std::string getName();
	void setName(std::string name);

	//In and output methods
	void printScore();
	void askPersonName();



	//Output and input operators are overloaded to allow you to use cin and cout directly with a Person object
	//Friend is an special keyword that lets the function to access the attributes of an object even they are private.
	friend std::ostream& operator<<(std::ostream& os, const Score& p);
	friend std::istream& operator >> (std::istream& is, Score& p);

	//File Output and input operators are overloaded to allow you to use cin and cout directly with a Person object
	//Friend is an special keyword that lets the function to access the attributes of an object even they are private.
	friend std::ofstream& operator<<(std::ofstream& os, const Score& p);
	friend std::ifstream& operator >> (std::ifstream& is, Score& p);

	//Update the age of the person based on the new age information. If the age is less than 0, an exception is raised
	void updateAge(int increment);
};