
#include <iostream>
#include "game.h"

bool  game_on = true;

void get_response()
{
    std::cout << "Game is over. \nYou want to restart? (Y/N)" << "  type 'y' or 'n' and press ENTER"<< std::endl;
    std::string response;
    std::cin >> response;

    if (response == "y" || response == "Y")
        start_game();
    else if (response == "n" || response == "N")
    {
        std::cout << "OK, goodbye" << std::endl;
        game_on = false;
    }
    else
    {
        std::cout << "unknown choise , try again" << std::endl;
        get_response();
    }
}

int main()
{
  


        
        start_game(); 
    
      
        
        while (game_on)
        {
            get_response();
        }

    return 0;
}