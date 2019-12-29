#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include<cstdlib>
#include "Bullet.h"
#include "Asteroid.h"
#include "Asteroid.h"
#include<cctype>





void start_game()
{


    srand(time(NULL));



    //Some variables

     //Screen size
    int width = 1200.f;
    int height = 800.f;

    //Buttons
    bool wButton = false;
    bool sButton = false;
    bool aButton = false;
    bool dButton = false;
    bool leftButton = false;
    bool rightButton = false;
    bool upButton = false;
    bool downButton = false;

    const float PI = 3.14159265;

    //Spaceship
    int shipRotation = 0;
    float xVelocity = 0.f;
    float yVelocity = 0.f;

    sf::Vector2f aim_dir;  // Direction of projectile
    sf::Vector2f asteroid_dir; // Direction of asteroid (towards player)
    sf::Vector2f small_roid_dir; // Direction of small asteroid (towards player)

    //Create window
    sf::RenderWindow window(sf::VideoMode(width, height), "Asteroids", sf::Style::Titlebar | sf::Style::Close);

    //Set FPS
    window.setFramerateLimit(60);

    //Change cursor
    sf::Cursor cursor;
    if (cursor.loadFromSystem(sf::Cursor::Cross))
        window.setMouseCursor(cursor);

    //Loading background
    sf::Vector2u TextureSize;  //Added to store texture size.
    sf::Vector2u WindowSize;   //Added to store window size.

    sf::Texture bg_texture;
    if (!bg_texture.loadFromFile("Data/bg_space.png"))
    {
        std::cout << "Error openig file" << std::endl;
    }

    TextureSize = bg_texture.getSize(); //Get size of texture.
    WindowSize = window.getSize();             //Get size of window.

    float ScaleX = (float)WindowSize.x / TextureSize.x;
    float ScaleY = (float)WindowSize.y / TextureSize.y;     //Calculate scale.

    sf::Sprite background(bg_texture);

    background.setTexture(bg_texture);
    background.setScale(ScaleX, ScaleY);      //Set scale. 




    std::cout << "Game Started" << std::endl;



    //Figures


        //Spaceship load

    sf::Texture SpaceShip_texture;

    if (SpaceShip_texture.loadFromFile("Data/spaceship.png") == false)
    {
        std::cout << "Failed to load file" << std::endl;
    }

    SpaceShip_texture.setSmooth(true);

    sf::Sprite SpaceShip;
    SpaceShip.setTexture(SpaceShip_texture);
    SpaceShip.setScale(0.2f, 0.2f);
    SpaceShip.setOrigin(170, 220);
    SpaceShip.setPosition(width / 2, height / 2);

    //Projectile

    Bullet projectile;
    std::vector <Bullet> projectiles;

    //Asteroid
   
    Asteroid asteroid;
    std::vector <Asteroid> asteroids;

    Asteroid small_roid;
    small_roid.asteroid_shape.setOrigin(9.f, 9.f);
    std::vector <Asteroid> small_roids;



    small_roid.asteroid_shape.setScale(sf::Vector2f(0.2f, 0.2f));

    sf::Texture asteroid_image;
    if (!asteroid_image.loadFromFile("Data/asteroid_image.png"))
    {
        std::cout << "Error opening file" << std::endl;
    }

   asteroid_image.setSmooth(true);

    asteroid.asteroid_shape.setTexture(asteroid_image);
    
    small_roid.asteroid_shape.setTexture(asteroid_image);


    //Music

    sf::Music music;

    if (!music.openFromFile("Data/music.wav"))
    {
        std::cout << "Error opening file" << std::endl;
    }

    music.setVolume(20.f);

    music.setLoop(true);
    music.play();



    //Game loop

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

        }




        //Events for buttons


          //Movement
        //Up move
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            wButton = true;
        else
            wButton = false;
        //Right move
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            dButton = true;
        else
            dButton = false;
        //Down move
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            sButton = true;
        else
            sButton = false;
        //Left move
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            aButton = true;
        else
            aButton = false;


        //Arrow keys
        if (event.type == sf::Event::KeyPressed)
        {

            if (event.key.code == sf::Keyboard::Left) leftButton = true;
            if (event.key.code == sf::Keyboard::Right) rightButton = true;
            if (event.key.code == sf::Keyboard::Up) upButton = true;
            if (event.key.code == sf::Keyboard::Down) downButton = true;
        }

        if (event.type == sf::Event::KeyReleased)
        {

            if (event.key.code == sf::Keyboard::Left) leftButton = false;
            if (event.key.code == sf::Keyboard::Right) rightButton = false;
            if (event.key.code == sf::Keyboard::Up) upButton = false;
            if (event.key.code == sf::Keyboard::Down) downButton = false;
        }




        //Movement properties

            //Horizontal movement (x)


        if (rightButton == true || dButton == true)
        {
            xVelocity = 5.f;
        }

        if (leftButton == true || aButton == true)
        {
            xVelocity = -5.f;
        }

        if (leftButton == true && rightButton == true && aButton == true && dButton == true)
        {
            xVelocity = 0.f;
        }

        if (leftButton == false && rightButton == false && aButton == false && dButton == false)
        {
            xVelocity = 0.f;
        }


        //Vertical movement (y)

        if (downButton == true || sButton == true)
        {
            yVelocity = 5.f;
        }

        if (upButton == true || wButton == true)
        {
            yVelocity = -5.f;

        }






        if (downButton == true && upButton == true && sButton == true && wButton == true)
        {
            yVelocity = 0.f;
        }

        if (downButton == false && upButton == false && sButton == false && wButton == false)
        {
            yVelocity = 0.f;
        }



        //Mouse 
           // (rotation in  cursor's direction)

        sf::Vector2f mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));
        sf::Vector2f ship_pos = sf::Vector2f(SpaceShip.getPosition());

        sf::Vector2f da = mouse_pos - ship_pos;

        float dy = da.y;
        float dx = da.x;

        float angle = (atan2(dy, dx)) * 180 / PI;

        SpaceShip.setRotation(angle + 90);

        //(Shooting)


        sf::Vector2f projectile_pos = sf::Vector2f(projectile.shape.getPosition());

        aim_dir = da / (sqrt(pow(dx, 2) + pow(dy, 2)));

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            projectile.shape.setPosition(ship_pos);

            projectile.projectile_velocity = aim_dir * 10.f;

            projectiles.push_back(Bullet(projectile));

            if (projectiles.size() > 1)

            {
                for (size_t i = projectiles.size() - 1; i > 0; i--)
                    projectiles.erase(projectiles.begin() + i);
            }



        }


        //Spawn asteroids


      //  Asteroid small_roid;

      //  small_roid.asteroid_shape.setScale(sf::Vector2f(2.f, 2.f));
        small_roid.asteroid_velocity = asteroid_dir * 1.f;

        sf::Vector2f small_roid_pos;

      //  std::vector <Asteroid> small_roids;

        if (asteroids.size() < 6)
        {

            asteroid.asteroid_pos = sf::Vector2f(rand() % (width - (int)asteroid.asteroid_size.x),
                rand() % (height - (int)asteroid.asteroid_size.y));

            // distance threshhold
            if (!(asteroid.asteroid_pos.x - ship_pos.x < 400.f) && (asteroid.asteroid_pos.y - ship_pos.y < 300.f))
            {

                asteroid.asteroid_shape.setPosition(asteroid.asteroid_pos);
                asteroids.push_back(asteroid);
            }



        }

        //Direct asteroids to ship(player) and set speed
        for (size_t i = 0; i < asteroids.size(); i++)
        {
            asteroids[i].asteroid_pos = asteroids[i].asteroid_shape.getPosition();
            sf::Vector2f db = ship_pos - asteroids[i].asteroid_pos;

            asteroid_dir = db / (sqrt(pow(db.x, 2) + pow(db.y, 2)));

            asteroids[i].asteroid_velocity = asteroid_dir * 1.f;


            asteroids[i].asteroid_shape.move(asteroids[i].asteroid_velocity);
        }

        // Screen bounds and collision 
        for (size_t i = 0; i < projectiles.size(); i++)
        {
            //Check out of bounds

            if (projectiles[i].shape.getPosition().x < 0 || projectiles[i].shape.getPosition().x > width
                || projectiles[i].shape.getPosition().y < 0 || projectiles[i].shape.getPosition().y > height)

            {
                projectiles.erase(projectiles.begin() + i);
            }
            else
            {
                //Enemy collision (and spasning small asteroids)
                for (size_t k = 0; k < asteroids.size(); k++)
                {
                    if (projectiles[i].shape.getGlobalBounds().intersects(asteroids[k].asteroid_shape.getGlobalBounds()))
                    {

                        
                            small_roid_pos = sf::Vector2f(asteroids[k].asteroid_shape.getPosition());
                        
                            small_roid.asteroid_shape.setPosition(small_roid_pos);
                            small_roids.push_back(small_roid);

                            small_roid.asteroid_shape.setPosition(small_roid_pos.x+40, small_roid_pos.y + 40);
                            small_roids.push_back(small_roid);

                        projectiles.erase(projectiles.begin() + i);
                        asteroids.erase(asteroids.begin() + k);

                        //  std::cout << small_roid_pos.x << std::endl;

                        break;
                    }
                }
            }

        
        }

        //Collision of bullets and smalll asteroids
        for (size_t i = 0; i < projectiles.size(); i++)
        {
            
                //Enemy collision
                for (size_t k = 0; k < small_roids.size(); k++)
                {
                    if (projectiles[i].shape.getGlobalBounds().intersects(small_roids[k].asteroid_shape.getGlobalBounds()))
                    {

                        projectiles.erase(projectiles.begin() + i);
                        small_roids.erase(small_roids.begin() + k);

                        break;
                    }
                }
            }


        



        //Direct small asteroids to player
        for (size_t i = 0; i < small_roids.size(); i++)
        {
           

            small_roids[i].asteroid_pos = small_roids[i].asteroid_shape.getPosition();
            sf::Vector2f dv = ship_pos - small_roids[i].asteroid_pos;

            small_roid_dir = dv / (sqrt(pow(dv.x, 2) + pow(dv.y, 2)));

            small_roids[i].asteroid_velocity = small_roid_dir * 1.5f;

            small_roids[i].asteroid_shape.move(small_roids[i].asteroid_velocity);
            
             
        }
         
        

        ;

         //Asteroids collision

        for (size_t i = 0; i < asteroids.size(); i++)
        {
            for (size_t k = 0; k < asteroids.size(); k++)
            {
                if (i == k)
                    continue;
                if (asteroids[i].asteroid_shape.getGlobalBounds().intersects(asteroids[k].asteroid_shape.getGlobalBounds()))
                {
                    asteroids[i].asteroid_shape.setPosition(asteroids[i].asteroid_pos.x - 10.f, asteroids[i].asteroid_pos.y - 10.f);
                    asteroids[k].asteroid_shape.setPosition(asteroids[k].asteroid_pos.x + 10.f, asteroids[k].asteroid_pos.y + 10.f);
                }

            }



            if (asteroids[i].asteroid_shape.getGlobalBounds().intersects(SpaceShip.getGlobalBounds()))
            {

                window.close();

            }
        }


        //Small asteroids collision
        
            for (size_t i = 0; i < small_roids.size()  ; ++i)
            {
                for (size_t k = 0; k < small_roids.size()   ; ++k)
                {
                    if (i == k)
                        continue;
                    if (small_roids[i].asteroid_shape.getGlobalBounds().intersects(small_roids[k].asteroid_shape.getGlobalBounds()))
                    {
                        small_roids[i].asteroid_shape.setPosition(small_roids[i].asteroid_shape.getPosition().x - 10.f, small_roids[i].asteroid_shape.getPosition().y - 10.f);
                        small_roids[k].asteroid_shape.setPosition(small_roids[k].asteroid_shape.getPosition().x + 10.f, small_roids[k].asteroid_shape.getPosition().y + 10.f);
                    }
                }

                if (small_roids[i].asteroid_shape.getGlobalBounds().intersects(SpaceShip.getGlobalBounds()))
                {

                    window.close();

                }

            }

            //Collision of big asteroids with small ones
            {
                for (size_t i = 0; i < asteroids.size(); ++i)
                {
                    for (size_t k = 0; k < small_roids.size(); ++k)
                    {
                        if (i == k)
                            continue;
                        if (asteroids[i].asteroid_shape.getGlobalBounds().intersects(small_roids[k].asteroid_shape.getGlobalBounds()))
                        {
                            asteroids[i].asteroid_shape.setPosition(asteroids[i].asteroid_shape.getPosition().x - 10.f, asteroids[i].asteroid_shape.getPosition().y - 10.f);
                            small_roids[k].asteroid_shape.setPosition(small_roids[k].asteroid_shape.getPosition().x + 10.f, small_roids[k].asteroid_shape.getPosition().y + 10.f);
                        }
                    }

                }
            }
        


        //Asteroids screen bounds check
        for (size_t i = 0; i < projectiles.size(); i++)
            projectiles[i].shape.move(projectiles[i].projectile_velocity);

        for (size_t i = 0; i < asteroids.size(); i++)
        {
            if (asteroids[i].asteroid_pos.x < 0)
                asteroids[i].asteroid_shape.setPosition(width, asteroids[i].asteroid_pos.y);
            if (asteroids[i].asteroid_pos.x > width)
                asteroids[i].asteroid_shape.setPosition(0, asteroids[i].asteroid_pos.y);
            if (asteroids[i].asteroid_pos.y < 0)
                asteroids[i].asteroid_shape.setPosition(asteroids[i].asteroid_pos.x, height);
            if (asteroids[i].asteroid_pos.y > height)
                asteroids[i].asteroid_shape.setPosition(asteroids[i].asteroid_pos.x, 0);

        }



        //Move ship 

        SpaceShip.move(xVelocity, 0);

        SpaceShip.move(0, yVelocity);

        if (ship_pos.x < 0)
            SpaceShip.setPosition(width, ship_pos.y);
        if (ship_pos.x > width)
            SpaceShip.setPosition(0, ship_pos.y);
        if (ship_pos.y < 0)
            SpaceShip.setPosition(ship_pos.x, height);
        if (ship_pos.y > height)
            SpaceShip.setPosition(ship_pos.x, 0);





        //Render
        window.clear();

        //Draw
        window.draw(background);
        window.draw(SpaceShip);
        //window.draw(asteroid.asteroid_shape);

        for (size_t i = 0; i < asteroids.size(); i++)
        {
            window.draw(asteroids[i].asteroid_shape);
        }

        for (size_t i = 0; i < small_roids.size(); i++)
        {
            window.draw(small_roids[i].asteroid_shape);
        }

       


        for (size_t i = 0; i < projectiles.size(); i++)
        {

            window.draw(projectiles[i].shape);

        }


        window.display();

    }



}
