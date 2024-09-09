#!/bin/bash

g++ socket/client.cpp -o build/client -std=c++2a
g++ socket/server.cpp -o build/server -std=c++2a