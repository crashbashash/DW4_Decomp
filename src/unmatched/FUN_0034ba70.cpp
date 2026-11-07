struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_0034bba0();
extern S *DAT_00588498[4];
void *FUN_0034ba70(void);
}
void *FUN_0034ba70(void) {
    bool ok;
    if (DAT_00588498[0] == 0) goto make;
    ok = !!(DAT_00588498[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_0034bba0();
done:;
    return DAT_00588498[0];
}
