CC=gcc

BIN = xml2ini
CFLAGS = -I/usr/include
LDFLAGS = -L/usr/lib

#BIN = xml2ini.exe
#CFLAGS = -I/usr/local/include
#LDFLAGS = -I/usr/local/lib

OBJS = xml2ini.o
LIBS = -lexpat

all: $(BIN)

xml2ini.o: xml2ini.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN): xml2ini.o
	$(CC) $(CFLAGS) -o $(BIN) $(OBJS) $(LDFLAGS) $(LIBS)

clean:
	$(RM) $(OBJS) $(BIN)
