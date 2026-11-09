typedef struct AudRecDesc {
    int w[6];
    int f24;
    int f28;
} AudRecDesc;

typedef struct AudRecState {
    int done;
    AudRecDesc desc;
    int a;
    int b;
} AudRecState;

typedef struct AudRecBuf {
    char data[512];
    int size;
} AudRecBuf;

typedef struct AudRecRec {
    int valid;
    int f4;
    int f8;
    AudRecState state;
    AudRecBuf buf;
} AudRecRec;

typedef struct AudRecObj {
    char pad[3428];
    AudRecState state;
} AudRecObj;

typedef struct AudRecChunk {
    char *addr;
    int size;
} AudRecChunk;

int FUN_0028f360(void * handle, AudRecChunk *chunk, int *out);
int FUN_002a0bb8(AudRecObj *obj, int code);
AudRecRec *FUN_002a82c8(AudRecObj *obj);


int FUN_002a81d0(AudRecObj *obj, void * *src, int *ok)
{
    AudRecRec *rec;
    AudRecChunk chunk;
    AudRecBuf *buf;
    int out[4];

    *ok = 0;
    rec = FUN_002a82c8(obj);
    if (rec == 0)
        return 0;
    if (rec->valid == 0)
        return 0;
    obj->state = rec->state;
    buf = &rec->buf;
    chunk.addr = buf->data;
    chunk.size = buf->size;
    if (FUN_0028f360(*src, &chunk, out) != 0)
        return FUN_002a0bb8(obj, 0xFF000F1B);
    *ok = 1;
    return 0;
}
