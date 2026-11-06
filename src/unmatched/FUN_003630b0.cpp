extern "C" {
void *beFileChkObj_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003630b0(void);
}
void FUN_003630b0(void)
{
    igMetaObject_RunStaticInit(beFileChkObj_Register);
}
