struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_003bca60();
extern S *DAT_0058b0d0[4];
void *FUN_003bc980(void);
}
void *FUN_003bc980(void) {
    bool ok;
    if (DAT_0058b0d0[0] == 0) goto make;
    ok = !!(DAT_0058b0d0[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_003bca60();
done:;
    return DAT_0058b0d0[0];
}
