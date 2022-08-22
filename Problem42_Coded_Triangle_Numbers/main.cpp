//
// Created by andreas on 22.08.22.
//
#include "./../helpers/read_csv_file.h"

int main()
{
	std::string full_file_path("/media/linux_data/projects/cpp/eulerei/Problem42_Coded_Triangle_Numbers/p042_words.txt");
	auto result = read_csv_file(full_file_path);
	return 0;
}