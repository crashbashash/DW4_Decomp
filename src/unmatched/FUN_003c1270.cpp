extern "C" {
void *beNDMWMdlItem_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c1270(void);
}
void FUN_003c1270(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlItem_Register);
}
