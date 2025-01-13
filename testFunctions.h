#ifndef _TESTFUNCTIONS_H
#define _TESTFUNCTIONS_H

#include "StringType.h"
#include <exec/types.h>

void runTests(void (*test)(UBYTE stage, BOOL *done));
void printTestResult(char *testName, UBYTE stage, char *msg);

void expectStringIsNil(char *testName, UBYTE stage, String *result);
void expectStringsAreEqual(char *testName, UBYTE stage, String *str,
                           String *result, String *expected);

void expect(BOOL condition, char *testName, UBYTE stage, char *msg);

#endif
