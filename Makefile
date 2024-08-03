CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -O2
LDFLAGS = -pthread

SERVER_SRCS = src/main.cpp src/server.cpp
CLIENT_SRC = src/client.cpp
SERVER_TARGET = server
CLIENT_TARGET = client

all: $(SERVER_TARGET) $(CLIENT_TARGET)

$(SERVER_TARGET): $(SERVER_SRCS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(SERVER_SRCS) -o $(SERVER_TARGET)

$(CLIENT_TARGET): $(CLIENT_SRC)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(CLIENT_SRC) -o $(CLIENT_TARGET)

clean:
	rm -f $(SERVER_TARGET) $(CLIENT_TARGET)

.PHONY: all clean
