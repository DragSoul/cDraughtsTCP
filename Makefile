CC=gcc
CFLAGS=
LDFLAGS=
EXEC=dame serv cli

all: $(EXEC)

serv: serverTCP.o
	$(CC) -Wall -o $@ $^ $(LDFLAGS) -lm

cli: clientTCP.o
	$(CC) -o $@ $^ $(LDFLAGS) -lm

dame: dame.o
	$(CC) -o $@ $^ $(LDFLAGS) -lm

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) -lm

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)