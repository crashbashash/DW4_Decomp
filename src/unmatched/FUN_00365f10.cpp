extern "C" {
void *beDBManagerInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00365f10(void);
}
void FUN_00365f10(void)
{
    igMetaObject_RunStaticInit(beDBManagerInfo_Register);
}
