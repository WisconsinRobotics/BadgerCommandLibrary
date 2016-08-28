CC = gcc
CFLAGS = -std=c99 -Wall -Wno-unused-parameter -Wextra -pedantic -fPIC -g
INCLUDE_FLAGS = -I../../include
LDFLAGS = -lpthread
BUILD_DIR = $(shell pwd)
SRC_DIR = ../../src
BCL_OBJS =  $(SRC_DIR)/executor/Service.o $(SRC_DIR)/executor/ServiceMaster.o $(SRC_DIR)/executor/ServiceMaster_linux.o \
			$(SRC_DIR)/executor/Subsystem.o $(SRC_DIR)/net/net_linux.o $(SRC_DIR)/serial/serial_linux.o $(SRC_DIR)/parser/Packet.o \
			$(SRC_DIR)/parser/ControlServicePackets.o  $(SRC_DIR)/util/bprintf.o $(SRC_DIR)/util/crc8.o

LIBBCL := libbcl.a

all: $(LIBBCL)

$(LIBBCL): $(BCL_OBJS)
	@echo "Linking $@."
	@$(AR) -cq $@ $(BUILD_DIR)/$(BCL_OBJS)

%.o: %.c
	@echo "[CC]    $@"
	@$(CC) $(CFLAGS) $(INCLUDE_FLAGS) $(LDFLAGS) -c $< -o $(BUILD_DIR)/$@

.PHONY: clean
clean:
	@find $(SRC_DIR) -name "*.o" -print | xargs rm -f 
	@rm -f *.a