#include <iostream>
//#include <cmath>
#include <string>
#include <vector>
//#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <iomanip>    /* time */
//#include <sstream>
#include <limits>
using namespace std ;

// using ints not chars in * as int is done on the level of hardware(less processing) whereas chars 'll be done in software (more processing) 

// when calling a fn on a const object >> it must be a const fn 

// don't return a local variable by refrence as it'll be forcibly emmitted from memory before returning it

const int base_num = 10;


// class Big_Number;

// class Division_Result
// {
// private:
//  Big_Number *Result = new Big_Number();
// Big_Number *Remainder new Big_Number;

// public:
// 	void set_Result_and_Remainder(Big_Number& res , Big_Number& rem)
// 	{
//  *Result = res;
//  *Remainder = rem;
// 	}
// const Big_Number get_Result()
// {
// 	return Result;
// }
// const Big_Number get_Remainder()
// {
// 	return Remainder;
// }

// };



class Big_Number
{


private:

	vector<char> digits;
	unsigned int digits_num ;
	unsigned int k ;
	char my_sign;

public:


unsigned int get_K()
{
return k;
}

char get_sign()
{	return my_sign ;
}
	Big_Number(int num) // Default Constructor
	{
	k=0;		//digits.resize(1);
	digits_num=0;
	my_sign='+';
	// handle least-significant digit of num (handles num == 0)
	//AddSigDigit(num % base_num);
	//num = num / base_num;
	// handle remaining digits of num
	while (num != 0)
	{
	AddSigDigit(num % base_num);
	num = num / base_num;
	}
	}



Big_Number(string st) // string Constructor
	{
		k=0;
		//digits.resize(1);
		digits_num=0;
		my_sign='+';
		if (st.length() == 0)
		{

		AddSigDigit(0);
		return;
		}

		
		for(int k=st.length() - 1; k >= 0; k--)
		{
		if (! isdigit(st[k]))
		{
		cout<< "badly formed Big_Number value = " << st << endl;
		abort();
		}
		AddSigDigit(st[k]-'0');
		}
		//Normalize();

	}



	void Add_Big( const Big_Number & rhs)  
	{

	int sum;
	int carry = 0;
	int len = NumDigits(); // length of larger addend
	
//	clock_t tStart = clock();


	 if ( IsNegative() != rhs.IsNegative()) // signs not the same, subtract
	{
	//cout<<"hhhh";
	Big_Number rhs_copy(rhs); 

	rhs_copy.Toggle_Sign();

	this->Sub_Big(rhs_copy);
	
	//rhs.Toggle_Sign();
	return ;
	
	}

	
	if (len < rhs.NumDigits())
	{
	len = rhs.NumDigits();
	}


	for(int k=0; k < len; k++)
	{
	sum = GetDigit(k) + rhs.GetDigit(k) + carry;
	carry = sum / base_num;
	sum = sum % base_num;
	
	if (k < digits_num)
	{

	ChangeDigit(k,sum);//    ????????????????????????????????????????????????????????????????
	}
	else
	{
	AddSigDigit(sum);
	}
	}

	
	if (carry != 0)
	{
	AddSigDigit(carry);
	}

	// printf("Time taken: %.4fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
	return  ;

	}	




	void Sub_Big( const Big_Number & rhs)
	{
	
		//clock_t tStart = clock();
	
	int diff;
	int borrow = 0;
	//int len = NumDigits();

	// signs opposite? then lhs - (-rhs) = lhs + rhs
	//  -lhs - (rhs)
	if (IsNegative() != rhs.IsNegative())               //*******************************
	{

	Big_Number	rhs_copy(rhs);
	rhs_copy.Toggle_Sign();
	this->Add_Big( rhs_copy ); // signs add ?????????????????????????????????? Sum takes the sign of the left operand
	
	return;
	//return *this;
	}

	// signs are the same, check which number is larger
	// and switch to get larger number "on top" if necessary
	// since sign can change when subtracting
	// examples: 7 - 3 no sign change, 3 - 7 sign changes
	// -7 - (-3) no sign change, -3 -(-7) sign changes
	
	if ( !IsNegative() && this->LessThan(rhs) || IsNegative() && this->LessThan(rhs))
	{

	Big_Number	rhs_copy(rhs);
	
	rhs_copy.Sub_Big(*this);

	*this = rhs_copy;
	//this->Print(cout);

	 this->Toggle_Sign();
	
	return;
	//return *this;
	}

	// same sign and larger number on top
	for(int k=0; k < NumDigits()   /* len*/; k++)
	{
	diff = GetDigit(k) - rhs.GetDigit(k) - borrow;
	borrow = 0;
	if (diff < 0)
	{
	diff += 10;
	borrow = 1;
	}
	ChangeDigit(k,diff);
	}

	Normalize();
	//return *this;
//printf("Time taken: %.4fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
	}	


