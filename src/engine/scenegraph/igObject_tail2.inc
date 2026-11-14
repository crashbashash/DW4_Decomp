bool FUN_001d08d0(Self *arg0, int arg1) {
    bool r = false;
    int n;
    int i;
    int j;
    if (arg0->f48 == 0) {
        n = arg0->f44->f20;
        setFloats(arg0->f48, igSmartPointer<igFloatList>((igFloatList *)igFloatList_Create(((void *)igObject_GetAllocator(arg0)))));
        setFloats(arg0->f52, igSmartPointer<igFloatList>((igFloatList *)igFloatList_Create(((void *)igObject_GetAllocator(arg0)))));
        setBytes(arg0->f56, igSmartPointer<igUnsignedCharList>((igUnsignedCharList *)igUnsignedCharList_Create(((void *)igObject_GetAllocator(arg0)))));
        { igFloatList *l = arg0->f48; if (n >= 0) { if (n <= l->_capacity) l->_count = n; else List_Resize((void *)l, n, 4); } }
        { igFloatList *l = arg0->f52; if (n >= 0) { if (n <= l->_capacity) l->_count = n; else List_Resize((void *)l, n, 4); } }
        { igUnsignedCharList *l = arg0->f56; if (n >= 0) { if (n <= l->_capacity) l->_count = n; else List_Resize((void *)l, n, 1); } }
        for (i = 0; i < n; i++) {
            igFloatList *a = arg0->f48;
            int c = a->_count;
            if (c != 0 && i >= 0 && i < c) ((float *)a->_data)[i] = DAT_0048da38[0];
            igFloatList *b = arg0->f52;
            c = b->_count;
            if (c != 0 && i >= 0 && i < c) ((float *)b->_data)[i] = DAT_0048da40[0];
            igUnsignedCharList *d = arg0->f56;
            c = d->_count;
            if (c != 0 && i >= 0 && i < c) ((unsigned char *)d->_data)[i] = GPR_00554988;
        }
    }
    for (j = 0; j < arg1; j++) {
        if (((float *)arg0->f52->_data)[j] != ((float *)arg0->f48->_data)[j]) { r = true; break; }
    }
    return r;
}

void FUN_001d1550(void *arg0, int arg1) {
    int temp_a0;

    temp_a0 = *(int *)((char *)arg0 + 68);
    if (temp_a0 != 0) {
        FUN_001d1a80(temp_a0, (int)(arg0), arg1);
    }
    if (*(int *)((char *)arg0 + 64) != 0) {
        FUN_001d0c90(arg0);
    }
}

void FUN_001d15a0(KeyReducer *self) {
    unsigned int n;
    KeyChannelList *channels;
    unsigned int kept;
    int c;
    KeyChannel *channel;
    unsigned int k;
    int index;
    unsigned int i;
    int at;
    KeyIndexList *list;
    self->kept->count = 0;
    n = self->values->count;
    for (i = 0; i < n; i++) {
        KeyFloatBits u;
        u.f = self->values->data[i];
        u.b.sign = 0;
        if (u.f > 4.99999999e-07f) {
            list = self->kept;
            at = list->count;
            if (list->capacity > at) {
                list->count = list->getCount() + 1;
            } else {
                FUN_002d6790(list, at + 1, 4);
            }
            list->data[at] = i;
        }
    }
    channels = self->owner->channels;
    kept = self->kept->count;
    for (c = 0; c < channels->count; c++) {
        channel = channels->data[c];
        channel->setKeyCount(kept);
        for (k = 0; k < kept; k++) {
            index = self->kept->data[k];
            channel->setKeyValue(k, self->values->data[index]);
            channel->setKeyIndex(k, index);
        }
    }
}

void FUN_001d1760(void *arg0, int arg1) {
    int temp_a0;

    temp_a0 = *(int *)((char *)arg0 + 52);
    if (temp_a0 != 0) {
        FUN_001d1a90(temp_a0, *(int *)((char *)arg0 + 44), arg1);
    }
    FUN_001d15a0((KeyReducer *)arg0);
}

