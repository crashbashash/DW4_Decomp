extern "C" {
void *beNDMWWindow_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b1e70(void);
}
void FUN_003b1e70(void)
{
    igMetaObject_RunStaticInit(beNDMWWindow_Register);
}
