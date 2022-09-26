#########################################################
# Define paths for our build tree
#OBJ = ./

CC    = $(shell fltk-config --cc)
CXX   = $(shell fltk-config --cxx)
LD    = $(CXX)
FLUID = fluid
STRIP = strip
POST  = fltk-config --post

#########################################################
LDFLAGS   = $(shell fltk-config --ldflags)
CXXFLAGS  = -Wall -Os $(shell fltk-config --cxxflags)
#CXXFLAGS  = -Wall -g $(shell fltk-config --cxxflags)
CFLAGS    = -Wall -Os $(shell fltk-config --cflags)
LIBS      = -lm

#########################################################
ifeq '$(OS)' "Windows_NT"
# The extension to use for executables...
EXE = .exe
else # end of WIN32 options
EXE =
endif 
#########################################################


#########################################################
.SUFFIXES: .cxx .h .o .fl

.fl.h .fl.cxx:
	@echo Passing $< to fluid...
	$(FLUID) -c $<

# Rule to build an object file from a C++ source file
%.o : %.cxx
	@echo Compile $@...
	$(CXX) -c -o $@ $< $(CXXFLAGS)

# Rule to build an object file from a C source file
%.o : %.c
	@echo Compile $@...
	$(CC) -c -o $@ $< $(CFLAGS)

#########################################################
TARGET = dock_group_test

TARGET_OBJS = test.o toolwin.o toolgrp.o dropwin.o drag_btn.o dock_gp.o

all: $(TARGET)$(EXE) 

$(TARGET)$(EXE) : $(TARGET_OBJS)
	$(LD) -o $@ $(TARGET_OBJS) $(CXXFLAGS) $(LDFLAGS) $(LIBS)
	$(STRIP) $@
	$(POST)  $@


clean:
	-rm -f *.o
	-rm -f $(TARGET)$(EXE)

#archive:
#	tar cvf $(TARGET).tar *.cxx  *.h ICONS  Makefile placekeeper
#	gzip $(TARGET).tar

# end of file #
