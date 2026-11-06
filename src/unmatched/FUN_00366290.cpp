extern "C" {
void *beDBManager_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00366290(void);
}
void FUN_00366290(void)
{
    igMetaObject_RunStaticInit(beDBManager_Register);
}
