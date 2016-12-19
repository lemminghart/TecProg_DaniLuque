#include "GameEngine.hh"


//#define WIDTH 400
//#define HEIGHT 650

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char* args[]) {
	GameEngine::Run<WIDTH, HEIGHT>("SNAKE");
	return 0;
}