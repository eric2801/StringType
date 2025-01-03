#include <exec/exec.h>
#include <stdio.h>
#include "StringType.h"

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

void test_StringPadLeadingChar(UBYTE stage, BOOL *done)
{
  String *str = nil,
         *result = nil,
         *expected = nil;

  char *testName = "StringPadLeadingChar";

  *done = stage >= 2;

  switch (stage)
  {
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

void test_StringCharAt()
{
  String *str;
  char c;

  printf("test_StringCharAt\n");

  str = MakeString("foo");
  c = StringCharAt(str, 0);
  c = StringCharAt(str, 1);
  c = StringCharAt(str, 2);

  c = StringCharAt(str, 3);

  FreeString(str);
}

void test_StringAppend()
{
  String *foo, *bar;

  printf("test_StringAppend\n");

  foo = MakeString("foo");
  bar = MakeString("bar");
  StringAppend(foo, bar);
  printf("`%s`\n", CString(foo));

  FreeString(bar);
  FreeString(foo);
}

void test_StringTrim()
{
  String *str;
  
  printf("test_StringTrim\n");

  str = MakeString("   foo   ");
  StringTrim(str);
  printf("`%s`\n", CString(str));
  FreeString(str);
}

void test_StringTrimTrailing()
{
  String *str;
  
  printf("test_StringTrimTrailing\n");

  str = MakeString("   foo   ");
  StringTrimTrailing(str);
  printf("`%s`\n", CString(str));
  FreeString(str);
}

void test_StringTrimLeading()
{
  String *str;
  char *msg = nil;

  printf("test_StringTrimLeading\n");

  str = nil;
  StringTrimLeading(str);
  if (str)
  {
    msg = "trimmed leading nil should be nil";
    goto done;
  }

  str = MakeString("");
  StringTrimLeading(str);
  if (str->length != 0)
  {
    msg = "trimmed empty string should still be an empty string";
    goto done;
  }

  FreeString(str);
  str = MakeString("   foo   ");
  StringTrimLeading(str);
  if (str->length != 6 || str->_guts[0] != 'f')
  {
    msg = "'   foo   ' trimmed leading should be 'foo   '";
    goto done;
  }

  FreeString(str);
  str = MakeString("foo");
  StringTrimLeading(str);
  if (str->length != 3 || str->_guts[0] != 'f')
  {
    msg = "'foo' trimmed leading should be 'foo'";
    goto done;
  }

done:
  if (str)
    FreeString(str);
 
  if (msg)
    printf("    FAIL: %s\n", msg);
  else
    printf("    PASSED OK\n");
}

void test_StringHasSuffix()
{
  String *str = nil, *suffix = nil;
  char *msg = nil;

  printf("test_StringHasSuffix\n");

  if (StringHasSuffix(str, suffix))
  {
    msg = "nil arguments should return NO";
    goto done;
  }

  str = MakeString("");
  if (StringHasSuffix(str, suffix))
  {
    msg = "empty string and nil suffix should return NO";
    goto done;
  }

  suffix = MakeString("");
  if (StringHasSuffix(str, suffix))
  {
    msg = "empty string and suffix should return NO";
    goto done;
  }

  FreeString(str);
  str = MakeString("foobar");
  if (StringHasSuffix(str, suffix))
  {
    msg = "'foobar' should not have an empty string suffix";
    goto done;
  }
  
  FreeString(suffix);
  suffix = MakeString("bar");
  if (!StringHasSuffix(str, suffix))
  {
    msg = "'foobar' should have suffix 'bar'";
    goto done;
  }

  FreeString(suffix);
  suffix = MakeString("foobar");
  if (!StringHasSuffix(str, suffix))
  {
    msg = "'foobar' should have suffix 'foobar'";
    goto done;
  }

  FreeString(suffix);
  suffix = MakeString("baz");
  if (StringHasSuffix(str, suffix))
  {
    msg = "'foobar' should not have suffix 'baz'";
    goto done;
  }

  FreeString(suffix);
  suffix = MakeString("car");
  if (StringHasSuffix(str, suffix))
  {
    msg = "'foobar' should not have suffix 'car'";
    goto done;
  }

done:
  if (str)
    FreeString(str);
  if (suffix)
    FreeString(suffix);
 
  if (msg)
    printf("    FAIL: %s\n", msg);
  else
    printf("    PASSED OK\n");
}

void test_StringHasPrefix()
{
  String *str = nil, *prefix = nil;
  char *msg = nil;

  printf("test_StringHasPrefix\n");

  if (StringHasPrefix(str, prefix))
  {
    msg = "nil arguments should return NO";
    goto done;
  }

  str = MakeString("");
  if (StringHasPrefix(str, prefix))
  {
    msg = "empty string and nil prefix should return NO";
    goto done;
  }

  prefix = MakeString("");
  if (StringHasPrefix(str, prefix))
  {
    msg = "empty string and prefix should return NO";
    goto done;
  }

  FreeString(str);
  str = MakeString("foo");
  if (StringHasPrefix(str, prefix))
  {
    msg = "'foo' should not have an empty string prefix";
    goto done;
  }

  FreeString(prefix);
  prefix = MakeString("fo");
  if (! (StringHasPrefix(str, prefix)) )
  {
    msg = "'foo' should have prefix 'fo'";
    goto done;
  }

  FreeString(prefix);
  prefix = MakeString("foo");
  if (! (StringHasPrefix(str, prefix)) )
  {
    msg = "'foo' should have prefix 'foo'";
    goto done;
  }

  FreeString(prefix);
  prefix = MakeString("fop");
  if (StringHasPrefix(str, prefix))
  {
    msg = "'foo' should not have prefix 'fop'";
    goto done;
  }

done:
  if (str)
    FreeString(str);
  if (prefix)
    FreeString(prefix);
 
  if (msg)
    printf("    FAIL: %s\n", msg);
  else
    printf("    PASSED OK\n");
}

void test_StringLength()
{
  String *str;

  printf("test_StringLength\n");

  str = MakeString("hello");
  printf("`%s` length: %ld\n", CString(str), StringLength(str));

  FreeString(str);
}

void test_StringsAreEqual()
{
  String *str1 = nil, *str2 = nil;
  char *msg = nil;

  printf("test_StringsAreEqual\n");

  if (!StringsAreEqual(str1, str2))
  {
    msg = "two nil Strings should be equal";
    goto done;
  }

  str1 = MakeString("");
  if (StringsAreEqual(str1, str2))
  {
    msg = "empty vs nil Strings should not be equal";
    goto done;
  }

  FreeString(str1); str1 = nil;
  str2 = MakeString("");
  if (StringsAreEqual(str1, str2))
  {
    msg = "nil vs empty Strings should not be equal";
    goto done;
  }

  str1 = MakeString("");
  if (!StringsAreEqual(str1, str2))
  {
    msg = "two empty strings should be equal";
    goto done;
  }

  FreeString(str1); str1 = nil;
  FreeString(str2); str2 = nil;
  str1 = MakeString("a");
  str2 = MakeString("a");
  if (!StringsAreEqual(str1, str2))
  {
    msg = "'a' should equal 'a'";
    goto done;
  }

done:
  if (str1) FreeString(str1);
  if (str2) FreeString(str2);

  if (msg)
    printf("    FAIL: %s\n", msg);
  else
    printf("    PASSED OK\n");
}

void test_StringIsBlank()
{
  String *str = nil;
  char *msg = nil;

  printf("test_StringIsBlank\n");


  if (! (StringIsBlank(str)) )
  {
    msg = "nil String should be blank";
    goto done;
  }

  str = MakeString("");
  if (! (StringIsBlank(str)) )
  {
    msg = "zero-length string should be blank";
    goto done;
  }
  FreeString(str); str = nil;

  str = MakeString(" ");
  if (! (StringIsBlank(str)) )
  {
    msg = "single-whitespace string should be blank";
    goto done;
  }
  FreeString(str); str = nil;

  str = MakeString("  ");
  if (! (StringIsBlank(str)) )
  {
    msg = "multi-whitespace string should be blank";
    goto done;
  }
  FreeString(str); str = nil;

  str = MakeString("a");
  if (StringIsBlank(str))
  {
    msg = "string 'a' should not be blank";
    goto done;
  }
  FreeString(str); str = nil;

done:
  if (str)
    FreeString(str);
 
  if (msg)
    printf("    FAIL: %s\n", msg);
  else
    printf("    PASSED OK\n");
}

void test_StringIsEmpty()
{
  String *str = nil;
  char *msg = nil;

  printf("test_StringIsEmpty\n");

  if (! (StringIsEmpty(str)) )
  {
    msg = "nil String should be empty";
    goto done;
  }

  str = MakeString("");
  if (! (StringIsEmpty(str)) )
  {
    msg = "zero-length string should be empty";
    goto done;
  }
  FreeString(str); str = nil;

  str = MakeString(" ");
  if (StringIsEmpty(str))
  {
    msg = "single-whitespace string should not be empty";
    goto done;
  }
  FreeString(str); str = nil;

  str = MakeString("a");
  if (StringIsEmpty(str))
  {
    msg = "single character string should not be empty";
    goto done;
  }
  FreeString(str); str = nil;

done:
  if (str)
    FreeString(str);
 
  if (msg)
    printf("    FAIL: %s\n", msg);
  else
    printf("    PASSED OK\n");
}

int main()
{
  String *string;

  printf("AvailMem: %ld\n", AvailMem(MEMF_PUBLIC));

  string = MakeString("No matter where you go... there you are.");
  printf("%s\n", CString(string));

  FreeString(string);

  /*
  test_StringIsEmpty();
  test_StringIsBlank();
  test_StringHasPrefix();
  test_StringHasSuffix();
  test_StringsAreEqual();
  test_StringLength();
  test_StringTrimLeading();
  test_StringTrimTrailing();
  test_StringTrim();
  test_StringAppend();
  test_StringCharAt();
  test_StringPadLeadingChar();
  test_StringPadLeading();
  */

  runTests(test_StringPadLeading);
  runTests(test_StringPadLeadingChar);

  printf("AvailMem: %ld\n", AvailMem(MEMF_PUBLIC));
  printf("test complete\n");
  
  return 0;
}

