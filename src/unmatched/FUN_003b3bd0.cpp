extern "C" {
void *beNDMWStatusTitle01_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b3bd0(void);
}
void FUN_003b3bd0(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusTitle01_Register);
}
