igMetaObject *g_igVectorBlending_metaObject;

igMetaObject *FUN_00186ee0(void)
{
    unsigned char ready;
    if (g_igVectorBlending_metaObject != 0) {
        ready = (g_igVectorBlending_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_00186f70();
done:
    return g_igVectorBlending_metaObject;
}

int igVectorBlending_GetVTable(void) {
    struct Obj3 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igVectorBlending_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
}

void FUN_00186f70(void)
{
    igMetaObject_RunStaticInit(igVectorBlending_Register);
}

CallbackArray *igVectorBlending_Register(void) {
    FUN_00186a40();  /* Set-once guard (gp-relative byte flag) that chains to sibling registrars. */
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igVectorBlending_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        (igMetaObjectCallback)thunk_igVectorBlending_GetMetaObject_00186ff0,
        "igVectorBlending",
        8, /* instance size */
        igVectorBlending_GetVTable,
        0,
        FUN_00187000,                                  /* static-initializer callback item (appended on fresh configuration) */
        0                                              /* 0-terminated dependency-callback list */
    );
}

void thunk_FUN_00186ee0(void) {
    FUN_00186ee0();
}

void FUN_00187000(void) {
    FUN_0018e9b0();
}

