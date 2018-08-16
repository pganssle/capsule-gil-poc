## Licensed under the MIT Licence
## (C) 2014 Christoph Martin
## For licence text go to http://opensource.org/licenses/MIT

## Makefile
# change to your prefered compiler
CC=gcc

# replace with name of the executable
OUTPUTNAME=gil
# add all source files here but with '.o' instead of '.c'
OBJS=main.o

PY_MAJOR=3
PY_MINOR=7
PY_PATCH=0

PYTHON_VERSION=$(PY_MAJOR).$(PY_MINOR).$(PY_PATCH)
LIBPYTHON=python$(PY_MAJOR).$(PY_MINOR)m

LDFLAGS += -lpthread -l$(LIBPYTHON)
CFLAGS += -I$(VIRTUAL_ENV)/include/$(LIBPYTHON) -I/usr/include/$(LIBPYTHON)
CFLAGS += -DPY_VERSION$(PY_MAJOR)_$(PY_MINOR)

default: all

all: $(OBJS)
	$(CC) -o $(OUTPUTNAME) $(OBJS) ${LDFLAGS}

debug: $(OBJS)
	$(CC) -g -o $(OUTPUTNAME) $(OBJS)

opt: $(OBJS)
	$(CC) -O3 -o $(OUTPUTNAME) $(OBJS)

.PHONY: clean
clean:
	rm *.o
	rm $(OUTPUTNAME)
