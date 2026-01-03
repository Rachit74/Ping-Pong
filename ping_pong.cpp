#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define RADIUS 10

/*
clampToWindow functions makes sure that the ball stays in the window height and width limit
it's checks the ball position and changes the ball position it it tries to go outside of the limit

pos - vector position object which will have position.x and position.y
*/
bool clampToWindow(sf::CircleShape& circle) {
    float radius = circle.getRadius();
    float diameter = radius * 2.f;

    sf::Vector2f pos = circle.getPosition();
    bool hitBottom = false;

    if (pos.x < 0.f) {
        pos.x = 0.f;
    }
    
    if (pos.x > WINDOW_WIDTH - diameter) {
        pos.x = WINDOW_WIDTH - diameter;
    }

    if (pos.y < 0.f) {
        pos.y = 0.f;
    }
    
    if (pos.y > WINDOW_HEIGHT - diameter) {
        pos.y = WINDOW_HEIGHT - diameter;
        hitBottom = true;
    }

    circle.setPosition(pos);
    return hitBottom;
}



int main() {

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ping Pong C++");
    
    // ball object
    sf::CircleShape Ball(RADIUS);
    Ball.setFillColor(sf::Color::White);
    Ball.setPosition(WINDOW_WIDTH/2,WINDOW_HEIGHT/2);

    // gravity logic
    float veclocity = 0.f;
    const float gravity = 500.f; // pixels per second squared

    sf::Clock clock;

    
    // game loop

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float dt = clock.restart().asSeconds();
        veclocity += gravity * dt;
        Ball.move(0.f, veclocity * dt);

        // clampToWindow(Ball);
        if (clampToWindow(Ball)) {
            veclocity = -veclocity * 0.7f; // reverse velocity and apply damping
        }

        window.clear();
        window.draw(Ball);
        window.display();

    }



}