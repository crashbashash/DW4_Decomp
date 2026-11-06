extern "C" {
void *beNDMWStatusInfoRam_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b5d70(void);
}
void FUN_003b5d70(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusInfoRam_Register);
}
