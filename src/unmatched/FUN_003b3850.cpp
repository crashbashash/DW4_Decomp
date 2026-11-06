extern "C" {
void *beNDMWStatusTitle03_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b3850(void);
}
void FUN_003b3850(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusTitle03_Register);
}
