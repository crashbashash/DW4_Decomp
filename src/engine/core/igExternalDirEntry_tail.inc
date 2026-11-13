void Gap__Core__igExternalDirEntry__vfunc_31(O_2e25a0 *arg0, void *arg1) {
    int s2, v, old, r;
    int *hd;
    s2 = ((A_2e25a0 *)arg1)->f200;
    if (g_stringPool[0] == 0) {
        v = ((int)StringPool_Allocate(16));
        if (v != 0) {
            v = ((int)StringPool_Construct((struct S_2eadf0 *)v));
        }
        g_stringPool[0] = v;
    }
    s2 = StringPool_Intern((StringPool *)g_stringPool[0], (const char *)s2);
    old = arg0->f40;
    if (old != 0) {
        hd = (int *)(old - 8);
        v = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = v;
        if (v == 0) {
            StringChunk_ReleaseHeader((StringChunkOwnerView *)(*hd), (int)hd);
        }
    }
    arg0->f40 = s2;
    arg0->v172(((B_2e25a0 *)arg1)->f160);
    if (arg0->f24 == 0 && GPR_00554c00 == 0) {
        r = FUN_00308390(DAT_004f99f0, arg0->f32, arg0->f40);
        if (r != 1 && r == 2) {
            GPR_00554c00 = 1;
        }
    }
    FUN_002d7da0((A7da0 *)arg1, arg0->f12, arg0->f24);
}

void FUN_002e26b0(struct O_2e26b0 *arg0, int arg1) {
    int *temp_a1;
    int temp_v1;
    int var_v0;
    int *temp_a0;
    int *temp_s0;
    if (g_stringPool[0] == 0) {
        var_v0 = ((int)StringPool_Allocate(0x10));
        if (var_v0 != 0) {
            var_v0 = ((int)StringPool_Construct((S_2eadf0 *)var_v0));
        }
        g_stringPool[0] = var_v0;
    }
    temp_s0 = (int *)(((void *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)arg1)));
    temp_a0 = arg0->s;
    if (temp_a0 != 0) {
        temp_a1 = temp_a0 - 2;
        temp_v1 = temp_a0[-1] - 1;
        temp_a0[-1] = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1), (int)temp_a1);
        }
    }
    arg0->s = temp_s0;
}

void Gap__Core__igExternalDirEntry__vfunc_23(S0_2e2750 *arg0, S1_2e2750 *arg1) {
    S_temp_a0_2e2750 *temp_a0;
    if (arg1 != 0) {
        arg1->f4 = (int)((int) (arg1->f4 + 1));
    }
    temp_a0 = (S_temp_a0_2e2750 *)((void *)(arg0->f18));
    if (temp_a0 != 0) {
        temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
        if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->f18 = (int)(arg1);
}

int Gap__Core__igExternalDirEntry__vfunc_44(Ent *arg0, int arg1) {
    igSmartPointer<Obj_2e27d0> stream(((class Obj_2e27d0 *)FUN_002c37e0(((int)igObject_GetAllocator((int)arg0)))));
    char *s1;
    int len;
    int c;
    char *buf;
    stream.get()->f160 = arg1;
    stream.get()->vX(arg0->f28);
    if (stream.get()->f8 == 0) {
        s1 = arg0->f28;
        len = strlen(arg0->f40);
        len = len + strlen(s1);
        c = strlen(&DAT_004f9a48[0]);
        buf = (char *)igObject_AllocateStorage((int)arg0, c + len + 1);
        strcpy(buf, arg0->f40);
        strcat(buf, &DAT_004f9a48[0]);
        strcat(buf, arg0->f28);
        stream.get()->vX(buf);
        FUN_00300f50((int)arg0, (int)buf);
    }
    arg0->vY(((void *)FUN_002d8e70((int)(stream.get()), (int)arg0->f32)));
    if (arg0->f24 == 0) {
        arg0->vY(((void *)FUN_002d8e70((int)(stream.get()), (int)&DAT_004f9a50[0])));
    }
    return arg0->f24 != 0;
}

static inline void releaseObject(Obj_2e2950 *object) {
    object->_refCount = object->_refCount - 1;
    if ((object->_refCount & 0x7FFFFF) == 0) {
        igObject_Destroy(object);
    }
}

void Gap__Core__igExternalDirEntry__vfunc_11(igDirEntry *arg0) {
    Gap__Core__igDirEntry__vfunc_11((int)arg0);
    arg0->_resolveMethod = 2;
    arg0->_refType = 0;
}

void Gap__Core__igExternalDirEntry__vfunc_12(void **arg0) {
    ((DW4VC_92_1 *)(arg0))->vX((int)(0));
    Gap__Core__igObject__vfunc_10((int)arg0);
}

