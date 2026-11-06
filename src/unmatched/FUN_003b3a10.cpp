extern "C" {
void *beNDMWStatusTitle02_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b3a10(void);
}
void FUN_003b3a10(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusTitle02_Register);
}
