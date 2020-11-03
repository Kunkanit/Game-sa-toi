#include <SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include"Animation.h"
#include "Player.h"
#include"Platform.h"



static const float VIEW_HIGHT = 1080.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HIGHT * aspectRatio, VIEW_HIGHT);
}
int main()
{

    sf::RenderWindow window(sf::VideoMode(520, 520), "Testtt", sf::Style::Close | sf::Style::Resize);
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1080.0f, 720.0f));

   // sf::RectangleShape background(sf::Vector2f(1080.0f, 720.0f));
    //background.setPosition(0.0f, 0.0f);
   // sf::Texture space;
   // space.loadFromFile("Background.png");
   // background.setTexture(&space);

    sf::Texture playtexture;
    playtexture.loadFromFile("k2.png");
    Player player(&playtexture, sf::Vector2u(10, 2), 0.1f, 150.0f, 200.0f);

   

    //  sf::Texture Floor;
    //  Floor.loadFromFile("F.png");

    std::vector<Platform>platforms;
    
    platforms.push_back(Platform(nullptr, sf::Vector2f(600.0f, 250.0f), sf::Vector2f(500.0f, 720.0f)));
   // platforms.push_back(Platform(&Floor, sf::Vector2f(2000.0f, 250.0f), sf::Vector2f(500.0f, 720.0f)));
    


    float deltatime = 0.0f;
    sf::Clock clock;
   

    while (window.isOpen())
    {
        deltatime = clock.restart().asSeconds();
        sf::Vector2f pos = player.getPosition();
        std::cout << pos.x << ' ' << pos.y << '\n';

        if (deltatime > 1.0 / 20.0f)
            deltatime = 1.0 / 20.0f;
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                ResizeView(window, view);
                break;

            }
        }


        player.Update(deltatime);


        sf::Vector2f direction;


       
        //Collider playerCollision = player.GetCollider();
       // for (Platform& platform : platforms)
               
      // if (platform.GetCollider().CheckCollision(playerCollision, direction, 1.0f))
                player.OnCollision(direction);


        view.setCenter(player.getPosition());

        window.clear();
        window.setView(view);
       // window.draw(background);
        player.Draw(window);
       for (Platform& platform : platforms)
        platform.Draw(window);
        window.display();
    }

    return 0;
}