BIN	=	test\
	myms\

all: $(BIN)

test: test.c testcurses.c
	gcc -o $@ $^ -lcurses

test: test.c
	gcc -o $@ $^

myms: myms.c
	gcc -o $@ $^

clean:
	rm -f $(BIN)
