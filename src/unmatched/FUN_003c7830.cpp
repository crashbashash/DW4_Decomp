extern "C" {
void *beNDMWLoadIntf2TextOrder_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c7830(void);
}
void FUN_003c7830(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2TextOrder_Register);
}
