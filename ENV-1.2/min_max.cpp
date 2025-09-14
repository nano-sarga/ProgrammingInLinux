#include <iostream>
#include <sstream>

int main(int arg_cout, char* arg_arr[] ) {
	if (arg_cout != 4) {
		std::cerr << "Enter arguments like this : " 
			<< arg_arr[0] << "arg1 arg2 arg3\n";
		return 1;
	}

	int arg1, arg2, arg3;
	std::stringstream ss1(arg_arr[1]), ss2(arg_arr[2]), ss3(arg_arr[3]);
	ss1 >> arg1;
	ss2 >> arg2;
	ss3 >> arg3;

	int min = arg1;
	int max = arg1;

	if (arg2 < min) { min = arg2; }
	if (arg3 < min) { min = arg3; }

	if (arg2 > max) { max = arg2; }
	if (arg3 > max) { max = arg3; }

	std::cout << "min-" << min << ", max-" << max << "\n";	
	return 0;

}
