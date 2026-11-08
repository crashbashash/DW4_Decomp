extern "C" {
typedef struct N { int w[2]; char *name; int w3[3]; int val; } N;
typedef struct L { int w[2]; int cnt; int w3; N **arr; } L;
extern char DAT_0050e480[], DAT_004e0858[];
int strcmp(char *, char *);
void FUN_002829f0(int, int);
void FUN_0037dc60(int *arg0, char *arg1);
}

void FUN_0037dc60(int *arg0, char *arg1) {
    L *t = (L *)arg0[11];
    N *s0;
    if (t->cnt > 0) {
        s0 = t->arr[0];
        if (arg1 == 0) {
            arg1 = DAT_0050e480;
        }
        if (strcmp(arg1, s0->name != 0 ? s0->name : DAT_004e0858) == 0) {
            FUN_002829f0(0xA4000000, s0->val);
            return;
        }
        FUN_002829f0(0xA4000000, 0x7F);
        return;
    }
    FUN_002829f0(0xA4000000, 0x7F);
}
