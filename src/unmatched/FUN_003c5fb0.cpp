extern "C" {
void *beNDMWMcSlotPS2_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c5fb0(void);
}
void FUN_003c5fb0(void)
{
    igMetaObject_RunStaticInit(beNDMWMcSlotPS2_Register);
}
