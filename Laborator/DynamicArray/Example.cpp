//
// Created by Luca Tudor on 11.03.2023.
//
#include "Example.h"
#include <iostream>

Example::Example(int value) : m_value(value) {}

void Example::printValue() const {
    std::cout << "The value is: " << m_value << std::endl;
}