extern "C" {
void *beGroupKeepList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0035eee0(void);
}
void FUN_0035eee0(void)
{
    igMetaObject_RunStaticInit(beGroupKeepList_Register);
}
