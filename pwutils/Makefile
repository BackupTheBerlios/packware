CC = gcc
STRIP = strip
RM = rm -f

CFLAGS = -Wall -O2 -g -fomit-frame-pointer
LDFLAGS = 

TARGET = clearpath desc getsfmirror sltd sltm spn tod

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(LDFLAGS) $@.c -o $@

strip: $(TARGET)
	$(STRIP) $(TARGET)

clean:
	$(RM) $(TARGET)
