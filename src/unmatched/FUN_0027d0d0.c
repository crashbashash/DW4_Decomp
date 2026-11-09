typedef struct {
    char *ptr;
    int len;
} CriSjChunk;

typedef struct CriNode CriNode;
struct CriNode {
    CriNode *next;
    int f4;
    CriSjChunk ck;
};

typedef struct {
    int f0;
    signed char used;
    signed char merge;
    char pad6[2];
    int f8;
    int f12;
    int f16;
    CriNode *free;
    CriNode *line[4];
    void (*err)(int, int);
    int errobj;
} SjList;

void FUN_0027b2e0(const char *message);
extern char DAT_004f22e8[];
extern char DAT_004f2318[];

void FUN_0027d0d0(SjList *sj, unsigned int line, CriSjChunk *ck)
{
    CriNode *n;

    if (sj == 0) {
        FUN_0027b2e0(DAT_004f22e8);
        return;
    }
    if (sj->used == 0) {
        FUN_0027b2e0(DAT_004f2318);
        return;
    }
    if (line >= 4) {
        if (sj->err != 0) {
            sj->err(sj->errobj, -3);
        }
        return;
    }
    if (ck->len <= 0 || ck->ptr == 0) {
        return;
    }
    n = sj->line[line];
    if (sj->merge == 1 && n != 0 && ck->ptr + ck->len == n->ck.ptr) {
        n->ck.ptr = ck->ptr;
        n->ck.len += ck->len;
        return;
    }
    n = sj->free;
    if (n == 0) {
        if (sj->err != 0) {
            sj->err(sj->errobj, -3);
        }
        return;
    }
    sj->free = n->next;
    n->ck = *ck;
    n->next = 0;
    n->next = sj->line[line];
    sj->line[line] = n;
}
