struct S { int a; int b; int c; };
int FUN_004578c0(void *, struct S *);
extern int DAT_0058cb08[4];
void FUN_00462d30(void *arg0) {
    struct S s;
    *(int *)((char *)(*(int *)((char *)(arg0) + 20)) + 244) = 1;
    s.a = 2;
    s.b = 0;
    s.c = DAT_0058cb08[0];
    FUN_004578c0(*(void **)((char *)(arg0) + 20), &s);
}
