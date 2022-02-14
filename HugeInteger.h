#ifndef HUGEINTEGER_H_
#define HUGEINTEGER_H_
#include <iostream>

class HugeInteger
{
private:
	int sign=1; 
	int length; 
	int* digits;
	
		
public:
	// Required methods
	HugeInteger(const std::string& val);
	HugeInteger(int n);
	
	HugeInteger user_add(const HugeInteger& h);
	HugeInteger add(const HugeInteger& h);
	
	HugeInteger user_sub(const HugeInteger& h);
	HugeInteger subtract(const HugeInteger& h);
	
	HugeInteger multiply(const HugeInteger& h);	
	int compareTo(const HugeInteger& h);
	std::string toString();

	//unique methods
	int LargerLen(const HugeInteger& h);
	int IsLarger(const HugeInteger& h);
	int toInt();
	HugeInteger RemoveZeros();

};

#endif /* HUGEINTEGER_H_ */

