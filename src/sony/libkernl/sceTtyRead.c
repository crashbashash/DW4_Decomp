typedef struct { int size; volatile int count; char *rd; char *wr; } Q;
typedef struct { int id; int a; int b; int c; unsigned int tx; unsigned int rx; Q *q; } D;
extern D DAT_00555bd0;
void FUN_0010c2d0(Q *);
int sceTtyRead(char *buf, int n) {
    int i;
    for (i = 0; i < n; i++) {
        while (DAT_00555bd0.q->count == 0);
        buf[i] = *DAT_00555bd0.q->rd;
        FUN_0010c2d0(DAT_00555bd0.q);
        if (buf[i] == '\n' || buf[i] == '\r') return i + 1;
    }
    return i;
}
