typedef struct { int size; int count; char *rd; char *wr; char buf[16]; } Q;
extern Q DAT_00555ac0;
Q *FUN_0010c268(int size) {
    Q *q = &DAT_00555ac0;
    q->size = size;
    q->count = 0;
    q->wr = q->buf;
    q->rd = q->buf;
    return q;
}
