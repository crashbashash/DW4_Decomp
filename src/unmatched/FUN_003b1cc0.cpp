extern "C" {
void *beNDMWWindowList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b1cc0(void);
}
void FUN_003b1cc0(void)
{
    igMetaObject_RunStaticInit(beNDMWWindowList_Register);
}
