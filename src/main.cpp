#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <ratio>
#include <thread>

//temporaries
#include "IterList.h"
#include "RegularHitbox.h"

const int MAXFPS = 60;
const long long int MAXMS = 1000000/MAXFPS;
IterList<Hitbox>* hitboxes;
Hitbox* box1, *box2;

void init() {
    hitboxes = new IterList<Hitbox>();
    box1 = RegularHitbox::rectangle(50, 150, 200, 50);
    box2 = new RegularHitbox(300, 160, 40, 5);
    hitboxes->add(box1);
    hitboxes->add(box2);
}

void update(sf::RenderWindow* window) {
    Hitbox* box = hitboxes->head();
    sf::Color color = sf::Color::Green;
    while (box) {
        Hitbox* next = hitboxes->next();
        IterListElem<Hitbox>* temp_iter;
        for (temp_iter = hitboxes->expose(); temp_iter > 0; temp_iter = temp_iter->next) {
            if (box->collision(temp_iter->obj))
                color = sf::Color::Red;
            else
                color = sf::Color::Green;
        }
        box->draw(window, color);
        box = next;
    }
    box1->translate(5, 0);
    box2->rotate_rad(0.1);
}

void draw(sf::RenderWindow* window) {

}

int main()
{
    using namespace std::chrono;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Window!");

    time_point<high_resolution_clock> prev = high_resolution_clock::now();
    time_point<high_resolution_clock> now = high_resolution_clock::now();
    microseconds delta = duration_cast<microseconds>(now - prev);

    init();

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
            update(&window);
            window.display();
        } else {
            //frames will always be lower than the max tho
            std::this_thread::sleep_for(microseconds(MAXMS - diff));
        }
    }

    return 0;
}