void FUN_001d17a0(KeyTrackOwner *self, igFloatListView *out, int last) {
    int i;

    if (last == 0) {
        for (i = 0; i < self->count; i++) {
            igFloatListView *k = self->tracks->data[i]->keys;
            if (k->count > 0) {
                setValue(out, i, k->data);
            }
        }
    } else {
        for (i = 0; i < self->count; i++) {
            igFloatListView *k = self->tracks->data[i]->keys;
            setValue(out, i, &k->data[k->count - 1]);
        }
    }
}

void FUN_001d18a0(S_1d18a0 *arg0, int *arg1, int *arg2, float *arg3, K_1d18a0 *arg4, int arg5, unsigned arg6)
{
    unsigned a;
    unsigned *keys;
    if (arg5 <= 0) {
        *arg1 = 0;
        *arg2 = 0;
        *arg3 = 0.0f;
        return;
    }
    *arg2 = 0;
    while (*arg2 < arg5 && arg6 > arg4->keys[*arg2]) {
        *arg2 += 1;
    }
    if (*arg2 >= arg5) {
        if (arg0->f24 == 3) {
            *arg1 = arg5 - 1;
            *arg2 = 0;
            a = arg4->keys[*arg1];
            *arg3 = (float)(arg6 - a) / (float)(arg0->f56 - a);
            return;
        }
        *arg2 = arg5 - 1;
        *arg1 = arg5 - 1;
        *arg3 = 0.0f;
        return;
    }
    if (*arg2 == 0) {
        *arg1 = *arg2;
        *arg3 = 0.0f;
        return;
    }
    *arg1 = *arg2 - 1;
    keys = arg4->keys;
    a = keys[*arg1];
    *arg3 = (float)(arg6 - a) / (float)(keys[*arg2] - a);
}

void FUN_001d1a80(int a0, int a1, int) {
    FUN_001d1a90(a0, *(int *)((char *)a1 + 48));
}

void FUN_001d1da0(MorphLevelState *self, float t) {
    MorphShortList *steps;
    MorphBaseIndices *base;
    unsigned int count;
    unsigned int first;
    unsigned short *indices;
    unsigned int i;
    unsigned short j;
    unsigned short *parents;
    unsigned int last;
    unsigned short *from;
    unsigned short *walk;
    unsigned int done;
    unsigned short *src;
    int w;
    unsigned int bits;
    unsigned int v;
    MorphWordList *c;
    int n;
    unsigned int bit;
    unsigned int *word;
    unsigned int diff;
    unsigned int end;
    MorphTarget *target;
    MorphTables *tables;
    target = self->targets->data[0];
    tables = self->tables;
    first = tables->firstFrame;
    last = tables->lastFrame;
    steps = tables->steps;
    self->frame = (unsigned int)((float)first + t * (float)(last - first));
    if (self->frame != first) {
        unsigned int previous = self->frame - 1;
        self->level = steps->data[previous];
        if (self->frame < last) {
            if (self->level == steps->data[self->frame]) {
                self->frame = self->frame + 1;
            }
        }
    } else {
        self->level = self->tables->leafCount - 1;
    }
    if (self->shownFrame != self->frame) {
        base = self->tables->base;
        indices = self->indices->lock(0, 0, -1);
        parents = self->tables->parents->data;
        if (self->shownLevel > self->level) {
            count = self->frame * 3;
            for (i = 0; i < count; i++, indices++) {
                if (*indices > self->level) {
                    do {
                        *indices = parents[*indices];
                    } while (*indices > self->level);
                }
            }
            self->shownLevel = self->level;
        } else if (self->level > self->shownLevel) {
            diff = self->level - self->shownLevel;
            walk = indices;
            from = &parents[self->shownLevel];
            for (j = 0; j <= diff; j++) {
                v = *from;
                c = self->changed;
                w = v >> 5;
                bit = 1 << (v & 0x1f);
                word = &c->data[w];
                n = c->count;
                bits = bit | *word;
                if (n != 0 && w >= 0 && w < n) {
                    *word = bits;
                }
                from++;
            }
            done = self->shownFrame * 3;
            src = base->data;
            for (i = 0; i < done; i++, walk++, src++) {
                unsigned int v = *walk;
                if ((1 << (v & 0x1f)) & self->changed->data[v >> 5]) {
                    int level;
                    unsigned short x;
                    x = *src;
                    level = self->level;
                    while (x > level) {
                        x = parents[x];
                    }
                    *walk = x;
                }
            }
            end = self->frame * 3;
            memcpy(walk, src, (end - done) * 2);
            for (; done < end; done++, walk++) {
                int level;
                unsigned short x;
                x = *walk;
                level = self->level;
                while (x > level) {
                    x = parents[x];
                }
                *walk = x;
            }
            igBitMask_ClearAll((igDataList *)self->changed);
            self->shownLevel = self->level;
        }
        self->indices->unlock(indices, 0, 0, -1);
        self->shownFrame = self->frame;
        target->setRange(3, self->frame, 0);
    }
}

