CC=gcc
CFLAGS=-I -v
OBJ = main.c filereader.c memman.c processor.c
OUT = RiscVSim

buildandrun: $(OBJ)
	$(CC) -o $(OUT) $^ $(CFLAGS) && ./$(OUT)

build: $(OBJ)
	$(CC) -o $(OUT) $^ $(CFLAGS)

release:
        $(call build,)

debug:
        $(call buildandrun, DEBUG=1)

clean:
	rm -f $(OUT)