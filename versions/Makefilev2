# default make target
build: main.c src/am.c src/gm.c src/hm/hm.c
	gcc $^ -Iinc -o main.out -lm

run: build
	./main.out

clean:
	rm -f main.out