#include "testFunctions.h"
#include "StringType.h"

void test_StringPadLeading(UBYTE stage, BOOL *done)
{
  String *str = nil,
         *result = nil,
         *expected = nil;

  char *testName = "StringPadLeading";

  *done = stage >= 2;

  switch (stage)
  {
    case 0:
      StringPadLeading(result, 3);

      expectStringIsNil(testName, stage, result);
      break;

    case 1:
      str = MakeString("");
      result = CopyString(str);
      expected = MakeString("   ");

      StringPadLeading(result, 3);

      expectStringsAreEqual(testName, stage, str, result, expected);
      break;

    case 2:
      str = MakeString("foo");
      result = CopyString(str);
      expected = MakeString("   foo");

      StringPadLeading(result, 3);

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
