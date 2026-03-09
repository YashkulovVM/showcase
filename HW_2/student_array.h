#pragma once

#include "student.h"

enum class io_status;
class student;

int createValue(int n, int s, int i); //create an int value for student "value" field 

io_status importFromFile(student* array, int size, char* filename);

io_status formulaeFill(student* array, int size, int formulae);

void printArray(student* array, int size, int p);

int diff(student* a, int n);