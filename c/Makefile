# default make target
build: main.out

# Build executable by linking object files
main.out: main.o src/am.o src/gm.o src/hm/hm.o
	gcc $^ -o $@ -lm

# Compile C source files
%.o: %.c
	gcc -Iinc -MMD -MP -c $< -o $@

# Include dependencies generated from every c source file
-include main.d src/am.d src/gm.d src/hm/hm.d

run: build
	./main.out

clean:
	rm -f main.out
	rm -f main.o src/am.o src/gm.o src/hm/hm.o
	rm -f main.d src/am.d src/gm.d src/hm/hm.d