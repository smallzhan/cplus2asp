# Builds the complete cplus2asp application.
# Variable DEBUG can be set to true via command line to turn on debugging options.

INSTALLPATH=/usr/local
BINPATH=$(INSTALLPATH)/bin
LIBPATH=$(INSTALLPATH)/lib

DEBUG=
CC=g++
CFLAGS=-c
LDFLAGS=
DEBUGFLAGS=-Wall -O0 -g3
RELEASEFLAGS=-Wall -O3

OBJECTS=
MAINSOURCE=cplus2asp.cpp
EXECUTABLE=cplus2asp
STD_ASP_FILE=cplus2asp_std.f2lp
ADDITIVE_ASP_FILE=cplus2asp_additive.f2lp
EXEC_SCRIPT=cplus2asp_base.sh
INSTALL_EXEC_SCRIPT_NAME=cplus2asp
INSTALL_BINLOC=$(BINPATH)/
INSTALL_LIBLOC=$(LIBPATH)/cplus2asp/

.PHONY : all
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(MAINSOURCE)
ifeq ($(DEBUG),true)
	$(CC) $(LDFLAGS) $(DEBUGFLAGS) $(OBJECTS) $(MAINSOURCE) -o $@
else
	$(CC) $(LDFLAGS) $(RELEASEFLAGS) $(OBJECTS) $(MAINSOURCE) -o $@
endif

$(OBJECTS): $(OTHEROBJS:.o=.cpp) $(OTHEROBJS:.o=.h)

.PHONY : remake
remake: realclean all

.PHONY : clean
clean:
	-rm -f *.o

.PHONY : realclean
realclean:
	-rm -f *.o
	-rm -f $(EXECUTABLE)

.PHONY : install
install:
	@cd $(INSTALL_LIBLOC) 2>/dev/null || mkdir $(INSTALL_LIBLOC)
	@-rm $(INSTALL_LIBLOC)$(EXECUTABLE) 2>/dev/null || true
	cp $(EXECUTABLE) $(INSTALL_LIBLOC)
	@-rm $(INSTALL_LIBLOC)$(STD_ASP_FILE) 2>/dev/null || true
	cp $(STD_ASP_FILE) $(INSTALL_LIBLOC)
	@-rm $(INSTALL_LIBLOC)$(ADDITIVE_ASP_FILE) 2>/dev/null || true
	cp $(ADDITIVE_ASP_FILE) $(INSTALL_LIBLOC)
	cp $(EXEC_SCRIPT) $(INSTALL_BINLOC)$(INSTALL_EXEC_SCRIPT_NAME)
	@echo "$(INSTALL_LIBLOC)$(EXECUTABLE) \"\$$@\"" >> $(INSTALL_BINLOC)$(INSTALL_EXEC_SCRIPT_NAME)

.cpp.o:
ifeq ($(DEBUG),true)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) $< -o $@
else
	$(CC) $(CFLAGS) $(RELEASEFLAGS) $< -o $@
endif
