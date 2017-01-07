#include "Score.h"

/*
* Default constructor. It initializes the initial values
*/
Score::Score() {
	_name[0] = '\0';
	_score = 0;
}

/*
* Copy constructor
* @param p is the person object used to initialize the current object
*/
Score::Score(Score & s) {
	strcpy_s(_name, s._name);
	_score = s._score;

}

/*
* Overload constructor
* @param name is the name of the person
* @param age is the age of the person
* @param sex is the sex of the person
*/
Score::Score(std::string name, int score) {
	strcpy_s(_name, name.c_str());
	_score = score;

}

/**
* Destructor. In this case the destructor is useless because we are not allocating memory
*/
Score::~Score() {
}

/*
* Gets the age value
* @return the age of the person
*/
int Score::getScore() {
	return _score;
}

/*
* Sets the new age value
* @param age is the new value of the age
*/
void Score::setScore(int score) {
	_score = score;
}


/*
* Gets the name of the person
* @return the name value
*/
std::string Score::getName() {
	std::string str = std::string(_name);
	return str;
}

/*
* Sets the new name of the person
* @param name is the new value of the name
*/
void Score::setName(std::string name) {
	strcpy_s(_name, name.c_str());
}

/*
* Print the person data
*/
void Score::printScore() {
	std::cout << _name << " - " << _score << " - " << std::endl;
}

/*
* Fill the person's data
*/
void Score::askPersonName() {
	std::cout << "What's your name?";
	std::cin >> _name;
}


/**
* Output operator is overloaded to allow you to use "cout<<p;"
* @param os is the output operator
* @param p is the object (person) that will be used inside the function
*/
std::ostream& operator<<(std::ostream& os, const Score& s) {
	os << "Name:" << s._name << ", Score:" << s._score;
	return os;
}

/**
* Input operator is overloaded to allow you to use "cin>>p;". In this implementation we write inside the question that is asked to the user.
* @param is is the input operator
* @param p is the object (person) that will be used inside the function
*/
std::istream& operator >> (std::istream& is, Score& s) {
	//Ask data to the user
	std::cout << "What's your name?";
	is >> s._name;
	return is;
}


/**
* Output operator is overloaded to allow you to use "ofstream<<p;"
* @param os is the output operator
* @param p is the object (person) that will be used inside the function
*/

std::ofstream& operator<<(std::ofstream& os, const Score& s) {
	os << s._name << " ";
	os << s._score << " ";
	return os;
}

/**
* Input operator is overloaded to allow you to use "ifstream>>p"
* @param is is the input operator
* @param p is the object (person) that will be used inside the function
*/
std::ifstream& operator >> (std::ifstream& is, Score& s) {
	is >> s._name;
	is >> s._score;
	return is;
}