extern "C" {
void beNDMWShinkaObject_ResolveMetaObject(void);
void beNDMWShinkaObject_GetMetaObject(void);
}
void beNDMWShinkaObject_GetMetaObject(void)
{
    beNDMWShinkaObject_ResolveMetaObject();
}
