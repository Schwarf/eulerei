//
// Created by andreas on 12.06.22.
//

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <set>

long name_score(const std::string & name)
{
	long score{};
	for( const auto & c : name ){
		if( std::isalpha(c)){ // Do not care about quotes
			score += toupper(c) - 'A'+1;
		}
	}
	return score;
}


long sum(const char *file_name)
{
	std::set<std::string> sorted_names;
	std::ifstream file(file_name);
	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << file_name << std::endl;
	}

	for (std::string line; std::getline(file, line);) {
		std::stringstream stream(line);
		std::string name;
		while (std::getline(stream, name, ',')) {
			sorted_names.insert(name);
		}
	}
	std::cout << sorted_names.size() << std::endl;
	long count{1};
	long sum{};
	for (const auto & sorted_name : sorted_names) {
		sum += count * name_score(sorted_name);\
		count++;
	}
	return sum;
}

	int main()
	{


		std::cout << sum("/media/linux_data/projects/cpp/eulerei/Problem22_NamesScores/names.text") << std::endl;
		return 0;
	}