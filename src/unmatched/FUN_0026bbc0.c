/* Between FUN_0025f2d0 and FUN_0025f2e8, stops a handle: resets its field-12 object (FUN_00265cb8,
 * FUN_00265cd0, FUN_0027a948), detaches its stream with FUN_002662c8, releases its source in mode
 * 2, frees field 116 with FUN_0025b610 and clears the state. */
/* Handle layout shared by FUN_0026bb38 through FUN_0026ebf8. */
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

void FUN_0025f2d0(void);
void FUN_0025f2e8(void);
void FUN_00265cb8(void *object, int value);
void FUN_00265cd0(void *object, int value);
void FUN_0027a948(void *object, int value);
void FUN_002662c8(void *stream);
void FUN_0025b610(void *object);

void FUN_0026bbc0(Handle_26bbc0 *handle) {
    Source_26bbc0 *source;

    FUN_0025f2d0();
    FUN_00265cb8(handle->f12, 0);
    FUN_00265cd0(handle->f12, 0);
    FUN_0027a948(handle->f12, 1);
    FUN_002662c8(handle->stream);
    if (handle->mode == 2) {
        source = handle->source;
        if (source != 0) {
            handle->source = 0;
            source->table->release(source);
        }
    }
    if (handle->f116 != 0) {
        FUN_0025b610(handle->f116);
    }
    handle->source = 0;
    handle->state = 0;
    handle->f172 = 0;
    FUN_0025f2e8();
}
