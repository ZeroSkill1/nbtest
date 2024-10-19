CFLAGS   = -std=gnu++11  -Wno-unused-variable -Wno-unused-function -Wno-unused-but-set-variable $(foreach includedir,$(INCLUDES), -I$(includedir))
SOURCES  := . ../nbtest ../nbtest/tests
INCLUDES := . ../nbtest ../../nblib
CC       := g++
LD       := $(CC)
TARGET   := nblib-test
LIBS     :=

CFILES := $(foreach cfiledir,$(SOURCES),$(wildcard $(cfiledir)/*.cc))
OFILES := $(foreach cfile,$(CFILES),$(patsubst %.cc,%.pc.o,$(cfile)))

.PHONY: all
all: CFLAGS += -g
all: $(TARGET)

optimized: CFLAGS += -Os
optimized: $(TARGET)

%.pc.o: %.cc
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OFILES)
	$(LD) -o $(TARGET) $(^) $(LIBS)

clean:
	@echo $(OFILES)
	@echo
	rm $(OFILES) -rfv
	rm $(TARGET) -rfv

