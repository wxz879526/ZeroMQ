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
		zmq_msg_t request;
		zmq_msg_init(&request);
		zmq_msg_recv(&request, responder, 0);
		printf("Received Hello\n");
		zmq_close(&request);

		Sleep(1);

		zmq_msg_t reply;
		zmq_msg_init_size(&reply, 5);
		memcpy(&reply, "hello", 5);
		zmq_msg_send(&reply, responder, 0);
		zmq_close(&reply);
	}

	zmq_close(responder);
	zmq_ctx_destroy(context);
	
    return 0;
}

