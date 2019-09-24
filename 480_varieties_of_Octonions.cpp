// 480_varieties_of_Octonions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

/* 
int main()
{
    std::cout << "Hello World!\n";
}
*/



#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using std::cout;
using std::setw;
using std::ostream;

struct fail {
	fail(char const* const m)
	{
		cout << "\n\n *** fail *** " << m << " *** \n\n";
	}
};

#include "raw_mult.h"
#include "octonion.h"

octonion const a{ +0.1102, +2.1444, +0.3271, -3.0073, -0.5028, +2.5546, +2.0196, -2.2802 };
octonion const b{ -3.0707, +2.8979, -2.2969, -0.7543, +1.8099, +0.4488, +2.2909, +0.0866 };
octonion const c{ +3.6636, +3.4529, -0.5472, +1.1329, +3.4134, +2.6410, -1.5240, -0.6316 };

double const a_abs{ a.abs() };
double const b_abs{ b.abs() };
double const c_abs{ c.abs() };

#include "demo.h"

int main(void) 
{
	cout.setf(std::ios::fixed, std::ios::floatfield);
	cout.precision(6);

	cout << "\n ";
	cout << "\n a: " << a << " abs = " << a_abs;
	cout << "\n b: " << b << " abs = " << b_abs;
	cout << "\n c: " << c << " abs = " << c_abs;

	//    demo1 (409);

	demo1(352);

	//    demo1 ( 75);

	//    demo2 ();

	//    demo3 ();

	//    demo4 ();

	//    demo5 ();

	cout << "\n\n";
	return 0;
}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
