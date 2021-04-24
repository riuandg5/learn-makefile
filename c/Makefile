# default make target
build: main.out

main.out: main.c src/am.c src/gm.c src/hm/hm.c
	gcc $^ -Iinc -o $@ -lm

run: build
	./main.out

clean:
	rm -f main.out