typedef struct MediaRpcTransfer { char *buffer; } MediaRpcTransfer;
typedef struct MediaRpcShared { char pad[8]; char *buffer; } MediaRpcShared;
typedef struct MediaRpcCompletion {
    char pad[12];
    int kind;
    union {
        struct { int headSize; int tailSize; char *head; char *tail; } read;
        struct { void (*callback)(int, int); int thread; int value; int *slot; } wait;
    } u;
} MediaRpcCompletion;
extern MediaRpcShared *DAT_00587360;
void *memcpy(void *, const void *, int);
void *memmove(void *, const void *, int);
void FUN_0010b858(char *, char *);
void iWakeupThread(int);
void FUN_0032db00(MediaRpcCompletion *c) {
    int headSize;
    int tailSize;
    char *head;
    char *tail;
    int gap;
    int kind = c->kind;
    MediaRpcCompletion *w;
    void (*callback)(int, int);
    int thread;
    switch (kind) {
    case 1:
        headSize = c->u.read.headSize;
        tailSize = c->u.read.tailSize;
        head = c->u.read.head;
        tail = c->u.read.tail;
        memcpy(head, DAT_00587360->buffer, headSize);
        gap = (4 - (int)head) & 3;
        if (gap != 0) {
            memmove(head + headSize, head + headSize + gap, tail - (head + headSize));
        }
        memcpy(tail, DAT_00587360->buffer + headSize, tailSize);
        FUN_0010b858(DAT_00587360->buffer, DAT_00587360->buffer + 128);
        break;
    case 2:
        callback = c->u.wait.callback;
        w = (MediaRpcCompletion *)(int)c;
        thread = w->u.wait.thread;
        if (callback == 0) {
            *w->u.wait.slot = w->u.wait.value;
            iWakeupThread(thread);
        } else {
            callback(thread, w->u.wait.value);
        }
        break;
    }
}
