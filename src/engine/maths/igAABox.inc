void FUN_0018a660(int arg0) {
    FUN_0018a780();
    igMetaObject_CreateInstance(*(int *)0x5610E0, arg0);
}

igMetaObject *FUN_0018a6a0(void) {
    if (g_igAABox_metaObject[0] == 0) {
        g_igAABox_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igAABox_metaObject[0];
}

igMetaObject *igAABox_GetMetaObject(void)
{
    igMetaObject *g = g_igAABox_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0018a780();
    return g_igAABox_metaObject[0];
}

int igAABox_GetVTable(void) {
    int tmp[8];
    int off;
    igObject_InitHeader(&tmp[0]);
    tmp[0] = (int)&DAT_005277e0[0];
    off = *(int *)((char *)(g_objectSystem[0]) + 916);
    return *(int *)((char *)tmp + off);
}

void FUN_0018a780(void)
{
    igMetaObject_RunStaticInit(igAABox_Register);
}

void igAABox_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAABox_metaObject,
        igVolume_Register,
        igVolume_GetPublishedMetaObject,
        thunk_igAABox_GetMetaObject,
        igAABox_className,
        0x20, /* instance size */
        igAABox_GetVTable,
        &igAABox_InitFields,
        thunk_FUN_0018a8f0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igAABox_GetMetaObject(void) {
    igAABox_GetMetaObject();
}

void igAABox_InitFields(void) {
    float va[4];
    float vb[4];
    int temp_a0;
    int temp_a0_2;
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igAABox_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igAABox_ctorTable[0], 2);
    temp_a0 = igMetaObject_GetFieldAt(temp_s0, temp_s1);
    va[0] = 3.402823466e+38f;
    va[1] = 3.402823466e+38f;
    va[2] = 3.402823466e+38f;
    FUN_0018e470((igVec3fMetaFieldView *)temp_a0, va);
    temp_a0_2 = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1);
    vb[0] = -3.402823466e+38f;
    vb[1] = -3.402823466e+38f;
    vb[2] = -3.402823466e+38f;
    FUN_0018e470((igVec3fMetaFieldView *)temp_a0_2, vb);
    igMetaObject_NameFields(temp_s0, &g_igAABox_fieldTable[0], &DAT_0048ae68[0], &DAT_0048ae70[0], temp_s1);
}

void thunk_FUN_0018a8f0(void) {
    FUN_0018a8f0();
}

void FUN_0018a8f0(void) {
    FUN_0018fbc0((void *)g_igAABox_metaObject[0], (void *)g_igAABox_metaObject[0], (int)FUN_0018b050);
    FUN_0018fbc0((void *)g_igAABox_metaObject[0], igPlane_GetMetaObject(), (int)FUN_0018b110);
    FUN_0018fbc0((void *)g_igAABox_metaObject[0], igSphere_GetMetaObject(), (int)FUN_0018afa0);
    FUN_0018fca0((PairKeyedItem *)g_igAABox_metaObject[0], (PairKeyedItem *)g_igAABox_metaObject[0], (int)FUN_0018b350);
    FUN_0018fca0((PairKeyedItem *)g_igAABox_metaObject[0], (PairKeyedItem *)g_igPlane_metaObject[0], (int)FUN_0018b300);
    FUN_0018fca0((PairKeyedItem *)g_igAABox_metaObject[0], (PairKeyedItem *)g_igSphere_metaObject[0], (int)FUN_0018b450);
    FUN_0018fc30((IndexedWordPairKey *)g_igAABox_metaObject[0], (IndexedWordPairKey *)g_igAABox_metaObject[0], (int)FUN_0018b730);
    FUN_0018fc30((IndexedWordPairKey *)g_igAABox_metaObject[0], (IndexedWordPairKey *)g_igSphere_metaObject[0], (int)FUN_0018b7d0);
    FUN_0018fd10((int *)g_igAABox_metaObject[0], (int)FUN_0018b170);
    FUN_0018fd90((IndexedWordKey *)g_igAABox_metaObject[0], (int)FUN_0018b540);
    FUN_0018fd50((IndexedSlotKey *)g_igAABox_metaObject[0], (int)FUN_0018b6b0);
    FUN_0018fe10((int *)g_igAABox_metaObject[0], (int)igAABox_IntersectPoint);
    FUN_0018fdd0(g_igAABox_metaObject[0], (int)FUN_0018b890);
    FUN_0018fe50((IndexedSlotKey *)g_igAABox_metaObject[0], (int)thunk_FUN_0018ac80);
    FUN_0018fe90((IndexedWordKey *)g_igAABox_metaObject[0], (int)FUN_0018b940);
    FUN_0018fed0(g_igAABox_metaObject[0], (int)FUN_0018b970);
    FUN_0018ff10((int *)g_igAABox_metaObject[0], (int)FUN_0018b990);
}

