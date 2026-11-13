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

void SJERR_CallErr(const char *message);
void SJ_SplitChunk(CriSjChunk *chunk, int max, CriSjChunk *head, CriSjChunk *rest);
extern char DAT_004f2228[];
extern char DAT_004f2258[];

void FUN_0027cdd8(SjList *sj, unsigned int line, int nbyte, CriSjChunk *ck)
{
    CriSjChunk head;
    CriSjChunk rest;
    CriNode *n;

    if (sj == 0) {
        SJERR_CallErr(DAT_004f2228);
        return;
    }
    if (sj->used == 0) {
        SJERR_CallErr(DAT_004f2258);
        return;
    }
    if (line >= 4) {
        if (sj->err != 0) {
            sj->err(sj->errobj, -3);
        }
    } else {
        n = sj->line[line];
        if (n != 0) {
            head = n->ck;
            if (nbyte >= head.len) {
                *ck = head;
                sj->line[line] = n->next;
                n->next = sj->free;
                sj->free = n;
                return;
            }
            if (sj->merge == 1) {
                SJ_SplitChunk(&head, nbyte, &head, &rest);
                *ck = head;
                n->ck = rest;
                return;
            }
        }
    }
    ck->ptr = 0;
    ck->len = 0;
}
