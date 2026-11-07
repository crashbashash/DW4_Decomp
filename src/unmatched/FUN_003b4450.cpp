struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_003b4520();
extern S *DAT_0058ab90[4];
void *FUN_003b4450(void);
}
void *FUN_003b4450(void) {
    bool ok;
    if (DAT_0058ab90[0] == 0) goto make;
    ok = !!(DAT_0058ab90[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_003b4520();
done:;
    return DAT_0058ab90[0];
}
