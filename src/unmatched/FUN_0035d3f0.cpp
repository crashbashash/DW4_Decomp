extern "C" {
void *beHitLandModelInfoRam_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0035d3f0(void);
}
void FUN_0035d3f0(void)
{
    igMetaObject_RunStaticInit(beHitLandModelInfoRam_Register);
}
