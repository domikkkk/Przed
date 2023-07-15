//
// Created by DominikSidorczuk on 20.03.2022.
//
#include <string>
#include "BCD.h"

BCD::BCD() {
    this -> liczba_int = 0;
}

BCD::BCD(int liczba_int) {
    this -> liczba_int = liczba_int;
}
// zwraca n-tą cyfrę w postaci binarnej
std::string BCD::get_nth_digit(int n) {
    int liczba = std::stoi(std::to_string(liczba_int), nullptr, 16);
    std::string l = to_binary((liczba>>4*(n-1))&0xf);
    if(l.size() == 0) l="0";
    return l;
}
// zwraca cala liczbe w postaci binarnej (przydatne do testow)
std::string BCD::get_bcd_number() {
    int liczba = std::stoi(std::to_string(liczba_int), nullptr, 16);
    std::string l = to_binary(liczba);
    if(l.size()==0) return "0";
    return l;
}

int BCD::get_int_number() {
    return liczba_int;
}
// dodawanie
BCD BCD::operator+(const BCD &bcd) const {
    return BCD{this -> liczba_int + bcd.liczba_int};
}
// odejmowanie
BCD BCD::operator-(const BCD &bcd) const {
    return BCD{this -> liczba_int - bcd.liczba_int};
}
// mnożenie
BCD BCD::operator*(const BCD &bcd) const {
    return BCD{this -> liczba_int * bcd.liczba_int};
}
//dzielenie
BCD BCD::operator/(const BCD &bcd) const {
    return BCD{this -> liczba_int / bcd.liczba_int};
}
// znak mniejszości
bool BCD::operator<(const BCD &bcd) const {
    return this->liczba_int<bcd.liczba_int;
}
// znak większości
bool BCD::operator>(const BCD &bcd) const {
    return this->liczba_int>bcd.liczba_int;
}
// znaka porównania
bool BCD::operator==(const BCD &bcd) const {
    return this->liczba_int==bcd.liczba_int;
}
// przesunięcie cyfrowe w lewo w liczbie bcd (czyli o 4 bity)
void BCD::operator<<(int const &a) {
    int hex = std::stoi(std::to_string(liczba_int), nullptr, 16);
    hex = hex << (4*a);
    liczba_int = to_int(hex);
}
// przesunięcie cyfrowe w prawo w liczbie bcd (czyli o 4 bity)
void BCD::operator>>(int const &a) {
    int hex = std::stoi(std::to_string(liczba_int), nullptr, 16);
    hex = hex >> (4*a);
    liczba_int = to_int(hex);
}
int to_int(int liczba) {
    return liczba? to_int(liczba/16) * 10 + liczba % 16 : 0;
}
// zwracanie liczby bcd w postaci binarnej
std::string to_binary(int liczba) {
    if(liczba < 0){
        liczba *= -1;
        return '-' + to_binary(liczba);
    }
    return liczba? to_binary(liczba/2) + char(liczba%2 + 48) : "";
}
// funkcja wejścia
std::istream &operator>>(std::istream &is, BCD &bcd){
    is >> bcd.liczba_int;
    return is;
}
// funkcja wyjścia
std::ostream &operator<<(std::ostream &os, const BCD &bcd){
    os << bcd.liczba_int;
    return os;
}
