typedef struct { int size; int count; char *rd; char *wr; char buf[16]; } Q;
void FUN_0010c2d0(Q *q) {
    q->count--;
    if (++q->rd == q->buf + q->size) q->rd = q->buf;
}
