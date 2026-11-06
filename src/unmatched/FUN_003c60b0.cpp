extern "C" {
void *beNDMWMcSlot_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c60b0(void);
}
void FUN_003c60b0(void)
{
    igMetaObject_RunStaticInit(beNDMWMcSlot_Register);
}
