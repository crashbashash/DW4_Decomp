struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_00362690();
extern S *DAT_005896d8[4];
void *FUN_00362530(void);
}
void *FUN_00362530(void) {
    bool ok;
    if (DAT_005896d8[0] == 0) goto make;
    ok = !!(DAT_005896d8[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_00362690();
done:;
    return DAT_005896d8[0];
}
