struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_003baaf0();
extern S *DAT_0058af30[4];
void *FUN_003baaa0(void);
}
void *FUN_003baaa0(void) {
    bool ok;
    if (DAT_0058af30[0] == 0) goto make;
    ok = !!(DAT_0058af30[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_003baaf0();
done:;
    return DAT_0058af30[0];
}
