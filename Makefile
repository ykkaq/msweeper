BIN	=	map\
	map2\
	test\
	mswe\

all: $(BIN)

map: map.c
	gcc -o $@ $^

map2: map2.c
	gcc -o $@ $^

#test: test.c testcurses.c
#	gcc -o $@ $^ -lcurses

test: test.c
	gcc -o $@ $^

mswe: myms.c
	gcc -o $@ $^

clean:
	rm -f $(BIN)
