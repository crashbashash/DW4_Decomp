int FUN_002eb010();
int FUN_00307700();
void *FUN_00307c10();
int StringChunk_ReleaseHeader();
int StringPool_Construct();
int *StringPool_Intern();
extern char *DAT_004c22f0[4];
extern int DAT_00586f20[4];
typedef struct ShortStr { char pad[8]; char *text; } ShortStr;
typedef struct Pair { char pad[12]; ShortStr *value; } Pair;
static inline int pool(void) {
    int p;
    if (DAT_00586f20[0] == 0) {
        p = FUN_002eb010(0x10);
        if (p != 0) {
            p = StringPool_Construct(p);
        }
        DAT_00586f20[0] = p;
    }
    return DAT_00586f20[0];
}
static inline char *text(ShortStr *s) { char *t = s->text; if (t == 0) { return DAT_004c22f0[0]; } return t; }
static inline void assign(int **slot, char *s) {
    int *v = StringPool_Intern(pool(), s);
    int *old = *slot;
    int *hd;
    int rc;
    if (old != 0) {
        hd = old - 2;
        rc = old[-1] - 1;
        old[-1] = rc;
        if (rc == 0) {
            StringChunk_ReleaseHeader(*hd, hd);
        }
    }
    *slot = v;
}
int FUN_00306910(int arg0, int arg1, int arg2, int **out, char *def, int create) {
    Pair *p;

    p = FUN_00307c10(arg0, arg1, arg2, 0);
    if (p != 0) {
        assign(out, text(p->value));
    } else {
        assign(out, def);
        if (create != 0) {
            FUN_00307700(arg0, arg1, arg2, def);
        }
    }
    return p != 0;
}
