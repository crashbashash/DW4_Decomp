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
        Matrix44_GetQuaternion(&o->_quatList->_data[index], rot);
    } else if (o->_drivenChannels & 4) {
        off = index * 16;
        Matrix44_GetQuaternion((char *)o->_quatList->_data + off, rot);
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

    if (g_igTransformSequence1_5_metaObject[0] != 0) {
        temp_v0 = igMetaObject_FindFieldByName(g_igTransformSequence1_5_metaObject[0], &text_interpolationMethod[0]);
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

void igTransformSequence1_5_InterpolateTranslation(igTransformSequence1_5 *self, float *out, int from, int to, float t) {
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
        Vec3_Lerp(out, t, (void *)(keys + from * 12), (void *)(keys + to * 12));
        return;
    }
    FUN_001930f0(out, (float *)(((igVec3fList *)self->_xlateList)->_data + from * 12),
                 (float *)(((igDataList *)self->_interpolationDataTranslation)->_data + from * 24),
                 (float *)(((igDataList *)self->_interpolationDataTranslation)->_data + (from * 2 + 1) * 12),
                 (float *)(((igVec3fList *)self->_xlateList)->_data + to * 12), t);
}

void igTransformSequence1_5_InterpolateRotation(igTransformSequence1_5 *self, float *out, int from, int to, float t) {
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
        Quaternion_Lerp(out, t, (void *)(keys + from * 16), (void *)(keys + to * 16));
    }
}

