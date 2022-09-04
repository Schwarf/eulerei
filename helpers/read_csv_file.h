//
// Created by andreas on 22.08.22.
//

#ifndef READ_CSV_FILE_H
#define READ_CSV_FILE_H
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<std::vector<std::string>> read_csv_file(std::string full_path_to_file)
{
	std::fstream file(full_path_to_file, std::ios::in);
	std::vector<std::vector<std::string>> file_content;
	std::string line;
	std::vector<std::string> row;
	std::string word;
	char delimiter = ',';
	if(!file.is_open())
		std::cout << "Could not open file" << std::endl;

	while(std::getline(file, line));
	{
		row.clear();
		std::stringstream stream(line);
		while(std::getline(stream, word, delimiter))
			row.push_back(word);
		file_content.push_back(row);
	}
	return file_content;
}

#endif //READ_CSV_FILE_H
