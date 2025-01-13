#include "StringType.h"
#include "custom_defs.h"
#include <exec/exec.h>
#include <string.h>

String *MakeString(char *str) {
  String *string;
  ULONG length;

  if ((string = (String *)AllocMem(sizeof(String), MEMF_PUBLIC))) {
    string->_guts = nil;
    string->length = strlen(str);

    if (string->length) {
      /* Add 1 to length for trailing '\0' */
      if ((string->_guts = (char *)AllocMem(string->length + 1,
                                            MEMF_PUBLIC | MEMF_CLEAR))) {
        strcpy(string->_guts, str);
      }
    }
  }

  return string;
}

VOID FreeString(String *str) {
  if (str) {
    if (str->length && str->_guts) {
      FreeMem(str->_guts, str->length + 1);
      str->_guts = nil;
    }

    FreeMem(str, sizeof(String));
  }
}

char *CString(String *str) { return str->_guts; }

BOOL StringIsEmpty(String *str) {
  if (!str)
    return YES;
  if (!str->_guts)
    return YES;
  if (!str->length)
    return YES;

  return NO;
}

BOOL StringIsBlank(String *str) {
  ULONG i;

  if (!str)
    return YES;
  if (!str->_guts)
    return YES;

  for (i = 0; i < str->length; i++)
    if (str->_guts[i] != ' ')
      return NO;

  return YES;
}

BOOL StringsAreEqual(String *str1, String *str2) {
  ULONG i;

  if (!str1 && !str2)
    return YES;
  if (!str1 || !str2)
    return NO;
  if (str1->length != str2->length)
    return NO;

  for (i = 0; i < str1->length; i++)
    if (str1->_guts[i] != str2->_guts[i])
      return NO;

  return YES;
}

ULONG StringLength(String *str) { return str ? str->length : 0; }

String *CopyString(String *str) { return MakeString(str->_guts); }

BOOL StringHasPrefix(String *str, String *prefix) {
  ULONG i;

  if (!str || !prefix)
    return NO;

  if (prefix->length < 1 || prefix->length > str->length)
    return NO;

  for (i = 0; i < prefix->length; i++)
    if (str->_guts[i] != prefix->_guts[i])
      return NO;

  return YES;
}

BOOL StringHasSuffix(String *str, String *suffix) {
  ULONG i, difference;

  if (!str || !suffix)
    return NO;

  if (suffix->length < 1 || suffix->length > str->length)
    return NO;

  difference = str->length - suffix->length;

  for (i = 0; i < suffix->length; i++)
    if (str->_guts[i + difference] != suffix->_guts[i])
      return NO;

  return YES;
}

VOID StringTrimLeading(String *str) {
  BOOL copy = NO;
  ULONG srcIndex;
  char *new_guts;
  ULONG destIndex;

  if (!str || !str->_guts || str->length < 1)
    return;

  for (srcIndex = 0; srcIndex < str->length;) {
    if (copy)
      new_guts[destIndex++] = str->_guts[srcIndex++];
    else {
      if (str->_guts[srcIndex] != ' ') {
        /* We have found our first non-whitespace.  Prepare the new_guts
         * and start copying. */
        copy = YES;

        new_guts = (char *)AllocMem(str->length - srcIndex + 1,
                                    MEMF_PUBLIC | MEMF_CLEAR);
        destIndex = 0;
      } else {
        /* Ignore this whitespace. */
        srcIndex++;
      }
    }
  }

  /* Replace existing guts with new trimmed guts. */
  FreeMem(str->_guts, str->length);
  str->_guts = new_guts;
  str->length = destIndex;
}

VOID StringTrimTrailing(String *str) {
  ULONG wsIndex, index;
  char *new_guts;

  if (!str || !str->_guts || str->length < 1 ||
      str->_guts[str->length - 1] != ' ')
    return;

  for (wsIndex = str->length; wsIndex > 0 && str->_guts[wsIndex - 1] == ' ';
       wsIndex--)
    ;

  if (wsIndex < 1) {
    FreeMem(str->_guts, str->length + 1);
    str->_guts = nil;
    str->length = 0;
    return;
  }

  new_guts = (char *)AllocMem(wsIndex + 1, MEMF_PUBLIC | MEMF_CLEAR);
  for (index = 0; index < wsIndex; index++)
    new_guts[index] = str->_guts[index];

  FreeMem(str->_guts, str->length + 1);
  str->_guts = new_guts;
  str->length = wsIndex;
}

VOID StringTrim(String *str) {
  StringTrimLeading(str);
  StringTrimTrailing(str);
}

VOID StringAppend(String *str, String *other) {
  char *new_guts;
  ULONG newLength;

  if (!str || !other)
    return;
  if (other->length < 1)
    return;

  newLength = str->length + other->length;
  new_guts = (char *)AllocMem(newLength + 1, MEMF_PUBLIC | MEMF_CLEAR);

  CopyMem(str->_guts, new_guts, str->length);
  CopyMem(other->_guts, new_guts + str->length, other->length);

  FreeMem(str->_guts, str->length + 1);
  str->_guts = new_guts;
  str->length = newLength;
}

char StringCharAt(String *str, ULONG index) {
  if (!str || index >= str->length)
    return '\0';

  return str->_guts[index];
}

VOID StringPadLeading(String *str, ULONG count) {
  StringPadLeadingChar(str, count, ' ');
}

VOID StringPadLeadingChar(String *str, ULONG count, char chr) {
  char *new_guts;
  ULONG newLength, i;

  if (!str)
    return;

  newLength = str->length + count;
  new_guts = (char *)AllocMem(newLength + 1, MEMF_PUBLIC | MEMF_CLEAR);

  if (str->length > 0) {
    CopyMem(str->_guts, new_guts + count, str->length);
    FreeMem(str->_guts, str->length + 1);
  }
  str->_guts = new_guts;
  str->length = newLength;

  for (i = 0; i < count; i++)
    str->_guts[i] = chr;
}
