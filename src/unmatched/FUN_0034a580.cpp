extern "C" {
void *beSvSlotDataList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0034a580(void);
}
void FUN_0034a580(void)
{
    igMetaObject_RunStaticInit(beSvSlotDataList_Register);
}
