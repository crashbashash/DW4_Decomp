typedef struct { char *buf; int size; int pos; } Buf;
typedef struct { char pad[328]; Buf b; } Dec;
void *memcpy();
void FUN_00286ce8(Dec *d, void *src, int len) {
    Buf *b = &d->b;
    int n = b->size - b->pos;
    char *dst = b->buf + b->pos;
    if (len < n) n = len;
    b->pos += n;
    memcpy(dst, src, n);
}
