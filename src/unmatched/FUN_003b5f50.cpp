struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_003b6110();
extern S *DAT_0058ac48[4];
void *FUN_003b5f50(void);
}
void *FUN_003b5f50(void) {
    bool ok;
    if (DAT_0058ac48[0] == 0) goto make;
    ok = !!(DAT_0058ac48[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_003b6110();
done:;
    return DAT_0058ac48[0];
}
