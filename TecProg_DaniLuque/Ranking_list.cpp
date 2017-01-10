#include "Ranking_list.h"

using namespace std;

Ranking_list::Ranking_list() {

}


Ranking_list::Ranking_list(bool u) {
	if (u) {
		for (int i = 0; i < 10; i++) {
			list_rank.insert(std::pair<int, std::string>(0, " - "));
		}
	}
	else {
		list_rank.insert(std::pair<int, std::string>(1, " qwert "));
		list_rank.insert(std::pair<int, std::string>(2, " asdf "));
		list_rank.insert(std::pair<int, std::string>(54, " zxcv "));
		list_rank.insert(std::pair<int, std::string>(32, " rtyu "));
		list_rank.insert(std::pair<int, std::string>(5, " fghj "));
		list_rank.insert(std::pair<int, std::string>(324, " cvbn "));
		list_rank.insert(std::pair<int, std::string>(53, " yuio "));
		list_rank.insert(std::pair<int, std::string>(6, " hjkl "));
		list_rank.insert(std::pair<int, std::string>(10, " qawsed "));
	}
}

Ranking_list::~Ranking_list() {

}

void Ranking_list::askPersonName(void) {
	cout << "What's your name?";
	getline(cin, _name);
}

void Ranking_list::deletePair(int index) {
	list_rank.erase(index);
}

std::string Ranking_list::getName() {
	return _name;
}