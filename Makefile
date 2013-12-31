PREFIX = /usr/local

# Empty 'all' target to prevent accidental installation.
all:
	@echo "Use 'make install' to install MereTest."
	@echo "Use 'make uninstall' to uninstall MereTest."

.PHONY: clean
clean:
	rm -f test/meretest_test

.PHONY: test
test:
	gcc -Iinclude -o test/meretest_test test/meretest_test.c
	test/meretest_test

install:
	install -c -m 644 include/meretest.h $(PREFIX)/include

uninstall:
	rm -f $(PREFIX)/include/meretest.h
