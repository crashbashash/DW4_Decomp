struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_0045c680();
extern S *DAT_0058cbf8[4];
void *igRotateMode_GetMetaObject(void);
}
void *igRotateMode_GetMetaObject(void) {
    bool ok;
    if (DAT_0058cbf8[0] == 0) goto make;
    ok = !!(DAT_0058cbf8[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_0045c680();
done:;
    return DAT_0058cbf8[0];
}
