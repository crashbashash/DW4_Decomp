typedef struct { char *start; int size; char *cur; int count; } Buf;
extern char DAT_004d21e8[];
int FUN_00109b10(void *, char *);
char *FUN_00109388(void *x, Buf *b, int size, unsigned int align) {
    char *p = (char *)((((unsigned int)b->cur + align - 1) / align) * align);
    char *end = p + size;
    if (b->start + b->size >= end) {
        b->cur = end;
        return p;
    }
    FUN_00109b10(x, DAT_004d21e8);
    return 0;
}
