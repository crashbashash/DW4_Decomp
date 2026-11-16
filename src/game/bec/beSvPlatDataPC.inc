igMetaObject *g_beSvPlatDataPC_metaObject;

void *beSvPlatDataPC_GetMetaObject(void) {
    bool ok;
    if (g_beSvPlatDataPC_metaObject == 0) goto make;
    ok = !!(g_beSvPlatDataPC_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beSvPlatDataPC_EnsureRegistered();
done:;
    return g_beSvPlatDataPC_metaObject;
}

int beSvPlatDataPC_GetVTable(void) {
    beSvPlatDataPC obj;
    int vtable;
    igObject **slotListSlot;

    igObject_InitHeader(&obj);
    slotListSlot = (igObject **)&obj._slotList;
    *slotListSlot = 0;
    obj._vtable = (int)&g_beSvPlatBaseData_vtable[0];
    obj._vtable = (int)&g_beSvPlatDataPC_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beSvPlatBaseData_vtable[0];
    igObjectRef_Release(slotListSlot);
    return vtable;
}

O_347150 *beSvPlatBaseData_Destroy(O_347150 *arg0, short arg1) {
    Q *t;

    if (arg0 != 0) {
        arg0->vt = &g_beSvPlatBaseData_vtable[0];
        if (&arg0->m != 0) {
            t = arg0->m;
            if (t != 0) {
                t->f4 -= 1;
                if ((t->f4 & 0x7fffff) == 0) {
                    igObject_Destroy(t);
                }
            }
        }
        if (arg1 > 0) {
            Memory_FreeBufferAliasC(arg0);
        }
    }
    return arg0;
}

void beSvPlatDataPC_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvPlatDataPC_Register);
}

void *beSvPlatDataPC_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvPlatDataPC_metaObject,
        beSvPlatBaseData_Register,
        beSvPlatBaseData_GetPublishedMetaObject,
        beSvPlatDataPC_GetMetaObjectFunction,
        "beSvPlatDataPC",
        0x18, /* instance size */
        beSvPlatDataPC_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvPlatDataPC_GetMetaObjectFunction(void)
{
    beSvPlatDataPC_GetMetaObject();
}

igMetaObject *beSvPlatBaseData_GetPublishedMetaObject(void) {
    return g_beSvPlatBaseData_metaObject;
}

