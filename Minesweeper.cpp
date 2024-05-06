#include "Minesweeper.hpp"

    bool over = false;

    game G;

int main() 
{
    startMenu(G);
    play(G);
    endMenu(G);
    
    G.printBoard();
/*
    while (!over)
    {
        
    }
*/
    return 0;       
}