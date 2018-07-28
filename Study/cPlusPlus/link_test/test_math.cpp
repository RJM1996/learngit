#include <iostream>
#include "math.h"
using namespace std;

int main()
{
    double x, y;
    Math math;
    cin >> x >> y;

    cout << "x + y = " << math.add(x, y) << endl;
    cout << "x - y = " << math.sub(x, y) << endl;
    cout << "x * y = " << math.mul(x, y) << endl;
    cout << "x / y = " << math.div(x, y) << endl;
}

