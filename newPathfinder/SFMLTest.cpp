#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <iostream>




//int main()
//{
//
//
//
//    sf::Font* font = new sf::Font;
//    if (!font->loadFromFile("arial.ttf"));
//
//
//
//    delete font;
//
//    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//    sf::RectangleShape rectangle;
//    rectangle.setSize(sf::Vector2f(1, 1));
//    rectangle.setFillColor(sf::Color::Red);
//    rectangle.setOutlineThickness(0);
//    rectangle.setPosition(0, 0);
//
//
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        window.clear();
//        window.draw(rectangle);
//        
//        window.display();
//    }
//
//    return 0;
//}
