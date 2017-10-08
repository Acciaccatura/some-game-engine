#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <ratio>
#include <thread>

//temporaries
#include "Hitbox.h"

const int MAXFPS = 60;
const long long int MAXMS = 1000000/MAXFPS;

int dir = 1;
Hitbox* box1 = Hitbox::rectangle(400, 300, 100, 30);
Hitbox* box2 = Hitbox::rectangle(300, 300, 50, 600);
sf::Color current_color = sf::Color::Green;

void update() {
    if (box2->get_center()->x > 600) {
        dir = -1;
    } else if (box2->get_center()->x < 200) {
        dir = 1;
    }
    box1->rotate_rad(-0.03);
    box2->rotate_rad(0.01);
    box2->translate(dir, 0);
    bool collided = box1->collision(box2);
    if (collided) {
        current_color = sf::Color::Red;
    } else {
        current_color = sf::Color::Green;
    }
}

void draw(sf::RenderWindow* window) {
    box1->draw(window, current_color);
    box2->draw(window, current_color);
}

int main()
{

    using namespace std::chrono;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Window!");

    time_point<high_resolution_clock> prev = high_resolution_clock::now();
    time_point<high_resolution_clock> now = high_resolution_clock::now();
    microseconds delta = duration_cast<microseconds>(now - prev);

    while (window.isOpen()) {

        now = high_resolution_clock::now();
        delta = duration_cast<microseconds>(now - prev);
        long int diff = delta.count();
        if (diff >= MAXMS) {
            prev = high_resolution_clock::now();
            //should I check for close events here?
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }
            window.clear();
            update();
            draw(&window);
            window.display();
        } else {
            //frames will always be lower than the max tho
            std::this_thread::sleep_for(microseconds(MAXMS - diff));
        }
    }

    return 0;
}
