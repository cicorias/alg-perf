CC = gcc
# CFLAGS: Compiler flags
# -O0: Disable all optimizations.
# -fno-lto: Explicitly disable Link Time Optimization.
# -Wall: Enable all warnings (good practice).
# -g: Generate debugging information (good practice, does not affect optimization).
CFLAGS = -O0 -fno-lto -Wall -g

# LDFLAGS: Linker flags (can be empty if CFLAGS cover optimization for linker driver)
LDFLAGS = -lm # Added -lm for math library

BIN_DIR = ./bin
TARGET = $(BIN_DIR)/Cache_Associativity
SRCS = Cache_Associativity.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean run run_100

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR) # Create bin directory if it doesn't exist
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

run: $(TARGET)
	@echo "Running $(TARGET) with default iterations..."
	@$(TARGET)

run_100: $(TARGET)
	@echo "Running $(TARGET) with --iterations 100..."
	@$(TARGET) --iterations 100

clean:
	@echo "Cleaning all generated files..."
	rm -f $(OBJS)
	rm -f $(TARGET)
	@rmdir $(BIN_DIR) 2>/dev/null || true # Remove bin directory if empty