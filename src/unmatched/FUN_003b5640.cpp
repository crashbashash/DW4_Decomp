extern "C" {
void *beNDMWStatusSelect01_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b5640(void);
}
void FUN_003b5640(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusSelect01_Register);
}
