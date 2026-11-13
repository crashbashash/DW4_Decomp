void FUN_0018d480(void) {
    FUN_0018fbc0((void *)g_igSphere_metaObject[0], igAABox_GetMetaObject(), (int)FUN_0018d700);
    FUN_0018fbc0((void *)g_igSphere_metaObject[0], igPlane_GetMetaObject(), (int)FUN_0018d7b0);
    FUN_0018fbc0((void *)g_igSphere_metaObject[0], (void *)g_igSphere_metaObject[0], (int)FUN_0018d820);
    FUN_0018fca0((PairKeyedItem *)g_igSphere_metaObject[0], (PairKeyedItem *)g_igAABox_metaObject[0], (int)FUN_0018da00);
    FUN_0018fca0((PairKeyedItem *)g_igSphere_metaObject[0], (PairKeyedItem *)g_igPlane_metaObject[0], (int)FUN_0018d9b0);
    FUN_0018fca0((PairKeyedItem *)g_igSphere_metaObject[0], (PairKeyedItem *)g_igSphere_metaObject[0], (int)FUN_0018db20);
    FUN_0018fc30((IndexedWordPairKey *)g_igSphere_metaObject[0], (IndexedWordPairKey *)g_igAABox_metaObject[0], (int)FUN_0018dd20);
    FUN_0018fc30((IndexedWordPairKey *)g_igSphere_metaObject[0], (IndexedWordPairKey *)g_igSphere_metaObject[0], (int)&FUN_0018de10);
    FUN_0018fd10((int *)g_igSphere_metaObject[0], (int)igSphere_IntersectsRay);
    FUN_0018fd90((IndexedWordKey *)g_igSphere_metaObject[0], (int)&FUN_0018dbc0);
    FUN_0018fd50((IndexedSlotKey *)g_igSphere_metaObject[0], (int)&FUN_0018dfc0);
    FUN_0018fe10((int *)g_igSphere_metaObject[0], (int)FUN_0018dcb0);
    FUN_0018fdd0(g_igSphere_metaObject[0], (int)FUN_0018e040);
    FUN_0018fe50((IndexedSlotKey *)g_igSphere_metaObject[0], (int)thunk_FUN_0018d630);
    FUN_0018fe90((IndexedWordKey *)g_igSphere_metaObject[0], (int)FUN_0018e150);
    FUN_0018fed0(g_igSphere_metaObject[0], (int)FUN_0018e160);
    FUN_0018ff10((int *)g_igSphere_metaObject[0], (int)FUN_0018e190);
}

