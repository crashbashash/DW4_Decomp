extern "C" {
void *beModelCtrlPDMOVE_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003552a0(void);
}
void FUN_003552a0(void)
{
    igMetaObject_RunStaticInit(beModelCtrlPDMOVE_Register);
}