void FUN_0018aaa0(S *arg0, float *arg1) {
    float z, y, x;
    arg1[0] = arg0->f[0];
    arg1[1] = arg0->f[1];
    arg1[2] = arg0->f[2];
    z = arg0->f[5]; y = arg0->f[1]; x = arg0->f[0];
    arg1[3] = x; arg1[4] = y; arg1[5] = z;
    z = arg0->f[2]; y = arg0->f[4]; x = arg0->f[0];
    arg1[6] = x; arg1[7] = y; arg1[8] = z;
    z = arg0->f[5]; y = arg0->f[4]; x = arg0->f[0];
    arg1[9] = x; arg1[10] = y; arg1[11] = z;
    z = arg0->f[2]; y = arg0->f[1]; x = arg0->f[3];
    arg1[12] = x; arg1[13] = y; arg1[14] = z;
    z = arg0->f[5]; y = arg0->f[1]; x = arg0->f[3];
    arg1[15] = x; arg1[16] = y; arg1[17] = z;
    z = arg0->f[2]; y = arg0->f[4]; x = arg0->f[3];
    arg1[18] = x; arg1[19] = y; arg1[20] = z;
    arg1[21] = arg0->f[3];
    arg1[22] = arg0->f[4];
    arg1[23] = arg0->f[5];
}

void igAABox_GetCorner(igAABox *arg0, unsigned int arg1, V3 *arg2) {
    float c, b, a;
    switch (arg1) {
    case 7:
        arg2->x = *(float *)&arg0->_min[0];
        arg2->y = *(float *)&arg0->_min[1];
        arg2->z = *(float *)&arg0->_min[2];
        break;
    case 6:
        c = ((float *)&arg0->_max)[2];
        b = *(float *)&arg0->_min[1];
        a = *(float *)&arg0->_min[0];
        arg2->x = a;
        arg2->y = b;
        arg2->z = c;
        break;
    case 5:
        c = *(float *)&arg0->_min[2];
        b = ((float *)&arg0->_max)[1];
        a = *(float *)&arg0->_min[0];
        arg2->x = a;
        arg2->y = b;
        arg2->z = c;
        break;
    case 4:
        c = ((float *)&arg0->_max)[2];
        b = ((float *)&arg0->_max)[1];
        a = *(float *)&arg0->_min[0];
        arg2->x = a;
        arg2->y = b;
        arg2->z = c;
        break;
    case 3:
        c = *(float *)&arg0->_min[2];
        b = *(float *)&arg0->_min[1];
        a = ((float *)&arg0->_max)[0];
        arg2->x = a;
        arg2->y = b;
        arg2->z = c;
        break;
    case 2:
        c = ((float *)&arg0->_max)[2];
        b = *(float *)&arg0->_min[1];
        a = ((float *)&arg0->_max)[0];
        arg2->x = a;
        arg2->y = b;
        arg2->z = c;
        break;
    case 1:
        c = *(float *)&arg0->_min[2];
        b = ((float *)&arg0->_max)[1];
        a = ((float *)&arg0->_max)[0];
        arg2->x = a;
        arg2->y = b;
        arg2->z = c;
        break;
    case 0:
        arg2->x = ((float *)&arg0->_max)[0];
        arg2->y = ((float *)&arg0->_max)[1];
        arg2->z = ((float *)&arg0->_max)[2];
        break;
    }
}

