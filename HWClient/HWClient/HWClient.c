// HWServer.cpp : 定义控制台应用程序的入口点。
//

#include "zmq.h"
#include <assert.h>

#pragma comment(lib, "lib/libzmq.lib")

int main()
{
	void *context = zmq_ctx_new();
	void *responder = zmq_socket(context, ZMQ_REP);
	int rc = zmq_bind(responder, "tcp://*:5555");
	assert(rc == 0);

	while (1)
	{
		char buffer[10] = { 0 };
		zmq_recv(responder, buffer, 10, 0);
		printf("Received Hello\n");

		Sleep(1);

		zmq_send(responder, "world", 5, 0);
	}
	
    return 0;
}

