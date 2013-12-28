PREFIX = /usr/local

# Empty 'all' target to prevent accidental installation.
all:
	@echo "Use 'make install' to install SimpleTest."
	@echo "Use 'make uninstall' to uninstall SimpleTest."

install:
	install -c -m 644 include/simpletest.h $(PREFIX)/include

uninstall:
	rm -f $(PREFIX)/include/simpletest.h
