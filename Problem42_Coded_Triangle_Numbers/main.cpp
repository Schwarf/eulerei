//
// Created by andreas on 22.08.22.
//
#include "./../helpers/read_csv_file.h"
#include <unordered_set>
int main()
{
	std::string full_file_path("/media/linux_data/projects/cpp/eulerei/Problem42_Coded_Triangle_Numbers/p042_words.text");
	auto result = read_csv_file(full_file_path);
	std::unordered_set<int> triangle_values;
	for(int i=1; i < 1000; ++i)
	{
		triangle_values.insert(i*(i+1)/2);
	}
	int count{};
	for(const auto & word: result[0])
	{
		int sum{};
		for(const auto & character: word)
		{
			sum += 1 + character - 'A' ;

		}
		if(triangle_values.find(sum) != triangle_values.end())
			count++;
	}
	std::cout << count << std::endl;

	return 0;
}