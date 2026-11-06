extern "C" {
void *beNDMWTitle2Option_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b2370(void);
}
void FUN_003b2370(void)
{
    igMetaObject_RunStaticInit(beNDMWTitle2Option_Register);
}
