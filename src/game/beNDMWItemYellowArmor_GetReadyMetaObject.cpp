struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_003c8a40();
extern S *DAT_0058bf50[4];
void *beNDMWItemYellowArmor_GetReadyMetaObject(void);
}
void *beNDMWItemYellowArmor_GetReadyMetaObject(void) {
    bool ok;
    if (DAT_0058bf50[0] == 0) goto make;
    ok = !!(DAT_0058bf50[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_003c8a40();
done:;
    return DAT_0058bf50[0];
}
