extern "C" {
void *beNDMWTitle2Info_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b21a0(void);
}
void FUN_003b21a0(void)
{
    igMetaObject_RunStaticInit(beNDMWTitle2Info_Register);
}
