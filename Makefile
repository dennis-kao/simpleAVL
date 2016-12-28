all: avltree

main.o: src/main.c
	gcc -c $< -Wall -std=c99 -Iinclude

avltree.o: src/avltree.c
	gcc -c $< -Wall -std=c99 -Iinclude

avltree: main.o avltree.o
	gcc main.o avltree.o -Wall -std=c99 -Iinclude -o avltree

run:
	./avltree

clean:
	rm -rf *.o
	rm -rf avltree
