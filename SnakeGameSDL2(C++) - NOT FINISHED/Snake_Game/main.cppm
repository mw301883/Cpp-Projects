import <SDL.h>;
import <iostream>;
import <stdexcept>;
import Interface;

int main(int argc, char* argv[]) {
	try {
		Interface Game;
		Game.Main_Loop();
	}
	catch (std::exception& e) { std::cerr << "\nError during game runtime : " << e.what() << "\n"; }

	return 0;
}