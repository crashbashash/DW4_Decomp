extern "C" {
void *beMatCtrlInfoWork_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00359640(void);
}
void FUN_00359640(void)
{
    igMetaObject_RunStaticInit(beMatCtrlInfoWork_Register);
}
