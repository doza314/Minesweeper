#include "Minesweeper.hpp"

void startMenu(game& G) //Title screen and difficulty prompt
{
    sf::RenderWindow window(sf::VideoMode(600,400), "MINESWEEPER");

    button easy;
    easy.coords = { 20, 20 };
    easy.textureFile = "src/res/easy.png";

    button medium;
    medium.coords = { 20, 150 };
    medium.textureFile = "src/res/medium.png";

    button hard;
    hard.coords = { 20, 280 };
    hard.textureFile = "src/res/hard.png";

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        easy.drawButton(window);
        medium.drawButton(window);
        hard.drawButton(window);

        window.display();
    }
}

void play(game& G)
{
    G.spawnMines(2, {11,11});
    sf::RenderWindow window(sf::VideoMode(G.getWidth() * 20, G.getHeight() * 20), "MINESWEEPER");
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        G.drawBoard(window);
        window.display();
    }
}

void endMenu(game& G)
{

}

