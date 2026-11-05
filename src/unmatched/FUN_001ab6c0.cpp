extern "C" {
int igStrCmp(...);
extern int DAT_004e0858[4];
}
struct E { char pad[8]; int *f8; };
struct L { char pad[8]; int count; char pad1[4]; E **data; };
struct S { char pad[20]; L *f20; };
extern "C" {
int FUN_001ab6c0(S *arg0, int arg1);
}
int FUN_001ab6c0(S *arg0, int arg1) {
    int i;
    int n;
    int *s;

    n = arg0->f20->count;
    for (i = 0; i < n; i++) {
        s = arg0->f20->data[i]->f8;
        s = s != 0 ? s : &DAT_004e0858[0];
        if (igStrCmp(s, arg1) == 0) {
            return i;
        }
    }
    return -1;
}