int FUN_0018afa0(igAABox *box, igSphere *sphere) {
    float dist;
    int i;
    if (!(box->_min[0] <= box->_max[0]) || sphere->_radius < 0.0f) {
        return 0;
    }
    dist = 0.0f;
    for (i = 0; i < 3; i++) {
        float lo = box->_min[i];
        float c = sphere->_center[i];
        if (c < lo) {
            float s = c - lo;
            dist += s * s;
        } else if (box->_max[i] < c) {
            float s = c - box->_max[i];
            dist += s * s;
        }
    }
    {
        /* matching construct: hand enumeration under C++ — int result set then cleared, no bool narrowing */
        int hit = 1;
        if (!(dist <= sphere->_radius * sphere->_radius)) {
            hit = 0;
        }
        return hit;
    }
}

int FUN_0018b050(struct B *arg0, struct B *arg1) {
    int var_v0;

    /* matching construct: hand enumeration under C++ — int result set then cleared, no bool narrowing */
    var_v0 = 1;
    if (!(arg1->f8 <= arg0->f20)) {
        var_v0 = 0;
    }
    if (var_v0 != 0) {
        var_v0 = 1;
        if (!(arg0->f8 <= arg1->f20)) {
            var_v0 = 0;
        }
    }
    if (var_v0 != 0) {
        var_v0 = 1;
        if (!(arg1->f12 <= arg0->f24)) {
            var_v0 = 0;
        }
    }
    if (var_v0 != 0) {
        var_v0 = 1;
        if (!(arg0->f12 <= arg1->f24)) {
            var_v0 = 0;
        }
    }
    if (var_v0 != 0) {
        var_v0 = 1;
        if (!(arg1->f16 <= arg0->f28)) {
            var_v0 = 0;
        }
    }
    if (var_v0 != 0) {
        var_v0 = 1;
        if (!(arg0->f16 <= arg1->f28)) {
            var_v0 = 0;
        }
    }
    return var_v0;
}

int FUN_0018b110(void *arg0, void *arg1) {
    int sp20[4];

    if (!(*(float *)((char *)(arg0) + 8) <= *(float *)((char *)(arg0) + 20))) {
        return 0;
    }
    igAABox_GetCorner((igAABox *)arg0, ~*(int *)((char *)(arg1) + 24) & 7, (V3 *)sp20);
    return FUN_0018d060((P2 *)arg1, (float *)sp20) == 2;
}

int FUN_0018b300(igAABox *box, void *other) {
    unsigned char inside;
    if (!(box->_min[0] <= box->_max[0])) {
        return kOutside;
    }
    inside = FUN_0018c920(other, box);
    return inside ? kInside : kOutside;
}

int FUN_0018b350(B2 *arg0, B2 *arg1) {
    if (!(arg0->x0 <= arg0->x1) || !(arg1->x0 <= arg1->x1)) {
        return 0;
    }
    if (FUN_0018ffa0((void **)arg0, (void **)arg1) != 0) {
        if (arg0->x0 <= arg1->x0) {
            if (!(arg0->x1 < arg1->x1) && (arg0->y0 <= arg1->y0) && !(arg0->y1 < arg1->y1) && (arg0->z0 <= arg1->z0) && !(arg0->z1 < arg1->z1)) {
                return 2;
            }
        }
        return 1;
    }
    return 0;
}

