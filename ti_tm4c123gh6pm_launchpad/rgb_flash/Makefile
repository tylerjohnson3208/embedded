include ../makefile.conf
NAME=rgbflash
STARTUP_DEFS=-D__STARTUP_CLEAR_BSS -D__START=main

LDSCRIPTS=-L. -L$(BASE)/ldscripts -T nokeep.ld
LFLAGS=$(USE_NANO) $(USE_NOHOST) $(LDSCRIPTS) $(GC) $(MAP)
INCLUDES=$(DRIVERLIB)

$(NAME)-$(CORE).axf: $(NAME).c $(STARTUP)
	$(CC) $^ $(CFLAGS) $(LFLAGS) -I$(INCLUDES) -o $@

clean: 
	rm -f $(NAME)*.axf *.map *.o
