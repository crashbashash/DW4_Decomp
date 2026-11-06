extern "C" {
void *beNDMWLoadCtrl2Info_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c4a90(void);
}
void FUN_003c4a90(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadCtrl2Info_Register);
}
