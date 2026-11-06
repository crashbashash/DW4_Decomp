extern "C" {
void *beNDMWMdlEnemy_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c1860(void);
}
void FUN_003c1860(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlEnemy_Register);
}
