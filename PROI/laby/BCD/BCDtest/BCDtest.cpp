//
// Created by DominikSidorczuk on 23.03.2022.
//
#include <exception>
#include <gtest/gtest.h>
#include "BCD.h"

TEST(TEST, operatorplus){
    BCD a(12), b(4);
    ASSERT_EQ(24, (a+a).get_int_number());
    ASSERT_EQ(16, (a+b).get_int_number());
    ASSERT_EQ("10110", (a+b).get_bcd_number());
}

TEST(TEST, operatorminus){
    BCD a(12), b(4);
    ASSERT_EQ(0, (a-a).get_int_number());
    ASSERT_EQ(8, (a-b).get_int_number());
    ASSERT_EQ("1000", (a-b).get_bcd_number());
}

TEST(TEST, operatormultiply){
    BCD a(12), b(4);
    ASSERT_EQ(144, (a*a).get_int_number());
    ASSERT_EQ(48, (a*b).get_int_number());
    ASSERT_EQ("1001000", (a*b).get_bcd_number());
}

TEST(TEST, operatordivide){
    BCD a(12), b(4);
    ASSERT_EQ(1, (a/a).get_int_number());
    ASSERT_EQ(3, (a/b).get_int_number());
    ASSERT_EQ("11", (a/b).get_bcd_number());
}

TEST(TEST, operatorbigger){
    BCD a(12), b(4);
    ASSERT_EQ(false, a<b);
    ASSERT_EQ(true, b<a);
    ASSERT_EQ(false, a<a);
    ASSERT_EQ(false, b<b);
}

TEST(TEST, operatorsmaller){
    BCD a(12), b(4);
    ASSERT_EQ(true, a>b);
    ASSERT_EQ(false, b>a);
    ASSERT_EQ(false, a>a);
    ASSERT_EQ(false, b>b);
}

TEST(TEST, operatorequal){
    BCD a(12), b(4);
    ASSERT_EQ(false, a==b);
    ASSERT_EQ(false, b==a);
    ASSERT_EQ(true, a==a);
    ASSERT_EQ(true, b==b);
}

TEST(TEST, RSHIFT){
    BCD a(1200), b(453);
    ASSERT_EQ(1200, a.get_int_number());
    ASSERT_EQ(453, b.get_int_number());
    a>>2;
    b>>3;
    ASSERT_EQ(12, a.get_int_number());
    ASSERT_EQ(0, b.get_int_number());
    ASSERT_EQ("0", b.get_bcd_number());
    ASSERT_EQ("10010", a.get_bcd_number());
}

TEST(TEST, LSHIFT){
    BCD a(1254), b(212);
    ASSERT_EQ(1254, a.get_int_number());
    ASSERT_EQ("1000010010", b.get_bcd_number());
    a<<3;
    b<<1;
    ASSERT_EQ(1254000, a.get_int_number());
    ASSERT_EQ("1001001010100000000000000", a.get_bcd_number());
    ASSERT_EQ(2120, b.get_int_number());
    ASSERT_EQ("10000100100000", b.get_bcd_number());
}

TEST(TEST, get_nth_degit){
    BCD a(24351), b(2349);
    ASSERT_EQ("11", a.get_nth_digit(3));
    ASSERT_EQ("10", b.get_nth_digit(4));
    ASSERT_EQ("111", (a*b).get_nth_digit(7));
    ASSERT_EQ("110", (a+b).get_nth_digit(4));
}

TEST(TEST, is_the_same){
    BCD a(23);
    std::stringstream out;
    out << a;
    BCD b;
    out >> b;
    ASSERT_EQ(a, b);
}