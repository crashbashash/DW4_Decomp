void Gap__Sg__igTransformSequence1_5__vfunc_66(VC_1dd570 *arg0) {
    int n, i; float *a; float *b; float dot;
    if (arg0->v240() & 2) {
        n = arg0->v156();
        for (i = 0; i < n - 1; i++) {
            a = arg0->v180(i);
            b = arg0->v180(i + 1);
            dot = a[0]*b[0] + a[1]*b[1] + a[2]*b[2] + a[3]*b[3];
            if (dot < -0.999989986f) {
                b[0] = -b[0]; b[1] = -b[1]; b[2] = -b[2]; b[3] = -b[3];
            }
        }
    }
}

/* Address of key {index} in this sequence's quaternion track, or 0 when the sequence does not
 * drive that channel. _drivenChannels is a bitmask (1 = translation, 2 and 4 = the two rotation
 * slots, 8 = scale); the key array starts 16 bytes into the list object and each key is 0x10
 * bytes. */

int Gap__Sg__igTransformSequence1_5__vfunc_45(igTransformSequence1_5 *self, int index) {
    if (self->_drivenChannels & 2) {
        return *(int *)((char *)(self->_quatList) + 16) + (index * 0x10);
    }
    return 0;
}

void Gap__Sg__igTransformSequence1_5__vfunc_62(void *arg0, long long arg1) {
    *(long long *)((char *)arg0 + 80) = arg1;
}

void Gap__Sg__igTransformSequence1_5__vfunc_34(KeySequenceView *o, int index, KeyMatrixView *m) {
    int off;
    int i;
    KeyQuatView *q;
    float *s;
    float *pz;
    float *py;
    float z;
    float y;
    float x;
    float euler[3];
    float inv[3];
    float rot[16];
    if (o->_drivenChannels & 1) {
        KeyVec3View *t = &o->_xlateList->_data[index];
        t->x = m->tx;
        t->y = m->ty;
        t->z = m->tz;
    }
    igMatrix44f_SetIdentity(rot);
    if (o->_drivenChannels & 8) {
        s = (float *)&o->_scaleList->_data[index];
        for (i = 0; i < 3; i++) {
            float *r = m->r[i];
            s[i] = sqrtf(r[0] * r[0] + r[1] * r[1] + r[2] * r[2]);
        }
        Matrix44_Copy(rot, m);
        if (FUN_00192290(m) < 0.0f) {
            s[0] = -s[0];
            s[1] = -s[1];
            s[2] = -s[2];
        }
        {
                        z = 1.0f / s[2];
            x = 1.0f / s[0];
            y = 1.0f / s[1];
            inv[0] = x;
            inv[2] = z;
            inv[1] = y;
        }
        FUN_00190cb0(rot, inv);
    } else {
        Matrix44_Copy(rot, m);
    }
    if (o->_drivenChannels & 2) {
        FUN_001925f0(&o->_quatList->_data[index], rot);
    } else if (o->_drivenChannels & 4) {
        off = index * 16;
        FUN_001925f0((char *)o->_quatList->_data + off, rot);
        pz = &euler[2];
        py = &euler[1];
        FUN_00192990((char *)o->_quatList->_data + off, euler, py, pz);
        euler[0] = euler[0] * 57.29578f;
        *py = *py * 57.29578f;
        *pz = *pz * 57.29578f;
        q = (KeyQuatView *)((char *)o->_quatList->_data + off);
        {
            float a;
            float b;
            float c;
            c = *pz;
            b = *py;
            a = euler[0];
            q->x = a;
            q->y = b;
            q->z = c;
        }
        q->w = 0.0f;
    }
}

/* matching construct: the list/arena-reference fields are 4-byte handles; the casts give the typed list views (no layout effect).
 * The three interpolation-data lists (+60/+64/+68) are hypothesised to be Vec3f lists (12-byte elements, two per key); kept as igDataList. */
