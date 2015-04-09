# Build cmd
    g++ -Wall -Wextra -O0 -g -Isrc  -o Build/debug/./src/main.o -c -MMD -MP -MF Build/debug/./src/main.d src/main.cpp
    g++ -Wall -Wextra -O0 -g -Isrc  -o Build/debug/./src/ethframe.o -c -MMD -MP -MF Build/debug/./src/ethframe.d src/ethframe.cpp
    g++ -Wall -Wextra -O0 -g -Isrc  -o Build/debug/./src/udpsender.o -c -MMD -MP -MF Build/debug/./src/udpsender.d src/udpsender.cpp
    g++  -o Build/debug/udp_packet_sender Build/debug/./src/main.o Build/debug/./src/ethframe.o Build/debug/./src/udpsender.o 