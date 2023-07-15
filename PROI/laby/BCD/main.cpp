#include <iostream>
#include "Lib/BCD.h"

int main() {
    BCD a, b;
    std::cout<<"Podaj wartosci a i b:\n";
    std::cin>>a>>b;
    std::cout<<a.get_nth_digit(2)<<'\n';
    std::cout<<"Roznica a i b w postaci BCD to:\n"<<(a-b).get_bcd_number()<<'\n';
    return 0;
}
