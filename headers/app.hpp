#pragma once

#include "database.hpp"

class app {
public: 

    app();

    void run();

private:

    void eventProcessor();

    void render();

    void textProcess();

    void imageProcess();
    
    sf::RenderWindow window;

    
};
