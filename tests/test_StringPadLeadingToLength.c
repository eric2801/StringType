#include "StringType.h"
#include "custom_defs.h"
#include "testFunctions.h"
#include <exec/exec.h>

void test_StringPadLeadingToLength(UBYTE stage, BOOL *done) {
  String *str = nil, *result = nil, *expected = nil;

  char *testName = "StringPadLeadingToLength";

  *done = stage >= 2;

  switch (stage) {
  case 0:
    StringPadLeadingToLength(result, 3);

    expectStringIsNil(testName, stage, result);
    break;

  case 1:
    str = MakeString("");
    result = CopyString(str);
    expected = MakeString("   ");

    StringPadLeadingToLength(result, 3);

    expectStringsAreEqual(testName, stage, str, result, expected);
    break;

  case 2:
    str = MakeString("foo");
    result = CopyString(str);
    expected = MakeString("   foo");

    StringPadLeadingToLength(result, 6);

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
