extern "C" {
void *beNDMWMdlPBullet_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c0aa0(void);
}
void FUN_003c0aa0(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlPBullet_Register);
}
