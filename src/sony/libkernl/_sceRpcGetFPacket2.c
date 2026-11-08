typedef struct { char pad[64]; } P;
typedef struct { char pad[28]; P *base; int count; } T;
P *FUN_0010dbd0(T *, int);
P *_sceRpcGetFPacket2(T *t, int i) {
    if (i < 0 || i >= t->count) {
        return FUN_0010dbd0(t, i);
    }
    return &t->base[i];
}
