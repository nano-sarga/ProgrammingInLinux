#include <iostream>
#include <vector>
#include "Complex.h"
#include "SortComplex.h"


int main() {
    Complex num1(2, 5);
    Complex num2(6, 4);
    
    Complex numAdd = num1 + num2;
    std::cout << "Addition: " << "(" << num1 << ")" << "+" 
                << "(" << num2 << ")" << " = " << numAdd << std::endl;
    
    Complex numSub = num1 - num2;
    std::cout << "Subtraction: " << "(" << num1 << ")" << "-" 
                << "(" << num2 << ")" << " = " << numSub << std::endl;
    
    Complex numMul = num1 * num2;
    std::cout << "Multiplication: " << "(" << num1 << ")" << "*" 
                << "(" << num2 << ")" << " = " << numMul << std::endl;
    
    double constNum = 73;
    Complex numMulConst = num1 * constNum;
    std::cout << "Multiply by " << constNum << " : " << "(" << num1 << ")" << "*" 
                << "(" << num2 << ")" << " = " << numMulConst << std::endl;

    std::cout << std::endl;
    std::vector<Complex> nums = {
        Complex(1, 2),
        Complex(3, 4),
        Complex(0, 5),
        Complex(2, -1),
        Complex(4, 0),
        Complex(-2, 1)
    };
    mergeSort(nums);
    
    std::vector<Complex> null = {};
    mergeSort(null);
}
