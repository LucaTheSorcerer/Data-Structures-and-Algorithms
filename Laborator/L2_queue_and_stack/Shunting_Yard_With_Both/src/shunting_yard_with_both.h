//
// Created by Luca Tudor on 24.04.2023.
//

#pragma once

#include <string>

using namespace std;

int get_precedence_both(char op);
int evaluate_postfix_both(string postfix);
string infix_to_postfix_conversion_both(const string& infix);
