#include<iostream>
#include<string>
#include<math.h>
#include<vector>
#include<limits.h>
#include<algorithm>
using namespace std;

// ----------------------
// GROUP 10 : 
// Kaumudi Patil
// -----------
// RSA Algorithm
// Input : 
// M : message , character string
// e : public key, integer
// Output:
// Decrypted string
// BEARCATII data
// ---------------

#define BEARCATII_BASE 27

namespace // anonymous
{
	// Extened Euclid's GCD
	int extendedGcd(int a, int b, int &s, int &t)
	{
		if (b == 0)
		{
			s = 1;
			t = 0;
			return a;
		}
		else
		{
			int r = a % b;
			int q = a / b;
			int g = extendedGcd(b, r, s, t);
			int stemp = s;
			s = t;
			t = stemp - t * q;
			return g;
		}

	}

	unsigned long long int powerMod(unsigned long long int base, unsigned long long int exp, unsigned long long int modN)
	{
		unsigned long long int result = base % modN;
		for (int inx = 2; inx <= exp; inx++)
		{
			result = (result*base) % modN;
		}
		return result;
	}

	// Naive Power 
	unsigned long long int power1(unsigned long long int base, unsigned long long int powers)
	{
		if (powers == 1)
			return (base);
		else if (powers % 2 == 0)
			return(power1(base*base, powers / 2));
		else
			return(base*power1(base*base, (powers - 1) / 2));

	}
	/* Naive Prime function : 
	bool isPrime(long int a)
	{
		int b, c;
		b = sqrt(a);
		for (c = 2; c <= b; c++)
		{
			if (a%c == 0)
			{
				return false;
			}
		}
		return true;

	}*/


/* Miller-Rabin Test :
  Refered from https://www.geeksforgeeks.org/primality-test-set-3-miller-rabin/
*/
	// It returns (x^y) % p 
	int power(int x, unsigned int y, int p)
	{
		int res = 1;      // Initialize result 
		x = x % p;  // Update x if it is more than or 
					// equal to p 
		while (y > 0)
		{
			// If y is odd, multiply x with result 
			if (y & 1)
				res = (res*x) % p;

			// y must be even now 
			y = y >> 1; // y = y/2 
			x = (x*x) % p;
		}
		return res;
	}

	// This function is called for all k trials. It returns 
	// false if n is composite and returns false if n is 
	// probably prime. 
	// d is an odd number such that  d*2<sup>r</sup> = n-1 
	// for some r >= 1 
	bool miillerTest(int d, int n)
	{
		// Pick a random number in [2..n-2] 
		// Corner cases make sure that n > 4 
		int a = 2 + rand() % (n - 4);

		// Compute a^d % n 
		int x = power(a, d, n);

		if (x == 1 || x == n - 1)
			return true;

		// Keep squaring x while one of the following doesn't 
		// happen 
		// (i)   d does not reach n-1 
		// (ii)  (x^2) % n is not 1 
		// (iii) (x^2) % n is not n-1 
		while (d != n - 1)
		{
			x = (x * x) % n;
			d *= 2;

			if (x == 1)      return false;
			if (x == n - 1)    return true;
		}

		// Return composite 
		return false;
	}

	// It returns false if n is composite and returns true if n 
	// is probably prime.  k is an input parameter that determines 
	// accuracy level. Higher value of k indicates more accuracy. 
	bool isPrime(int n, int k)
	{
		// Corner cases 
		if (n <= 1 || n == 4)  return false;
		if (n <= 3) return true;

		// Find r such that n = 2^d * r + 1 for some r >= 1 
		int d = n - 1;
		while (d % 2 == 0)
			d /= 2;

		// Iterate given nber of 'k' times 
		for (int i = 0; i < k; i++)
			if (!miillerTest(d, n))
				return false;

		return true;
	}
/*---------------------Miller-Rabin End-----------------------*/

	unsigned long long int getRandomPrime( int bitLen)
	{
		unsigned long long int num = 1;
		int constant = 51;
		bool is_prime = false;
		if (bitLen < 2)
			bitLen = 2;
		while (!is_prime)
		{
			num = rand() % power1(10,bitLen) + constant;
			long long int m = num - 1;
			while (m % 2 == 0)
				m /= 2;
			
			if(isPrime(num, 4))
			{
				is_prime = true;
				return num;
			}
			else
			{
				is_prime = false;
			}
		}
	}

