/* Starts ADXT playback: resets each channel stream (vtable +20, count at +3, streams at +24),
 * starts the source (+4) with the argument (FUN_002661d8, also kept at +20) and ADXSJD_Start, sets
 * the state byte (+1) to 1 and resets the playback counters (+76, +113, +140, +144, +156, +160
 * from adxt_vsync_cnt, +164); kicks the attached object (+116) with FUN_0025b470 when present. */
typedef struct Stream_26b978 Stream_26b978;
typedef struct StreamVtbl_26b978 {
    void *pad0[5];
    void (*reset)(Stream_26b978 *stream);  /* 0x14 */
} StreamVtbl_26b978;
struct Stream_26b978 {
    StreamVtbl_26b978 *vtbl;  /* 0x00 */
};

typedef struct Adxt_26b978 {
    signed char pad0;
    signed char state;          /* 0x01 */
    signed char pad2;
    signed char channels;       /* 0x03 */
    int source;                 /* 0x04 */
    char pad8[12];
    int start_arg;              /* 0x14 */
    Stream_26b978 *streams[2];  /* 0x18 */
    char pad32[44];
    int f76;                /* 0x4c */
    char pad80[33];
    signed char f113;        /* 0x71 */
    char pad114[2];
    int attached;               /* 0x74 */
    char pad120[20];
    int limit;                  /* 0x8c */
    int last;                   /* 0x90 */
    char pad148[8];
    int f156;               /* 0x9c */
    int setting;                /* 0xa0 */
    int f164;               /* 0xa4 */
} Adxt_26b978;

extern int adxt_vsync_cnt;
void FUN_002661d8(int source, int arg);
int ADXSJD_Start(int source);
void FUN_0025b470(int attached);

void FUN_0026b978(Adxt_26b978 *adxt, int arg) {
    int i;

    for (i = 0; i < adxt->channels; i++) {
        adxt->streams[i]->vtbl->reset(adxt->streams[i]);
    }
    FUN_002661d8(adxt->source, arg);
    adxt->start_arg = arg;
    ADXSJD_Start(adxt->source);
    /* matching construct: statement-order sweep — limit is written before last */
    adxt->state = 1;
    adxt->limit = 0x7fffffff;
    adxt->last = -1;
    adxt->f76 = 0;
    adxt->f113 = 0;
    adxt->f156 = 0;
    adxt->f164 = 0;
    adxt->setting = adxt_vsync_cnt;
    if (adxt->attached != 0) {
        FUN_0025b470(adxt->attached);
    }
}
