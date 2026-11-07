struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_00364930();
extern S *DAT_00589868[4];
void *FUN_00364800(void);
}
void *FUN_00364800(void) {
    bool ok;
    if (DAT_00589868[0] == 0) goto make;
    ok = !!(DAT_00589868[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_00364930();
done:;
    return DAT_00589868[0];
}
