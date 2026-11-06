extern "C" {
void *beNDMWWindowSelect_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b5900(void);
}
void FUN_003b5900(void)
{
    igMetaObject_RunStaticInit(beNDMWWindowSelect_Register);
}
