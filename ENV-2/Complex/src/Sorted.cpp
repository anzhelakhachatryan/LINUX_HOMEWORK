#include "../include/Sorted.h"

void sortComplex(std::vector<Complex>& nums){
	int n = nums.size();
	for(int i = 0; i < n-1; ++i){
		for(int j = 0; j < n-i-1; ++j){
			if(nums[j].abs() > nums[j+1].abs()){
				Complex temp = nums[j];
				nums[j] = nums[j+1];
				nums[j+1] = temp;
			}
		}
	}
}
