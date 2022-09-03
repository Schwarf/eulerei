//
// Created by andreas on 03.09.22.
//


int main()
{
	int x1=21, x2=12, x3=27;
	int y1=16, y2=12, y3=27;
	int z1 = 17*17, z2 = 17*16, z3 = 67890;
	std::cout << is_power_of<3, int>(x1) << std::endl;
	std::cout << is_power_of<3, int>(x2) << std::endl;
	std::cout << is_power_of<3, int>(x3) << std::endl;

	std::cout << is_power_of<4, int>(y1) << std::endl;
	std::cout << is_power_of<4, int>(y2) << std::endl;
	std::cout << is_power_of<4, int>(y3) << std::endl;

	for(int i{}; i < 1000; ++i)
	{
		if(is_power_of<17, int>(i))
			std::cout << i << std::endl;
	}
	return 0;
}