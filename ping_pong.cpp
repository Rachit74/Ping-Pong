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

/*
isBalllOutOfBounds functions check if a player has missed the ball and ball has gone out of window
returns a bool
*/
bool isBallOutOfBounds(const sf::CircleShape& ball) {
    float radius = ball.getRadius();
    float diameter = radius * 2.f;
    sf::Vector2f pos = ball.getPosition();

    return (pos.x < 0.f || pos.x + diameter > WINDOW_WIDTH ||
            pos.y < 0.f || pos.y + diameter > WINDOW_HEIGHT);
}


/*
clampBarToWindow function checks if left and right bar are going out of the window
if they go out of the window we reset their position
top-left corner of the rectangle is taken as pos.y, we need to sub bar height to calculte bottom borders
*/
void clampBarToWindow(sf::RectangleShape& bar) {
    sf::Vector2f pos = bar.getPosition();
    float barHeight = bar.getSize().y;

    if (pos.y < 0) {
        pos.y = 0;
    }

    if (pos.y > WINDOW_HEIGHT - barHeight) {
        pos.y = WINDOW_HEIGHT - barHeight;
    }

    bar.setPosition(pos);
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
    sf::RectangleShape LeftBar(sf::Vector2f(10.f, 120.f));
    LeftBar.setFillColor(sf::Color::White);
    LeftBar.setPosition(0.f, WINDOW_HEIGHT/2);

    // Right Bar
    sf::RectangleShape RightBar(sf::Vector2f(10.f, 120.f));
    RightBar.setFillColor(sf::Color::White);
    RightBar.setPosition(WINDOW_WIDTH - 10.f, WINDOW_HEIGHT/2);

    // Ball Velocity Vector
    sf::Vector2f velocity(300.f, 200.f);

    sf::Clock clock;

    // Ball pause Variables
    bool ballPaused = false;
    float pauseTimer = 0.f;
    const float PAUSE_DURATION = 1.f; // seconds


    
    // game loop

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float dt = clock.restart().asSeconds(); // ONE dt PER FRAME


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            RightBar.move(0.f, -400.f * dt);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            RightBar.move(0.f, 400.f * dt);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            LeftBar.move(0.f, -400.f * dt);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            LeftBar.move(0.f, 400.f * dt);
        }


        if (!ballPaused) {
            Ball.move(velocity * dt);

            if (isBallOutOfBounds(Ball)) {
                // rest to center
                Ball.setPosition(WINDOW_WIDTH / 2.f - RADIUS,
                                WINDOW_HEIGHT / 2.f - RADIUS);

                // pause ball
                ballPaused = true;
                pauseTimer = 0.f;

                // reset velocity direction
                velocity.x = (velocity.x > 0 ? 300.f : -300.f);
                velocity.y = 200.f;
            }
        }
        else {
            pauseTimer += dt;
            if (pauseTimer >= PAUSE_DURATION) {
                ballPaused = false;
            }
        }


        /*
        check ball collision with respective bars
        */
        if (checkHitsBar(Ball, BottomBar)) {
            velocity.y *= -1.f;
        }

        if (checkHitsBar(Ball, UpperBar)) {
            velocity.y *= -1.f;
        }
        if (checkHitsBar(Ball, LeftBar)) {  
            velocity.x *= -1.f;

        }
        if (checkHitsBar(Ball, RightBar)) {
            velocity.x *= -1.f;

        }

        clampBarToWindow(LeftBar);
        clampBarToWindow(RightBar);


        window.clear();
        window.draw(Ball);
        window.draw(BottomBar);
        window.draw(UpperBar);
        window.draw(LeftBar);
        window.draw(RightBar);
        window.display();

    }



}