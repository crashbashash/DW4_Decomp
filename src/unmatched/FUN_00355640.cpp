struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_00355720();
extern S *DAT_00588da0[4];
void *FUN_00355640(void);
}
void *FUN_00355640(void) {
    bool ok;
    if (DAT_00588da0[0] == 0) goto make;
    ok = !!(DAT_00588da0[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_00355720();
done:;
    return DAT_00588da0[0];
}
