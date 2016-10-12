CC = gcc
CCX = g++
CFLAGS = -std=c99 -Wall -Wno-unused-parameter -Wextra -pedantic -fPIC -g
CXXFLAGS = -std=c++11 -Wall -Wno-unused-parameter -Wextra -pedantic -fPIC -g
INCLUDE_FLAGS = -I../../packet/include -I../../services/include
LDFLAGS = -lpthread
PACKET_DIR = ../../packet/src
SERVICE_DIR = ../../services/src


BCL_OBJS = ${PACKET_DIR}/crc8.o ${PACKET_DIR}/Packet.o ${PACKET_DIR}/ControlServicePackets.o \
		   ${SERVICE_DIR}/Serial.o ${SERVICE_DIR}/UdpSocket.o ${SERVICE_DIR}/Timer.o \
		   ${SERVICE_DIR}/Service.o ${SERVICE_DIR}/ServiceMaster.o

LIBBCL := libbcl.a

all: $(LIBBCL)

$(LIBBCL): $(BCL_OBJS)
	@echo "Linking $@."
	@$(AR) -cq $@ $(BCL_OBJS)

%.o: %.c 
	@echo "[CC]    $@"
	@$(CC) $(CFLAGS) $(INCLUDE_FLAGS) $(LDFLAGS) -c $< -o $@

%.o: %.cpp 
	@echo "[CXX]    $@"
	@$(CC) $(CXXFLAGS) $(INCLUDE_FLAGS) $(LDFLAGS) -c $< -o $@


.PHONY: clean
clean:
	@find ../.. -name "*.o" -print | xargs rm -f 
	@rm -f *.a
