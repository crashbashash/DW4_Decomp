extern "C" {
void *beHitLandDeliv_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0035ed50(void);
}
void FUN_0035ed50(void)
{
    igMetaObject_RunStaticInit(beHitLandDeliv_Register);
}
