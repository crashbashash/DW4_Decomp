extern "C" {
void beNDMWShinkaObjectList_ResolveMetaObject(void);
void beNDMWShinkaObjectList_GetMetaObject(void);
}
void beNDMWShinkaObjectList_GetMetaObject(void)
{
    beNDMWShinkaObjectList_ResolveMetaObject();
}
