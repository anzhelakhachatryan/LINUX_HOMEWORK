#include <iostream>
#include <vector>
#include "../include/Complex.h"
#include "../include/Sorted.h"

int main() {
	std::vector<Complex> CompNums = {
		Complex(3, 4),
		Complex(-4, -6),
		Complex(0, 4),
		Complex(10, -4)

	};
	std::cout<< "Unsorted: " << std::endl;
	for(size_t i = 0; i < CompNums.size(); ++i){
		std::cout << " " << CompNums[i]
			  << " abs: " << CompNums[i].abs() <<std::endl;	
	}
	std::cout<< "Dem. operations: " <<std::endl;
	Complex c1(4, 5);
	Complex c2(1, 1);
	Complex sum = c1 + c2;
	Complex diff = c1 - c2;
	Complex scaled = 1.5* c1;

	std::cout<< "c1 = " << c1 << "c2 = " << c2 << std::endl;
	std::cout<< "C1 + C2 = " << sum << std::endl;	
	std::cout<< "C1 - C2 = " << diff << std::endl;
	std::cout<< "1.5 * c1 = " << scaled << std::endl;
	
	return 0;
}
