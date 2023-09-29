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

    Money a1("-3");
    Money a2("2");
    Money a3 = a1.add(a2);
    Money a4("1001");
    a3.print(std::cout);
    // cout << a2.greater(a2) << '\n';

    cout << "================\n";

    Money a5("2");
    Money a6("2");
    Money a7 = a5.add(a2);
    Money a8("1001");

    cout << a6.less(a5) << '\n';

    cout << "================\n";

    Money a9("7890");
    Money a10("898");
    Money a11 = a9.substract(a10);
    a11.print(std::cout);

}