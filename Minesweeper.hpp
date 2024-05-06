#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <random>
#include <iomanip>
#include <ctime>
#include <vector>
#include <string>
#include <sstream>

class game
    {
        private:
            int difficulty = 0;
            int mines = 10;
            std::vector<std::vector<int>> safe_zone ={{0,0}, {0,0}, {0,0},
                                                      {0,0}, {0,0}, {0,0},
                                                      {0,0}, {0,0}, {0,0}}; 
            std::vector<std::vector<int>> mine_coords;
            int size[2] = {9, 9};
            std::vector<std::vector<int>> board;

            void generateSafeZone(std::vector<int> coords) //Generates 3x3 safe zone with no bombs based on first click on board
            {
                safe_zone[0][0] = coords[0] - 1;
                safe_zone[0][1] = coords[1] - 1;
                
                safe_zone[1][0] = coords[0];
                safe_zone[1][1] = coords[1] - 1;

                safe_zone[2][0] = coords[0] + 1;
                safe_zone[2][1] = coords[1] - 1;

                safe_zone[3][0] = coords[0] - 1;
                safe_zone[3][1] = coords[1];

                safe_zone[4] = coords;

                safe_zone[5][0] = coords[0] + 1;
                safe_zone[5][1] = coords[1];

                safe_zone[6][0] = coords[0] - 1;
                safe_zone[6][1] = coords[1] + 1;

                safe_zone[7][0] = coords[0];
                safe_zone[7][1] = coords[1] + 1;

                safe_zone[8][0] = coords[0] + 1;
                safe_zone[8][1] = coords[1] + 1;
                
                for (auto coords : safe_zone)
                {
                    std::cout << "Safe zone: " << coords[0] << " " << coords[1] << std::endl;
                }

            }

            bool checkSafeZone(int x, int y) //Checks for safe zone collisions
            {
                bool collision = false;
                for (auto coords : safe_zone)
                        {
                            if (x == coords[0] && y == coords[1])
                            {
                                collision = true;
                                std::cout << "Collision" << std::endl;
                                return collision;
                                break;
                            }
                        }
                collision = false;
                return collision;
            }

            bool checkCollision(int x, int y) //Checks for mine collisions
            {
                bool collision = false;
                for (int j = 0; j < mine_coords.size(); j++)
                        {
                            if ((x == mine_coords[j][0] && y == mine_coords[j][1]) || checkSafeZone(x, y))
                            {
                                collision = true;
                                return collision;
                                break;
                            }
                        }
                collision = false;
                return collision;
            }

            void initialize()
            {
                srand(time(0));

                for (int i = 0; i < size[1]; i++) //Set all cells to 0
                {
                    for (int j = 0; j < size[0]; j++)
                    {
                        board[j][i] = 0;
                        for (auto coords : safe_zone)
                        {
                            if (j == coords[0] && i == coords[1])
                            {
                                board[j][i] = 6;
                            }

                        }
                    }
                }

                for (int i = 0; i < mines; i++) //Initialize mine_coords to -1 so mines can potentially be placed at 0,0
                {
                    mine_coords[i] = {-1, -1};
                } 

            /*  for (int i = 0; i < mines; i++) //Print mine coords
                {
                    std::cout << "Mine " << i + 1 << ": " << mine_coords[i][0] << ", " << mine_coords[i][1] << std::endl;
                } */

                //printBoard();

                int mines_placed = 0;

                for (int i = 0; i < mines; i++) //Random mine placement
                {   
                    int x = rand() % size[0];
                    int y = rand() % size[1];

                    // Check for collisions
                    while (checkCollision(x, y)) {
                        x = rand() % size[0];
                        y = rand() % size[1];
                    }
                    mine_coords[i][0] = x;
                    mine_coords[i][1] = y;
                    board[x][y] = -1;
                    mines_placed++;
                    std::cout << mines_placed << ") Mine placed at: " << mine_coords[i][0] << ", " << mine_coords[i][1] << std::endl;
                }
            }

        public:


            void spawnMines(int d, std::vector<int> first_click) //Sets board dimensions and initializes cells based on difficulty selection
            {   
                difficulty = d;
                switch (difficulty)
                {
                    case 0:
                        size[0] = 9;
                        size[1] = 9;
                        mines = 10;
                        mine_coords.resize(mines, std::vector<int>(2));
                        board.resize(size[0], std::vector<int>(size[1]));  
                        generateSafeZone(first_click);
                        initialize(); 
                        break;  
                    case 1:
                        size[0] = 16;
                        size[1] = 16;
                        mines = 40;
                        mine_coords.resize(mines, std::vector<int>(2));
                        board.resize(size[0], std::vector<int>(size[1]));
                        generateSafeZone(first_click);
                        initialize();
                        break;
                    case 2:
                        size[0] = 30;
                        size[1] = 16;
                        mines = 99;
                        mine_coords.resize(mines, std::vector<int>(2));
                        board.resize(size[0], std::vector<int>(size[1]));
                        generateSafeZone(first_click);
                        initialize();
                        break;
                }
            }

            void drawBoard(sf::RenderTarget& target) //Draws board in window
            {
                sf::Texture texture;
                if (!texture.loadFromFile("src/res/blank.png")) 
                {
                    // Handle loading error (e.g., print an error message)
                    std::cout << "ERROR" << std::endl;
                }

                sf::Sprite cellSprite(texture);
                cellSprite.setScale(0.2, 0.2);

                for (int i = 0; i < size[1]; i++)
                {
                    for (int j = 0; j < size[0]; j++)
                    {
                        cellSprite.setPosition(j * 20, i * 20);
                        target.draw(cellSprite);
                    }
                }
            }

            void printBoard() //Prints matrix to terminal
            {
                int minecount = 0;
                for (int i = 0; i < size[1]; i++)
                {
                    for (int j = 0; j < size[0]; j++)
                    {
                        std::cout << board[j][i] << " ";
                        if (board[j][i] == -1)
                        {
                            minecount++;
                        }

                    }
                    std::cout << std::endl;
                }
                std::cout << minecount << " mines" << std::endl;

            }

            int getWidth()
            {
                return size[0];
            }
            int getHeight()
            {
                return size[1];
            }
    };

class button
{
    public:
        std::vector<int> coords = {0, 0};
        std::vector<int> size = {200, 100};
        bool pressed = false;
        bool clicked = false;
        std::string textureFile;
        sf::Texture texture;
        sf::Sprite sprite;

        void drawButton(sf::RenderTarget& target)
        {   
            if (!texture.loadFromFile(textureFile))
            {
                std::cout << "ERROR" << std::endl;
            }

            sprite.setTexture(texture);
            sprite.setPosition(coords[0], coords[1]);
            target.draw(sprite);
        }
};

void startMenu(game& G);
void play(game& G);
void endMenu(game& G);