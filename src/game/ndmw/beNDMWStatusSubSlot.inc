beNDMWStatusSubSlot *beNDMWStatusSubSlot_Create(int allocator) {
    beNDMWStatusSubSlot_EnsureRegistered();
    return (beNDMWStatusSubSlot *)igMetaObject_CreateInstance(g_beNDMWStatusSubSlot_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNDMWStatusSubSlot_GetMetaObject(void) {
    if (g_beNDMWStatusSubSlot_metaObject == 0 || !isValid(g_beNDMWStatusSubSlot_metaObject)) beNDMWStatusSubSlot_EnsureRegistered();
    return g_beNDMWStatusSubSlot_metaObject;
}

int beNDMWStatusSubSlot_GetVTable(void) {
    beNDMWStatusSubSlot obj;
    int vtable;

    beNDMWStatusCtrlBaseEquip_Construct((beNDMWStatusCtrlBaseEquip *)&obj);
    *(int **)&obj._vtable = &g_beNDMWStatusSubSlot_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_beNDMWStatusSubSlot_vtable[0];
    beNDMWStatusCtrlBaseEquip_Destroy((beNDMWStatusCtrlBaseEquip *)&obj, 0);
    return vtable;
}

igSmartPointer<igObject> *beNDMWStatusSubSlot_igSmartPointer_igObject_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)object);
        }
        if ((short)delete_storage > 0) operator delete(self);
    }
    return self;
}

void *beNDMWStatusCtrlBaseEquip_Destroy(beNDMWStatusCtrlBaseEquip *self, short flags) {
    if (self != 0) {
        *(int **)&self->_vtable = &g_beNDMWStatusCtrlBaseEquip_vtable[0];
        if (&self->_deviceFolder != 0) {
            igRelease((igObject *)self->_deviceFolder);
        }
        if (&self->_apuPocket != 0) {
            igRelease((igObject *)self->_apuPocket);
        }
        if (&self->_wpuPocket != 0) {
            igRelease((igObject *)self->_wpuPocket);
        }
        if (&self->_subSlot != 0) {
            igRelease((igObject *)self->_subSlot);
        }
        if (&self->_mainSlot != 0) {
            igRelease((igObject *)self->_mainSlot);
        }
        if (&self->_powerSocket != 0) {
            igRelease((igObject *)self->_powerSocket);
        }
        if (&self->_playerList != 0) {
            igRelease((igObject *)self->_playerList);
        }
        if (self != 0) {
            *(int **)&self->_vtable = &g_beNDMWWindowCtrl_vtable[0];
            beNDMWWindow_Destroy((beNDMWWindowCtrl *)self, 0);
        }
        if (flags > 0) {
            Memory_FreeBufferAliasC(self);
        }
    }
    return self;
}

