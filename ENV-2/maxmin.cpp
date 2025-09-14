#include <iostream>
#include <algorithm>
int main(int argv, char** argc)
{
	int a = std::atoi(argc[1]);
	int b = std::atoi(argc[2]);
	int c = std::atoi(argc[3]);

	int max = std::max({a, b, c});
	int min =std::min({a, b, c});
	std::cout << "max- " << max <<std::endl;
	std::cout <<"min- " << min <<std::endl;
	return 0;
}
