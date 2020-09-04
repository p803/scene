TARGET ?= dist/main
SRC_DIRS ?= ./src

SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
OBJS := $(addsuffix .o,$(basename $(SRCS)))
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CC := g++
CPPFLAGS ?= $(INC_FLAGS) $(shell pkg-config gtkmm-3.0 --cflags) -MMD -Wall -O2
LDLIBS := $(shell pkg-config gtkmm-3.0 --libs) -lX11 -lpthread -lboost_program_options

$(TARGET): $(OBJS)
	mkdir -p dist
	$(CC) $(OBJS) -o $@ $(LDLIBS)

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS) $(DEPS)

-include $(DEPS)