int FUN_0018b450(float *a, float *b) {
    float r, d0, d1, d2, d3, d4, d5;
    if (FUN_0018afa0((igAABox *)a, (igSphere *)b) == 0) return 0;
    d0 = b[2] - a[2];
    d1 = b[3] - a[3];
    d2 = b[4] - a[4];
    d3 = b[2] - a[5];
    d4 = b[3] - a[6];
    d5 = b[4] - a[7];
    r = b[5] * b[5];
    d0 = d0 * d0; d1 = d1 * d1; d2 = d2 * d2; d3 = d3 * d3; d4 = d4 * d4; d5 = d5 * d5;
    if (!(r <= d0 && r <= d1 && r <= d2 && r <= d3 && r <= d4 && r <= d5)) return 1;
    return 2;
}

int FUN_0018b540(void *parg0, P *b) {
    int a = (int)parg0;
    float v[3];
    float t;
    int s0, v0;
    if (!(((B3 *)a)->f8 <= ((B3 *)a)->f20)) return 0;
    s0 = igAABox_IntersectPoint((B4 *)a, (V *)&b->f8) != 0;
    t = b->f32;
    v[0] = b->f8 + t * b->f20;
    v[1] = b->f12 + t * b->f24;
    v[2] = b->f16 + t * b->f28;
    v0 = igAABox_IntersectPoint((B4 *)a, (V *)v) != 0;
    if (s0 != 0 && v0 != 0) return 2;
    if (s0 != 0 || v0 != 0 || FUN_0018b170(a, b) != 0) return 1;
    return 0;
}

int igAABox_IntersectPoint(struct B4 *arg0, struct V *arg1) {
    float temp_f1;
    float temp_f1_2;
    float temp_f1_3;
    temp_f1 = arg1->x;
    if (arg0->lox <= temp_f1 && temp_f1 <= arg0->hix) {
        temp_f1_2 = arg1->y;
        if ((arg0->loy <= temp_f1_2) && (temp_f1_2 <= arg0->hiy)) {
            temp_f1_3 = arg1->z;
            if ((arg0->loz <= temp_f1_3) && (temp_f1_3 <= arg0->hiz)) {
                return 2;
            }
        }
    }
    return 0;
}

void FUN_0018b730(igAABox *box, igAABox *other) {
    if (!(box->_min[0] <= other->_min[0])) box->_min[0] = other->_min[0];
    if (!(box->_min[1] <= other->_min[1])) box->_min[1] = other->_min[1];
    if (!(box->_min[2] <= other->_min[2])) box->_min[2] = other->_min[2];
    if (box->_max[0] < other->_max[0]) box->_max[0] = other->_max[0];
    if (box->_max[1] < other->_max[1]) box->_max[1] = other->_max[1];
    if (box->_max[2] < other->_max[2]) box->_max[2] = other->_max[2];
}

void FUN_0018b7d0(igAABox *box, igSphere *sphere) {
    float radius;
    float low[3];
    float high[3];

    radius = sphere->_radius;
    if (radius < 0.0f) {
        return;
    }
    low[0] = sphere->_center[0] - radius;
    low[1] = sphere->_center[1] - radius;
    low[2] = sphere->_center[2] - radius;
    high[0] = sphere->_center[0] + radius;
    high[1] = sphere->_center[1] + radius;
    high[2] = sphere->_center[2] + radius;
    if (!(box->_min[0] <= low[0])) box->_min[0] = low[0];
    if (!(box->_min[1] <= low[1])) box->_min[1] = low[1];
    if (!(box->_min[2] <= low[2])) box->_min[2] = low[2];
    if (box->_max[0] < high[0]) box->_max[0] = high[0];
    if (box->_max[1] < high[1]) box->_max[1] = high[1];
    if (box->_max[2] < high[2]) box->_max[2] = high[2];
}

