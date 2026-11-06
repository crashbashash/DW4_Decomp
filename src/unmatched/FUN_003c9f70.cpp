extern "C" {
void *beNDMWGameRam_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c9f70(void);
}
void FUN_003c9f70(void)
{
    igMetaObject_RunStaticInit(beNDMWGameRam_Register);
}
