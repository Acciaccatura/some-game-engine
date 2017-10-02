#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <ratio>
#include <thread>

//temporaries
#include "Hitbox.h"

#define MAXFPS 10

const long long int MAXMS = 1000000/MAXFPS;
Hitbox box1(300, 300);
Hitbox box2(100, 100);
sf::Color current_color = sf::Color::Green;

void update() {
    box1.rotate_rad(0.1);
    box1.translate(1, 1);
    if (box1.collision(box2)) {
        current_color = sf::Color::Red;
    } else {
        current_color = sf::Color::Green;
    }
}

void draw(sf::RenderWindow* window) {
    sf::VertexArray box1_draw(sf::Lines, 8);
    sf::VertexArray box2_draw(sf::Lines, 8);
    int index;
    for (index = 0; index < 3; index++) {
        box1_draw[index*2].position = sf::Vector2f(box1.vertices[index].x, box1.vertices[index].y);
        box1_draw[index*2].color = current_color;
        box1_draw[index*2 + 1].position = sf::Vector2f(box1.vertices[index + 1].x, box1.vertices[index + 1].y);
        box1_draw[index*2 + 1].color = current_color;
    }
    box1_draw[6].position = sf::Vector2f(box1.vertices[3].x, box1.vertices[3].y);
    box1_draw[6].color = current_color;
    box1_draw[7].position = sf::Vector2f(box1.vertices[0].x, box1.vertices[0].y);
    box1_draw[7].color = current_color;
    for (index = 0; index < 3; index++) {
        box2_draw[index*2].position = sf::Vector2f(box2.vertices[index].x, box2.vertices[index].y);
        box2_draw[index*2].color = current_color;
        box2_draw[index*2 + 1].position = sf::Vector2f(box2.vertices[index + 1].x, box2.vertices[index + 1].y);
        box2_draw[index*2 + 1].color = current_color;
    }
    box2_draw[6].position = sf::Vector2f(box2.vertices[3].x, box2.vertices[3].y);
    box2_draw[6].color = current_color;
    box2_draw[7].position = sf::Vector2f(box2.vertices[0].x, box2.vertices[0].y);
    box2_draw[7].color = current_color;
    window->draw(box1_draw);
    window->draw(box2_draw);
}

int main()
{
    Hitbox::rectangle(&box1, 20, 30);
    Hitbox::rectangle(&box2, 30, 40);

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
