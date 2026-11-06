extern "C" {
void *beHitLandModel_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0035da30(void);
}
void FUN_0035da30(void)
{
    igMetaObject_RunStaticInit(beHitLandModel_Register);
}
