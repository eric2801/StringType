#include "StringType.h"
#include "testFunctions.h"

void test_StringCharAt(UBYTE stage, BOOL *done)
{
  String *str = nil;
  char c;

  char *testName = "StringCharAt";

  *done = stage >= 3;

  switch (stage)
  {
    case 0:
      str = nil;
      c = StringCharAt(str, 0);
      expect(c == '\0', testName, stage, "expected char to equal '\\0'");
      break;
    case 1:
      str = MakeString("");
      c = StringCharAt(str, 0);
      expect(c == '\0', testName, stage, "expected char(0) to equal '\\0'");

      c = StringCharAt(str, 1);
      expect(c == '\0', testName, stage, "expected char(1) to equal '\\0'");

      break;
    case 2:
      str = MakeString("a");
      c = StringCharAt(str, 0);
      expect(c == 'a', testName, stage, "expected char(0) to equal 'a'");

      c = StringCharAt(str, 1);
      expect(c == '\0', testName, stage, "expected char(1) to equal '\\0'");

      break;
    case 3:
      str = MakeString("foo");
      c = StringCharAt(str, 0);
      expect(c == 'f', testName, stage, "expected char(0) to equal 'f'");

      c = StringCharAt(str, 1);
      expect(c == 'o', testName, stage, "expected char(1) to equal 'o'");

      c = StringCharAt(str, 2);
      expect(c == 'o', testName, stage, "expected char(2) to equal 'o'");
      
      break;
  }

  if (str)
    FreeString(str);
}
