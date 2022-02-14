#include "HugeInteger.h"
#include <math.h> 
#include <string>
using namespace std; 

HugeInteger::HugeInteger(const std::string& val) {
	// TODO
	
	//x.length returns length of string x
	if (val.length() == 0) {
		throw std::invalid_argument("Cannot have empty string");
	}
	
	int check = 1; //check var checks if all contents of string are digit values [0-9]-> check is set to 0 if not digit 
	
	//must ensure all elements of string are digits (no invalid element) 
	//
	//different conditions if val[0] = '-': --> start loop at i=1
	if (val[0] == '-') {
		
		for (int i = 1; i < val.length(); i++) {
			if (check == 0) { break; } //break - no need to continue loop if one character fails

			if (val[i] >= 48 && val[i] <= 57) {
				check = 1;
			}

			else {
				check = 0;
				break;
			}
		}
	}

	//different conditions when val[0] != '-' -> must start loop at i=0
	else {
		 
		for (int i = 0; i < val.length(); i++) {
			if (check == 0) { break; } //break - no need to continue loop if one character fails

			if (val[i] >= 48 && val[i] <= 57) {
				check = 1;
			}
			else {
				check = 0;
				break;
			}
		}
	}
	
	//if string = invalid, throw invalid string argument
	if (check == 0) { 
		throw std::invalid_argument("Invalid String Element");
	}
	
	this->length = val.length(); //initialize length if valid input 
	this->digits = new int[this->length]; //intialize digits if valid input

	string val_new = ""; //create new string -> holds digits of strings that start w ' - ' 
	if (val[0] == '-') {
		sign = -1;
		val_new = val.substr(1); //creates string of only digits -> no minus sign 
		length = val_new.length();

	}
	else {
		sign = 1;
		val_new = val;
		length = val_new.length();

	}

	for (int i = 0; i < this->length; i++) {
		this->digits[i] = val_new[i]-48; //all valid digits -> digit value = (ASCII value) - 48
	}
		
}

HugeInteger::HugeInteger(int n) {
	// TODO
	
	/*
	if (n > 1000000) {
		throw std::invalid_argument("Input must be smaller");
	}
	*/

	if (n < 1) {
		throw std::invalid_argument("Input must be larger than 1"); //throw argument if n less than 1
	}
	else {

		this->length = n; 
		this->digits = new int[length];
		
		//rand() % x creates a random integer from [0:x-1]

		this->digits[0] = rand() % 9 + 1; //ensures first term is random, less than 10, and greater 0

		for (int i = 1; i < this->length; i++) {
			this->digits[i] = rand() % 10; //random number between 0-9
		}
	}

		
}


HugeInteger HugeInteger::user_add(const HugeInteger& h) {
	// TODO
	
	//LargerLen method created to determine which Huge Int (this or h) has more digits (different loop param required):

	HugeInteger huge_out = HugeInteger(this->LargerLen(h));

	//handle case where carry increases digits by (max) 1 -> LargerLen(h) + 1
	HugeInteger huge_out2 = HugeInteger(this->LargerLen(h)+1); 

	int flag = 0; //set to 1 if carry is on Most significant digit -> must return huge_out2 as digits increase by 1
	
	if (this->LargerLen(h) == this->length) {
		
		for (int i = 0; i < this->length; i++) {
			huge_out.digits[i] = this->digits[i];  //set contents of this into output
		}
		for (int i = 0; i < h.length; i++) {
			huge_out.digits[this->length - 1 - i] += h.digits[h.length - 1 - i]; //add h to output (currently elements in array can be > 10) 
		}

		for (int i = this->length - 1; i >= 0; i--) {
			if (huge_out.digits[i] >= 10) { //if element is > 10, store modulo and add carry to next sig digit (i-1) 
				if (i == 0) {
					//set flag = 1 because most significant digit has carry
					flag = 1; 
					huge_out.digits[i] = huge_out.digits[i] % 10;
				}
				else {
					int temp = huge_out.digits[i]; 
					huge_out.digits[i] = huge_out.digits[i] % 10; 
					huge_out.digits[i - 1] += temp / 10; 
				}
			}
		}

	}

	//same process as above just for case where h.length > this->length

	if (this->LargerLen(h) == h.length) {
		for (int i = 0; i < h.length; i++) {
			huge_out.digits[i] = h.digits[i]; 
		}

		for (int i = 0; i < this->length; i++) {
			huge_out.digits[h.length - 1 - i] += this->digits[this->length - 1 - i]; 
		}

		for (int i = h.length - 1; i >= 0; i--) {
			if (huge_out.digits[i] >= 10) {
				if (i == 0) {
					flag = 1; 
					huge_out.digits[i] = huge_out.digits[i] % 10; 
				}
				else {
					int temp = huge_out.digits[i]; 
					huge_out.digits[i] = huge_out.digits[i] % 10;
					huge_out.digits[i - 1] += temp / 10; 
				}
			}
		}
	}
		
	//if flag = 0, no carry on MSD 
	if (flag == 0) {
		return huge_out; 
	}
	//if flag = 1, there is a carry on MSD -> return hhuge_out2
	else {
		for (int i = 0; i < LargerLen(h); i++) {
			huge_out2.digits[i + 1] = huge_out.digits[i];
		}
		//carry term will always add a 1 to the MSD
		huge_out2.digits[0] = 1; 
		
		return huge_out2;
	}
}

