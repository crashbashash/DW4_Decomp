extern "C" {
void *beNDMWLoadCtrl2_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c7ef0(void);
}
void FUN_003c7ef0(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadCtrl2_Register);
}
