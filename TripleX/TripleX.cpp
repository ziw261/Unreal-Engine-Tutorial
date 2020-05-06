#include <iostream>

int main(){
    std::cout << "You are a secret agent breaking into a secure server room..." << std::endl;
    std::cout << "Enter the correct code to continue..." << std::endl;

    int a = 4, b = 5, c = 7;
    int sum = a + b + c;
    int product = a * b * c;

    std::cout << "a: " << a << " b: " << b << " c: " << c << std::endl;
    std::cout << "sum: " << sum << std::endl;
    std::cout << "product: " << product << std::endl;

    return 0;
}