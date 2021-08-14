CC      = gcc
CFLAGS  = -O4 -Wall -I/usr/include
LDFLAGS = -L/usr/lib64
LIBS    = -lcurl
OBJS    = example_curl.o
PROGRAM = example_curl

all:		$(PROGRAM)

$(PROGRAM):	$(OBJS)
			$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o $(PROGRAM)

clean:
			rm -f *.o *~ $(PROGRAM)
