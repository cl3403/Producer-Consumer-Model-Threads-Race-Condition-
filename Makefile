OPTS = -g -Wall -std=c++11

mapqueue: mapqueue.cc
	g++ ${OPTS} -pthread -o mapqueue mapqueue.cc
