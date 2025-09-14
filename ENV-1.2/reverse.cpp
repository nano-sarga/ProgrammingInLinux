#include <iostream> 


int main(int arg_count, char* arg_arr[]) {
	if (arg_count < 2) {
		std::cerr << "Enter arguments like this : " 
		       << arg_arr[0] << "arg1, arg2, ... etc\n";
	return 1;
	}

	for (int i = arg_count - 1; i >= 1; i--) {
		std::cout << arg_arr[i] << "\n";
	}

	return 0;

}
