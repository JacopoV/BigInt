/*
 *  BigInt.cpp
 *  BigInteger
 *
 *  Created by FOX on 02/11/10.
 *  Copyright 2010 Fox. All rights reserved.
 *
 */

#include "BigInt.h" 

BigInt BigInt::zero = BigInt(0);
BigInt BigInt::one = BigInt(1);
BigInt BigInt::two = BigInt(2);
BigInt BigInt::ten = BigInt(10);

BigInt BigInt::ConvertForPrint(){

	  BigInt base(1000000000);
	  BigInt result;

	  if(*this == BigInt::zero)
		  return BigInt::zero;
	
	  while(*this > BigInt::zero)
      {
		 BigInt tmpValue = *this % base;
         result.m_number.push_back(tmpValue.m_number[0]);
         *this /= base;
      }

	  return result;
}

BigInt::BigInt(){
	
	m_sign = true;  // positive

}

BigInt::BigInt(const int i_value){

	int val = i_value;

	if(val>=0){
		m_sign = true;			// POSITIVE
	}
	else{
		val*=-1;
		m_sign = false;			// NEGATIVE
	}

	if(val > MAX){
		ConvertToBase(val,m_number);
	}

	else{
		m_number.push_back(val);
	}

}

BigInt::BigInt(const string& i_value){

	BigInt finalValue(0);
	vector<char> i_number;
	
	unsigned int string_size = i_value.size();
	char *buffer = new char [string_size*sizeof(unsigned int)];
	strcpy_s(buffer,string_size*sizeof(unsigned int),i_value.c_str());
	
	for (unsigned int i=0; i<string_size; i++) {

		if(buffer[i]!='-')
		  i_number.push_back(buffer[i]);
	}

	if(buffer[0]=='-'){
		m_sign = false;
		string_size--;
	}
	else{
		m_sign = true;
	}

	BigInt exp(1);
	
	for (int k=string_size-1; k>=0; k--){
	
		BigInt n (i_number.at(k) - 48);
		BigInt n_value (n*exp);
		n_value.m_sign=true;
		finalValue += n_value;
		exp*= BigInt::ten ;
	}
	
	m_number = finalValue.m_number;

}

BigInt pow (const BigInt& i_value, const BigInt& i_exp){ 
	
	// base case n^0 = 1
	if (i_exp == BigInt::zero || i_value == BigInt::one) {
		return BigInt::one;
	}

	if (i_value == BigInt::zero ){
		return BigInt::zero;
	}
	
	// base for _exp > 1
	
	BigInt i(0);
	BigInt o_value (i_value);
	BigInt exp (i_exp);

	exp -= BigInt::one;
	
	/*
		ABSOLUTE VALUE
	*/

	o_value.m_sign=true;

	while(i < exp){
		o_value*=i_value;
		i++;
	}

	if(i_value.m_sign == false)
		o_value.m_sign = false;
	return o_value;
};


BigInt pow (const BigInt& i_value,const int i_exp){

	// base case n^0 = 1
	if (i_exp == 0 || i_value == BigInt::one) {
		return BigInt::one;
	}

	if (i_value == BigInt::zero ){
		return BigInt::zero;
	}
	
	// base for _exp > 1
	
	int i=0, exp = i_exp-1;
	BigInt o_value (i_value);
	
	/*
		ABSOLUTE VALUE
	*/

	o_value.m_sign=true;

	while(i < exp){
		o_value*=i_value;
		i++;
	}

	if(i_value.m_sign == false)
		o_value.m_sign = false;
	return o_value;
	
	
};
ostream& operator<<(ostream& _os, const BigInt& i_value){
	
	for (int i=i_value.m_number.size()-1; i>=0; i--){

		_os<<i_value.m_number.at(i)<<" ";
	}

	return _os;
};

