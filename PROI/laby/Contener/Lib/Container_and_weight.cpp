//
// Created by DominikSidorczuk on 02.04.2022.
//
#include "Container_and_weight.h"
#include <string>
#include <sstream>
#include <utility>

Weight::Weight() {
    mass = 0;
    unit = KILOGRAM;
}

Weight::Weight(double mass) {
    this -> mass = mass;
    this -> unit = KILOGRAM;
}

Weight::Weight(double mass, Unit unit) {
    this -> mass = mass;
    this -> unit = unit;
}

void Weight::set_new_unit(Unit new_unit) {
    this -> mass = mass * conversion.at(unit) / conversion.at(new_unit);
    this -> unit = new_unit;
}

double Weight::get_mass() {
    return mass;
}

Unit Weight::get_unit() {
    return unit;
}

Weight Weight::operator+(Weight const &wt) {
    Weight new_weight(mass, unit);
    new_weight.set_new_unit(wt.unit);
    new_weight.mass += wt.mass;
    new_weight.set_new_unit(unit);
    return new_weight;
}

Weight Weight::operator-(Weight const &wt) {
    Weight new_weight(mass, unit);
    new_weight.set_new_unit(wt.unit);
    new_weight.mass -= wt.mass;
    new_weight.set_new_unit(unit);
    return new_weight;
}

std::istream &operator>>(std::istream &is, Weight &wt) {
    std::string unitName;
    is >> wt.mass >> unitName;
    wt.unit = KILOGRAM;
    for (auto &kvPair: names) {
        if (kvPair.second == unitName) {
            wt.unit = kvPair.first;
            break;
        }
    }
    return is;
}

std::ostream &operator<<(std::ostream &os, const Weight &wt) {
    os << wt.mass << " " << names.at(wt.unit);
    return os;
}

bool Weight::operator==(const Weight &wt) {
    Weight temporary_weight(mass, unit);
    return (temporary_weight - wt).get_mass() == 0;
}

Weight Weight::operator*(const int a) {
    return {mass * a, unit};
}

Weight Weight::operator/(const int a) {
    return {mass / a, unit};
}

Container::Container(double capacity) {
    this -> capacity = capacity;
    this -> unit = KILOGRAM;
}

Container::Container(double capacity, Unit unit) {
    this -> capacity = capacity;
    this -> unit = unit;
}

void Container::add_item(Weight &wt) {
    Unit old_unit = wt.get_unit();
    wt.set_new_unit(unit);
    if( this -> capacity >= wt.get_mass()){
        this -> capacity -= wt.get_mass();
        wt.set_new_unit(old_unit);
        Weights.push_back(wt);
    }
    wt.set_new_unit(old_unit);
}

void Container::remove_item(Weight &wt) {
    Unit old_unit = wt.get_unit();
    wt.set_new_unit(unit);
    ContainerIterator it(Weights.begin(), Weights.end(), Weights);
    for(it; it<0; ++it){
        if(*it == wt){
            Weights.erase(&it);
            this -> capacity += wt.get_mass();
        }
    }
    wt.set_new_unit(old_unit);
}

std::stringstream Container::show_capacity() {
    std::stringstream out;
    for(Weight &item: Weights){
        out<<item<<std::endl;
    }
    return out;
}

Weight Container::operator[](int n) {
    if(n > Weights.size()) return {};
    return Weights[n];
}

std::istream &operator>>(std::istream &is, Container &cn) {
    std::string unitName;
    is >> cn.capacity >> unitName;
    cn.unit = KILOGRAM;
    for (auto &kvPair: names) {
        if (kvPair.second == unitName) {
            cn.unit = kvPair.first;
            break;
        }
    }
    return is;
}

std::ostream &operator<<(std::ostream &os, const Container &cn) {
    os << cn.capacity << " " << names.at(cn.unit);
    return os;
}

double Container::get_actual_capacity() {
    return this->capacity;
}

Unit Container::get_unit() {
    return this->unit;
}

Container Container::operator+(Container &ct) {
    ContainerIterator it(ct.Weights.begin(),ct.Weights.end(),ct.Weights);
    this -> capacity += ct.capacity;
    for(it; it<0; ++it){
        this -> Weights.push_back(*it);
    }
}

Container::ContainerIterator::ContainerIterator(std::vector<Weight>::iterator begin,
                                                std::vector<Weight>::iterator end,
                                                std::vector<Weight> weights) {
    this -> current = begin;
    this -> end = end;
    this -> weights = weights;
}

Container::ContainerIterator &Container::ContainerIterator::operator++() {
    this -> current += 1;
}

Container::ContainerIterator Container::ContainerIterator::operator++(int) {
    this -> current += 1;
}

bool Container::ContainerIterator::operator<(int) {
    return this->current<this->end;
}

Weight Container::ContainerIterator::operator*() {
    return *current;
}

std::vector<Weight>::iterator Container::ContainerIterator::operator&() {
    return current;
}
