#include "database.hpp"

database::database(std::string file) {
	this->filepath = file;
}

int database::findPart(std::string partID) {
		int count = 0;
		for (int i = 0; i < parts.size(); ++i) {
			if (parts[i].id == partID) {
				count = i;
				break;
			}
		}
		return count;
}

void database::init(void) {
	system("cd C:\\Users\\Pranav\\Desktop\\inventory\\source\\ && python -u download.py");

	std::ifstream in(filepath);

	std::string temp;

	// pushes the current data into the vector parts for easy manipulation and writing. 
	while (!in.eof()) {
		std::string tempPart[3];

		std::getline(in, temp);

		std::istringstream ss(temp);
		std::string temp2;

		int i = 0;

		while (std::getline(ss, temp2, ',')) {
			tempPart[i] = temp2;
			++i;
		}
		parts.push_back(part(tempPart[0], tempPart[1], std::atoi(tempPart[2].c_str())));
	}
	in.close();
}

void database::addPart(part newPart) {
		parts.push_back(newPart);
}

void database::editPart(std::string id, int newQuantity) {
		parts[findPart(id)].quantity = newQuantity;
}

void database::deletePart(std::string id) {
	parts.erase(parts.begin() + findPart(id) - 1);
}

void database::close(void) {
	std::ofstream out(filepath, std::ofstream::out | std::ofstream::trunc);
	for (int i = 0; i < parts.size(); ++i) {
		if (i != parts.size() - 1)
			out << parts[i].id << "," << parts[i].type << "," << std::to_string(parts[i].quantity) << std::endl;
		else
			out << parts[i].id << "," << parts[i].type << "," << std::to_string(parts[i].quantity);
	}
	out.close();

	system("cd C:\\Users\\Pranav\\Desktop\\inventory\\source\\ && python -u upload.py");
}
void database::inputCmd(std::string input) {
	if (input.substr(0, 7) == "addPart") {
		std::cout << "ADD WORKING" << std::endl;
		std::cout << input << std::endl;
		dbText.clear();
		input = input.substr(8, input.length() - 7);
		input = input.substr(0, input.size() - 1);
		
		std::vector<std::string> temp;
		std::istringstream ss(input);
		std::string i;
		while(std::getline(ss, i, ',')) {
			temp.push_back(i);
		}
		part Part(temp[0], temp[1], std::atoi(temp[2].c_str()));
		addPart(Part);
		dbText = "Part Added!";
	}
	else if (input.substr(0, 8) == "editPart") {			
		dbText.clear();
		input = input.substr(9, input.size() - 8);
		input = input.substr(0, input.size() - 1);
		std::istringstream ss(input);
		std::string i, store[2];
		int k = 0;
		while(std::getline(ss, i, ',')) {
			store[k] = i;
			std::cout << i;
			++k;
		}
		editPart(store[0], std::atoi(store[1].c_str()));
		close();
		dbText = store[0] + " has been updated to reflect new count of " + store[1];
	}
	else if (input.substr(0, 10) == "deletePart") { 
		dbText.clear();
		input = input.substr(11, 10);
		input = input.substr(0, input.size() - 1);
		deletePart(input);
	}
	else if (input.substr(0, 10) == "updateData") {
		close();
	}
	else if (input.substr(0, 10) == "displayAll") {
		dbText.clear();
		for (int i = 0; i < parts.size(); ++i) {
			dbText += parts[i].id + " " + parts[i].type + " " + std::to_string(parts[i].quantity) + "\n";
		}
	}
	else if (input.substr(0, 11) == "displayPart") {
		dbText.clear();
		input = input.substr(12, input.size() - 11);
		input = input.substr(0, input.size() - 1);
		part temp = parts[findPart(input)];
		dbText = temp.id + " " + temp.type + " " + std::to_string(temp.quantity) + "\n";
	}
	else if (input.substr(0, 4) == "exit") {
		dbText.clear();
		dbText = "EXITING, ALL CHANGES WILL BE UPLOADED";
		close();
		exit(0);
	}
	else {
		dbText = "Not Valid Command.";
	}		
}
