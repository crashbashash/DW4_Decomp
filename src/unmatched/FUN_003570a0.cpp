struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_00357170();
extern S *DAT_00588ea0[4];
void *FUN_003570a0(void);
}
void *FUN_003570a0(void) {
    bool ok;
    if (DAT_00588ea0[0] == 0) goto make;
    ok = !!(DAT_00588ea0[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_00357170();
done:;
    return DAT_00588ea0[0];
}
