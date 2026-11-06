extern "C" {
void *beNDMWMdlMapCursor_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c0e80(void);
}
void FUN_003c0e80(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlMapCursor_Register);
}
