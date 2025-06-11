#ifndef BUTTON_H
#define BUTTON_H
#include "Minesweeper.h"

class button
{
    private:

    public:
        std::vector<int> coords = {0, 0};
        std::vector<int> size = {100, 50};
        bool pressed = false;
        bool clicked = false;
        bool inside = false;
        std::string textureFile = "";
        std::string names[5] = {"easy", "medium", "hard", "restart", "exit"};
        int diff = 0;
        std::string name;
        sf::Texture texture;
        sf::Sprite sprite;

        void drawButton(sf::RenderWindow& target) //Draws button in window
        {   
            if (!texture.loadFromFile(getResourcePath(textureFile))) // Load texture from file
            {
                //std::cout << "ERROR" << std::endl;
            }

            sprite.setTexture(texture);
            sprite.setScale(0.5, 0.5);
            sprite.setPosition(coords[0], coords[1]);
            target.draw(sprite);
        }

        bool checkClick(sf::RenderWindow& target)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(target);

                while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
                {
                    if (mousePos.x > coords[0] && mousePos.x < coords[0] + size[0] && mousePos.y > coords[1] &&  mousePos.y < coords[1] + size[1])
                    {
                        pressed = true;
                        inside = true;
                        textureFile = "";

                        if (name != names[diff] + " pressed.png") 
                        {
                            name += " pressed.png";
                        }
                        textureFile += name;
                        drawButton(target);
                    }
                    

                    if (mousePos.x < coords[0] || mousePos.x > coords[0] + size[0] ||
                        mousePos.y < coords[1] || mousePos.y > coords[1] + size[1] && pressed == true)
                    {
                        inside = false;
                    }
                    
                    return false; 
                } 

                if (pressed)
                {   
                    
                    textureFile = "";
                    name = names[diff];
                    textureFile += name + ".png";
                    drawButton(target);
                    pressed = false;

                    if (inside)
                    {
                        clicked = true;
                    }
                }
                
                if (clicked) 
                {
                    clicked = false;                
                    return true; 
                }

            return false; // Not pressed or not within bounds
        }
};


#endif