void Gap__Sg__igTransformSequence1_5__vfunc_37(igTransformSequence1_5 *t, int idx) {
    long long sp216;
    V3_1dda90 sp200;
    V3_1dda90 sp184;
    V3_1dda90 sp168;
    V3_1dda90 sp152;
    V3_1dda90 sp136;
    V3_1dda90 sp120;
    V3_1dda90 sp104;
    V3_1dda90 sp88;
    V4_1dda90 sp64;
    int s0;
    sp216 = ((long long *)((igLongList *)t->_timeListLong)->_data)[idx];
    List_InsertBytes((igLongList *)t->_timeListLong, idx, 1, &sp216, 8);
    if (t->_drivenChannels & 1) {
        sp200 = ((V3_1dda90 *)((igVec3fList *)t->_xlateList)->_data)[idx];
        List_InsertBytes((igVec3fList *)t->_xlateList, idx, 1, &sp200, 12);
        if (t->_interpolationDataTranslation != 0) {
            s0 = idx * 2;
            sp184 = ((V3_1dda90 *)((igDataList *)t->_interpolationDataTranslation)->_data)[idx * 2];
            sp168 = ((V3_1dda90 *)((igDataList *)t->_interpolationDataTranslation)->_data)[s0 + 1];
            List_InsertBytes((igDataList *)t->_interpolationDataTranslation, s0, 1, &sp168, 12);
            List_InsertBytes((igDataList *)t->_interpolationDataTranslation, s0, 1, &sp184, 12);
        }
    }
    if (t->_drivenChannels & 8) {
        sp152 = ((V3_1dda90 *)((igVec3fList *)t->_scaleList)->_data)[idx];
        List_InsertBytes((igVec3fList *)t->_scaleList, idx, 1, &sp152, 12);
        if (t->_interpolationDataScale != 0) {
            s0 = idx * 2;
            sp136 = ((V3_1dda90 *)((igDataList *)t->_interpolationDataScale)->_data)[idx * 2];
            sp120 = ((V3_1dda90 *)((igDataList *)t->_interpolationDataScale)->_data)[s0 + 1];
            List_InsertBytes((igDataList *)t->_interpolationDataScale, s0, 1, &sp120, 12);
            List_InsertBytes((igDataList *)t->_interpolationDataScale, s0, 1, &sp136, 12);
        }
    }
    if ((t->_drivenChannels & 2) || (t->_drivenChannels & 4)) {
        sp64 = ((V4_1dda90 *)((igQuaternionfList *)t->_quatList)->_data)[idx];
        List_InsertBytes((igQuaternionfList *)t->_quatList, idx, 1, &sp64, 16);
        if (t->_interpolationDataRotation != 0) {
            s0 = idx * 2;
            sp104 = ((V3_1dda90 *)((igDataList *)t->_interpolationDataRotation)->_data)[idx * 2];
            sp88 = ((V3_1dda90 *)((igDataList *)t->_interpolationDataRotation)->_data)[s0 + 1];
            List_InsertBytes((igDataList *)t->_interpolationDataRotation, s0, 1, &sp88, 12);
            List_InsertBytes((igDataList *)t->_interpolationDataRotation, s0, 1, &sp104, 12);
        }
    }
}

void FUN_001ddfd0(void) {
    int temp_v0;

    if (DAT_005611d8[0] != 0) {
        temp_v0 = igMetaObject_FindFieldByName(DAT_005611d8[0], &DAT_004e13a0[0]);
        if (temp_v0 != 0) {
            FUN_002d4c20(temp_v0, 0, 1);
            FUN_002d4c20(temp_v0, 1, 3);
            FUN_002d4c20(temp_v0, 2, 1);
        }
    }
}

