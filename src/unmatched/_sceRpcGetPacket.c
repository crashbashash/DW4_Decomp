typedef struct {
    int pad0[4];
    unsigned int state;
    void *self;
    int id;
    int pad28[9];
} RpcPacket;
typedef struct {
    int nextId;
    RpcPacket *packets;
    int packetCount;
} RpcPacketPool;
int DIntr(void);
int EIntr(void);
RpcPacket *_sceRpcGetPacket(RpcPacketPool *pool) {
    RpcPacket *packet;
    int i;
    int id;
    DIntr();
    packet = pool->packets;
    for (i = 0; i < pool->packetCount; i++, packet++) {
        if (!(packet->state & 1)) {
            packet->state = (i << 16) | 5;
            pool->nextId++;
            if (pool->nextId == 1) {
                pool->nextId++;
                id = 1;
            } else {
                id = pool->nextId;
            }
            packet->self = packet;
            packet->id = id;
            EIntr();
            return packet;
        }
    }
    EIntr();
    return 0;
}
