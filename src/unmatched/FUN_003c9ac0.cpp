extern "C" {
void *beNDMWShinkaObject_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c9ac0(void);
}
void FUN_003c9ac0(void)
{
    igMetaObject_RunStaticInit(beNDMWShinkaObject_Register);
}
