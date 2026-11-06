extern "C" {
void *beNDMWWindowTitle_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b3e90(void);
}
void FUN_003b3e90(void)
{
    igMetaObject_RunStaticInit(beNDMWWindowTitle_Register);
}
