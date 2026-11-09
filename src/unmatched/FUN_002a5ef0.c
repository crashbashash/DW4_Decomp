typedef struct AudSaveDesc {
    int w[6];
    int f24;
    int f28;
} AudSaveDesc;

typedef struct AudSaveState {
    int done;
    AudSaveDesc desc;
    int a;
    int b;
} AudSaveState;

typedef struct AudSaveBuf {
    char data[512];
    int size;
} AudSaveBuf;

typedef struct AudSaveRec {
    int valid;
    int pts;
    int has_pts;
    AudSaveState state;
    AudSaveBuf buf;
} AudSaveRec;

typedef struct AudSaveSub {
    char pad[60];
    AudSaveState state;
} AudSaveSub;

typedef struct AudSaveObj {
    char pad[3368];
    AudSaveSub sub;
} AudSaveObj;

typedef struct AudSaveChunk {
    char *addr;
    int size;
} AudSaveChunk;

int FUN_0028b0c0(void *dst, void *src, int n);
AudSaveRec *FUN_002a82c8(AudSaveObj *obj);

void FUN_002a5ef0(AudSaveObj *obj, int pts, AudSaveChunk *chunk)
{
    AudSaveRec *rec;
    AudSaveBuf *buf;
    int len;
    AudSaveSub *sub;

    rec = FUN_002a82c8(obj);
    if (rec == 0 || rec->valid != 0)
        return;
    len = chunk->size;
    buf = &rec->buf;
    if (len > 512)
        len = 512;
    sub = &obj->sub;
    buf->size = len;
    FUN_0028b0c0(buf->data, chunk->addr, len);
    if (pts == 0x3FFFF) {
        rec->pts = 0;
        rec->has_pts = 0;
    } else {
        rec->has_pts = 1;
        rec->pts = pts * 50;
    }
    rec->state = sub->state;
    rec->valid = 1;
}
