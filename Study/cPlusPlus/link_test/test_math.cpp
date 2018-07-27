#include <iostream>
#include "math.h"
using namespace std;

int main()
{
    double x, y;
    Math math;
    cin >> x >> y;

    cout << math.add(x, y) << endl;
    cout << math.sub(x, y) << endl;
    cout << math.mul(x, y) << endl;
    cout << math.div(x, y) << endl;
}