	const Big_Number  Times_Big (const Big_Number & rhs)
	{
	//clock_t tStart = clock();
	
	
	Big_Number sum(""); // to accumulate sum

	//sum.digits.resize(rhs.NumDigits()+this->NumDigits() );
		
	Big_Number left =*this;     // bigger in numb of digits
	Big_Number right = rhs ;

	if(left.NumDigits() < right.NumDigits())
	{
		left = rhs ;
		right = *this ;

	}

			
	string st = right.ToString() ;
	
	unsigned long long cc ;

	for( int k =st.length()-1 ; k >= 0 ; k-=18)
	{
		cc =stoull(st.substr(k<18 ? 0 : k-17 ,  k<18 ? k+1: 18 ))  ;
		Big_Number c = left.Times_int(cc) ; 
		sum.Add_Big(c); // k-th digit * self

		//if(k > 0)
	 left.AddS_Zeros_right(18); 
	 
	
	 //same.destruct;
	}
	

  if( this->IsNegative() != rhs.IsNegative() )
			{//	sum.Print(cout);
				sum.Toggle_Sign();
				//cout<<"entered\n";	

			}


 //printf("Time taken: %.3fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
	return sum;

	
	}	





 Big_Number Times_int(unsigned long long num) const
// postcondition: returns num * value of BigInt after multiplication
	{
		
	unsigned long long carry = 0;
	
	unsigned long long product ; // product of num and one digit + carry
	
	if (0 == num || this->Big_Equal_small(0)) // treat zero as special case and stop
	{

	Big_Number zero("");
	return zero;

	}


	Big_Number self = *this ; // copy of self    ???????????
	self.my_sign='+';
	
	if (1 == num) // treat one as special case, no work
	{

	return self;
	}



	//string st = self.ToString();


	for(int k=0; k <NumDigits() ;  k++) // two for each digit//5
	{		

	product = num *GetDigit(k) + carry ;

	carry = product/base_num ; //226
	self.ChangeDigit (k , product % base_num);//8


	}

	while (carry != 0) // carry all digits
	{
	self.AddSigDigit(carry % base_num);
	carry /= base_num;
	}

	return self;
	}



	
	

int NumDigits() const 
{
return digits_num;
}


void AddSigDigit(int value)
{
if( 9>= value >=0 )
{
	//char x =; // pushback  0 if its >1 
digits.insert ( begin(digits) + digits_num ,  '0' + value  );
digits_num++;
}

}


int GetDigit(int k) const 
{
if (0 <= k && k < NumDigits())
{
return (digits[k]) - '0';
}
return 0;
}


void ChangeDigit(int k, int value)
{
if (0 <= k && k < NumDigits())
{
digits[k] = char('0' + value);
}
else
{
	//this->AddSigDigit(value);
//cout<< "error changeDigit " << k << " " << digits_num << endl;
}
}


bool LessThan(const Big_Number & rhs) const
{

// if # digits aren’t the same must check # digits and sign
if (NumDigits() != rhs.NumDigits())
{

return (NumDigits() < rhs.NumDigits());

}
// assert: # digits same 

//int len = ;
for(int k=NumDigits()-1; k >= 0; k--)
{
if (GetDigit(k) < rhs.GetDigit(k))
 {	return true ; 
 }
 else if (GetDigit(k) > rhs.GetDigit(k))
 {	return false ; 
 }
}
return false ; // means equals
}


bool BiggerThan(const Big_Number & rhs) const
{

// if # digits aren’t the same must check # digits and sign
if (NumDigits() != rhs.NumDigits())
{

return (NumDigits() > rhs.NumDigits());

}
// assert: # digits same 

//int len = ;
for(int k=NumDigits()-1; k >= 0; k--)
{
if (GetDigit(k) > rhs.GetDigit(k))
 {	return true ; 
 }
 else if (GetDigit(k) < rhs.GetDigit(k))
 {	return false ; 
 }
}

return false ; // means equals
}





const Big_Number  Remainder_or_Mod ( Big_Number * divisors , int NumDigits) // can get remainder or division result
{
	// check if B = zero or -ve
	//clock_t tStart = clock();

 //printf("Time taken: %.3fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

	//divisors[2].Print(cout);
	//cout<<"\n";

	//try{

	int y = this->NumDigits() ; // 11

	string st = this->ToString();
	
	
	Big_Number remainder(st.substr(0, NumDigits)); // can be string comparison instead of constructing Big number to compare  @@@@@
	
	int z=0 ;

// 		3 < 4
	while (NumDigits < y+1)
	{
		
	
		if(! remainder.LessThan(divisors[0]))//remainder > divisor
		{
			//cout<<"2\n";
		while(remainder.BiggerThan( divisors[z] ))
				z++ ;

			remainder.Sub_Big(divisors[z-1]);// z=3

			z=0;
		}

	//	remainder.Print(cout);
		//if(x<y)
		remainder.AddSigDigit_right(st[NumDigits]);
		//cout<<x<<"\n";
	remainder.Normalize();
			NumDigits++;
		}
return remainder;
	//}

// catch(int e){

// cout << "An exception occurred. Exception Nr. " << e << '\n';
// }



}




