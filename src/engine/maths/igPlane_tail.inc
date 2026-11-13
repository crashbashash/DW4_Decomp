void FUN_0018c660(void) {
    FUN_0018fbc0((void *)g_igPlane_metaObject[0], igAABox_GetMetaObject(), (int)&FUN_0018c920);
    FUN_0018fbc0((void *)g_igPlane_metaObject[0], (void *)g_igPlane_metaObject[0], (int)FUN_0018ca00);
    FUN_0018fbc0((void *)g_igPlane_metaObject[0], igSphere_GetMetaObject(), (int)FUN_0018c990);
    FUN_0018fca0((PairKeyedItem *)g_igPlane_metaObject[0], (PairKeyedItem *)g_igAABox_metaObject[0], (int)FUN_0018cc10);
    FUN_0018fca0((PairKeyedItem *)g_igPlane_metaObject[0], (PairKeyedItem *)g_igPlane_metaObject[0], (int)&FUN_0018cb10);
    FUN_0018fca0((PairKeyedItem *)g_igPlane_metaObject[0], (PairKeyedItem *)g_igSphere_metaObject[0], (int)FUN_0018cf20);
    FUN_0018fc30((IndexedWordPairKey *)g_igPlane_metaObject[0], (IndexedWordPairKey *)g_igPlane_metaObject[0], (int)FUN_0018d100);
    FUN_0018fc30((IndexedWordPairKey *)g_igPlane_metaObject[0], (IndexedWordPairKey *)g_igAABox_metaObject[0], (int)FUN_0018d110);
    FUN_0018fc30((IndexedWordPairKey *)g_igPlane_metaObject[0], (IndexedWordPairKey *)g_igSphere_metaObject[0], (int)FUN_0018d160);
    FUN_0018fd10((int *)g_igPlane_metaObject[0], (int)FUN_0018ca80);
    FUN_0018fd90((IndexedWordKey *)g_igPlane_metaObject[0], (int)&FUN_0018cfb0);
    FUN_0018fd50((IndexedSlotKey *)g_igPlane_metaObject[0], (int)&FUN_0018d1d0);
    FUN_0018fe10((int *)g_igPlane_metaObject[0], (int)&FUN_0018d060);
    FUN_0018fdd0(g_igPlane_metaObject[0], (int)&FUN_0018d0b0);
    FUN_0018fe50((IndexedSlotKey *)g_igPlane_metaObject[0], (int)thunk_FUN_0018c820);
    FUN_0018fe90((IndexedWordKey *)g_igPlane_metaObject[0], (int)FUN_0018d260);
    FUN_0018fed0(g_igPlane_metaObject[0], (int)FUN_0018d270);
    FUN_0018ff10((int *)g_igPlane_metaObject[0], (int)FUN_0018d280);
}

void FUN_0018c820(igPlane *plane, const void *matrix) {
    igVec3f point;
    float d;
    float scale;

    d = plane->_offset;
    point.x = d * plane->_norm[0];
    point.y = d * plane->_norm[1];
    point.z = d * plane->_norm[2];
    FUN_00192f50(plane->_norm, plane->_norm, (float *)matrix);
    FUN_00192fc0((float *)&point, (float *)&point, (float *)matrix);
    scale = 1.0f / lengthOf(plane->_norm);
    plane->_norm[0] = plane->_norm[0] * scale;
    plane->_norm[1] = plane->_norm[1] * scale;
    plane->_norm[2] = plane->_norm[2] * scale;
    plane->_offset = point.dot(plane->_norm);
    plane->_octant = FUN_00192e50(plane->_norm);
}

int FUN_0018c920(void *arg0, void *arg1) {
    int buf[4];

    if (!(*(float *)((char *)(arg1) + 8) <= *(float *)((char *)(arg1) + 20))) {
        return 0;
    }
    igAABox_GetCorner((igAABox *)arg1, ~*(int *)((char *)(arg0) + 24) & 7, (V3 *)buf);
    return FUN_0018d060((P2 *)arg0, (float *)buf) == 2;
}

int FUN_0018c990(void *arg0, void *arg1) {
    float temp_f7;
    int var_v0;

    temp_f7 = *(float *)((char *)(arg1) + 20);
    if (temp_f7 < 0.0f) {
        return 0;
    }
    var_v0 = 1;
    if (!((((*(float *)((char *)(arg0) + 8) * *(float *)((char *)(arg1) + 8)) + (*(float *)((char *)(arg0) + 12) * *(float *)((char *)(arg1) + 12)) + (*(float *)((char *)(arg0) + 16) * *(float *)((char *)(arg1) + 16))) - *(float *)((char *)(arg0) + 20)) <= temp_f7)) {
        var_v0 = 0;
    }
    return var_v0;
}