HugeInteger HugeInteger::add(const HugeInteger& h){
    
    HugeInteger huge_out = HugeInteger(this->LargerLen(h));
    
    if(this->sign == 1 & h.sign == 1){
        huge_out = this->user_add(h); 
    
    }
    if(this->sign == -1 && h.sign == 1){
        huge_out = this->user_sub(h);
        if(this->IsLarger(h)){
            huge_out.sign = -1; 
            
        }
        else{
            huge_out.sign = 1; 
        }
    }
    
    if(this->sign == 1 && h.sign == -1){
        huge_out = this->user_sub(h);
        if(this->IsLarger(h)==0){
            huge_out.sign = -1; 
        }
        else{
            huge_out.sign = 1; 
        }
    }
    
    
    if(this->sign == -1 && h.sign == -1){
        huge_out = this->user_add(h); 
        huge_out.sign = -1;
    }
    
    if(huge_out.digits[0] == 0){
        huge_out.sign = 1; 
    }
    
    return huge_out;
}


int HugeInteger::IsLarger(const HugeInteger& h) {

	//returns 1 if this is larger than h
	//returns 0 if h is larger than this 

	int check=0;
	if (this->LargerLen(h) == this->length && this->LargerLen(h) != h.length) {
		check = 1;
	}

	else if (this->LargerLen(h) == h.length && this->LargerLen(h) != this->length) {
		check = 0;
	}

	else {
		for (int i = this->length - 1; i >= 0; i--) {
			if (this->digits[i] > h.digits[i]) {
				check = 1;
			}
			else if (h.digits[i] > this->digits[i]) {
				check = 0;
			}
			else {
				check = check;
			}
		}
	}

	return check;

}

int HugeInteger::LargerLen(const HugeInteger& h) {

	//returns the larger length between HI(this) and HI(h) 
	
	if (this->length >= h.length) {
		return this->length;
	}
	else {
		return h.length;
	}
}

HugeInteger HugeInteger::RemoveZeros(){
    
    string orig = "";
    int z_count=0; 
    for(int i=0; i < this->length; i++){
        if(this->digits[i] == 0)
            z_count++;
        else
            break;
    }
    
    for(int i=0;i < this->length; i++){
        orig += to_string(this->digits[i]);
    }
    
    string new_str = orig.substr(z_count); 
   
    //check to see if empty string
    //if empty: all digits = 0 and therefore huge integer = 0
    if(new_str == ""){
        new_str = "0";
    }
    
    HugeInteger out = HugeInteger(new_str);
    out.sign = this->sign; 
    
    return out; 
    
}

HugeInteger HugeInteger::user_sub(const HugeInteger& h) {
	//array size of this->HI (in case this > h) 
	HugeInteger huge_out = HugeInteger(this->LargerLen(h));
	
	
	if (this->IsLarger(h)==1) {

		for (int i = 0; i < this->length; i++) {
			huge_out.digits[i] = this->digits[i]; 
		}

		for (int i = 0; i < h.length; i++) {
			huge_out.digits[this->length - 1 - i] -= h.digits[h.length - 1 - i];
		}

		for (int i = (this->length - 1); i >= 0; i--) {
			if (huge_out.digits[i] < 0) {
			    huge_out.digits[i] += 10;
				huge_out.digits[i - 1] -= 1; 

			}
		}
	}
	
	if (this->IsLarger(h) == 0){
	    
	    huge_out.sign = -1; 
	    
	    
	    for(int i=0; i< h.length; i++){
	        huge_out.digits[i] = h.digits[i]; 
	    }
	    
	    for(int i=0; i< this->length; i++){
	        huge_out.digits[h.length - 1 - i] -= this->digits[this->length - 1 - i];
	    }
	    
	    for(int i = (h.length -1); i >= 0; i--){
	        if (huge_out.digits[i] < 0) {
			    huge_out.digits[i] += 10;
				huge_out.digits[i - 1] -= 1; 

			}
		}
        
        
    
	}
	
	HugeInteger huge_out_return = huge_out.RemoveZeros();
	
	return huge_out_return;
}

HugeInteger HugeInteger::subtract(const HugeInteger& h){
    
    HugeInteger huge_out = HugeInteger(this->LargerLen(h));
    
    if(this->sign == 1 && h.sign == 1){
        huge_out = this->user_sub(h); 
    }
    
    if(this->sign == -1 && h.sign == 1){
        huge_out = this->user_add(h); 
        huge_out.sign = -1; 
    }
    
    if(this->sign == 1 && h.sign == -1){
        huge_out = this->user_add(h); 
    }
    
    if(this->sign == -1 && h.sign == -1){
        huge_out = this->user_sub(h); 
        
        if(this->IsLarger(h)==1){
            huge_out.sign = -1;
        }
        else{
            huge_out.sign = 1;
        }
    }
    
    if(huge_out.digits[0] == 0){
        huge_out.sign = 1; 
    }
    
    return huge_out;
}


