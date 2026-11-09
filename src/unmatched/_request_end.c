typedef struct {
    void *packet;
    int pad4;
    int sema;
    int pad12[2];
    void *buffer;
    void *gp;
    void (*endFunction)(void *);
    void *endParam;
    void *server;
} RpcClientData;
typedef struct {
    int pad0[7];
    RpcClientData *client;
    unsigned int command;
    void *server;
    void *buffer;
} RpcEndPacket;
int iSignalSema(int sema);
void FUN_0010dbb0(void *packet);
static inline void *swapGp(void *gp) {
    void *old;
    __asm__ volatile("move %0,$28; move $28,%1" : "=&r"(old) : "r"(gp) : "memory");
    return old;
}
void _request_end(RpcEndPacket *request) {
    RpcClientData *client;
    void *savedGp;
    switch (request->command) {
    case 0x8000000A:
        client = request->client;
        if (client->endFunction) {
            savedGp = swapGp(client->gp);
            client->endFunction(client->endParam);
            swapGp(savedGp);
        }
        break;
    case 0x80000009:
        client = request->client;
        client->server = request->server;
        client->buffer = request->buffer;
        break;
    case 0x8000000B: /* matching construct: case sweep — an empty third case orders the switch compares */
        break;
    }
    client = request->client;
    if (client->sema >= 0) iSignalSema(client->sema);
    FUN_0010dbb0(client->packet);
    client->packet = 0;
}
