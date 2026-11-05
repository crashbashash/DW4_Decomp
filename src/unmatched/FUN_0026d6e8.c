/* 0x0026d6e8 — FUN_0026d6e8 (180 bytes). Reports DAT_004eecd8 for a null handle or name; otherwise calls FUN_0026bc60, copies name into the handle buffer, stores the two extra arguments, resets the cursor and flags (state 1) and calls FUN_0026d158(handle, 0). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
/* Handle layout shared by FUN_0026bb38 … FUN_0026d6e8 (offsets from their accesses). */
typedef struct Source_26bbc0 Source_26bbc0;
typedef struct SourceTable_26bbc0 {
    void *slot0[3];
    void (*release)(Source_26bbc0 *self);          /* +0x0c */
    void *slot4[5];
    int (*position)(Source_26bbc0 *self, int which); /* +0x24 */
} SourceTable_26bbc0;
struct Source_26bbc0 {
    SourceTable_26bbc0 *table;
};

typedef struct Handle_26bbc0 {
    char f0;
    signed char state;          /* 0x01 */
    char mode;                  /* 0x02 */
    char pad3;
    void *stream;               /* 0x04 */
    void *request;              /* 0x08 */
    void *f12;                  /* 0x0c */
    int f16;                    /* 0x10 */
    Source_26bbc0 *source;      /* 0x14 */
    char pad24[36];
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
    char pad120[52];
    char f172;                  /* 0xac */
    char pad173[3];
    char *name;                 /* 0xb0 */
    char *cursor;               /* 0xb4 */
    int f184;                   /* 0xb8 */
    int f188;                   /* 0xbc */
    int f192;                   /* 0xc0 */
} Handle_26bbc0;

extern char DAT_004eecd8[];
void FUN_002607e8(const char *message);
void FUN_0026bc60(void);
char *strcpy(char *dst, const char *src);
void FUN_0026d158(Handle_26bbc0 *handle, int value);

void FUN_0026d6e8(Handle_26bbc0 *handle, const char *name, int f188, int f192) {
    if (handle == 0 || name == 0) {
        FUN_002607e8(DAT_004eecd8);
        return;
    }
    FUN_0026bc60();
    strcpy(handle->name, name);
    handle->cursor = handle->name;
    handle->f188 = f188;
    handle->f192 = f192;
    handle->f184 = 0;
    handle->state = 1;
    handle->f172 = 1;
    handle->mode = 0;
    FUN_0026d158(handle, 0);
}