HugeInteger HugeInteger::multiply(const HugeInteger& h) {
    
    
	if (this->compareTo(h) >= 0 ){

		int** out = new int* [h.length]; 
		for (int i = 0; i < h.length; i++) {
			out[i] = new int[this->length + h.length]; 
		}
		for (int i = 0; i < h.length; i++) {
			for (int j = 0; j < (this->length + h.length); j++) {
				out[i][j] = 0;
			}
		}

		int* out2 = new int[this->length + h.length]; 
		for (int j = 0; j < this->length + h.length; j++) {
		    out2[j] = 0;
		}

		for (int i = 0; i < h.length; i++) {
			int temp1 = h.digits[h.length - 1 - i];

			for (int j = 0; j < this->length; j++) {
				int temp2 = this->digits[j];

				out[h.length - 1 - i][h.length + j - i] = temp1 * temp2; 
			}
		}

		for (int i = 0; i < h.length; i++) {
			for (int j = (this->length + h.length - 1); j >= 0; j--) {
				out2[j] += out[i][j]; 
			}
		}

		//handle carry
		for (int i = (this->length + h.length - 1); i >= 0; i--) {

			int temp = out2[i]; 
			out2[i] = out2[i] % 10; 
			out2[i - 1] += temp / 10;

		}

		string out_str = "";
		for (int i = 0; i < this->length + h.length; i++) {
			out_str += to_string(out2[i]);
		}

		HugeInteger huge1 = HugeInteger(out_str).RemoveZeros(); 

		if (this->sign == h.sign) {
			huge1.sign = 1; 
		}
		else{
			huge1.sign = -1; 
		}

		delete out; 
		delete out2; 
		
		return huge1; 
	}

	if(this->compareTo(h) == -1){

		int** out = new int* [this->length];
		for (int i = 0; i < this->length; i++) {
			out[i] = new int[this->length + h.length];
		}

		for (int i = 0; i < this->length; i++) {
			for (int j = 0; j < this->length + h.length; j++) {
				out[i][j] = 0;
			}
		}

		int* out2 = new int[this->length + h.length]; 
		for (int j = 0; j < this->length + h.length; j++) {
		    out2[j] = 0;
		}
		

		for (int i = 0; i < this->length; i++) {
			
			int temp1 = this->digits[this->length - 1 - i];

			for (int j = 0; j < h.length; j++) {
				int temp2 = h.digits[j]; 

				out[this->length - 1 - i][this->length + j - i] = temp1 * temp2; 

			}
		}

		for (int i = 0; i < this->length; i++) {
			for (int j = (this->length + h.length - 1); j >= 0; j--) {

				out2[j] += out[i][j]; 
			}
		}

		for (int i = this->length + h.length - 1; i >= 0; i--) {
			int temp = out2[i]; 
			out2[i] = out2[i] % 10;
			out2[i - 1] += temp / 10; 
		}

		string out_str = ""; 
		for (int i = 0; i < this->length + h.length; i++) {
			out_str += to_string(out2[i]);
		}

		HugeInteger huge1 = HugeInteger(out_str).RemoveZeros(); 
	
    
		if (this->sign == h.sign || huge1.digits[0] == 0) {
			huge1.sign = 1; 
		}
		else {
			huge1.sign = -1; 
		}
        
        delete out;
		delete out2; 
        
		return huge1; 

		

	}
	
	return HugeInteger("");
	

}

int HugeInteger::compareTo(const HugeInteger& h) {

	//returns 1 if this is larger than h
	//returns 0 if h is larger than this 

	int check= 0;
	if(this->sign == -1 && h.sign == 1){
	    check = -1;
	}
	else if(this->sign == 1 && h.sign == -1){
	    check = 1; 
	}
	else if (this->LargerLen(h) == this->length && this->LargerLen(h) != h.length) {
		check = 1;
	}

	else if (this->LargerLen(h) == h.length && this->LargerLen(h) != this->length) {
		check = -1;
	}

	else {
		for (int i = this->length - 1; i >= 0; i--) {
			if (this->digits[i] > h.digits[i]) {
				check = 1;
			}
			else if (h.digits[i] > this->digits[i]) {
				check = -1;
			}
			else {
				check = check;
			}
		}
	}
	
	if(this->sign == -1 && h.sign == -1){
	    check = check * -1; 
	}
	
	
	

	return check;

}

std::string HugeInteger::toString() {
	
	string output = "";

	if (sign < 0) {
		output = "-";
	}
	for (int i = 0; i < this->length; i++) {
		output += to_string(digits[i]);
	}

	/*
		for (int i = 0; i < this->length; i++) {
			output += to_string(digits[i]);
		}
	}
	else {
		for (int i = 0; i < this->length; i++) {
			output += to_string(digits[i]); 
		}
	}
	*/

	return output;
}

