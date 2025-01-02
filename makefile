StringType.o: StringType.c StringType.h custom_defs.h

test: StringType.o test.o
  ln StringType.o test.o -o test -lc
  @echo "your journey towards the dark side is now complete."
  @test

# preceding '-' ignores command's exit code
# preceding '@' prevents echoing command
clean:
  -@execute clean.sh

