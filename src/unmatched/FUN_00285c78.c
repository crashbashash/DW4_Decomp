typedef struct { char *data; int len; } Chunk;
typedef struct SjObj SjObj;
typedef struct {
    char pad0[24];
    void (*getChunk)(SjObj *sj, int id, int n, Chunk *ck);
    void (*ungetChunk)(SjObj *sj, int id, Chunk *ck);
    void (*putChunk)(SjObj *sj, int id, Chunk *ck);
} SjVtbl;
struct SjObj { SjVtbl *vt; };
typedef struct {
    char pad0[776];
    int ext_state;          /* +776 */
    int expected_ext_id;    /* +780 */
    char pad784[488];
    int error_count;        /* +1272 */
} Mpeg2Hdr;
typedef struct { char pad0[352]; Mpeg2Hdr hdr; } Mpeg2Ctx;

int FUN_00290898(SjObj *sj);
char *FUN_0028a260();
char *FUN_00289d08();
char *FUN_00286d28();
char *FUN_00286958();
char *FUN_00286010();
char *FUN_00286838();
void FUN_0027d470(Chunk *src, int n, Chunk *head, Chunk *tail);

int FUN_00285c78(Mpeg2Ctx *ctx, SjObj *sj) {
    Mpeg2Hdr *h = &ctx->hdr;
    Chunk ck;
    Chunk rest;
    int code;
    int saved;
    int ret = 0;
    char *end;

    h->ext_state = 0;
    saved = h->error_count;
    h->expected_ext_id = 0;
    h->error_count = 0;
    while ((code = FUN_00290898(sj)) != 0) {
        sj->vt->getChunk(sj, 1, 0x7FFFFFFF, &ck);
        end = 0;
        switch (code) {
        case 64:
            end = FUN_00286010(ctx, ck.data);
            break;
        case 128:
            end = FUN_00286838(ctx, ck.data);
            break;
        case 32:
            end = FUN_00286958(ctx, ck.data);
            break;
        case 16:
            end = FUN_00286d28(ctx, ck.data);
            break;
        case 8:
            end = FUN_00289d08(ctx, ck.data);
            break;
        case 4:
            end = FUN_0028a260(ctx, ck.data);
            break;
        }
        if (end == 0) {
            sj->vt->ungetChunk(sj, 1, &ck);
            break;
        }
        FUN_0027d470(&ck, end - ck.data, &ck, &rest);
        sj->vt->putChunk(sj, 0, &ck);
        sj->vt->ungetChunk(sj, 1, &rest);
        if (h->error_count != 0) {
            ret = -2;
            break;
        }
    }
    h->error_count += saved;
    return ret;
}
