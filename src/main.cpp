#include "date.h"
#include <iostream>

int main() {
	// output
	Date d1(4, Date::dec, 2018);
	Date d2(3, 12, 2017);
	std::cout << d1 << std::endl;
	std::cout << ymd_slash << d2 << std::endl << std::endl;

	// subtraction
	std::cout << dmy_hyphen << d1 << " - " << d2 << " = " 
		<< (d1 - d2) << std::endl << std::endl;
	
	// comparison
	std::cout << std::boolalpha;
	std::cout << dmy_hyphen << d1 << " > " << d2 << " : "
		<< (d1 > d2) << std::endl;
	std::cout << dmy_hyphen << d1 << " == " << d2 << " : "
		<< (d1 == d2) << std::endl << std::endl;

	// input
	Date input;
	std::cin >> input;
	std::cout << "\nInput date: " << dmy_period << input << std::endl;

	return 0;
}
