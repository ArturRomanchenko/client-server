CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -O2
LDFLAGS = -pthread

SERVER_SRCS = server/src/main.cpp server/src/server.cpp
CLIENT_SRCS = client/src/main.cpp client/src/client.cpp
SERVER_TARGET = server_app
CLIENT_TARGET = client_app

all: $(SERVER_TARGET) $(CLIENT_TARGET)

$(SERVER_TARGET): $(SERVER_SRCS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(SERVER_SRCS) -o $(SERVER_TARGET)

$(CLIENT_TARGET): $(CLIENT_SRCS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(CLIENT_SRCS) -o $(CLIENT_TARGET)

clean:
	rm -f $(SERVER_TARGET) $(CLIENT_TARGET)

.PHONY: all clean
