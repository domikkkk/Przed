 //
// Created by DominikSidorczuk on 20.03.2022.
//

#ifndef BCD_BCD_H
#define BCD_BCD_H
#endif //BCD_BCD_H
#include <iostream>
#include <string>

class BCD{
    // Działania na intach czyli długosc 32 bitów
    int liczba_int;
public:
    BCD();
    explicit BCD(int liczba);
    std::string get_nth_digit(int n);
    std::string get_bcd_number();
    int get_int_number();
    BCD operator+(BCD const &bcd) const;
    BCD operator-(BCD const &bcd) const;
    BCD operator*(BCD const &bcd) const;
    BCD operator/(BCD const &bcd) const;
    bool operator<(BCD const &bcd) const;
    bool operator>(BCD const &bcd) const;
    bool operator==(BCD const &bcd) const;
    void operator<<(int const &a);
    void operator>>(int const &a);
//    BCD operator^(BCD const &bcd) const;
    friend std::istream &operator>>(std::istream &is, BCD &bcd);
    friend std::ostream &operator<<(std::ostream &os, const BCD &bcd);
};
int to_int(int liczba);
std::string to_binary(int liczba);
