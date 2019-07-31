#include "app.hpp"

database frc("data/frcTestData.csv");

sf::Event event; 

sf::Font font; 
 
std::string inputText;

sf::Text dispText("", font, 50);
sf::Text outputText("", font, 25);

sf::Texture background;
   
sf::Sprite bgDrawable;


app::app() : window(sf::VideoMode(1920,1080), "InspireNC Inventory") {
    window.setVerticalSyncEnabled(true);
}

void app::textProcess() {
    if (!font.loadFromFile("resources/Avenir.otf")) { 
        std::cerr << "Cannot load font. " << std::endl;
        window.close();
    }

    sf::Event event;
    
    dispText.setPosition(158, 909);
    dispText.setFillColor(sf::Color::Black);

    outputText.setPosition(sf::Vector2f(0.0f, 148.0f));
    outputText.setFillColor(sf::Color(31,24,255));
}

void app::imageProcess() {
    if (!background.loadFromFile("resources/background.png", sf::IntRect(0,0,1920,1080))) {
        std::cerr << "Error: Cannot load background image. " << std::endl;
        window.close();
    }

    bgDrawable.setTexture(background);
}



void app::eventProcessor() {
    while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    frc.close();
                    window.close();
                    break;
                case sf::Event::TextEntered:
                   switch (event.text.unicode) {
                        case 13:
                        frc.inputCmd(inputText);
                        inputText.clear();
                        break;
                        case 8:
                        inputText = inputText.substr(0, inputText.size() - 1);
                        break;
                        default:
                        inputText += event.text.unicode;
                    }
                    dispText.setString(inputText);
                    outputText.setString(frc.dbText);
                    std::cout << frc.dbText;
                    break;
            }
        }
}

void app::render() {
    window.draw(bgDrawable);
        window.draw(dispText);
        window.draw(outputText);
        window.display();
        window.clear(sf::Color::White);
}

void app::run() {
    frc.init();
    textProcess();
    imageProcess();
    while(window.isOpen()) {
        eventProcessor();
        render();
    }
}