void Gap__Sg__igTransformSequence1_5__vfunc_57(TransformSequenceView *s, int channel, unsigned int mode) {
    if ((s->channels & channel) == 0) { return; }
    switch (channel) {
    case 1:
        if (mode < 3) {
            s->translationMode = mode;
            if (mode == 2) {
                assignRef(s->translations, SeqTempRef(FUN_0018a060(igObject_GetAllocator(s))));
                setCount_1de040(s->translations, s->keys->count * 2, 12);
            } else {
                releaseRef_1de040(s->translations);
                s->translations = 0;
            }
        }
        break;
    case 2:
        if (mode <= 1 || mode == 3) {
            s->rotationMode = mode;
            releaseRef_1de040(s->rotations);
            s->rotations = 0;
        }
        break;
    case 4:
        if (mode < 3) {
            s->rotationMode = mode;
            if (mode == 2) {
                assignRef(s->rotations, SeqTempRef(FUN_0018a060(igObject_GetAllocator(s))));
                setCount_1de040(s->rotations, s->keys->count * 2, 12);
            } else {
                releaseRef_1de040(s->rotations);
                s->rotations = 0;
            }
        }
        break;
    case 8:
        if (mode < 3) {
            s->scaleMode = mode;
            if (mode == 2) {
                assignRef(s->scales, SeqTempRef(FUN_0018a060(igObject_GetAllocator(s))));
                setCount_1de040(s->scales, s->keys->count * 2, 12);
            } else {
                releaseRef_1de040(s->scales);
                s->scales = 0;
            }
        }
        break;
    }
}

int Gap__Sg__igTransformSequence1_5__vfunc_59(igTransformSequence1_5 *arg0, int arg1) {
    if (!(arg0->_drivenChannels & arg1)) {
        return -1;
    }
    switch (arg1) {
    case 1:
        return *(unsigned char *)((char *)(arg0) + 73);
    case 2:
    case 4:
        return *(unsigned char *)((char *)(arg0) + 74);
    case 8:
        return *(unsigned char *)((char *)(arg0) + 75);
    default:
        return -1;
    }
}

void Gap__Sg__igTransformSequence1_5__vfunc_58(TransformSequenceView *s, unsigned char channels) {
    unsigned char old;
    if ((channels & 2) != 0 && (channels & 4) != 0) { return; }
    old = s->channels;
    s->channels = channels;
    if ((channels & 1) != 0) {
        s->translationMode = 1;
        if ((old & 1) == 0) {
            assignRef_1de4e0(s->translationKeys, SeqTempRef(FUN_0018a060(igObject_GetAllocator(s))));
            setCount_1de4e0(s->translationKeys, s->keys->count, 12);
            releaseRef_1de4e0(s->translations);
            s->translations = 0;
        }
    } else {
        releaseRef_1de4e0(s->translationKeys);
        s->translationKeys = 0;
    }
    releaseRef_1de4e0(s->translations);
    s->translations = 0;
    if ((channels & 2) != 0 || (channels & 4) != 0) {
        if ((old & 2) == 0 && (old & 4) == 0) {
            assignRef_1de4e0(s->rotationKeys, SeqTempRef(FUN_00189bd0(igObject_GetAllocator(s))));
            setCount_1de4e0(s->rotationKeys, s->keys->count, 16);
        }
        if ((channels & 2) != 0) {
            s->rotationMode = 3;
        } else {
            s->rotationMode = 1;
        }
    } else {
        releaseRef_1de4e0(s->rotationKeys);
        s->rotationKeys = 0;
    }
    releaseRef_1de4e0(s->rotations);
    s->rotations = 0;
    if ((channels & 8) != 0) {
        if ((old & 8) == 0) {
            assignRef_1de4e0(s->scaleKeys, SeqTempRef(FUN_0018a060(igObject_GetAllocator(s))));
            setCount_1de4e0(s->scaleKeys, s->keys->count, 12);
        }
        s->scaleMode = 1;
    } else {
        releaseRef_1de4e0(s->scaleKeys);
        s->scaleKeys = 0;
    }
    releaseRef_1de4e0(s->scales);
    s->scales = 0;
}

void Gap__Sg__igTransformSequence1_5__vfunc_61(T_1de9c0 *t, int idx, int ch, V_1de9c0 *p, V_1de9c0 *q) {
    L_1de9c0 *l;
    int n;
    int i;
    V_1de9c0 *e;
    if (t->flags & ch) {
        l = 0;
        if (ch & 1) {
            l = t->a;
        } else if ((ch & 2) || (ch & 4)) {
            l = t->b;
        } else if (ch & 8) {
            l = t->c;
        }
        if (l->count == 0) {
            n = t->tl->count * 2;
            if (n >= 0) {
                if (n <= l->cap) {
                    l->count = n;
                } else {
                    List_Resize((void *)l, n, 12);
                }
            }
        }
        Set::put(l, idx * 2, p);
        Set::put(l, (idx << 1) + 1, q);
    }
}

