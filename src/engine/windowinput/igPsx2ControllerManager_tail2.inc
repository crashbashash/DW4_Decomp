void Gap__igPsx2ControllerManager__vfunc_24(igPsx2ControllerManager *arg0, int arg1) {
    PropertyText *sp8C;
    void *al;
    char *s0;
    int s3;
    int s2;
    Al *al2;
    int s1;
    int v1;
    void *base;
    int mem;
    igObject *q;
    if (GPR_00554b18 == 0) {
        GPR_00554b18 = 1;
        arg0->_validControllerManager = 1;
        if (arg0->_loadIRXs != 0) {
            FUN_0032cf50(&DAT_004d7020[0], 1, 0, 0);
            FUN_0032cf50(&DAT_004d7030[0], 1, 0, 0);
        }
        FUN_00117c78(0);
        base = igObject_GetAllocator(arg0);
        if (GPR_00554c14 != 0) {
            al = base;
        } else {
            al = Memory_GetAllocatorBySelector(g_temporaryAllocatorSelector[0]);
        }
        sp8C = (PropertyText *)FUN_002b9500(al);
        if (FUN_00306770(g_objectSystem[0]->f56, 3, &DAT_004d7040[0], &sp8C, &DAT_004d7050[0], 0) != 0) {
            s0 = sp8C->chars;
            s0 = (s0 == 0) ? g_stringObjEmptyText[0] : s0;
            if (strcmp(s0, &DAT_004d6ce0[0]) == 0) {
                v1 = 0xFFFF;
                arg0->_multitap = v1;
            } else if (strcmp(s0, &DAT_004d6cc8[0]) == 0) {
                arg0->_multitap = 0;
            } else if (strncmp(s0, &DAT_004d7058[0], 4) == 0) {
                v1 = 2;
                if (s0[4] == 0x30) { v1 = 1; arg0->_multitap = v1; } else { arg0->_multitap = v1; }
            }
        }
        q = sp8C;
        if (q != 0) {
            q->_refCount = q->_refCount - 1;
            if (((unsigned long long)(long long)q->_refCount & 0x7fffffULL) == 0) igObject_Destroy(q);
        }
        sp8C = 0;
        s3 = 0;
        if (arg0->_multitap != 0) {
            if (arg0->_loadIRXs != 0) {
                if (FUN_0032cf50(&DAT_004d7060[0], 1, 0, 0).ok()) {
                    sceMtapInit();
                    if (arg0->_multitap & 1) sceMtapPortOpen(0);
                    if (arg0->_multitap & 2) sceMtapPortOpen(1);
                }
            }
            s3 = 0;
        }
        s3 = 0;
        do {
            s1 = 0;
            { unsigned m = arg0->_multitap; s2 = !(m & (1u << s3)) ? 1 : 4; }
            for (; s1 < s2; s1++) {
                base = igObject_GetAllocator(arg0);
                if (GPR_00554c14 != 0) {
                    al2 = (Al *)base;
                } else {
                    al2 = (Al *)Memory_GetAllocatorBySelector(g_temporaryAllocatorSelector[0]);
                }
                mem = al2->vX(0x100, 0x40);
                if (scePadPortOpen(s3, s1, mem) != 1) {
                    Memory_FreeBuffer(mem);
                } else {
                    igSmartPointer<igPsx2Controller> controller((igPsx2Controller *)FUN_00147090((int)igObject_GetAllocator(arg0)));
                    controller.get()->_port = s3;
                    controller.get()->_slot = s1;
                    ((Pd *)controller.get())->vX((s3 | (s1 * 2)) & 0xFFFF);
                    controller.get()->_dmaBuffer = mem;
                    ((Pe *)controller.get())->vX(arg1);
                    ObjectList_AppendRetained((int)(igObject *)arg0->_controllers, (int)controller.get());
                }
            }
            s3 += 1;
        } while (s3 < 2);
        q = sp8C;
        if (q != 0) {
            q->_refCount = q->_refCount - 1;
            if (((unsigned long long)(long long)q->_refCount & 0x7fffffULL) == 0) igObject_Destroy(q);
        }
    }
}

void **FUN_001489a0(void **arg0, short arg1) {
    S_temp_a0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

