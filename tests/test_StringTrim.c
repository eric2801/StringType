#include "StringType.h"
#include "custom_defs.h"
#include "testFunctions.h"
#include <exec/exec.h>
#include <exec/types.h>

void test_StringTrim(UBYTE stage, BOOL *done) {
  String *str = nil, *result = nil, *expected = nil;

  char *testName = "StringTrim";

  *done = stage >= 1;

  switch (stage) {
  case 0:
    StringTrim(result);

    expectStringIsNil(testName, stage, result);
    break;

  case 1:
    str = MakeString("   foo  ");
    result = MakeString("   foo   ");
    expected = MakeString("foo");

    StringTrim(result);

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
