extern "C" {
void *beSaveDataDeliver_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0034af90(void);
}
void FUN_0034af90(void)
{
    igMetaObject_RunStaticInit(beSaveDataDeliver_Register);
}