 vector<Big_Number> divide_by_Big (const Big_Number & B) // can get remainder or division result
{
	// check if B = zero or -ve
	//clock_t tStart = clock();

	if(B.Big_Equal_small(0))
	{
		cout<<"Invalid Divison by Zero !";
		abort();
		
	}


	Big_Number result("");   // @@@@@
	

	if(	IsNegative() != B.IsNegative())
		result.my_sign= '-';
	else 
		result.my_sign='+';

	
	
	int x = B.NumDigits() ; //  1
	int y = this->NumDigits() ; // 4

	string st = this->ToString();

	Big_Number remainder(st.substr(0,x)); // can be string comparison instead of constructing Big number to compare  @@@@@

	int q = 0 ;
	
// 			1 < 4
	while (x < y+1)
	{

		while(! remainder.LessThan(B))
		{
			q++ ;
			remainder.Sub_Big(B);

		}
			

			result.AddSigDigit_right(char(q+'0')); //from right
			//03
			q=0;
		
			remainder.AddSigDigit_right (st[x]);// from right
	
			remainder.Normalize();

			x++;
	
}

result.Normalize();
 
//Division_Result dr ();

//dr.set_Result_and_Remainder(result, remainder);
//*this = remainder;
 vector<Big_Number> R;
 R.insert(begin(R), result);
 R.insert(begin(R)+1,remainder);
//printf("Time taken: %.3fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

return R;//new Big_Number[2]{ result, remainder};



}





 void AddSigDigit_right (char x) // from righ    ?????????????????????????????  Problem
 {

if(isdigit(x))
{

digits_num++;

 digits.insert(begin(digits), x);
	
}
	}


