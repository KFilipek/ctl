all: main libctl.so

main: main.c libctl.so
	gcc main.c -o main -L . -lctl

clean:
	rm -f main libctl.so

libctl.so: ctl.c
	gcc -shared -fPIC -o libctl.so ctl.c