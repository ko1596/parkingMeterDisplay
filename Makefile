CFLAGS = $(shell pkg-config --cflags gstreamer-1.0) -Wall -Wextra -g
TARGET = $(notdir $(CURDIR))
objs := $(patsubst %c, %o, $(shell ls *.c))
$(TARGET)_test:$(objs)
	$(CC) $(CFLAGS) -o $@ $^
%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $<
clean:
	rm -f $(TARGET)_test *.all *.o