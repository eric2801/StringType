#include "StringType.h"
#include "custom_defs.h"
#include "testFunctions.h"
#include <exec/exec.h>
#include <exec/types.h>

void test_StringAppend(UBYTE stage, BOOL *done) {
  String *str = nil, *result = nil, *expected = nil;

  char *testName = "StringAppend";

  *done = stage >= 3;

  switch (stage) {
  case 0:
    StringAppend(result, str);

    expectStringIsNil(testName, stage, result);
    break;

  case 1:
    result = MakeString("");
    expected = MakeString("");

    StringAppend(result, str);

    expectStringsAreEqual(testName, stage, str, result, expected);
    break;

  case 2:
    str = MakeString("");
    result = MakeString("");
    expected = MakeString("");

    StringAppend(result, str);

    expectStringsAreEqual(testName, stage, str, result, expected);
    break;

  case 3:
    str = MakeString("bar");
    result = MakeString("foo");
    expected = MakeString("foobar");

    StringAppend(result, str);

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
