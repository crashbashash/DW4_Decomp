struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_003536e0();
extern S *DAT_00588be8[4];
void *FUN_003535b0(void);
}
void *FUN_003535b0(void) {
    bool ok;
    if (DAT_00588be8[0] == 0) goto make;
    ok = !!(DAT_00588be8[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_003536e0();
done:;
    return DAT_00588be8[0];
}
