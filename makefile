all:
	g++ Minesweeper.cpp Minesweeper_functions.cpp -o Minesweeper -I src/include -L src/lib -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -std=c++17 