void igTransformSequence1_5_FindUniformKeys(SequenceKeyTimes *arg0, long long arg1, int *arg2, int *arg3, float *arg4) {
    float a = (float)(unsigned int)(arg1 >> 18);
    float b = (float)(unsigned int)(*arg0->_timeListLong->_data >> 18);
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

/* The igTransformSequence1_5 virtuals the key evaluators call (vfunc_N sits at vtable offset 4N). */
class TransformSequence1_5Slots {
public:
    virtual void slot2(); virtual void slot3(); virtual void slot4(); virtual void slot5(); virtual void slot6();
    virtual void slot7(); virtual void slot8(); virtual void slot9(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15(); virtual void slot16();
    virtual void slot17(); virtual void slot18(); virtual void slot19(); virtual void slot20(); virtual void slot21();
    virtual void slot22(); virtual void slot23(); virtual void slot24(); virtual void slot25(); virtual void slot26();
    virtual void slot27(); virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
    virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35(); virtual void slot36();
    virtual void slot37(); virtual void slot38();
    virtual int getKeyCount();                      /* vfunc_39 */
    virtual void slot40(); virtual void slot41();
    virtual float *getTranslationKey(int index);    /* vfunc_42 */
    virtual void slot43(); virtual void slot44();
    virtual float *getQuaternionKey(int index);     /* vfunc_45 */
};
static inline long long keyTime(igLongList *times, unsigned int index) { return ((long long *)times->_data)[index]; }
static inline void copyTranslation(float *dst, const float *src) { dst[0] = src[0]; dst[1] = src[1]; dst[2] = src[2]; }
static inline void copyQuaternion(float *dst, const float *src) { dst[0] = src[0]; dst[1] = src[1]; dst[2] = src[2]; dst[3] = src[3]; }
extern "C" void igTransformSequence1_5_FindKeys(igTransformSequence1_5 *self, long long time, int *key0, int *key1, float *t, int *lastKey);
extern "C" void igTransformSequence1_5_InterpolateTranslation(igTransformSequence1_5 *self, float *out, int from, int to, float t);
extern "C" void igTransformSequence1_5_InterpolateRotation(igTransformSequence1_5 *self, float *out, int from, int to, float t);
extern "C" void igTransformSequence1_5_FindUniformKeys(SequenceKeyTimes *arg0, long long arg1, int *arg2, int *arg3, float *arg4);
extern "C" int Gap__Sg__igTransformSequence1_5__evaluateRotationAndTranslation(igTransformSequence1_5 *self, float *quat, float *translation, long long time, int *lastKey, int flags);

/* Evaluates the translation and rotation tracks at {time}: wraps the time by the play mode, finds the
 * bracketing keys and interpolates between them into {translation} and {quat}. {lastKey} caches the
 * key search position. */
int Gap__Sg__igTransformSequence1_5__evaluateRotationAndTranslation(igTransformSequence1_5 *self, float *quat, float *translation, long long time, int *lastKey, int flags) {
    long long first;
    long long end;
    long long last;
    igLongList *times;
    long long duration;
    long long rem;
    float t;
    int key1;
    int key0;
    float span;

    long long now = time - self->_keyframeTimeOffset;
    if (!self->_uniformTimeEnabled) {
        times = (igLongList *)self->_timeListLong;
        first = ((long long *)times->_data)[0];
        last = keyTime(times, times->_count - 1);
        duration = self->_animationDuration;
        end = first + duration;
    } else {
        times = (igLongList *)self->_timeListLong;
        first = 0;
        last = ((long long *)times->_data)[0] * (long long)(((igQuaternionfList *)self->_quatList)->_count - 1);
        end = self->_animationDuration;
        duration = end;
    }
    if (duration == 0) {
        copyTranslation(translation, ((TransformSequence1_5Slots *)self)->getTranslationKey(0));
        return 1;
    }
    if (end < now) {
        switch (self->_playMode) {
        case 1: {
            int lastIndex = times->_count - 1;
            copyTranslation(translation, ((TransformSequence1_5Slots *)self)->getTranslationKey(lastIndex));
            copyQuaternion(quat, ((TransformSequence1_5Slots *)self)->getQuaternionKey(lastIndex));
        }
            return 1;
        case 3:
        case 0:
            UnsignedDivMod64_Cached(now - first, duration, &rem);
            now = first + rem;
            if (*lastKey != 1 && now < keyTime((igLongList *)self->_timeListLong, *lastKey - 1)) {
                *lastKey = 1;
            }
            break;
        case 2: {
            unsigned long long cycle = (unsigned long long)(unsigned int)UnsignedDivMod64_Cached(now - first, duration, &rem);
            if ((int)cycle & 1) {
                now = end - rem;
            } else {
                now = first + rem;
            }
        } break;
        default:
            copyTranslation(translation, ((TransformSequence1_5Slots *)self)->getTranslationKey(0));
            copyQuaternion(quat, ((TransformSequence1_5Slots *)self)->getQuaternionKey(0));
            return 1;
        }
    } else if (now < first) {
        copyTranslation(translation, ((TransformSequence1_5Slots *)self)->getTranslationKey(0));
        copyQuaternion(quat, ((TransformSequence1_5Slots *)self)->getQuaternionKey(0));
        return 1;
    }
    if (last < now) {
        if (self->_playMode == 3) {
            float elapsed;
            key0 = ((igLongList *)self->_timeListLong)->_count - 1;
            key1 = 0;
            if (!self->_uniformTimeEnabled) {
                elapsed = (float)(unsigned int)(int)((now - last) >> 18);
                span = (float)(unsigned int)(int)((end - last) >> 18);
            } else {
                span = (float)(unsigned int)(int)(((long long *)((igLongList *)self->_timeListLong)->_data)[0] >> 18);
                elapsed = fmodf((float)(unsigned int)(int)(now >> 18), span);
            }
            if (span < 9.99999997e-07f) {
                t = 0.0f;
            } else {
                t = elapsed / span;
            }
        } else {
            int lastIndex = ((TransformSequence1_5Slots *)self)->getKeyCount() - 1;
            copyTranslation(translation, ((TransformSequence1_5Slots *)self)->getTranslationKey(lastIndex));
            copyQuaternion(quat, ((TransformSequence1_5Slots *)self)->getQuaternionKey(lastIndex));
            return 1;
        }
    } else if (!self->_uniformTimeEnabled) {
        igTransformSequence1_5_FindKeys(self, now, &key0, &key1, &t, lastKey);
    } else {
        igTransformSequence1_5_FindUniformKeys((SequenceKeyTimes *)self, now, &key0, &key1, &t);
    }
    igTransformSequence1_5_InterpolateTranslation(self, translation, key0, key1, t);
    igTransformSequence1_5_InterpolateRotation(self, quat, key0, key1, t);
    return 1;
}

void Gap__Sg__igTransformSequence1_5__vfunc_25(IgForwardTarget_1dfd60 *o, int a, int b) { o->slot24(a, b, (char *)o + 40, 0); }

extern "C" int Gap__Sg__igTransformSequence1_5__evaluateRotation(igTransformSequence1_5 *self, float *quat, long long time, int *lastKey, int flags);

/* Evaluates the rotation track at {time}: wraps the time by the play mode, finds the bracketing keys
 * and interpolates between them into {quat}. {lastKey} caches the key search position. */
int Gap__Sg__igTransformSequence1_5__evaluateRotation(igTransformSequence1_5 *self, float *quat, long long time, int *lastKey, int flags) {
    long long first;
    long long end;
    long long last;
    igLongList *times;
    long long duration;
    long long rem;
    float t;
    int key1;
    int key0;
    float span;

    long long now = time - self->_keyframeTimeOffset;
    if (!self->_uniformTimeEnabled) {
        times = (igLongList *)self->_timeListLong;
        first = ((long long *)times->_data)[0];
        last = keyTime(times, times->_count - 1);
        duration = self->_animationDuration;
        end = first + duration;
    } else {
        times = (igLongList *)self->_timeListLong;
        first = 0;
        last = ((long long *)times->_data)[0] * (long long)(((igQuaternionfList *)self->_quatList)->_count - 1);
        end = self->_animationDuration;
        duration = end;
    }
    if (duration == 0) {
        copyQuaternion(quat, ((TransformSequence1_5Slots *)self)->getQuaternionKey(0));
        return 1;
    }
    if (end < now) {
        switch (self->_playMode) {
        case 1:
            copyQuaternion(quat, ((TransformSequence1_5Slots *)self)->getQuaternionKey(times->_count - 1));
            return 1;
        case 3:
        case 0:
            UnsignedDivMod64_Cached(now - first, duration, &rem);
            now = first + rem;
            if (*lastKey != 1 && now < keyTime((igLongList *)self->_timeListLong, *lastKey - 1)) {
                *lastKey = 1;
            }
            break;
        case 2: {
            unsigned long long cycle = (unsigned long long)(unsigned int)UnsignedDivMod64_Cached(now - first, duration, &rem);
            if ((int)cycle & 1) {
                now = end - rem;
            } else {
                now = first + rem;
            }
        } break;
        default:
            copyQuaternion(quat, ((TransformSequence1_5Slots *)self)->getQuaternionKey(0));
            return 1;
        }
    } else if (now < first) {
        copyQuaternion(quat, ((TransformSequence1_5Slots *)self)->getQuaternionKey(0));
        return 1;
    }
    if (last < now) {
        if (self->_playMode == 3) {
            float elapsed;
            key0 = ((igLongList *)self->_timeListLong)->_count - 1;
            key1 = 0;
            if (!self->_uniformTimeEnabled) {
                elapsed = (float)(unsigned int)(int)((now - last) >> 18);
                span = (float)(unsigned int)(int)((end - last) >> 18);
            } else {
                span = (float)(unsigned int)(int)(((long long *)((igLongList *)self->_timeListLong)->_data)[0] >> 18);
                elapsed = fmodf((float)(unsigned int)(int)(now >> 18), span);
            }
            if (span < 9.99999997e-07f) {
                t = 0.0f;
            } else {
                t = elapsed / span;
            }
        } else {
            copyQuaternion(quat, ((TransformSequence1_5Slots *)self)->getQuaternionKey(((TransformSequence1_5Slots *)self)->getKeyCount() - 1));
            return 1;
        }
    } else if (!self->_uniformTimeEnabled) {
        igTransformSequence1_5_FindKeys(self, now, &key0, &key1, &t, lastKey);
    } else {
        igTransformSequence1_5_FindUniformKeys((SequenceKeyTimes *)self, now, &key0, &key1, &t);
    }
    igTransformSequence1_5_InterpolateRotation(self, quat, key0, key1, t);
    return 1;
}


static inline bool centerOfRotationIsSet(const igTransformSequence1_5 *o) {
    return o->_centerOfRotation[0] != g_vec3Zero[0] || o->_centerOfRotation[1] != DAT_004e105c[0] || o->_centerOfRotation[2] != DAT_004e1060[0];
}

bool Gap__Sg__igTransformSequence1_5__vfunc_29(igTransformSequence1_5 *o) {
    if (centerOfRotationIsSet(o)) {
        return false;
    }
    if (o->_interpolationDataTranslation != 0 || o->_interpolationDataRotation != 0 || o->_interpolationDataScale != 0) {
        return false;
    }
    return true;
}
