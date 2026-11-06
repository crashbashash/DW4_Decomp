extern "C" {
void *beNDMWMdlEBullet_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c1de0(void);
}
void FUN_003c1de0(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlEBullet_Register);
}
