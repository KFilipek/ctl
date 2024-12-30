all: main libctl.so

main: main.c libctl.so module.c
	gcc -g -ggdb main.c module.c -o main -L . -lctl

clean:
	rm -f main libctl.so

libctl.so: ctl.c
	gcc -g -ggdb -shared -fPIC -o libctl.so ctl.c

# test: test_module.c module.c ctl.c
# 	g++ -g -ggdb -o test_module test_module.c module.c ctl.c -L . -lctl
# 	./test_module