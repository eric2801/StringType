#include <stdio.h>
#include "testFunctions.h"

void runTests(void (*test)(UBYTE stage, BOOL *done))
{
  UBYTE stage;
  BOOL done = NO;

  for (stage = 0; !done; stage++)
    test(stage, &done);
}

void printTestResult(char *testName, UBYTE stage, char *msg)
{
  printf("%s [%d]: ", testName, stage);

  if (msg)
    printf("FAILED - %s\n", msg);
  else
    printf("PASSED\n");
}

void expectStringIsNil(char *testName, UBYTE stage, String *result)
{
  char *msg = nil;

  if (result)
    msg = "expected result to be nil";

  printTestResult(testName, stage, msg);

  if (msg && result)
    printf("    result: `%s`\n", CString(result));
}

void expectStringsAreEqual(char *testName, UBYTE stage, String *str, String *result, String *expected)
{
  char *msg = nil;

  if (!StringsAreEqual(result, expected))
    msg = "expected strings to be equal";

  printTestResult(testName, stage, msg);

  if (msg)
  {
    if (str)
      printf("    test string: `%s`\n", CString(str));
    if (result)
      printf("    result: `%s`\n", CString(result));
    if (expected)
      printf("    expected: `%s`\n", CString(expected));
  }
}

void expect(BOOL condition, char *testName, UBYTE stage, char *msg)
{
  printTestResult(testName, stage, condition ? nil : msg);
}