	/*Referred for concepts from
	https://www.geeksforgeeks.org/multiplicative-inverse-under-modulo-m/
	*/
	unsigned long long int inverseMod(long long int e, long long int modN)
	{
		e = e % modN;
		for (int i = 1; i < modN; i++)
		{
			if ((e*i) % modN == 1)
				return i;
		}
		return 1;
	}


} // namespace anonymous end
class Bearcatii
{
public:
	Bearcatii(const char* str, int l)
	{
		unsigned long long int sum = 0;
		for (int i = 0; i < l; i++)
		{
			// TODO : Convert to upper case
			// multiply by 27 ^i
			int decimal_char = str[i];
			if (decimal_char == 32) {
				decimal_char = 0;
				continue;
			}
			else
				decimal_char = (int)str[i] - 64;
			sum += decimal_char * (int)pow(BEARCATII_BASE, (l - 1 - i));
		}
		decimal = sum;
	}
	void printD()
	{
		cout << "Decimal rep  " << decimal;
	}
	int getMsgLen() // Returns bit length of  the number
	{
		return log2(decimal) + 1;
	}
	long int getMsg() // Returns bit length of  the number
	{
		return decimal;
	}
	void getDecimalToMsg(unsigned long long int a) // , string &m)
	{
		std::vector<char> msg;
		while (a > 0)
		{
			int rem = a % BEARCATII_BASE;
			if (rem == 0)
			{
				msg.push_back(' ');
			}
			else
			{
				char a1 = (char)rem + 64;
				msg.push_back(a1);
			}
			a /= BEARCATII_BASE;
		}
		// Reverse string
		reverse(msg.begin(), msg.end());
		string finals(msg.begin(), msg.end());
		cout << endl<<finals<<endl;
		
	}

private:
	unsigned long long int decimal;
};

int main()
{
	int cnt = 5; // For test cases
	while (cnt > 0)
	{
		cout << "Test Case\n -------------\n";
		// Get plaintext msg
		string msg;
		// Conver to Uppercases
		transform(msg.begin(),msg.end(), msg.end(), ::toupper);
		unsigned long long int e = 0;
		cout << "Enter message : ";
		cin >> msg;

		// Get BEARCATII
		Bearcatii bMsg(msg.c_str(), msg.length());
		bMsg.printD();

		// n = p*q
		// Get bit length to and set p and q digit length
		// to len(M)/2
		// So that we can generate n greater than m(decimal)
		int  lenP = bMsg.getMsgLen()/2 + 1;
		unsigned long long int p = 0;
		p = getRandomPrime(lenP);
		unsigned long long int q = 0;
		q = getRandomPrime(lenP);
		//cout << "P   : " << p;
		//cout << "\nq  : " << q;
		unsigned long long int plaintextDecimal_n = 0, totient_phiN = 1;
		plaintextDecimal_n  = p * q;
		totient_phiN = (p - 1)*(q - 1);

		int g = 0;
		do {
			// Get public key
			cout << "\nEnter public key: ";
			cin >> e;
			//gcd function
			int s = 0; int t = 0;
			// get larger first
			unsigned long long int x1 = totient_phiN;
			unsigned long long int a = x1 > e ? x1 : e;
			unsigned long long int b = (x1 + e) - a;
			// get gcd ( n, e) as 1
			g = extendedGcd(a, b, s, t);
		} while (g != 1);

		// RSA Algorithm

		unsigned long long int privateKey_d = inverseMod(e, totient_phiN);
		
		// Encryption
		//c =  m^e mod n
		cout << "\nEncrypting Data..\n";
		unsigned long long int cipher = powerMod(bMsg.getMsg(), e, plaintextDecimal_n);

		// Decryption 
		// c^d mod n
		cout << "\nDecrypted string is : ";
		unsigned long long int decryptedDecimal = powerMod(cipher, privateKey_d, plaintextDecimal_n);
		
		// Get decrypted message to readable alphabets
		bMsg.getDecimalToMsg(decryptedDecimal);

		cnt--; // for test-case count
	}
	//system("pause");
	return 0;
}


/*
OUTPUT:
Test Case
-------------
Enter message : TEST
Decimal rep  397838
Enter public key: 5

Encrypting Data..

Decrypted string is :
TEST
Test Case
-------------
Enter message : RESTS
Decimal rep  9678763
Enter public key: 21

Enter public key: 4

Enter public key: 17

Encrypting Data..

Decrypted string is :
RESTS
Test Case
-------------
Enter message : JO
Decimal rep  285
Enter public key: 6

Enter public key: 7

Encrypting Data..

Decrypted string is :
JO
Test Case
-------------
Enter message : DONE
Decimal rep  90050
Enter public key: 3

Enter public key: 7

Encrypting Data..

Decrypted string is :
DONE
Test Case
-------------
Enter message : QWERT
Decimal rep  9491357
Enter public key: 7

Encrypting Data..

Decrypted string is :
QWERT
Press any key to continue . . .

*/