int FUN_001d2230(int a0, S_1d2230 *src, S_1d2230 *dst, O_1d2230 *obj, int flag) {
    int r;
    dst->t = src->t;
    switch (src->t) {
    case 1:
        r = 2;
        if (flag == 0) { dst->t = 0; obj->v128(6); obj->v132(0); }
        break;
    case 2:
        r = 1;
        if (flag == 0) { dst->t = 0; obj->v128(1); obj->v132(1); }
        break;
    case 3:
        dst->t = 0; r = 9; obj->f20 = 1;
        break;
    case 4:
        dst->t = 0; r = 9; obj->f20 = 2;
        break;
    case 11:
        r = 9;
        if (flag == 0) { dst->t = 0; obj->v128(4); obj->v132(5); }
        break;
    default:
        dst->t = 0; r = 9; obj->v128(4); obj->v132(5);
        break;
    }
    return r;
}

int FUN_001d3190(void *arg0) {
    void *temp_v0;

    temp_v0 = (void *)(*(int *)((char *)(arg0) + 16));
    if (temp_v0 != 0) {
        return *(int *)((char *)(temp_v0) + 8);
    }
    return 0;
}

int FUN_001d31b0(void *arg0, int arg1) {
    return *(int *)(*(int *)((char *)(*(int *)((char *)(arg0) + 16)) + 16) + (arg1 * 4));
}

int FUN_001d31d0(void *arg0, int arg1) {
        int temp_s2;
    struct L1d *temp_s1;
    temp_s1 = (struct L1d *)(*(int *)((char *)(arg0) + 16));
    if (temp_s1 != 0) {
        temp_s2 = temp_s1->count;
        if (temp_s2 < temp_s1->cap) {
            temp_s1->count = 1 + count_of(temp_s1);
        } else {
            List_Resize((void *)temp_s1, temp_s2 + 1, 4);
        }
        temp_s1->data[temp_s2] = arg1;
    }
    return 1;
}

int Gap__Core__igObject__vfunc_32(ObjectListOwner *self, igObject *object) {
    if (self->_list != 0) {
        igTDataList<igObject *> *list;
        int index = (list = self->_list)->find(object);
        int result;
        if (index >= 0) {
            List_RemoveWordAt(list, index);
            result = g_resultSuccess[0];
        } else {
            result = g_resultFailure[0];
        }
        return result == g_resultSuccess[0];
    }
    return 0;
}

void FUN_001d32f0(S_1d32f0 *arg0, int arg1) {
    int temp_a0;
    int var_s0;

    temp_a0 = arg0->f20;
    arg1 = arg1 & DAT_0048da58[0];
    if (arg1 != (arg1 & temp_a0)) {
        var_s0 = 0;
        arg0->f20 = temp_a0 | arg1;
        while (var_s0 < arg0->c()) {
            FUN_001d32f0(arg0->g(var_s0), arg0->f20);
            var_s0 += 1;
        }
    }
}

