/* 0x0026c2d8 — FUN_0026c2d8 (76 bytes). Returns -1 (after reporting DAT_004ee640) for a null handle, 0 while its state is below 2, else FUN_00267288 of its stream. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
/* Handle layout shared by FUN_0026bb38 … FUN_0026ebf8 (offsets from their accesses). */
typedef struct Source_26bbc0 Source_26bbc0;
typedef struct SourceTable_26bbc0 {
    void *slot0[3];
    void (*release)(Source_26bbc0 *self);          /* +0x0c */
    void *slot4;
    void (*start)(Source_26bbc0 *self);            /* +0x14 */
    void *slot6[3];
    int (*position)(Source_26bbc0 *self, int which); /* +0x24 */
} SourceTable_26bbc0;
struct Source_26bbc0 {
    SourceTable_26bbc0 *table;
};

typedef struct Handle_26bbc0 {
    char f0;
    signed char state;          /* 0x01 */
    char mode;                  /* 0x02 */
    signed char channel_count;  /* 0x03 */
    void *stream;               /* 0x04 */
    void *request;              /* 0x08 */
    void *f12;                  /* 0x0c */
    int f16;                    /* 0x10 */
    Source_26bbc0 *source;      /* 0x14 */
    Source_26bbc0 *channels[9]; /* 0x18: channel_count used; the count of 9 is only what fits before 0x3c */
    short f60;                  /* 0x3c: sectors */
    short f62;                  /* 0x3e: sectors */
    char pad64[32];
    short f96;                  /* 0x60 */
    char pad98[2];
    int f100;                   /* 0x64 */
    short f104;                 /* 0x68 */
    short f106;                 /* 0x6a */
    char f108;                  /* 0x6c */
    char pad109[3];
    char f112;                  /* 0x70 */
    char pad113[3];
    void *f116;                 /* 0x74 */
    char pad120[28];
    void *f148;                 /* 0x94 */
    char pad152[20];
    char f172;                  /* 0xac */
    char pad173[3];
    char *name;                 /* 0xb0 */
    char *cursor;               /* 0xb4 */
    int f184;                   /* 0xb8 */
    int f188;                   /* 0xbc */
    int f192;                   /* 0xc0 */
} Handle_26bbc0;

extern char DAT_004ee640[];
void FUN_002607e8(const char *message);
int FUN_00267288(void *stream);

int FUN_0026c2d8(Handle_26bbc0 *handle) {
    if (handle == 0) {
        FUN_002607e8(DAT_004ee640);
        return -1;
    }
    if (handle->state >= 2) {
        return FUN_00267288(handle->stream);
    }
    return 0;
}
