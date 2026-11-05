extern "C" {
int FUN_002eb010(int);
void *FUN_003a92e0(int, int *);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
void *StringPool_Intern(int, int *);
int beMessenger_GetObject(int, int);
int beMessenger_SendGroup(int, int *, int *);
void *igProperty_GetRecord(int, int *);
extern int DAT_0050d8f0[4];
extern int DAT_0050d940[4];
extern int DAT_0050d9a8[4];
extern int DAT_0050d9b8[4];
extern int DAT_0050d9c8[4];
extern int DAT_00586f20[4];
extern int DAT_0058a1c0[4];
typedef struct R { char p[12]; int *f12; } R;
void SYSsetGateStage(int *arg0, int arg1);
}

void SYSsetGateStage(int *arg0, int arg1) {
    int obj;
    int v;
    R *rec;
    int *s0;
    int *old;
    int *hd;
    int v1;

    beMessenger_SendGroup(DAT_0058a1c0[0], &DAT_0050d940[0], &DAT_0050d8f0[0]);
    obj = beMessenger_GetObject(DAT_0058a1c0[0], 0);
    *(int *)((char *)igProperty_GetRecord(obj, &DAT_0050d9a8[0]) + 12) = arg1;
    if (arg0 == 0) {
        rec = (R *)FUN_003a92e0(obj, &DAT_0050d9b8[0]);
        if (DAT_00586f20[0] == 0) {
            v = FUN_002eb010(0x10);
            if (v != 0) {
                v = StringPool_Construct(v);
            }
            DAT_00586f20[0] = v;
        }
        s0 = (int *)StringPool_Intern(DAT_00586f20[0], &DAT_0050d9c8[0]);
        old = rec->f12;
        if (old != 0) {
            hd = old - 2;
            v1 = old[-1] - 1;
            old[-1] = v1;
            if (v1 == 0) {
                StringChunk_ReleaseHeader(*hd, hd);
            }
        }
        rec->f12 = s0;
        return;
    }
    rec = (R *)FUN_003a92e0(obj, &DAT_0050d9b8[0]);
    if (DAT_00586f20[0] == 0) {
        v = FUN_002eb010(0x10);
        if (v != 0) {
            v = StringPool_Construct(v);
        }
        DAT_00586f20[0] = v;
    }
    s0 = (int *)StringPool_Intern(DAT_00586f20[0], arg0);
    old = rec->f12;
    if (old != 0) {
        hd = old - 2;
        v1 = old[-1] - 1;
        old[-1] = v1;
        if (v1 == 0) {
            StringChunk_ReleaseHeader(*hd, hd);
        }
    }
    rec->f12 = s0;
}
