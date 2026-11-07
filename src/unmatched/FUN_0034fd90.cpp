struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_0034fe80();
extern S *DAT_00588860[4];
void *FUN_0034fd90(void);
}
void *FUN_0034fd90(void) {
    bool ok;
    if (DAT_00588860[0] == 0) goto make;
    ok = !!(DAT_00588860[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_0034fe80();
done:;
    return DAT_00588860[0];
}
