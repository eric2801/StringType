StringType.o: StringType.c StringType.h custom_defs.h

test_StringAppend.o: tests/test_StringAppend.c
test_StringCharAt.o: tests/test_StringCharAt.c
test_StringPadLeading.o: tests/test_StringPadLeading.c
test_StringPadLeadingChar.o: tests/test_StringPadLeadingChar.c
test_StringPadLeadingToLength.o: tests/test_StringPadLeadingToLength.c
test_StringTrim.o: tests/test_StringTrim.c

test: StringType.o testFunctions.o \
      tests/test_StringAppend.o \
      tests/test_StringCharAt.o \
      tests/test_StringPadLeading.o \
      tests/test_StringPadLeadingChar.o \
      tests/test_StringPadLeadingToLength.o \
      tests/test_StringTrim.o \
      test.o
  ln StringType.o testFunctions.o \
      tests/test_StringAppend.o \
      tests/test_StringCharAt.o \
      tests/test_StringPadLeading.o \
      tests/test_StringPadLeadingChar.o \
      tests/test_StringPadLeadingToLength.o \
			tests/test_StringTrim.o \
      test.o -o test -lc
  @echo "your journey towards the dark side is now complete."
  @test

# preceding '-' ignores command's exit code
# preceding '@' prevents echoing command
clean:
  -@execute clean.sh