 void AddS_Zeros_right (int count) // from righ    ?????????????????????????????  Problem
 {

	for (int i = 0; i < count ; ++i)
 	digits.insert(begin(digits) , '0');

	digits_num += count ;

}


//     //return A-floor(A/B)*B; mod



void Normalize()
// postcondition: all leading zeros removed
{

for(int k =NumDigits()-1; k >= 0; k--) // find a non-zero digit
{

if(k==0)
	break;
else if (GetDigit(k) != 0) 
	break;
	
digits_num--; // "chop" off zeros


}
//digits.resize(digits_num*2);



}





void Print(ostream & os) const
// postcondition: BigInt inserted onto stream os
{
os << this->my_sign<<ToString()+"\n";
}


string ToString() const
// postcondition: returns apstring equivalent of BigInt
{


string s = "";

for(int k= NumDigits() -1; k >= 0; k--)
{

s += char('0'+GetDigit(k));
}
return s;
}



bool isPrime() // miller rabin test
{

	int x =this->GetDigit(0);
	

	 if(this->Big_Equal_small(1))
		return false;
	
	else if(this->Big_Equal_small(2) || this->Big_Equal_small(3))
		return true;
	
	else if(x%2 ==0)// the start char is 0 or 2 or 4 or even >>> not prime
	return false;

	else
	{

		Big_Number a (2) ;// zero

		Big_Number Q = this->Get_Q_from_Prime();

		unsigned int K = this->get_K();
		
		Big_Number same_1 = *this;

		same_1.Sub_Big(Big_Number(1));
		
		Big_Number total_pow = Q ;

		bool flag =false;

		for (int i = 0; i < 2; i++)
		{
			if(i == 1)
			a = Big_Number(3) ; 


		if(a.Pow_Big( Q , *this).Big_Equal_small(1) )
				continue ;
			
		else
		{
			if(a.Pow_Big( Q , *this).Big_Equal_Big(same_1))
					continue ;

			for (int i = 0; i < K; ++i)
			{	
				
				total_pow = total_pow.Times_int(2);

				if(a.Pow_Big(total_pow , *this).Big_Equal_Big(same_1))	// check if = p-1
				{flag=true;
					break ;}
			}
				if(!flag)
				return false;
		}

		 total_pow = Q ;
		
		}
		
		
		return true;

	}

}




  Big_Number Pow_Big( const Big_Number & power , const Big_Number & mod) 
 {
 	//Big_Number pow_Binary = power.Convert_Big_into_Big_Binary(power.isOdd()) ;

		//clock_t tStart = clock();	
// envitable to occur each calc for calculations of higher powers and tesitng
 	Big_Number accumlator(1);
	Big_Number divider(2);
	Big_Number same (*this) , pow (power);
	vector<Big_Number>  R ;

	Big_Number * divisors  = new Big_Number[10]{mod  , mod.Times_int(2) , mod.Times_int(3) ,mod.Times_int(4),mod.Times_int(5),mod.Times_int(6) , mod.Times_int(7) , mod.Times_int(8),mod.Times_int(9),mod.Times_int(10)}  ;


	int num_digits= mod.NumDigits() ;

	//for (int i = 0 ; i < pow_Binary.NumDigits(); i++)


	while(! pow.Big_Equal_small(0) )
	{
	
	//clock_t tStart = clock();
	
		same = ( same.Remainder_or_Mod( divisors , num_digits));  //  308 mod 155
 	
		R = pow.divide_by_Big(divider);
	
		pow = R[0];
		
		if( R[1].GetDigit(0) == 1)
		{
		
			accumlator = accumlator.Times_Big(same);	// the most time - consumping line

		accumlator=	(accumlator.Remainder_or_Mod(divisors , num_digits)); //  308 mod 155



		}	
			
		same = same.Times_Big(same);
			

		
	}
 

 	return accumlator ;


 }




bool isOdd() const
{
 
 	int f = (this->digits[0] )- '0';
 	
  if( f % 2 == 1)
	return true;

	return false;
}


const Big_Number  Get_Q_from_Prime()
{
	
	std::vector<Big_Number> R;
	Big_Number power_2(2);

	Big_Number result = *this ;
	result.Sub_Big(Big_Number(1));

	unsigned int counter =0;

	while(! result.isOdd())
	{
		
	 R = result.divide_by_Big(power_2);
		result =R[0];
		counter++;  // problem if the number needs big power to dvide ???????	
	
	}
	
	this->k = counter;

return result;


}


bool Big_Equal_small(int x) const
{

	if (1 != this->NumDigits() )
		return false;
	
	return (this->GetDigit(0) == x) ;

}


bool Big_Equal_Big (const Big_Number & rhs)
{

if(NumDigits() != rhs.NumDigits())
	return false ;

for (int i = 0; i < NumDigits() ; ++i)
{
	if(digits[i] != rhs.digits[i] )
		return false ;
}

return true ;

}




bool IsNegative() const
// postcondition: returns true iff BigInt is negative
{
	if(this->my_sign == '-')
	return true ;
	else 
		return false ;
}

void Toggle_Sign() //const
{
	if(IsNegative())
	{	
		my_sign = '+';
	}
	else
	{
	my_sign = '-' ;
	}

}

};

