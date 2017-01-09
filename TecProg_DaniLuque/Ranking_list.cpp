#include "Ranking_list.h"

using namespace std;

Ranking_list::Ranking_list() {
	for (int i = 0; i < 10; i++) {
		list_rank[i] = { " - " };
	}
	//list_rank[0] = { "lol" };
	//list_rank[1] = { " ert" };
	//list_rank[4] = { "k " };
	//list_rank[5] = { "yh " };
	//list_rank[3] = { "f " };
	//list_rank[5] = { "sdfg " };
	//list_rank[7] = { "gsdf " };
	//list_rank[865] = { "gf " };
	//list_rank[68] = { "vb " };
	//list_rank[556] = { " cvb" };
}

Ranking_list::~Ranking_list() {

}

void Ranking_list::askPersonName(void) {
	cout << "What's your name?";
	getline(cin, _name);
}


std::string Ranking_list::getName() {
	return _name;
}