struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_003601e0();
extern S *DAT_00589560[4];
void *FUN_003600b0(void);
}
void *FUN_003600b0(void) {
    bool ok;
    if (DAT_00589560[0] == 0) goto make;
    ok = !!(DAT_00589560[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_003601e0();
done:;
    return DAT_00589560[0];
}
