#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    sf::CircleShape circle(100.0);
    circle.setPosition(100.0, 300.0);
    circle.setFillColor(sf::Color(100, 250, 50));

    sf::RectangleShape rectangle(sf::Vector2f(240.0, 120.0));
    rectangle.setPosition(500.0, 400.0);
    rectangle.setFillColor(sf::Color(100, 50, 250));

    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(0.0, 0.0));
    triangle.setPoint(1, sf::Vector2f(0.0, 100.0));
    triangle.setPoint(2, sf::Vector2f(140.0, 40.0));
    triangle.setOutlineColor(sf::Color::Red);
    triangle.setOutlineThickness(5);
    triangle.setPosition(600.0, 100.0);

    float rectangle_velocity_x = 100;
    float rectangle_velocity_y = 300;
    float rectangle_angular_velocity = 5;

    sf::Clock clock;
    while (window.isOpen()) {
        // clock and fps counter
        sf::Time elapsed = clock.restart();
        float micro = elapsed.asMicroseconds();
        float sec = elapsed.asSeconds();
        std::cout << "FPS: " << 1000000/(micro+1) << std::endl; // +1 prevents dividing by 0

        // move and rotation
        rectangle.move(rectangle_velocity_x*sec, rectangle_velocity_y*sec);
        rectangle.rotate(rectangle_angular_velocity*sec);

        // collision detection
        sf::FloatRect rectangle_bounds = rectangle.getGlobalBounds();
        if(rectangle_bounds.top <= 0 || rectangle_bounds.top+rectangle_bounds.height >= window.getSize().y )
        {
            rectangle_velocity_y *= -1;
            int r = rand()%255,
                g = rand()%255,
                b = rand()%255;
            rectangle.setFillColor(sf::Color(r, g, b));
        }

        if(rectangle_bounds.left <= 0 || rectangle_bounds.left+rectangle_bounds.width >= window.getSize().x )
        {
            rectangle_velocity_x *= -1;
            int r = rand()%255,
                g = rand()%255,
                b = rand()%255;
            rectangle.setFillColor(sf::Color(r, g, b));
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // display
        window.clear(sf::Color::Black);

        window.draw(circle);
        window.draw(rectangle);
        window.draw(triangle);

        window.display();
    }

    return 0;
}
