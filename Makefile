BASENAME=ignore
PREFIX=/usr/local
CFLAGS=-O3 -static

all: $(BASENAME)
.PHONY: all

$(BASENAME): $(BASENAME).c
	$(CC) -o $@ $(CFLAGS) $<
	#strip -s $@

install: $(BASENAME)
	install -v -s -p -D -t $(DESTDIR)$(PREFIX)/bin $<
.PHONY: install


clean:
	@ rm -rf $(BASENAME)
.PHONY: clean
