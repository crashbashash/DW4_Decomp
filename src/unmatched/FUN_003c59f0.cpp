extern "C" {
void *beNDMWMcSlotList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c59f0(void);
}
void FUN_003c59f0(void)
{
    igMetaObject_RunStaticInit(beNDMWMcSlotList_Register);
}