int FUN_0018ca00(Plane *a, Plane *b) {
    float x = a->x + b->x;
    float y = a->y + b->y;
    float z = a->z + b->z;
    if (x * x + y * y + z * z < 5e-7f) {
        /* matching construct: hand enumeration under C++ — int result set then cleared, no bool narrowing */
        int hit = 1;
        if (!(0.0f <= a->d + b->d)) {
            hit = 0;
        }
        return hit;
    }
    return 1;
}

int FUN_0018ca80(void *arg0, void *arg1) {
    int var_v0;
    float temp_f8;
    float temp_f7;
    float temp_f6;
    float temp_f5;

    temp_f7 = *(float *)((char *)(arg0) + 12);
    temp_f6 = *(float *)((char *)(arg0) + 8);
    temp_f5 = *(float *)((char *)(arg0) + 16);
    temp_f8 = ((temp_f6 * *(float *)((char *)(arg1) + 8)) + (temp_f7 * *(float *)((char *)(arg1) + 12)) + (temp_f5 * *(float *)((char *)(arg1) + 16))) - *(float *)((char *)(arg0) + 20);
    if (temp_f8 <= 0.0f) {
        return 1;
    }
    var_v0 = 1;
    if (!((temp_f8 + (*(float *)((char *)(arg1) + 32) * ((temp_f6 * *(float *)((char *)(arg1) + 20)) + (temp_f7 * *(float *)((char *)(arg1) + 24)) + (temp_f5 * *(float *)((char *)(arg1) + 28))))) <= 0.0f)) {
        var_v0 = 0;
    }
    return var_v0;
}

int FUN_0018cb10(Plane *a, Plane *b) {
    V32 p;
    float d;
    int r;
    float dot = a->x * b->x + a->y * b->y + a->z * b->z;
    if (fabs_(dot - 1.0f) < 5e-7f) { return (b->d > a->d) ? 2 : 0; }
 if (fabs_(1.0f + dot) < 5e-7f) { d = b->d; p.x = d * b->x; p.y = d * b->y; p.z = d * b->z; return FUN_0018d060((P2 *)a, (float *)&p) ? 2 : 0;} else return 1;
}

int FUN_0018cf20(igPlane *plane, igSphere *sphere) {
    float radius = sphere->_radius; float d; int r; if (radius < 0.0f) return 0; d = plane->_norm[0] * sphere->_center[0] + plane->_norm[1] * sphere->_center[1] + plane->_norm[2] * sphere->_center[2] - plane->_offset; if (d <= -radius) r = 2; else if (d <= radius) r = 1; else r = 0; return r;
}

int FUN_0018cfb0(void *arg0, struct S2 *arg1) {
    float v[3];
    int s0, v0;
    v[0] = arg1->a[0] + arg1->b[0];
    v[1] = arg1->a[1] + arg1->b[1];
    v[2] = arg1->a[2] + arg1->b[2];
    s0 = FUN_0018d060((P2 *)arg0, arg1->a) == 2;
    v0 = FUN_0018d060((P2 *)arg0, v) == 2;
    if (s0 != 0 && v0 != 0) {
        return 2;
    }
    if (s0 != 0 || v0 != 0) {
        return 1;
    }
    return 0;
}

int FUN_0018d060(P2 *p, float *v) {
    int r;
    float d;
    d = p->a * v[0] + p->b * v[1] + p->c * v[2] - p->d;
    r = 0;
    if (d <= 0.0f) r = 2;
    return r;
}

void FUN_0018d0b0(V4 *a, float *b) {
    float t = b[0] * a->f8 + b[1] * a->f12 + b[2] * a->f16;
    if (a->f20 < t) a->f20 = t;
}

void FUN_0018d100(void) {

}

void FUN_0018d110(int arg0, struct S18d110 *arg1) {
    float buf[24];

    if (arg1->a <= arg1->b) {
        FUN_0018aaa0((S *)arg1, buf);
        FUN_00190120((void **)arg0, (int)buf, 8);
    }
}

void FUN_0018d160(struct A *arg0, struct B5 *arg1) {
    float v[3];
    float t = arg1->f20;
    if (!(t < 0.0f)) {
        v[0] = arg1->f8 + t * arg0->f8;
        v[1] = arg1->f12 + t * arg0->f12;
        v[2] = arg1->f16 + t * arg0->f16;
        FUN_0018d0b0((V4 *)arg0, v);
    }
}

void FUN_0018d1d0(void *arg0, float *arg1) {
    float sp20[3];
    float temp_f2;

    temp_f2 = arg1[8];
    sp20[0] = arg1[2] + (temp_f2 * arg1[5]);
    sp20[1] = arg1[3] + (temp_f2 * arg1[6]);
    sp20[2] = arg1[4] + (temp_f2 * arg1[7]);
    FUN_0018d0b0((V4 *)arg0, arg1 + 2);
    FUN_0018d0b0((V4 *)arg0, sp20);
}

void thunk_FUN_0018c820(igPlane *plane, const void *matrix) {
    FUN_0018c820(plane, matrix);
}

