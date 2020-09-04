TARGET ?= dist/main
SRC_DIRS ?= ./src

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(addsuffix .o,$(basename $(SRCS)))
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CC := g++
CPPFLAGS ?= $(INC_FLAGS) $(shell pkg-config gtkmm-3.0 --cflags) -MMD -MP -Wall -Werror -g
LDLIBS := $(shell pkg-config gtkmm-3.0 --libs) -lm -lX11 -lpthread -lboost_program_options

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@ $(LOADLIBES) $(LDLIBS)

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS) $(DEPS)

-include $(DEPS)
