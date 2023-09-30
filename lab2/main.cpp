#include <bits/stdc++.h>
#include "include/money.h"

using namespace std;


int main() {

    string s = "100";
    string s1 = "90";
    Money f(s);
    Money g(s1);

    f.print(std::cout);
    cout << '\n';
    g.print(std::cout);
    cout << '\n';

    Money h = f.add(g);
    Money l("100");

    Money k("9");
    Money j = l.add(k);
    cout << '\n';
    h.print(std::cout);
    cout << '\n';

    cout << j.equal(l) << '\n';
    cout << "================\n";

    Money a1("000");
    // Money a2("2");
    // Money a3 = a1.add(a2);
    Money a4("-0");
    // a3.print(std::cout);
    cout << std::boolalpha << a4.greater(a1) << " dsadsa" << '\n';

    cout << "================\n";

    Money a5("2");
    Money a6("2");
    // Money a7 = a5.add(a2);
    Money a8("1001");

    cout << a6.less(a5) << '\n';

    cout << "================\n";

    // -7890 - 0 => 0 - 7890

    Money a9("-7890");
    Money a10("-1000");
    Money a11 = a9.substract(a10);
    a11.print(std::cout);
    cout << "================\n";
    Money a12("-100000000000000000000000000000000000");
    Money a13("99999999999");
    Money a14 = a12.add(a13);
    a14.print(std::cout);
}