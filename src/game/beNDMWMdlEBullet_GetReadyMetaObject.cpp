struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_003c1de0();
extern S *DAT_0058b520[4];
void *beNDMWMdlEBullet_GetReadyMetaObject(void);
}
void *beNDMWMdlEBullet_GetReadyMetaObject(void) {
    bool ok;
    if (DAT_0058b520[0] == 0) goto make;
    ok = !!(DAT_0058b520[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_003c1de0();
done:;
    return DAT_0058b520[0];
}
