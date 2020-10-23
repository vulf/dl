all: dl.c
	gcc -o dl dl.c
install: dl.c
	gcc -o dl dl.c
	mv dl /usr/bin/
clean:
	/usr/bin/rm dl
uninstall:
	/usr/bin/rm /usr/bin/dl
