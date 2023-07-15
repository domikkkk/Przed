//
// Created by domik on 14.04.2022.
//

#include "Container_and_weight.cpp"
#include <gtest/gtest.h>
#include <exception>


TEST(test, add_mass){
    Weight a(20, POUND), b(10,KILOGRAM);
    ASSERT_FLOAT_EQ((a+b).get_mass(),42.046226218487758072297380134503);
    ASSERT_EQ((a+b).get_unit(), POUND);
    ASSERT_FLOAT_EQ((b+a).get_mass(), 19.071848);
    ASSERT_EQ((b+a).get_unit(), KILOGRAM);
}

TEST(test, sub_mass){
    Weight a(20, POUND), b(10,KILOGRAM);
    ASSERT_FLOAT_EQ((a-b).get_mass(),-2.046226218487758072297380134503);
    ASSERT_EQ((a-b).get_unit(), POUND);
    ASSERT_FLOAT_EQ((b-a).get_mass(), 0.92815262);
    ASSERT_EQ((b-a).get_unit(), KILOGRAM);
}

TEST(test, devide_mass_by_const){
    Weight a(20, POUND), b(10,KILOGRAM);
    ASSERT_EQ((a/2).get_mass(), 10);
    ASSERT_EQ((a/2).get_unit(), POUND);
    ASSERT_EQ((b/5).get_mass(), 2);
    ASSERT_EQ((b/5).get_unit(), KILOGRAM);
}

TEST(test, multiple_mass_by_const){
    Weight a(20, POUND), b(10,KILOGRAM);
    ASSERT_EQ((a*2).get_mass(), 40);
    ASSERT_EQ((a*2).get_unit(), POUND);
    ASSERT_EQ((b*5).get_mass(), 50);
    ASSERT_EQ((b*5).get_unit(), KILOGRAM);
}

TEST(test1, set_unit){
    Weight a(20, POUND), b(10);
    ASSERT_EQ(a.get_mass(), 20);
    ASSERT_EQ(a.get_unit(), POUND);
    ASSERT_EQ(b.get_mass(), 10);
    ASSERT_EQ(b.get_unit(), KILOGRAM);
    a.set_new_unit(KILOGRAM);
    b.set_new_unit(GRAM);
    ASSERT_FLOAT_EQ(a.get_mass(), 9.071847);
    ASSERT_EQ(a.get_unit(), KILOGRAM);
    ASSERT_EQ(b.get_mass(), 10000);
    ASSERT_EQ(b.get_unit(), GRAM);
}

TEST(test1, equal){
    Weight a(10000, GRAM), b(10);
    ASSERT_EQ(a==b, true);
    ASSERT_EQ((a*2)==b, false);
    ASSERT_EQ(a==(b*2), false);
}

//TEST(test1, is_the_same){
//    Weight a(23, KILOGRAM);
//    std::stringstream out;
//    out << a;
//    Weight b;
//    out >> b;
//    ASSERT_EQ(a, b);
//}

TEST(test2, container){
    Container c(20, KILOGRAM);
    ASSERT_EQ(c.get_unit(), KILOGRAM);
    ASSERT_EQ(c.get_actual_capacity(), 20);
}

TEST(test2, Container_add_item){
    Container c(20, KILOGRAM);
    Weight a(1), b(10), d(10);
    c.add_item(a);
    c.add_item(b);
    c.add_item(d);
    ASSERT_EQ(c.get_unit(), KILOGRAM);
    ASSERT_FLOAT_EQ(c.get_actual_capacity(), 5.4640763);
}

TEST(test2, Container_remove_item){
    Container c(20);
    Weight a(10), b(10, POUND), d(10, GRAM);
    c.add_item(a);
    c.add_item(b);
    c.add_item(d);
    ASSERT_FLOAT_EQ(c.get_actual_capacity(), 5.4540763);
    c.remove_item(d);
    ASSERT_FLOAT_EQ(c.get_actual_capacity(), 5.4640763);
    c.remove_item(a);
    ASSERT_FLOAT_EQ(c.get_actual_capacity(), 15.4640763);
    c.remove_item(b);
    ASSERT_FLOAT_EQ(c.get_actual_capacity(), 20);
}

TEST(test2, add_container){
    Container c(20), e(10);
    Weight a(10), b(25, DECAGRAM), d(10, GRAM);
    c.add_item(a);
    c.add_item(b);
    e.add_item(d);
    ASSERT_FLOAT_EQ((c+e).get_actual_capacity(), 9.75);
}