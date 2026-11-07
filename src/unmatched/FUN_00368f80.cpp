struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_00369060();
extern S *DAT_00589be8[4];
void *FUN_00368f80(void);
}
void *FUN_00368f80(void) {
    bool ok;
    if (DAT_00589be8[0] == 0) goto make;
    ok = !!(DAT_00589be8[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_00369060();
done:;
    return DAT_00589be8[0];
}
