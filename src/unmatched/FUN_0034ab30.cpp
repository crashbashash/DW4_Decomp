extern "C" {
void *beSvSlotData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0034ab30(void);
}
void FUN_0034ab30(void)
{
    igMetaObject_RunStaticInit(beSvSlotData_Register);
}
