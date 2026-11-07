struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_00359980();
extern S *DAT_005890d8[4];
void *FUN_003597c0(void);
}
void *FUN_003597c0(void) {
    bool ok;
    if (DAT_005890d8[0] == 0) goto make;
    ok = !!(DAT_005890d8[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_00359980();
done:;
    return DAT_005890d8[0];
}
