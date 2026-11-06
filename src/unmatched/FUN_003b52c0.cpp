extern "C" {
void *beNDMWStatusSelectE1_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b52c0(void);
}
void FUN_003b52c0(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusSelectE1_Register);
}
