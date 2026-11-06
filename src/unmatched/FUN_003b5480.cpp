extern "C" {
void *beNDMWStatusSelectE0_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b5480(void);
}
void FUN_003b5480(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusSelectE0_Register);
}
