extern "C" {
void *beNDMWMdlEnemyInfoWork_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c1a00(void);
}
void FUN_003c1a00(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlEnemyInfoWork_Register);
}
