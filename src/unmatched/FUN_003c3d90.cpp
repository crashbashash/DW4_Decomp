extern "C" {
void *beNDMWLoadIntf2DegiStateList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c3d90(void);
}
void FUN_003c3d90(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2DegiStateList_Register);
}
