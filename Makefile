CC=gcc
CFLAGS=-framework ApplicationServices -framework Carbon
SOURCES=keycounter.c
EXECUTABLE=keycounter
PLIST=keylogger.plist
INSTALLDIR=/usr/local/bin

all: $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -o $(EXECUTABLE)

debug: $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -g -o $(EXECUTABLE)

install: all
	mkdir -p $(INSTALLDIR)
	cp $(EXECUTABLE) $(INSTALLDIR)

uninstall:
	rm $(INSTALLDIR)/$(EXECUTABLE)
	rm /Library/LaunchDaemons/$(PLIST)

startup: install
	cp $(PLIST) /Library/LaunchDaemons

clean:
	rm $(EXECUTABLE)
