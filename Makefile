all: dl.c
	gcc -o dl dl.c
install: dl.c
	gcc -o dl dl.c
	mv dl ${HOME}/bin/
clean:
	rm dl
uninstall:
	rm ${HOME}/bin/dl
