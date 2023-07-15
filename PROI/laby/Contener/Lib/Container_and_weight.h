//
// Created by DominikSidorczuk on 02.04.2022.
//

#ifndef CONTENER_CONTAINER_H
#define CONTENER_CONTAINER_H
#endif //CONTENER_CONTAINER_H
#include <iostream>
#include <string>
#include <vector>
#include <map>

enum Unit {
    KILOGRAM,
    GRAM,
    TONNE,
    POUND,
    DECAGRAM,
    KARAT
};

const std::map<Unit, double> conversion = {
        {KILOGRAM, 1},
        {GRAM, 0.001},
        {TONNE, 1000},
        {POUND, 0.45359237},
        {DECAGRAM, 0.01},
        {KARAT, 0.0002}
};

const std::map<Unit, std::string> names = {
        {KILOGRAM, "kg"},
        {GRAM, "g"},
        {TONNE, "t"},
        {POUND, "lb"},
        {DECAGRAM, "dg"},
        {KARAT, "ct"}
};

class Weight{
    double mass;
    Unit unit;
public:
    Weight();
    explicit Weight(double mass);
    Weight(double  mass, Unit unit);
    void set_new_unit(Unit new_unit);
    double get_mass();
    Unit get_unit();
    Weight operator+(Weight const &wt);
    Weight operator-(Weight const &wt);
    Weight operator*(int a);
    Weight operator/(int a);
    bool operator==(Weight const &wt);
    friend std::istream &operator>>(std::istream &is, Weight &wt);
    friend std::ostream &operator<<(std::ostream &os, const Weight &wt);
};

class Container{
    double capacity;
    Unit unit;
    std::vector<Weight> Weights;
public:
    class ContainerIterator{
        std::vector<Weight>::iterator current, end;
        std::vector<Weight> weights;
    public:
        ContainerIterator(std::vector<Weight>::iterator begin, std::vector<Weight>::iterator end, std::vector<Weight> weights);
        ContainerIterator &operator++();
        ContainerIterator operator++(int);
        Weight operator*();
        std::vector<Weight>::iterator operator&();
        bool operator<(int);
    };
    explicit Container(double capacity);
    Container(double capacity, Unit unit);
    void add_item(Weight &wt);
    void remove_item(Weight &wt);
    double get_actual_capacity();
    Unit get_unit();
    std::stringstream show_capacity();
    Weight operator[](int n);
    Container operator+(Container &ct);
    friend std::istream &operator>>(std::istream &is, Container &cn);
    friend std::ostream &operator<<(std::ostream &os, const Container &cn);
};
