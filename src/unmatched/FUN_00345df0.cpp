extern "C" {
void *beSeInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00345df0(void);
}
void FUN_00345df0(void)
{
    igMetaObject_RunStaticInit(beSeInfo_Register);
}
