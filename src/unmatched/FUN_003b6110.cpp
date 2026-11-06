extern "C" {
void *beNDMWStatusInfoWork_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b6110(void);
}
void FUN_003b6110(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusInfoWork_Register);
}