int FUN_0018d700(igSphere *sphere, igAABox *box) {
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
        } else if (!(c <= box->_max[i])) {
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

int FUN_0018d7b0(igSphere *sphere, igPlane *plane) {
    float radius = sphere->_radius; if (radius < 0.0f) return 0; 
    /* matching construct: hand enumeration under C++ — int result set then cleared, no bool narrowing */
    int hit = 1;
    if (!(0.0f <= radius + plane->_offset - (sphere->_center[0] * plane->_norm[0] + sphere->_center[1] * plane->_norm[1] + sphere->_center[2] * plane->_norm[2]))) hit = 0;
    return hit;
}

/* matching construct: declaration-order sweep — dy, dx, dz order */
int FUN_0018d820(igSphere *a, igSphere *b) {
    if (a->_radius < 0.0f || b->_radius < 0.0f) {
        return 0;
    }
    {
        float r = a->_radius + b->_radius;
        float dy = a->_center[1] - b->_center[1];
        float dx = a->_center[0] - b->_center[0];
        float dz = a->_center[2] - b->_center[2];
        /* matching construct: hand enumeration under C++ — int result set then cleared, no bool narrowing */
        int hit = 1;
        if (!(dx * dx + dy * dy + dz * dz <= r * r)) {
            hit = 0;
        }
        return hit;
    }
}

/* matching construct: declaration-order sweep — t declared before root */
int igSphere_IntersectsRay(igSphere *sphere, igRay *ray) {
    float radiusSq, dx, dy, dz, proj, disc, t, root;
    if (sphere->_radius < 0.0f) {
        return 0;
    }
    radiusSq = sphere->_radius * sphere->_radius;
    dx = sphere->_center[0] - ray->_pos[0];
    dy = sphere->_center[1] - ray->_pos[1];
    dz = sphere->_center[2] - ray->_pos[2];
    proj = dx * ray->_dir[0] + dy * ray->_dir[1] + dz * ray->_dir[2];
    disc = radiusSq + proj * proj - dx * dx - dy * dy - dz * dz;
    if (disc < 0.0f) {
        return 0;
    }
    root = sqrtf(disc);
    t = proj - root;
    if (0.0f <= t && t <= ray->_len) {
        return 1;
    }
    t = proj + root;
    if (0.0f <= t && t <= ray->_len) {
        return 1;
    }
    return 0;
}

Intersection FUN_0018d9b0(igSphere *sphere, void *other)
{
    if (sphere->_radius < 0.0f)
        return kDisjoint;
    return FUN_0018ffa0((void **)other, (void **)sphere) ? kIntersecting : kDisjoint;
}

/* matching construct: declaration-order sweep — dy, dx, dz, distSq order */
int FUN_0018db20(igSphere *a, igSphere *b) {
    if (a->_radius < 0.0f) {
        return 0;
    }
    {
        float dy = a->_center[1] - b->_center[1]; float dx = a->_center[0] - b->_center[0]; float dz = a->_center[2] - b->_center[2]; float distSq;
        distSq = dx * dx + dy * dy + dz * dz;
        if (b->_radius <= a->_radius && distSq <= (a->_radius - b->_radius) * (a->_radius - b->_radius)) {
            return 2;
        }
        if (distSq <= (a->_radius + b->_radius) * (a->_radius + b->_radius)) {
            return 1;
        }
        return 0;
    }
}

/* matching construct: declaration-order sweep — dy, dx, dz order */
int FUN_0018dcb0(igSphere *sphere, float *point) {
    float radius = sphere->_radius;
    if (radius < 0.0f) {
        return 0;
    }
    {
        float dy = sphere->_center[1] - point[1]; float dx = sphere->_center[0] - point[0]; float dz = sphere->_center[2] - point[2];
        if (dx * dx + dy * dy + dz * dz <= radius * radius) {
            return 2;
        }
        return 0;
    }
}

void FUN_0018dd20(S4 *p, S4 *q) {
    float box[24];
    float dx, dy, dz;
    if (q->x <= q->r) {
        if (p->r < 0.0f) {
            p->x = 0.5f * q->x + 0.5f * q->r;
            p->y = 0.5f * q->y + 0.5f * q->ax;
            p->z = 0.5f * q->z + 0.5f * q->ay;
            dy = p->y - q->ax;
            dx = p->x - q->r;
            dz = p->z - q->ay;
            p->r = sqrtf(dx * dx + dy * dy + dz * dz);
        } else {
            FUN_0018aaa0((S *)q, box);
            FUN_00190120((void **)p, (int)box, 8);
        }
    }
}

void FUN_0018dfc0(void *parg0, S5 *arg1) {
    int arg0 = (int)parg0;
    float v[3];
    float s;
    FUN_001900d0((void **)arg0, (int)((char *)arg1 + 8));
    s = arg1->s;
    v[0] = arg1->x + s * arg1->dx;
    v[1] = arg1->y + s * arg1->dy;
    v[2] = arg1->z + s * arg1->dz;
    FUN_001900d0((void **)arg0, (int)v);
}

void thunk_FUN_0018d630(void) {
    FUN_0018d630();
}

void FUN_0018e150(void *arg0) {
    *(int *)((char *)(arg0) + 20) = 0xBF800000;
}

int FUN_0018e160(void *arg0) {
    int var_v0;

    var_v0 = 1;
    if (!(*(float *)((char *)(arg0) + 20) < 0.0f)) {
        var_v0 = 0;
    }
    return var_v0;
}

void FUN_0018e190(void *arg0, void *arg1) {
    *(float *)((char *)(arg1) + 0) = (float) *(float *)((char *)(arg0) + 8);
    *(float *)((char *)(arg1) + 4) = (float) *(float *)((char *)(arg0) + 12);
    *(float *)((char *)(arg1) + 8) = (float) *(float *)((char *)(arg0) + 16);
}