BigInt& BigInt::operator+=(const BigInt& i_value){

	BigInt o_value;
	const vec* sx = &m_number;
	const vec* dx = &i_value.m_number;
	
	/*
		SX points to the biggest or equal number
	*/

	if(*this<i_value){

		sx = &i_value.m_number;
		dx = &m_number;
	}


	// VERIFY THE FINAL SIGN
	// CASE :  +  -   ||  -  +
	if(m_sign==true && i_value.m_sign==false){
		
		BigInt cp (i_value);
		cp.m_sign = true;
		*this-=cp;
		return *this;

	}
	if(m_sign==false && i_value.m_sign==true){

		this->m_sign = true;
		o_value = (*this-i_value);
		if(*this<i_value)
			o_value.m_sign = true;
		else
			o_value.m_sign = false;
		o_value.zeroSign();
		*this = o_value;
		return *this;

	}

	if(m_sign==false && i_value.m_sign==false){
		o_value.m_sign=false;
	}
	
	unsigned int report = 0;

	for(unsigned int i=0; i<sx->size(); i++){

		long long int sx_value = sx->at(i);
		long long int dx_value = 0;
		
		if(i<dx->size()){
		 dx_value = dx->at(i);
		}

		long long int sum = sx_value + dx_value;

		if(report){
			sum += 1;
			report = 0;
		}
		
		if(sum>MAX){

			o_value.m_number.push_back(sum%BASE);
			report=1;
		}
		else{
			o_value.m_number.push_back((unsigned int)sum);
		}

		if( i == sx->size()-1 && report){
			o_value.m_number.push_back(report);
		}

	}

	o_value.zeroSign();
	*this = o_value;
	return *this;
	
};

BigInt& BigInt::operator-=(const BigInt& i_value){
	
	BigInt o_value;
	const vec* sx = &m_number;
	const vec* dx = &i_value.m_number;

	if(*this<i_value){

		sx = &i_value.m_number;
		dx = &m_number;
		o_value.m_sign = false;
	}

	// VERIFY THE FINAL SIGN
	// CASE :  +  -   ||  -  +
	if(m_sign==true && i_value.m_sign==false){
		
		BigInt cp (i_value);
		cp.m_sign = true;
		*this += cp;
		return *this;
	}
	if(m_sign==false && i_value.m_sign==true){

		this->m_sign = true;
		*this = (*this+i_value);
		if(*this<i_value)
			this->m_sign = true;
		else
		    this->m_sign = false;
		this->zeroSign();
		//*this = o_value;
		return *this;
	}

	if(m_sign==false && i_value.m_sign==false){
		BigInt cp (i_value);
		cp.m_sign = true;
		o_value = (*this+cp);
		if(*this<cp)
			o_value.m_sign = true;
		else
		    o_value.m_sign = false;
		o_value.zeroSign();
		*this = o_value;
		return *this;		
	}

	
	unsigned int report = 0;

	for(unsigned int i=0; i<sx->size(); i++){

		long long int sx_value = sx->at(i) - report;
		long long int dx_value = 0;
		
		if(i<dx->size()){
		 dx_value = dx->at(i);
		}

		if(sx_value<dx_value){
			sx_value+=BASE;
			report = 1;
		}
		else{
			report = 0;
		}

		long long int sub = sx_value - dx_value;

		
		o_value.m_number.push_back((unsigned int)sub);
	
	}

	o_value.TrimZeros();
	o_value.zeroSign();
	*this = o_value;
	return *this;

};


 BigInt& BigInt::operator*=(const BigInt& i_value){

	const vec* sx = &m_number;
	const vec* dx = &i_value.m_number;
	
	/*
		SX points to the biggest or equal number
	*/

	if(sx->size()<dx->size()){

		sx = &i_value.m_number;
		dx = &m_number;
	}

	vector<BigInt> support;

	for(unsigned int i=0; i<dx->size(); i++){

		BigInt tmp;
		
		long long int report = 0;

		if(i>0){
			for(unsigned int k = 0; k<i; k++){
					tmp.m_number.push_back(0);
			}
		}

		for(unsigned int j=0; j<sx->size(); j++){

			long long int sx_value = sx->at(j);
			long long int dx_value = dx->at(i);

			long long int cross = report + sx_value * dx_value;
			
			if(cross > MAX){

				report = cross / BASE;
				tmp.m_number.push_back(cross % BASE);

			}
			else{

				tmp.m_number.push_back((unsigned int)cross);
				report = 0;
			}

			if(j == sx->size()-1 && report){
		
			   tmp.m_number.push_back((unsigned int)report);
			   report = 0;
		
		    }
			
		}	
		
		support.push_back(tmp);
	}

	this->m_number.clear();
	this->m_number.push_back(0);

	for(unsigned int i=0; i< support.size(); i++){

		*this += support.at(i);
	}

	// TRIM ZEROS
	this->TrimZeros();
	
	// VERIFY THE FINAL SIGN
	if(m_sign==false && i_value.m_sign==false || m_sign==true && i_value.m_sign==true){
		this->m_sign=true;
	}
	else{
		this->m_sign=false;
	}

	this->zeroSign();
	return *this;
};


