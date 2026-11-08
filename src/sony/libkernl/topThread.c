typedef struct { unsigned char cmd; unsigned char arg; } Ent;
typedef struct { int idx; int x; Ent ent[512]; } R;
extern int DAT_00555680;
extern char DAT_004d2410[];
int FUN_0010af20(int);
int FUN_0010ae10(int);
int FUN_0010ad90(int);
int FUN_0010ae50(int);
int FUN_0010d0d0(const char *, ...);
void topThread(R *r) {
    int i;
    for (;;) {
        FUN_0010af20(DAT_00555680);
        i = r->idx & 0x1ff;
        r->idx = i + 1;
        switch (r->ent[i].cmd) {
        case 0:
            FUN_0010ae10(r->ent[i].arg);
            break;
        case 1:
            FUN_0010ad90(r->ent[i].arg);
            break;
        case 2:
            FUN_0010ae50(r->ent[i].arg);
            break;
        default:
            FUN_0010d0d0(DAT_004d2410);
            break;
        }
    }
}
