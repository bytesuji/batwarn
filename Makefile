CC = g++
CFLAGS = -Wall -O3
PKGFLAGS = `pkg-config --cflags --libs libnotify`
TARGET = batwarn

all: $(TARGET)
$(TARGET): $(TARGET).cc
	$(CC) $(CFLAGS) $(PKGFLAGS) -o $(TARGET) $(TARGET).cc
clean:
	$(RM) $(TARGET)
	 