BigInt& BigInt::operator/=(const BigInt& i_value){

	
	if (*this<i_value) {
		*this = BigInt::zero;
		return *this;
	}
	if (*this==i_value) {				
		*this = BigInt::one;
		return *this;
	}

	BigInt o_value(0);
	BigInt divider(i_value);
	int count=0;

	/*
		ABSOLUTE VALUE
	*/
	this->m_sign=true;
	divider.m_sign=true;

	while(*this > BigInt::zero)
	{
		if(*this>=divider)
		{
			*this-=divider;
			o_value+=pow( BigInt::two , count );
			divider*= BigInt::two;
			count++;
		}
		else
		{
			divider=i_value;
			count=0;
			if(*this<divider){
				*this = o_value;
				return *this;
			}
		}
		divider.m_sign = true;
	}

	// VERIFY THE FINAL SIGN
	if(m_sign==false && i_value.m_sign==false || m_sign==true && i_value.m_sign==true){
		o_value.m_sign=true;
	}
	else{
		o_value.m_sign=false;
	}

	o_value.zeroSign();
	*this = o_value;
	return *this;

};

BigInt& BigInt::operator%=(const BigInt& i_value){

	if (*this<i_value) {
		return *this;
	}
	if (*this==i_value) {
		*this = BigInt::zero;
		return *this;
	}
	
	BigInt div = *this/i_value;
	BigInt test = i_value*div;
	*this -=test;
	return *this;
	
};

bool BigInt::operator==(const BigInt& i_value) const{
	
	if(m_number.size()!=i_value.m_number.size())
		return false;
	else{

		for(unsigned int i=0; i<m_number.size(); i++){

			if(m_number.at(i)!=i_value.m_number.at(i))
				return false;

		}
		return true;
	}
	
};


bool BigInt::operator<(const BigInt& i_value) const{

	if(m_number.size()<i_value.m_number.size())
		return true;
	if(m_number.size()>i_value.m_number.size())
		return false;
	
	unsigned int countEquals = 0;
	bool min = true;

	if(m_number.size()==i_value.m_number.size()){

		for(unsigned int i=0; i<m_number.size(); i++){
		
			if(m_number.at(i) > i_value.m_number.at(i))
				min=false;
			if(m_number.at(i) < i_value.m_number.at(i))
				min=true;
			if(m_number.at(i) == i_value.m_number.at(i))
				countEquals++;
		}

		if(countEquals==m_number.size())
			min = false;
	}
	
	return min;	
};


BigInt& BigInt::operator&=(const BigInt& i_value){

	BigInt o_value;

	for(unsigned int i=0;  i<m_number.size(); i++){

		if(i < i_value.m_number.size()){
			
			long long int sx = m_number.at(i);
			long long int dx = i_value.m_number.at(i);

			o_value.m_number.push_back((unsigned int)sx&dx);
		}
		else{

			*this = o_value;
			return *this;
		}
	}

	o_value.zeroSign();
	*this = o_value;
	return *this;


};

BigInt& BigInt::operator|=(const BigInt& i_value){
	

	BigInt o_value;

	for(unsigned int i=0;  i<m_number.size(); i++){

		if(i < i_value.m_number.size()){
			
			long long int sx = m_number.at(i);
			long long int dx = i_value.m_number.at(i);

			o_value.m_number.push_back((unsigned int)(sx|dx));
		}
		else{

			*this = o_value;
			return *this;
		}
	}

	o_value.zeroSign();
	*this = o_value;
	return *this;

};


void BigInt::SlowPrint(){

	if(m_sign==false){
		cout << '-';
	}

	BigInt value(*this);
	value.m_sign=true;
	BigInt o_value = value.ConvertForPrint();

	for (int i=o_value.m_number.size()-1; i>=0; i--) {
		cout << o_value.m_number.at(i);
	}
	
}

void BigInt::DEBUG_SIGN(){

    if(!m_sign)
		cout<<"-";

}


