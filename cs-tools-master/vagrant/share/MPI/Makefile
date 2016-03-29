CC = /usr/lib64/mpich/bin/mpicc

CFLAGS = -I. -g -Wall
LDFLAGS = -L. -lm
PROGRAMS = hello potatoes potatoes

default: all
all: $(PROGRAMS)

.PHONY: clean

%.o:%.cc $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hello: hello.o
	$(CC) -o $@ $^ $(LDFLAGS)

potato: potato.o
	$(CC) -o $@ $^ $(LDFLAGS)

potatoes: potatoes.o
		$(CC) -o $@ $^ $(LDFLAGS)

clean:
	/bin/rm -f *.o $(PROGRAMS)

squeaky: clean
	/bin/rm -f *~ *.bak
