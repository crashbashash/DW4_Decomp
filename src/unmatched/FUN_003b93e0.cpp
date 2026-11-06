extern "C" {
void *beNDMWStatusCtrlSkill_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b93e0(void);
}
void FUN_003b93e0(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusCtrlSkill_Register);
}
