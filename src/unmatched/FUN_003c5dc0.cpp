extern "C" {
void *beNDMWMcSlotGC_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c5dc0(void);
}
void FUN_003c5dc0(void)
{
    igMetaObject_RunStaticInit(beNDMWMcSlotGC_Register);
}
