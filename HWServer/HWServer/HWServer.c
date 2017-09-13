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

	int i = 0;
	while (i >= 0)
	{
		char buffer[10] = { 0 };
		zmq_recv(responder, buffer, 10, 0);

		char szSnd[10] = { 0 };
		sprintf_s(szSnd, 10, "%s", buffer);
		printf("Received ");
		printf(szSnd);
		printf("\n");

		Sleep(1);

		char szSend[100] = { 0 };
		sprintf_s(szSend, 100, "%s%d", "world", i);
		zmq_send(responder, szSend, strlen(szSend), 0);
	}
	
    return 0;
}

