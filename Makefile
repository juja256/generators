GXX:= gcc
CFLAGS:= -O3 -g

all: generators

generators: main.o generators.o l.a
	$(GXX) $(CFLAGS) main.o generators.o l.a -lm -o generators

generators.o: generators.c
	$(GXX) $(CFLAGS) -c generators.c

main.o: main.c
	$(GXX) $(CFLAGS) -c main.c

clear:
	rm -f generators