void FUN_0018b890(struct Box *arg0, float *arg1) {
    float t;

    t = arg1[0];
    if (!(arg0->mn[0] <= t)) {
        arg0->mn[0] = t;
    }
    t = arg1[1];
    if (!(arg0->mn[1] <= t)) {
        arg0->mn[1] = t;
    }
    t = arg1[2];
    if (!(arg0->mn[2] <= t)) {
        arg0->mn[2] = t;
    }
    t = arg1[0];
    if (arg0->mx[0] < t) {
        arg0->mx[0] = t;
    }
    t = arg1[1];
    if (arg0->mx[1] < t) {
        arg0->mx[1] = t;
    }
    t = arg1[2];
    if (arg0->mx[2] < t) {
        arg0->mx[2] = t;
    }
}

int thunk_FUN_0018ac80()
{
    return FUN_0018ac80();
}

void FUN_0018b940(igAABox *box) {
    box->_min[0] = box->_min[1] = box->_min[2] = 3.4028235e38f;
    box->_max[0] = box->_max[1] = box->_max[2] = -3.4028235e38f;
}

int FUN_0018b970(void *arg0) {
    int var_v0;

    var_v0 = 1;
    if (*(float *)((char *)(arg0) + 8) <= *(float *)((char *)(arg0) + 20)) {
        var_v0 = 0;
    }
    return var_v0;
}

void FUN_0018b990(float *arg0, float *arg1) {
    arg1[0] = arg0[2] * 0.5f + arg0[5] * 0.5f;
    arg1[1] = arg0[3] * 0.5f + arg0[6] * 0.5f;
    arg1[2] = arg0[4] * 0.5f + arg0[7] * 0.5f;
}

float FUN_0018b9e0(Ray *ray, V2 *a, V2 *b, V2 *c, V2 *hit, V2 *n, int mode) {
    /* matching construct: enumeration — d1, d2 and d3 reused as temporaries in the hit-point calculation */
    V2 e1,e2,ha,hb,hc,c1,c2,c3;
    float denom, t, inv, d1, d2, d3, m1, m2, m3;
    e1.x = b->x - a->x; e1.y = b->y - a->y; e1.z = b->z - a->z;
    e2.x = c->x - a->x; e2.y = c->y - a->y; e2.z = c->z - a->z;
    FUN_00192dd0((float *)n, (float *)&e1, (float *)&e2);
    inv = 1.0f / sqrtf(dot(n, n));
    n->x *= inv; n->y *= inv; n->z *= inv;
    denom = n->dot(ray->d);
    if (mode != 2) {
        if ((isPos(denom) && mode == 0) || (isNeg(denom) && mode == 1) || isZero(denom) || denom != denom)
            return -2.0f;
    }
    t = -n->dot(ray->o - *a) / denom;
    if (isNeg(t) || !(t <= ray->maxT)) return -3.0f;
    d1 = t*ray->d.x; hit->x = ray->o.x + d1; d2 = t*ray->d.y; hit->y = ray->o.y + d2; d3 = t*ray->d.z; hit->z = ray->o.z + d3;
    ha.x = a->x - hit->x; ha.y = a->y - hit->y; ha.z = a->z - hit->z;
    hb.x = b->x - hit->x; hb.y = b->y - hit->y; hb.z = b->z - hit->z;
    hc.x = c->x - hit->x; hc.y = c->y - hit->y; hc.z = c->z - hit->z;
    FUN_00192dd0((float *)&c1, (float *)&ha, (float *)&hb);
    FUN_00192dd0((float *)&c2, (float *)&hb, (float *)&hc);
    FUN_00192dd0((float *)&c3, (float *)&hc, (float *)&ha);
    d1 = c1.x * n->x + c1.y * n->y + c1.z * n->z;
    d2 = c2.x * n->x + c2.y * n->y + c2.z * n->z;
    d3 = c3.x * n->x + c3.y * n->y + c3.z * n->z;
    if ((isNeg(d1) & isNeg(d2) & isNeg(d3)) || (isPos(d1) & isPos(d2) & isPos(d3)))
        return t;
    return -4.0f;
}

