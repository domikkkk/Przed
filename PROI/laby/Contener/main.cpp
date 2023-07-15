#include <iostream>
#include <sstream>
#include "Lib/Container_and_weight.h"

int main() {
    Weight a, b, d(10, GRAM);
    Container c(30, POUND), e(20);
    std::cin>>a>>b;
    c.add_item(a);
    c.add_item(b);
    e.add_item(d);
    std::cout<<(c+e).show_capacity().str();
    return 0;
}
