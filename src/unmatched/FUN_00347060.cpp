struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_003471f0();
extern S *DAT_00588038[4];
void *FUN_00347060(void);
}
void *FUN_00347060(void) {
    bool ok;
    if (DAT_00588038[0] == 0) goto make;
    ok = !!(DAT_00588038[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_003471f0();
done:;
    return DAT_00588038[0];
}
