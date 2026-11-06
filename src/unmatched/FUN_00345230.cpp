extern "C" {
void *beSelectCtrlInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00345230(void);
}
void FUN_00345230(void)
{
    igMetaObject_RunStaticInit(beSelectCtrlInfo_Register);
}
