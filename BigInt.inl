
/*
	FRIEND FUNCTIONS
*/

#define BASE 2147483648  // MAX_INT + 1
#define MAX  2147483647

inline void BigInt::ConvertToBase(const int i_value, vec & i_number ){
	
	int val = i_value;
	while(val > 0){

		i_number.push_back(val%(BASE));
		val/=BASE;
	}
}

inline bool BigInt::PositiveSign() const{

	if (m_sign==true)
		return true; // positive
	else
		return false;// negative

}

inline BigInt& operator-(BigInt& i_value){

	if(i_value.PositiveSign()){
		i_value.m_sign=false;
	}
	else{
		i_value.m_sign=true;
	}

	return i_value;
}

inline void operator++(BigInt& i_value){

	i_value += BigInt::one;
	
}

inline void operator--(BigInt& i_value){

	i_value -= BigInt::one;

}


inline bool BigInt::operator!=(const BigInt& i_value) const{
	
	return !(*this==i_value);

};


inline BigInt& BigInt::operator++(int){

	*this += BigInt::one;
	return *this;
	
};
inline BigInt& BigInt::operator--(int){
	
	*this -= BigInt::one;
	return *this;
};

inline bool BigInt::operator<=(const BigInt& i_value) const{

	bool test1 = *this < i_value;
	bool test2 = (*this==i_value);
	
	if (test1 || test2) {
		return true;
	}
	else {
		return false;
	}

	
};

inline bool BigInt::operator>(const BigInt& i_value) const{

	if(*this==i_value)
		return false;

	return !(*this<i_value);
	
};

inline bool BigInt::operator>=(const BigInt& i_value) const{
	
	bool test1 = *this > i_value;
	bool test2 = (*this==i_value);
	
	if (test1 || test2) {
		return true;
	}
	else {
		return false;
	}
};

inline BigInt& BigInt::operator<<=(const BigInt& i_value){

	BigInt o_value = (*this)*(pow(BigInt::two, i_value));
	*this = o_value;
	return *this;
	
};

inline BigInt& BigInt::operator>>=(const BigInt& i_value){

	BigInt o_value = (*this)/(pow(BigInt::two, i_value));
	*this = o_value;
	return *this;

};

inline BigInt& BigInt::TrimZeros(){

	while(m_number.size()!=1 && m_number.at(m_number.size()-1) == 0)
	 {
		 m_number.pop_back();
	  }
	
	return *this;
}

inline BigInt& BigInt::zeroSign(){

	if(*this == BigInt::zero)
	{
		// set the positive value to zero 
		m_sign = true;
	}
	return *this;

}


// NON MEMBER FUNCTIONTS
inline BigInt operator+(const BigInt& i_value1, const BigInt& i_value2){

	BigInt o_value = i_value1;
	o_value += i_value2;

	return o_value;
};

inline BigInt operator-(const BigInt& i_value1, const BigInt& i_value2){

	BigInt o_value = i_value1;
	o_value -= i_value2;

	return o_value;
};

inline BigInt operator*(const BigInt& i_value1, const BigInt& i_value2){

	BigInt o_value = i_value1;
	o_value *= i_value2;

	return o_value;

};

inline BigInt operator/(const BigInt& i_value1, const BigInt& i_value2){

	BigInt o_value = i_value1;
	o_value /= i_value2;

	return o_value;

};

inline BigInt operator%(const BigInt& i_value1, const BigInt& i_value2){

	BigInt o_value = i_value1;
	o_value %= i_value2;

	return o_value;

};

inline BigInt operator>>(const BigInt& i_value1, const BigInt& i_value2){

	BigInt o_value(i_value1);
	o_value>>=(i_value2) ;
	return o_value;

};

inline BigInt operator<<(const BigInt& i_value1, const BigInt& i_value2){
	
	BigInt o_value(i_value1);
	o_value<<=(i_value2);
	return o_value;

};

inline BigInt operator&(const BigInt& i_value1, const BigInt& i_value2){

	BigInt o_value(i_value1);
	o_value&=(i_value2);
	return o_value;
};

inline BigInt operator|(const BigInt& i_value1, const BigInt& i_value2){

	BigInt o_value(i_value1);
	o_value|=(i_value2);
	return o_value;
};