/* Address of key {index} in this sequence's quaternion track, or 0 when the sequence does not
 * drive that channel. _drivenChannels is a bitmask (1 = translation, 2 and 4 = the two rotation
 * slots, 8 = scale); the key array starts 16 bytes into the list object and each key is 0x10
 * bytes. */

int Gap__Sg__igTransformSequence1_5__vfunc_48(igTransformSequence1_5 *self, int index) {
    if (self->_drivenChannels & 4) {
        return *(int *)((char *)(self->_quatList) + 16) + (index * 0x10);
    }
    return 0;
}

void FUN_001deb50(igTransformSequence1_5 *self, float *out, int from, int to, float t) {
    unsigned char method = self->_interpolationMethod[0];
    if (method == 0) {
        float *key = (float *)(((igVec3fList *)self->_xlateList)->_data + from * 12);
        out[0] = key[0];
        out[1] = key[1];
        out[2] = key[2];
        return;
    }
    if (method == 1) {
        int keys = ((igVec3fList *)self->_xlateList)->_data;
        FUN_00192f00(out, t, (void *)(keys + from * 12), (void *)(keys + to * 12));
        return;
    }
    FUN_001930f0(out, (float *)(((igVec3fList *)self->_xlateList)->_data + from * 12),
                 (float *)(((igDataList *)self->_interpolationDataTranslation)->_data + from * 24),
                 (float *)(((igDataList *)self->_interpolationDataTranslation)->_data + (from * 2 + 1) * 12),
                 (float *)(((igVec3fList *)self->_xlateList)->_data + to * 12), t);
}

void FUN_001def90(igTransformSequence1_5 *self, float *out, int from, int to, float t) {
    unsigned char method = self->_interpolationMethod[1];
    if (method == 0) {
        float *key = (float *)(((igQuaternionfList *)self->_quatList)->_data + from * 16);
        out[0] = key[0];
        out[1] = key[1];
        out[2] = key[2];
        out[3] = key[3];
        return;
    }
    if (method == 3) {
        int keys = ((igQuaternionfList *)self->_quatList)->_data;
        FUN_00192ab0(out, t, (void *)(keys + from * 16), (void *)(keys + to * 16));
        return;
    }
    {
        int keys = ((igQuaternionfList *)self->_quatList)->_data;
        FUN_00192cc0(out, t, (void *)(keys + from * 16), (void *)(keys + to * 16));
    }
}

void FUN_001df1d0(A_1df1d0 *arg0, long long arg1, int *arg2, int *arg3, float *arg4) {
    float a = (float)(unsigned int)(arg1 >> 18);
    float b = (float)(unsigned int)(*arg0->b->p >> 18);
    *arg2 = (int)(a / b);
    *arg3 = *arg2 + 1;
    *arg4 = fmodf(a, b) / b;
}

long long Gap__Sg__igTransformSequence1_5__vfunc_31(O_1df6e0 *o) {
    int r = o->a();
    long long v = 0;
    if (r != 0) {
        v = o->b(0);
    }
    return o->f80 + v;
}

long long Gap__Sg__igTransformSequence1_5__vfunc_32(V_1df740 *arg0) {
    return arg0->f80 + (arg0->vA() != 0 ? arg0->f88 + arg0->vB() : 0);
}

void Gap__Sg__igTransformSequence1_5__vfunc_27(IgForwardTarget *o, int a, int b, int c) { o->slot26(a, b, c, (char *)o + 40, 0); }

void Gap__Sg__igTransformSequence1_5__vfunc_25(IgForwardTarget_1dfd60 *o, int a, int b) { o->slot24(a, b, (char *)o + 40, 0); }

