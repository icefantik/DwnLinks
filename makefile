all:
	gcc main.c dir.c dir.h href.c href.h shref.c shref.h  flink.c flink.h -lcurl -o pars
