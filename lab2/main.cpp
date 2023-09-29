#include <bits/stdc++.h>
#include "include/money.h"

using namespace std;


int main() {

    string s = "1";
    string s1 = "0";
    Money f(s);
    Money g(s1);

    f.print(std::cout);
    cout << '\n';
    g.print(std::cout);
    cout << '\n';

    Money h = f.add(g);
    Money l("100");

    Money k("9");
    Money j = h.add(k);
    j.print(std::cout);
    cout << '\n';

    cout << j.equal(l) << '\n';
    cout << "================\n";

    Money a1("-3");
    Money a2("2");
    Money a3 = a1.add(a2);
    Money a4("1001");

    cout << a2.greater(a2) << '\n';

}