const Big_Number EXTENDED_EUCLID  ( const Big_Number  & E ,const Big_Number & PhiOfN)//e=7>>d=23  phi =160
{
	Big_Number q(""),trial("");// 0

	Big_Number a2(q),a3(PhiOfN),b1(q),b3(E),c(q) ,One("1") ;
	
	Big_Number a1(One),b2(One)  ;

	std::vector<Big_Number>R;

	while(!b3.Big_Equal_small(1))// if no inverse >>>>Infinite loop 
	{	
		R=a3.divide_by_Big(b3);  //*******************
		q=R[0];
		
		//a1.Print(cout);
		c=b1;
		a1.Sub_Big(q.Times_Big(b1));
		b1=a1;
		a1=c;

		
		
		c=b2;
		a2.Sub_Big(q.Times_Big(b2) );
		b2= a2;
		a2=c;
		
	

		c=b3;
		a3.Sub_Big(q.Times_Big(b3));  //  + sub - 
		b3= a3;
		a3=c;
	



	}

	//b2.Print(cout);
	return b2 ;


}



int main ()
{
//EXTENDED_EUCLID(Big_Number("550") , Big_Number("1759")).Print(cout);
// Big_Number b("1");
//  Big_Number a("339");    // 1  *  -339 = 339  , -1 * 339 =-339
// b.Print(cout);

//  a.Toggle_Sign();
//  a.Print(cout);

//  b.Times_Big(a).Print(cout);
// a.Print(cout);




  string P,Q,E ;

  cin>>P>>Q>>E;

	P = P.substr(2);
	Q = Q.substr(2);
	E = E.substr(2);
	
	Big_Number PB (P), QB(Q),EB(E),DB(""),N(DB),PhiOfN(DB) ,One("1");
        


//PB.Remainder_or_Mod(QB).Print(cout);
//cout<<PB.LessThan(QB);


     string req,message ; 
     bool x,y;
      
	

      while(1)
    {
      	cin>>req ;
      

      if(req == "IsPPrime")
      {
      	 clock_t tStart = clock();
      if(PB.isPrime()) // 70 sec
      {cout<<"Yes\n";
      	y=true;

      }
      else
      {	 cout<<"No\n";
  		y=false;
		}

		printf("Time taken: %.3fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
      }
      else if(req =="IsQPrime" ) //9 min
      {
      	 clock_t tStart = clock();
      	if(QB.isPrime())
 		{cout<<"Yes\n";
			x=true;
		}
      else
      	{ cout<<"No\n";
  			x=false;
     	 }

printf("Time taken: %.3fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
  		}
       else if(req == "PrintN")
      { clock_t tStart = clock();
		//	EB.isPrime();
      	N = PB.Times_Big(QB);
      	N.Print(cout);

      	printf("Time taken: %.3fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
      }
       
       else if( req =="PrintPhi")
      { clock_t tStart = clock();
      	if(x&&y)
      	{
      		PB.Sub_Big(One);
      		QB.Sub_Big(One);
      		PhiOfN = QB.Times_Big(PB);
      		 PhiOfN.Print(cout);
      	}
printf("Time taken: %.3fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
      } 
 		else if( req =="PrintD") // with PhiOfN
      {	//error   D= -ve
      	 clock_t tStart = clock();
      	DB = EXTENDED_EUCLID(EB , PhiOfN);
      	if(DB.get_sign() =='-')
      		DB.Add_Big(PhiOfN);

      	DB.Print(cout);

      	printf("Time taken: %.3fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

      } 
      else if( req.substr(0,15)=="EncryptPublic=<")
      { clock_t tStart = clock();
      	 message = req.substr(15);
      	message.pop_back();
      	Big_Number MB(message);
      	MB.Pow_Big(EB , N).Print(cout);
      	printf("Time taken: %.3fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

      } 
      else if( req.substr(0,16) =="EncryptPrivate=<")
      { clock_t tStart = clock();

	 message = req.substr(16);
      	message.pop_back();
      	Big_Number MB(message);
      	MB.Pow_Big(DB , N).Print(cout);
      	printf("Time taken: %.3fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
      	
      } 
      else if( req =="Quit")
      {
      		break;

      }
  		}
     



cout<<"\n\n\t^_^   Done  ^_^\n" ;
//cout <<mymod(15,4) ;
 

	return 0;

}

 