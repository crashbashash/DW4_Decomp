extern "C" {
void beNDMWItemBase_ResolveMetaObject(void);
void beNDMWItemBase_GetMetaObject(void);
}
void beNDMWItemBase_GetMetaObject(void)
{
    beNDMWItemBase_ResolveMetaObject();
}
