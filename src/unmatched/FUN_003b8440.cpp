struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_003b8510();
extern S *DAT_0058ade8[4];
void *FUN_003b8440(void);
}
void *FUN_003b8440(void) {
    bool ok;
    if (DAT_0058ade8[0] == 0) goto make;
    ok = !!(DAT_0058ade8[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_003b8510();
done:;
    return DAT_0058ade8[0];
}
