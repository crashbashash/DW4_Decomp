struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_003346f0();
extern S *DAT_00587630[4];
void *FUN_00334660(void);
}
void *FUN_00334660(void) {
    bool ok;
    if (DAT_00587630[0] == 0) goto make;
    ok = !!(DAT_00587630[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_003346f0();
done:;
    return DAT_00587630[0];
}
