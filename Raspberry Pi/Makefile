all : sc16is750_selftest sc16is750_receiver sc16is750_gpio

sc16is750_selftest : sc16is750_selftest.c sc16is750.c sc16is750.h Makefile
	cc -o sc16is750_selftest sc16is750_selftest.c sc16is750.c -lwiringPi -Wall

sc16is750_receiver : sc16is750_receiver.c sc16is750.c sc16is750.h Makefile
	cc -o sc16is750_receiver sc16is750_receiver.c sc16is750.c -lwiringPi -Wall

sc16is750_gpio : sc16is750_gpio.c sc16is750.c sc16is750.h Makefile
	cc -o sc16is750_gpio sc16is750_gpio.c sc16is750.c -lwiringPi -Wall
