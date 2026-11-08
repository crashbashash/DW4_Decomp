typedef struct { int size; int count; char *rd; char *wr; char buf[16]; } Q;
void FUN_0010c290(Q *q) {
    q->count++;
    if (++q->wr == q->buf + q->size) q->wr = q->buf;
}
