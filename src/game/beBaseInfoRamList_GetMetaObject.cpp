extern "C" {
void *beBaseInfoRamList_GetReadyMetaObject(void);
void *beBaseInfoRamList_GetMetaObject(void);
}
void *beBaseInfoRamList_GetMetaObject(void)
{
    return beBaseInfoRamList_GetReadyMetaObject();
}
