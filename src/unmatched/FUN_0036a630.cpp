extern "C" {
void *beBaseInfoRamTimer_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0036a630(void);
}
void FUN_0036a630(void)
{
    igMetaObject_RunStaticInit(beBaseInfoRamTimer_Register);
}
