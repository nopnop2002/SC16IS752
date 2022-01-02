all : sc16is750_selftest sc16is750_receiver sc16is750_receiver_timeout sc16is750_gpio sc16is752_selftest sc16is752_receiver sc16is752_receiver_timeout sc16is752_gpio sc16is752_gpio_irq

sc16is750_selftest : sc16is750_selftest.c sc16is750.c sc16is750.h Makefile
	cc -o sc16is750_selftest sc16is750_selftest.c sc16is750.c -lwiringPi -Wall

sc16is750_receiver : sc16is750_receiver.c sc16is750.c sc16is750.h Makefile
	cc -o sc16is750_receiver sc16is750_receiver.c sc16is750.c -lwiringPi -Wall

sc16is750_receiver_timeout : sc16is750_receiver_timeout.c sc16is750.c sc16is750.h Makefile
	cc -o sc16is750_receiver_timeout sc16is750_receiver_timeout.c sc16is750.c -lwiringPi -Wall

sc16is750_gpio : sc16is750_gpio.c sc16is750.c sc16is750.h Makefile
	cc -o sc16is750_gpio sc16is750_gpio.c sc16is750.c -lwiringPi -Wall

sc16is752_selftest : sc16is752_selftest.c sc16is750.c sc16is750.h Makefile
	cc -o sc16is752_selftest sc16is752_selftest.c sc16is750.c -lwiringPi -Wall

sc16is752_receiver : sc16is752_receiver.c sc16is750.c sc16is750.h Makefile
	cc -o sc16is752_receiver sc16is752_receiver.c sc16is750.c -lwiringPi -Wall

sc16is752_receiver_timeout : sc16is752_receiver_timeout.c sc16is750.c sc16is750.h Makefile
	cc -o sc16is752_receiver_timeout sc16is752_receiver_timeout.c sc16is750.c -lwiringPi -Wall

sc16is752_gpio : sc16is752_gpio.c sc16is750.c sc16is750.h Makefile
	cc -o sc16is752_gpio sc16is752_gpio.c sc16is750.c -lwiringPi -Wall

sc16is752_gpio_irq : sc16is752_gpio_irq.c sc16is750.c sc16is750.h Makefile
	cc -o sc16is752_gpio_irq sc16is752_gpio_irq.c sc16is750.c -lwiringPi -Wall
