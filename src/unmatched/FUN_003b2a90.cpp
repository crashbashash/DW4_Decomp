extern "C" {
void *beNDMWTitle2_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b2a90(void);
}
void FUN_003b2a90(void)
{
    igMetaObject_RunStaticInit(beNDMWTitle2_Register);
}
