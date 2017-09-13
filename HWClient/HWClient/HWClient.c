// HWServer.cpp : 定义控制台应用程序的入口点。
//

#include "zmq.h"
#include <assert.h>

#pragma comment(lib, "lib/libzmq.lib")

int main()
{
	printf("Trying to Connect to hello world server...\n");
	void *context = zmq_ctx_new();
	void *requester = zmq_socket(context, ZMQ_REQ);
	zmq_connect(requester, "tcp://localhost:5555");
	
	int i = 0;
	while(i >= 0)
	{
		char buffer[10] = { 0 };
		printf("Sending Hello %d...\n", i);
		char szSnd[10] = { 0 };
		sprintf_s(szSnd, 10, "%s%d", "hello", i);
		zmq_send(requester, szSnd, strlen(szSnd), 0);
		zmq_recv(requester, buffer, 10, 0);
		printf("Received %s\n", buffer);
		++i;
	}

	zmq_close(requester);
	zmq_ctx_destroy(context);
	
    return 0;
}

