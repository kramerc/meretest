PREFIX = /usr/local

# Empty 'all' target to prevent accidental installation.
all:
	@echo "Use 'make install' to install MereTest."
	@echo "Use 'make uninstall' to uninstall MereTest."

install:
	install -c -m 644 include/meretest.h $(PREFIX)/include

uninstall:
	rm -f $(PREFIX)/include/meretest.h
