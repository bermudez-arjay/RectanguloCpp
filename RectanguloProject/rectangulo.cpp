#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Rebote dentro de Rectángulos");

    sf::Color color1(255, 0, 0);
    sf::Color color2(0, 255, 0);
    sf::Color color3(0, 0, 255);

    sf::RectangleShape rect1(sf::Vector2f(600, 400));
    rect1.setFillColor(color1);
    rect1.setPosition(100, 100);

    sf::RectangleShape rect2(sf::Vector2f(400, 300));
    rect2.setFillColor(color2);
    rect2.setPosition(200, 150);

    sf::RectangleShape rect3(sf::Vector2f(200, 200));
    rect3.setFillColor(color3);
    rect3.setPosition(300, 200);

    sf::CircleShape circle(25);
    circle.setFillColor(sf::Color::Yellow);
    circle.setPosition(350, 250);

    sf::Vector2f velocity(0.2f, 0.2f);

    bool isMoving = true;
    bool isRestricted = false;
    sf::RectangleShape *activeRectangle = nullptr;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
            {
                isMoving = !isMoving;
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                if (isRestricted)
                {
                    isRestricted = false;
                    activeRectangle = nullptr;
                }
                else
                {
                    if (rect3.getGlobalBounds().contains(circle.getPosition().x + circle.getRadius(),
                                                         circle.getPosition().y + circle.getRadius()))
                        activeRectangle = &rect3;
                    else if (rect2.getGlobalBounds().contains(circle.getPosition().x + circle.getRadius(),
                                                              circle.getPosition().y + circle.getRadius()))
                        activeRectangle = &rect2;
                    else if (rect1.getGlobalBounds().contains(circle.getPosition().x + circle.getRadius(),
                                                              circle.getPosition().y + circle.getRadius()))
                        activeRectangle = &rect1;

                    isRestricted = (activeRectangle != nullptr);
                }
            }
        }

        if (isMoving)
        {
            circle.move(velocity);

            sf::FloatRect bounds = (isRestricted && activeRectangle) ? activeRectangle->getGlobalBounds()
                                                                     : rect1.getGlobalBounds();

            if (circle.getPosition().x < bounds.left ||
                circle.getPosition().x + circle.getRadius() * 2 > bounds.left + bounds.width)
            {
                velocity.x = -velocity.x;
            }
            if (circle.getPosition().y < bounds.top ||
                circle.getPosition().y + circle.getRadius() * 2 > bounds.top + bounds.height)
            {
                velocity.y = -velocity.y;
            }
        }
        window.clear();
        window.draw(rect1);
        window.draw(rect2);
        window.draw(rect3);
        window.draw(circle);
        window.display();
    }

    return 0;
}
