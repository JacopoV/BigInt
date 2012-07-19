#include "BigInt.h"
#include "time.h"
#include <bitset>



int main () {
    
	clock_t ticks1, ticks2;
	
	

	cout<<"\n\nTest Suite for BigInt :\n"<<endl;

	cout<<"\nDo you want to print the results? (coded in base 2147483648) : \n(Y = YES / N = NO)\n----> ";
	
	char in;
	bool print;
	cin >> in ;
	cout<<"\n";

	if(in == 'Y')
		print = true;
	else
		print = false;

	

	cout<<"- division"<<endl;
	BigInt a ("21742178472138971249812481241921247129417284184124719417471");
	BigInt b (5);

	cout << "value a: "<< a << endl;
	cout << "value b: "<< b << endl;

	ticks1=clock();
	a/=b;
	ticks2=clock();
	cout << "operation time (ms) : " << ticks2-ticks1<<endl;
	if(print)
	 cout << "result : " << a <<endl;


	cout<<"\n- multiplication"<<endl;
	BigInt z1 ("-483249324");
	BigInt z2 ("321321312331");

	cout << "value a: "<< z1 << endl;
	cout << "value b: "<< z2 << endl;

	ticks1=clock();
	z1-=z2;
	ticks2=clock();
	cout << "operation time (ms) : " << ticks2-ticks1<<endl;
	if(print)
	 cout << "result : " << z1 <<endl;
	
	
	cout<<"\n- pow"<<endl;
	BigInt x ("4214432433");
	BigInt y (5424);

	cout << "value a: "<< x << endl;
	cout << "value b: "<< y << endl;

	ticks1=clock();
	x=pow(x,y);
	ticks2=clock();
	cout << "operation time (ms) : " << ticks2-ticks1<<endl;
	if(print)
	 //cout << "result : " << x <<endl;


	cout<<"\n- sum"<<endl;
	BigInt s1 ("58932785918745932751238957382915718957238957385473895718325789257328141");
	BigInt s2 ("72314821738921738217382137218937812937981273821372918372189378921372819371289371289378127839");

	cout << "value a: "<< s1 << endl;
	cout << "value b: "<< s2 << endl;

	ticks1=clock();
	s1+=s2;
	ticks2=clock();
	cout << "operation time (ms) : " << ticks2-ticks1<<endl;
	if(print)
	 cout << "result : " << s1 <<endl;

	cout<<"\n- subtract"<<endl;
	BigInt p1 ("5832798327892374892314");
	BigInt p2 ("324671264172864127846172");

	cout << "value a: "<< p1 << endl;
	cout << "value b: "<< p2 << endl;

	ticks1=clock();
	p1-=p2;
	ticks2=clock();
	cout << "operation time (ms) : " << ticks2-ticks1<<endl;
	if(print)
	 cout << "result : " << p1 <<endl;


	cout<<"\n- shift"<<endl;
	BigInt r1 ("2132132131");

	cout << "value a: "<< r1 << endl;

	ticks1=clock();
	BigInt one (1);
	BigInt r2 = r1<<one;
	ticks2=clock();
	cout << "operation time (ms) : " << ticks2-ticks1<<endl;
	if(print)
	 cout << "result : " <<	r2 <<endl;
	

    return 0;



}
