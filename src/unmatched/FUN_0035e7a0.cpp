extern "C" {
void *beHitLandDelivInfoRam_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0035e7a0(void);
}
void FUN_0035e7a0(void)
{
    igMetaObject_RunStaticInit(beHitLandDelivInfoRam_Register);
}
