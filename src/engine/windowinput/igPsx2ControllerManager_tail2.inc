static unsigned char g_igPsx2ControllerManager_initialized;

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
    if (g_igPsx2ControllerManager_initialized == 0) {
        g_igPsx2ControllerManager_initialized = 1;
        arg0->_validControllerManager = 1;
        if (arg0->_loadIRXs != 0) {
            igPsx2_LoadIopModule("sio2man.irx", 1, 0, 0);
            igPsx2_LoadIopModule("padman.irx", 1, 0, 0);
        }
        scePadInit(0);
        base = igObject_GetAllocator(arg0);
        if (g_useOwnerAllocator != 0) {
            al = base;
        } else {
            al = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleTemporary);
        }
        sp8C = (PropertyText *)igStringObj_Create((int)al);
        if (igRegistry_GetValueStringObj(*(igRegistry **)((char *)g_objectSystem + 56), 3, "supportMultitap", (igStringObj **)&sp8C, "", 0) != 0) {
            s0 = sp8C->chars;
            s0 = (s0 == 0) ? g_stringObjEmptyText : s0;
            if (strcmp(s0, "ALL") == 0) {
                v1 = 0xFFFF;
                arg0->_multitap = v1;
            } else if (strcmp(s0, "NONE") == 0) {
                arg0->_multitap = 0;
            } else if (strncmp(s0, "PORT", 4) == 0) {
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
                if (igPsx2_LoadIopModule("mtapman.irx", 1, 0, 0) == g_resultSuccess) {
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
                if (g_useOwnerAllocator != 0) {
                    al2 = (Al *)base;
                } else {
                    al2 = (Al *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleTemporary);
                }
                mem = al2->vX(0x100, 0x40);
                if (scePadPortOpen(s3, s1, (void *)mem) != 1) {
                    Memory_FreeBuffer((void *)mem);
                } else {
                    igSmartPointer<igPsx2Controller> controller((igPsx2Controller *)FUN_00147090((int)igObject_GetAllocator(arg0)));
                    controller.get()->_port = s3;
                    controller.get()->_slot = s1;
                    ((Pd *)controller.get())->vX((s3 | (s1 * 2)) & 0xFFFF);
                    controller.get()->_dmaBuffer = mem;
                    ((Pe *)controller.get())->vX(arg1);
                    ObjectList_AppendRetained((igObjectList *)((int)(igObject *)arg0->_controllers), (igObject *)((int)controller.get()));
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

igSmartPointer<igObject> *igSmartPointer_igStringObj_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if ((object->_refCount & 0x7fffff) == 0)
                igObject_Destroy(object);
        }
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

