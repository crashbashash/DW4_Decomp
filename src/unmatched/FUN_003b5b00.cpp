extern "C" {
void *beNDMWStatusInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b5b00(void);
}
void FUN_003b5b00(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusInfo_Register);
}
