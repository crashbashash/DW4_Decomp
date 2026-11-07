struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_00349cc0();
extern S *DAT_00588278[4];
void *FUN_00349b30(void);
}
void *FUN_00349b30(void) {
    bool ok;
    if (DAT_00588278[0] == 0) goto make;
    ok = !!(DAT_00588278[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_00349cc0();
done:;
    return DAT_00588278[0];
}
