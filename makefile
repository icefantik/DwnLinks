all:
	gcc main.c href.c shref.c -I ./include -lcurl -o pars
