//
// Created by andreas on 22.08.22.
//
#include <vector>
#include <iostream>
int main()
{
	std::vector<std::vector<long long unsigned >> result(101, std::vector<long long unsigned>(101, 0));
	result[0][0] = 0;
	result[1][0] = 1;
	result[1][1] = 1;
	int count{};
	for(int i=2; i < 101; ++i)
	{
		for(int j=0; j <= i; ++j)
		{
			if(j==0)
				result[i][j] = 1;
			else if(i==j)
				result[i][j] = 1;
			else if(i-1 == j)
				result[i][j] = i;
			else if (j > i)
				result[i][j] = 0;
			else
				result[i][j] = result[i-1][j-1] + result[i-1][j];

			if(result[i][j] > 1000000)
				count++;
		}
	}
	std::cout << count << std::endl;


	return 0;
}

