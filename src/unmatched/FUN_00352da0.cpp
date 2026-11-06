extern "C" {
void *beModelCtrlInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00352da0(void);
}
void FUN_00352da0(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfo_Register);
}
