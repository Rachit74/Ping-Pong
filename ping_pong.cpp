#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define RADIUS 10


int main() {

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ping Pong C++");
    
    // ball object
    sf::CircleShape Ball(RADIUS);
    Ball.setFillColor(sf::Color::White);
    Ball.setPosition(WINDOW_WIDTH/2,WINDOW_HEIGHT/2);

    
    // game loop

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(Ball);
        window.display();

    }



}