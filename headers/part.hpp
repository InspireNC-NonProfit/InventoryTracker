#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

// part class, stores essential data. 
class part {

public:
std::string id;
std::string type;
int quantity;

part(std::string, std::string, int);

};