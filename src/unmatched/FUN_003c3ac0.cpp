extern "C" {
void *beNDMWLoadIntf2DegiStateCtrl_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c3ac0(void);
}
void FUN_003c3ac0(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2DegiStateCtrl_Register);
}
