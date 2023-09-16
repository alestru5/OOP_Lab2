#ifndef MENU_H
#define MENU_H
#include <iostream>
#include "test.h"
#include "stack.h"
#include "help.h"
#include "unordered_map"

int (*menu())(Stack &stack);
int enter_stack(Stack &stack);
int show_stack(Stack &stack);
int show_info(Stack &stack);



#endif