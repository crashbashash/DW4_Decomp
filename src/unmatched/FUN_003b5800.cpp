extern "C" {
void *beNDMWStatusSelect00_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b5800(void);
}
void FUN_003b5800(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusSelect00_Register);
}
