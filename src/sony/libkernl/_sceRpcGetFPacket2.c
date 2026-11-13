typedef struct { char pad[64]; } P;
typedef struct { char pad[28]; P *base; int count; } T;
P *_sceRpcGetFPacket(T *, int);
P *_sceRpcGetFPacket2(T *t, int i) {
    if (i < 0 || i >= t->count) {
        return _sceRpcGetFPacket(t, i);
    }
    return &t->base[i];
}
