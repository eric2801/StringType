#include "StringType.h"
#include "custom_defs.h"
#include "testFunctions.h"
#include <exec/exec.h>

void test_StringPadLeadingChar(UBYTE stage, BOOL *done) {
  String *str = nil, *result = nil, *expected = nil;

  char *testName = "StringPadLeadingChar";

  *done = stage >= 2;

  switch (stage) {
  case 0:
    StringPadLeadingChar(result, 3, 'a');

    expectStringIsNil(testName, stage, result);
    break;

  case 1:
    str = MakeString("");
    result = CopyString(str);
    expected = MakeString("aaa");

    StringPadLeadingChar(result, 3, 'a');

    expectStringsAreEqual(testName, stage, str, result, expected);
    break;

  case 2:
    str = MakeString("foo");
    result = CopyString(str);
    expected = MakeString("aaafoo");

    StringPadLeadingChar(result, 3, 'a');

    expectStringsAreEqual(testName, stage, str, result, expected);
    break;
  }

  if (str)
    FreeString(str);
  if (result)
    FreeString(result);
  if (expected)
    FreeString(expected);
}
