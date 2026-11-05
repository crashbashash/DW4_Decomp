int CreateSema();
struct SemaParam { int a[6]; };
extern int DAT_00490b60[4];
extern struct SemaParam DAT_00496500;
extern struct SemaParam DAT_00496520;
extern unsigned int DAT_0056c330[4];
extern unsigned int DAT_0056c630[4];
extern int DAT_0056c638[4];
extern int DAT_0056c640[4];
void FUN_0020df10(void) {
    struct SemaParam s30;
    struct SemaParam s10;
    unsigned int *cur;
    unsigned int *prev;
    s30 = DAT_00496500;
    s10 = DAT_00496520;
    if (DAT_00490b60[0] != 0) {
        DAT_0056c638[0] = CreateSema(&s30);
        DAT_0056c640[0] = CreateSema(&s10);
        prev = &DAT_0056c630[0];
        for (cur = &DAT_0056c330[0]; cur < (unsigned int *)((char *)DAT_0056c330 + 768); cur += 3) {
            *prev = (unsigned int)cur;
            *cur = 0;
            prev = cur;
        }
    }
}
