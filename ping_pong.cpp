#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define RADIUS 10



/*
checkHitsBar function checks if the ball hits the bar
it returns true if the ball hits the bar otherwise it returns false
circle - circle shape object which represents the ball
bar - rectangle shape object which represents the bar
*/
bool checkHitsBar(sf::CircleShape& circle, sf::RectangleShape& bar) {
    if (circle.getGlobalBounds().intersects(bar.getGlobalBounds())) {
        return true;
    }
    return false;
}

int main() {

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ping Pong C++");
    
    // ball object
    sf::CircleShape Ball(RADIUS);
    Ball.setFillColor(sf::Color::White);
    Ball.setPosition(WINDOW_WIDTH/2,WINDOW_HEIGHT/2);

    // Bottom Bar
    sf::RectangleShape BottomBar(sf::Vector2f(WINDOW_WIDTH, 10.f));
    BottomBar.setFillColor(sf::Color::White);
    BottomBar.setPosition(0.f, WINDOW_HEIGHT - 10.f);

    // Upper Bar
    sf::RectangleShape UpperBar(sf::Vector2f(WINDOW_WIDTH, 10.f));
    UpperBar.setFillColor(sf::Color::White);
    UpperBar.setPosition(0.f, 0.f);

    // left bar
    sf::RectangleShape LeftBar(sf::Vector2f(10.f, WINDOW_HEIGHT));
    LeftBar.setFillColor(sf::Color::White);
    LeftBar.setPosition(0.f, 0.f);

    // Right Bar
    sf::RectangleShape RightBar(sf::Vector2f(10.f, WINDOW_HEIGHT));
    RightBar.setFillColor(sf::Color::White);
    RightBar.setPosition(WINDOW_WIDTH - 10.f, 0.f);

    // Ball Velocity Vector
    sf::Vector2f velocity(300.f, 200.f);

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
        Ball.move(velocity * dt);


        // check collision with bottom bar
        if (checkHitsBar(Ball, BottomBar)) {
            velocity.y *= -1.f;
        }

        // check collision with upper bar
        if (checkHitsBar(Ball, UpperBar)) {
            velocity.y *= -1.f;
        }
        // check collision with left bar
        if (checkHitsBar(Ball, LeftBar)) {  
            velocity.x *= -1.f;

        }
        // check collision with right bar
        if (checkHitsBar(Ball, RightBar)) {
            velocity.x *= -1.f;

        }



        window.clear();
        window.draw(Ball);
        window.draw(BottomBar);
        window.draw(UpperBar);
        window.draw(LeftBar);
        window.draw(RightBar);
        window.display();

    }



}