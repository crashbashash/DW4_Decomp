typedef struct { char *data; int len; } Chunk;
typedef struct SjObj SjObj;
typedef struct {
    char pad0[24];
    void (*getChunk)(SjObj *sj, int id, int n, Chunk *ck);
    char pad28[4];
    void (*putChunk)(SjObj *sj, int id, Chunk *ck);
} SjVtbl;
struct SjObj { SjVtbl *vt; };
typedef struct {
    SjObj *sj;
    void (*cb)(int, int);
    int cbArg;
} Out;
typedef struct {
    char pad0[280];
    Out out[1];
    char pad292[36];
    int on;             /* +328 */
    char pad332[984];
    int hdr;            /* +1316 */
    char pad1320[188];
    int idx;            /* +1508 */
} Dec;
int FUN_00286ce8();
void *memcpy();
extern char DAT_004f28a8[];
void FUN_00286b70(Dec *d, char *src, int n) {
    int idx = d->idx;
    SjObj *sj = d->out[idx].sj;
    Chunk ck;
    Chunk ck2;

    if (sj != 0) {
        sj->vt->getChunk(sj, 0, n, &ck);
        memcpy(ck.data, src, ck.len);
        sj->vt->putChunk(sj, 1, &ck);
        if (ck.len < n) {
            sj->vt->getChunk(sj, 0, n - ck.len, &ck2);
            memcpy(ck2.data, src + ck.len, ck2.len);
            sj->vt->putChunk(sj, 1, &ck2);
        }
        if (d->out[idx].cb != 0) {
            d->out[idx].cb(d->out[idx].cbArg, idx);
        }
    }
    if (idx == 3 && d->on != 0) {
        if (d->hdr != 0) {
            FUN_00286ce8(d, DAT_004f28a8, 8);
        }
        FUN_00286ce8(d, src, n);
    }
}
