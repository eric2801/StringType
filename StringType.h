#ifndef _STRINGTYPE_H
#define _STRINGTYPE_H

#include <exec/types.h>
#include "custom_defs.h"

typedef struct String
{
  char *_guts;
  ULONG length;
} String;



/* Allocate and initialize a String instance. */
String *MakeString(char *str);

/* Free a String instance. */
VOID FreeString(String *str);



/* Convert a String to a char pointer. */
char *CString(String *str);



/* Returns YES if a String is empty, otherwise NO. */
BOOL StringIsEmpty(String *str);

/* Returns YES if a String is blank (has no or only whitespace
 * characters), otherwise NO. */
BOOL StringIsBlank(String *str);



/* Returns YES if 2 strings are equal, else NO. */
BOOL StringsAreEqual(String *str1, String *str2);



/* Returns the length of the string. */
ULONG StringLength(String *str);



/* Returns a copy of a String. */
String *CopyString(String *str);



/* Returns YES if a String starts with the specified String, else NO. */
BOOL StringHasPrefix(String *str, String *prefix);

/* Returns YES if a String ends with the specified String, else NO. */
BOOL StringHasSuffix(String *str, String *suffix);



/* Removes leading whitespaces. */
VOID StringTrimLeading(String *str);

/* Removes trailing whitespaces. */
VOID StringTrimTrailing(String *str);

/* Removes leading and trailing whitespaces. */
VOID StringTrim(String *str);



/* Appends one String to another. */
VOID StringAppend(String *str, String *other);



/* Returns the character at a specified index. */
char StringCharAt(String *str, ULONG index);



/* Pads the String leader with 'n' number of whitespaces. */
VOID StringPadLeading(String *str, ULONG count);

/* Pads the String leader with 'n' number of characters. */
VOID StringPadLeadingChar(String *str, ULONG count, char chr);

#endif
