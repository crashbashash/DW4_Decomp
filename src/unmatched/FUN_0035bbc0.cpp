struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_0035bc50();
extern S *DAT_00589230[4];
void *FUN_0035bbc0(void);
}
void *FUN_0035bbc0(void) {
    bool ok;
    if (DAT_00589230[0] == 0) goto make;
    ok = !!(DAT_00589230[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_0035bc50();
done:;
    return DAT_00589230[0];
}
