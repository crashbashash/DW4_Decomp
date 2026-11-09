int FUN_00285118(int id, int arg, int a, int b);

typedef struct SofdecStream { int f0; int id; int arg; } SofdecStream;
typedef struct SofdecBusy { int busy; } SofdecBusy;
typedef struct SofdecParams { char pad0[36]; int f36; int f40; } SofdecParams;

typedef struct SofdecDecoder {
    char pad0[3560];
    SofdecParams params;  /* +3560 */
    char pad3604[44];
    SofdecBusy busy;      /* +3648 */
    char pad3652[10216];
    SofdecStream stream;  /* +13868 */
} SofdecDecoder;

int FUN_002a6470(SofdecDecoder *dec) {
    SofdecStream *stream = &dec->stream;
    SofdecParams *params = &dec->params;
    SofdecBusy *busy = &dec->busy;
    if (stream->id < 0) {
        return 0;
    }
    if (busy->busy != 0) {
        return 0;
    }
    return FUN_00285118(stream->id, stream->arg, params->f36, params->f40) == 0;
}
