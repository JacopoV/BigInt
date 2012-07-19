#include<iostream>
#include<vector>

using namespace std;


typedef vector<unsigned int> vec;

class BigInt{
	
public:

	//EXTERNAL FUNCTIONS
	friend BigInt pow (const BigInt&,const BigInt&);
	friend BigInt pow (const BigInt&,const int);
	friend BigInt& operator-(BigInt&);		// SIGNED / UNSIGNED operator
	friend void operator++(BigInt&);		// prefix ++
	friend void operator--(BigInt&);		// prefix --
	friend ostream& operator<<(ostream&, const BigInt&);
	
	//CTOR / DTOR
	BigInt();								//standard ctor
	explicit BigInt(const int);						//ctor for long long
	explicit BigInt(const string&);					//ctor for string
									
	//OPERATOR +=
	BigInt& operator+=(const BigInt&);

	//OPERATOR -=
	BigInt& operator-=(const BigInt&);

	//OPERATOR *=
	BigInt& operator*=(const BigInt&);

	//OPERATOR /=
	BigInt& operator/=(const BigInt&);

	//OPERATOR %=
	BigInt& operator%=(const BigInt&);

	//OPERATOR == / !=
	bool operator==(const BigInt&) const;
	bool operator!=(const BigInt&) const;

	//OPERATOR ++ --
	BigInt& operator++(int);
	BigInt& operator--(int);
	
	//OPERATOR < / >
	bool operator<(const BigInt&) const;
	bool operator<=(const BigInt&) const;
	bool operator>(const BigInt&) const;
	bool operator>=(const BigInt&) const;

	//OPERATOR SHIFTING
	BigInt& operator<<=(const BigInt&);
	BigInt& operator>>=(const BigInt&);

	//OPERATOR && ||
	BigInt& operator&=(const BigInt&);
	BigInt& operator|=(const BigInt&);

	// DEBUG FUNCTIONS
	void SlowPrint();
	void DEBUG_SIGN();
	
private:
	
	static BigInt zero;
	static BigInt one;
	static BigInt two;
	static BigInt ten;

	bool m_sign;					    // true = positive , false = negative
	vec m_number;						// rappresentation of a number 
	
	BigInt& TrimZeros();
	BigInt& zeroSign();					// set positive sign to zero values
	void ConvertToBase(const int, vec&);
	BigInt ConvertForPrint();			// convert to base ten before printing the value with decimal base
	bool PositiveSign() const;			// check if the numeber has positive sign
	
};

BigInt operator+(const BigInt&, const BigInt&);
BigInt operator-(const BigInt&, const BigInt&);
BigInt operator*(const BigInt&, const BigInt&);
BigInt operator/(const BigInt&, const BigInt&);
BigInt operator%(const BigInt&, const BigInt&);
BigInt operator<<(const BigInt&, const BigInt&);
BigInt operator>>(const BigInt&, const BigInt&);
BigInt operator&(const BigInt&, const BigInt&);
BigInt operator|(const BigInt&, const BigInt&);

#include "BigInt.inl"






