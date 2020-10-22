all: dl.c
	gcc -o dl dl.c
install: dl.c
	gcc -o dl dl.c
	mv dl /usr/bin/
clean:
	rm dl
uninstall:
	rm /usr/bin/dl
