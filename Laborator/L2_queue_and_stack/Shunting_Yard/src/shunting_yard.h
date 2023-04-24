//
// Created by Luca Tudor on 15.04.2023.
//

#pragma once

#include <string>

using namespace std;

int get_precedence(char op);
int evaluate_postfix(const string& postfix);
string infix_to_postfix_conversion(const string& infix);