extern "C" {
extern int DAT_00586f20[4];
typedef struct L { char p[8]; int n; char q[4]; int **data; } L;
typedef struct G { char p[52]; L *f52; } G;
extern G *DAT_0058a1b8[4];

int FUN_002eb010(int);
int List_Reserve(L *, int, int);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
int StringPool_Intern(int, int);
void CFLclear(void);
}

void CFLclear(void) {
    L *s5;
    int s4;
    int i;
    int **slot;
    int *s1;
    int off;
    int *old;
    int v;
    s5 = DAT_0058a1b8[0]->f52;
    s4 = s5->n;
    i = 0;
    if (0 < s4) {
        off = 0;
        do {
            slot = (int **)((char *)s5->data + off);
            if (DAT_00586f20[0] == 0) {
                v = FUN_002eb010(0x10);
                if (v != 0) {
                    v = StringPool_Construct(v);
                }
                DAT_00586f20[0] = v;
            }
            s1 = (int *)StringPool_Intern(DAT_00586f20[0], 0);
            old = *slot;
            if (old != 0) {
                int *hdr = old - 2;
                int r = old[-1] - 1;
                old[-1] = r;
                if (r == 0) {
                    StringChunk_ReleaseHeader(*hdr, hdr);
                }
            }
            i += 1;
            *slot = s1;
            off += 4;
        } while (i < s4);
    }
    s5->n = 0;
    {
        L *l2 = DAT_0058a1b8[0]->f52;
        if (!(0 < l2->n)) {
            List_Reserve(l2, 0, 4);
        }
    }
}
