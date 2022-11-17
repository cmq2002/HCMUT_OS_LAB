Compiler:= cc
Project1:=sum_serial.c
Object1:=run_serial
Project2:=sum_multi-thread.c
Object2:=run_thread
all: clean build
build:
	$(Compiler) -o $(Object1) $(Project1)
	$(Compiler) -o $(Object2) $(Project2)
clean:
	rm -f $(Object1)
	rm -f $(Object2)