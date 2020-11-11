#ifndef _UTIL_H_
#define _UTIL_H_
#include <iostream>
#include <cstring>

#include "Value.h"
#include "Value_List.h"

#define BUFFER_SIZE 127
#define BUFFER_BEGIN 0

void valikko();
void heap_error(const char *buffer);
char *check_the_buffer_for_brackets(const char *buffer, unsigned int &cur_location); //FUNCTION CHECKS IF BUFFER CONTAINS ( AND ) IF BOTH ARE FOUND THEN RETURNS POINTER 
bool read_the_buffer(const char *buffer, Value_List &values);
double read_digit(const char *buffer, unsigned int &jumps);
char read_ch(const char *buffer);
char jump_over_bracket(const char *buffer, unsigned int &jumps);
void exception_handling(const char *buffer, char *sub_buffer);

#endif