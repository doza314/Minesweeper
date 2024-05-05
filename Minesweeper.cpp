#include "Minesweeper.hpp"

    bool over = false;

    game G;

int main() 
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    G.spawnMines(2, {11,11});
    G.printBoard();

    while (!over)
    {
        
    }
    
    return 0;       
}