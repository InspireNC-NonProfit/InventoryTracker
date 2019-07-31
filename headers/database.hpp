#pragma once

#include "part.hpp"

class database {
public:
	std::string filepath;
	std::vector<part> parts;
	std::string dbText;

	database(std::string);

	void init(void);

	void close(void);

	void inputCmd(std::string);

private:
	int findPart(std::string);

	void addPart(part);

	void editPart(std::string, int);

	void deletePart(std::string);


};