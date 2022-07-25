all:
	gcc main.c href.c href.h shref.c shref.h flink.c flink.h dir.h -lcurl -o pars
