extern "C" {
void *beWaterMoveDataList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00340800(void);
}
void FUN_00340800(void)
{
    igMetaObject_RunStaticInit(beWaterMoveDataList_Register);
}
