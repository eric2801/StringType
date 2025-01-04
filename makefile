StringType.o: StringType.c StringType.h custom_defs.h

test_StringPadLeading.o: tests/test_StringPadLeading.c
test_StringPadLeadingChar.o: tests/test_StringPadLeadingChar.c

test: StringType.o testFunctions.o tests/test_StringPadLeading.o tests/test_StringPadLeadingChar.o test.o
  ln StringType.o testFunctions.o tests/test_StringPadLeading.o tests/test_StringPadLeadingChar.o test.o -o test -lc
  @echo "your journey towards the dark side is now complete."
  @test

# preceding '-' ignores command's exit code
# preceding '@' prevents echoing command
clean:
  -@execute clean.sh

