void beNDMWStatusSubSlot_Create(int allocator) {
    beNDMWStatusSubSlot_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWStatusSubSlot_metaObject, allocator);
}

igMetaObject *beNDMWStatusSubSlot_GetMetaObject(void) {
    if (g_beNDMWStatusSubSlot_metaObject == 0 || !isValid(g_beNDMWStatusSubSlot_metaObject)) beNDMWStatusSubSlot_EnsureRegistered();
    return g_beNDMWStatusSubSlot_metaObject;
}

int beNDMWStatusSubSlot_GetVTable(void) {
    union U_3ba2f0 u;
    int t;

    beNDMWStatusCtrlBaseEquip_Construct((beNDMWStatusCtrlBaseEquip *)u.b);
    u.vt = (int)&g_beNDMWStatusSubSlot_vtable[0];
    t = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beNDMWStatusSubSlot_vtable[0];
    FUN_003ba3d0((S_arg0 *)u.b, (long long)0);
    return t;
}

igSmartPointer<igObject> *beNDMWStatusSubSlot_igSmartPointer_igObject_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

void *FUN_003ba3d0(S_arg0 *arg0, long long arg1) {
    S_temp_a0_3ba3d0 *temp_a0;
    S_temp_a0_2 *temp_a0_2;
    S_temp_a0_3 *temp_a0_3;
    S_temp_a0_4 *temp_a0_4;
    S_temp_a0_5 *temp_a0_5;
    S_temp_a0_6 *temp_a0_6;
    S_temp_a0_7 *temp_a0_7;

    if (arg0 != 0) {
        arg0->f0 = (int)(&g_beNDMWStatusCtrlBaseEquip_vtable[0]);
        if (((char *)arg0 + 0x78) != 0) {
            temp_a0 = (S_temp_a0_3ba3d0 *)(arg0->f120);
            if (temp_a0 != 0) {
                temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
                if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(temp_a0);
                }
            }
        }
        if (((char *)arg0 + 0x74) != 0) {
            temp_a0_2 = (S_temp_a0_2 *)(arg0->f116);
            if (temp_a0_2 != 0) {
                temp_a0_2->f4 = (int)((int) (temp_a0_2->f4 - 1));
                if (((unsigned long long) ((long long) temp_a0_2->f4 << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(temp_a0_2);
                }
            }
        }
        if (((char *)arg0 + 0x70) != 0) {
            temp_a0_3 = (S_temp_a0_3 *)(arg0->f112);
            if (temp_a0_3 != 0) {
                temp_a0_3->f4 = (int)((int) (temp_a0_3->f4 - 1));
                if (((unsigned long long) ((long long) temp_a0_3->f4 << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(temp_a0_3);
                }
            }
        }
        if (((char *)arg0 + 0x6C) != 0) {
            temp_a0_4 = (S_temp_a0_4 *)(arg0->f108);
            if (temp_a0_4 != 0) {
                temp_a0_4->f4 = (int)((int) (temp_a0_4->f4 - 1));
                if (((unsigned long long) ((long long) temp_a0_4->f4 << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(temp_a0_4);
                }
            }
        }
        if (((char *)arg0 + 0x68) != 0) {
            temp_a0_5 = (S_temp_a0_5 *)(arg0->f104);
            if (temp_a0_5 != 0) {
                temp_a0_5->f4 = (int)((int) (temp_a0_5->f4 - 1));
                if (((unsigned long long) ((long long) temp_a0_5->f4 << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(temp_a0_5);
                }
            }
        }
        if (((char *)arg0 + 0x64) != 0) {
            temp_a0_6 = (S_temp_a0_6 *)(arg0->f100);
            if (temp_a0_6 != 0) {
                temp_a0_6->f4 = (int)((int) (temp_a0_6->f4 - 1));
                if (((unsigned long long) ((long long) temp_a0_6->f4 << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(temp_a0_6);
                }
            }
        }
        if (((char *)arg0 + 0x60) != 0) {
            temp_a0_7 = (S_temp_a0_7 *)(arg0->f96);
            if (temp_a0_7 != 0) {
                temp_a0_7->f4 = (int)((int) (temp_a0_7->f4 - 1));
                if (((unsigned long long) ((long long) temp_a0_7->f4 << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(temp_a0_7);
                }
            }
        }
        if (arg0 != 0) {
            arg0->f0 = (int)(&g_beNDMWWindowCtrl_vtable[0]);
            FUN_003b2d10((beNDMWWindowCtrl *)arg0, (short)0);
        }
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            Memory_FreeBufferAliasC(arg0);
        }
    }
    return arg0;
}

