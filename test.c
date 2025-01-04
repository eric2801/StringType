#include <exec/exec.h>
#include <stdio.h>
#include "StringType.h"
#include "testFunctions.h"

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

void test_StringAppend(UBYTE stage, BOOL *done);
void test_StringCharAt(UBYTE stage, BOOL *done);
void test_StringPadLeading(UBYTE stage, BOOL *done);
void test_StringPadLeadingChar(UBYTE stage, BOOL *done);

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

  runTests(test_StringAppend);
  runTests(test_StringCharAt);
  runTests(test_StringPadLeading);
  runTests(test_StringPadLeadingChar);

  printf("AvailMem: %ld\n", AvailMem(MEMF_PUBLIC));
  printf("test complete\n");
  
  return 0;
}

