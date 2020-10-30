CC=gcc
CFLAGS=
LDFLAGS=
EXEC=serv cli

all: $(EXEC)

serv: serverTCP.o dame.o
	$(CC) -Wall -o $@ $^ $(LDFLAGS) -lm

cli: clientTCP.o dame.o
	$(CC) -Wall -o $@ $^ $(LDFLAGS) -lm

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) -lm

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)