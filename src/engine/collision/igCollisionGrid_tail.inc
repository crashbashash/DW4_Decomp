static inline float minOf(float a, float b) { return a < b ? a : b; }

static inline void setVec3(float *v, float x, float y, float z) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
}

void FUN_0023b430(igCollisionGrid *grid) {
    igAABox *bound = (igAABox *)grid->_bound;
    float &stepY = grid->_deltas[1];
    float &stepZ = grid->_deltas[2];
    grid->_deltas[0] = bound->_max[0] - bound->_min[0];
    grid->_deltas[1] = bound->_max[1] - bound->_min[1];
    grid->_deltas[2] = bound->_max[2] - bound->_min[2];
    grid->_deltas[0] = grid->_deltas[0] / (float)grid->_sizeX;
    grid->_deltas[1] = grid->_deltas[1] / (float)grid->_sizeY;
    grid->_deltas[2] = grid->_deltas[2] / (float)grid->_sizeZ;
    grid->_maxRadius = minOf(grid->_deltas[0], grid->_deltas[1]);
    grid->_maxRadius = minOf(grid->_maxRadius, stepZ);
    grid->_maxRadius = grid->_maxRadius * 0.5f;
    int index = 0;
    const float *origin = ((igAABox *)grid->_bound)->_min;
    float x = origin[0];
    float y = origin[1];
    float z = origin[2];
    for (int k = 0; k < grid->_sizeZ; k++) {
        for (int j = 0; j < grid->_sizeY; j++) {
            for (int i = 0; i < grid->_sizeX; i++) {
                igSmartPointer<igCollisionCell> cell(FUN_0023a6e0(0), AdoptReference());
                float maxX = x + grid->_deltas[0];
                float maxY = y + grid->_deltas[1];
                float maxZ = z + grid->_deltas[2];
                cell->_grid = (int)grid;
                igCollisionCell *c = cell.p;
                setVec3(((igAABox *)c->_box)->_min, x, y, z);
                setVec3(((igAABox *)c->_box)->_max, maxX, maxY, maxZ);
                ((CellList *)grid->_cells)->set(index, cell);
                index++;
                x += grid->_deltas[0];
            }
            origin = ((igAABox *)grid->_bound)->_min;
            x = origin[0];
            y += stepY;
        }
        y = origin[1];
        z += stepZ;
    }
}

void FUN_0023b720(G *g, float *p, int *ox, int *oy, int *oz) {
    float x = p[0], y = p[1], z = p[2];
    B *b = g->box;
    float *v = b->v;
    float *nv = b->v;
    float t;
    t = b->v[0]; if (x < t) x = t;
    t = v[1]; if (y < t) y = t;
    t = v[2]; if (z < t) z = t;
    {
    float a0 = nv[0], a1 = nv[1], a2 = nv[2];
    x = x - a0; y = y - a1; z = z - a2;
    x = x / g->sx; y = y / g->sy; z = z / g->sz;
    }
    *ox = (int)x;
    if (g->nx <= *ox) *ox = g->nx - 1;
    *oy = (int)y;
    if (g->ny <= *oy) *oy = g->ny - 1;
    *oz = (int)z;
    if (g->nz <= *oz) *oz = g->nz - 1;
}

void FUN_0023b820(Grid *arg0, Arg1 *arg1) {
    int mnx, mny, mnz, mxx, mxy, mxz;
    float v[3];
    Sph *s0;
    int z;
    int y;
    int x;
    int base1, base2;
    Ent *e;
    float r;
    s0 = arg1->f12;
    mnx = -1; mny = -1; mnz = -1; mxx = -1; mxy = -1; mxz = -1;
    if (g_igSphere_metaObject[0] == s0->vX()) {
        r = s0->f20;
        v[0] = s0->f8 - r;
        v[1] = s0->f12 - r;
        v[2] = s0->f16 - r;
        FUN_0023b720((G *)arg0, v, &mnx, &mny, &mnz);
        v[0] = s0->f8 + r;
        v[1] = s0->f12 + r;
        v[2] = s0->f16 + r;
        FUN_0023b720((G *)arg0, v, &mxx, &mxy, &mxz);
    }
    for (z = mnz; z <= mxz; z++) {
        base1 = arg0->f20 * z;
        for (y = mny; y <= mxy; y++) {
            base2 = arg0->f16 * (y + base1);
            for (x = mnx; x <= mxx; x++) {
                e = (Ent *)arg0->f8->f16[x + base2];
                if (FUN_0018ffa0(e->f16, arg1->f12) != 0) {
                    FUN_0023b3b0((RetainedList *)e, (RefCounted *)arg1);
                }
            }
        }
    }
}

int Gap__igCollisionGrid__vfunc_23(int arg0, struct L *arg1, int arg2) {
    struct E *e;
    int n = arg1->count;
    while (arg2 < n) {
        e = arg1->data[arg2];
        arg2++;
        e->f88 = 0x3F800000;
        e->f60 = e->f36;
        e->f64 = e->f40;
        e->f68 = e->f44;
    }
    return 0;
}

int Gap__igCollisionGrid__vfunc_24(A *arg0) {
    L_23ba40 *l;
    int n;
    int i;
    R_23ba40 *o;
    int n2;
    int j;

    l = arg0->f44;
    n = l->f8;
    for (i = 0; i < n; i++) {
        o = l->f16[i];
        if (o != 0) {
            o->f4 = o->f4 - 1;
            if (((unsigned long long) ((long long) o->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    n2 = l->f8;
    for (j = 0; j < n2; j++) {
        l->f16[j] = 0;
    }
    l->f8 = 0;

    l = arg0->f48;
    n = l->f8;
    for (i = 0; i < n; i++) {
        o = l->f16[i];
        if (o != 0) {
            o->f4 = o->f4 - 1;
            if (((unsigned long long) ((long long) o->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    n2 = l->f8;
    for (j = 0; j < n2; j++) {
        l->f16[j] = 0;
    }
    l->f8 = 0;

    l = arg0->f52;
    n = l->f8;
    for (i = 0; i < n; i++) {
        o = l->f16[i];
        if (o != 0) {
            o->f4 = o->f4 - 1;
            if (((unsigned long long) ((long long) o->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    n2 = l->f8;
    for (j = 0; j < n2; j++) {
        l->f16[j] = 0;
    }
    l->f8 = 0;
    return 0;
}

void FUN_0023bc30(igCollisionGroup *arg0) {
    igSphere *temp_v1;

    *(int *)&arg0->_time = 0xBF800000;
    temp_v1 = (igSphere *)arg0->_bound;
    *(float *)&arg0->_position[0] = (float) *(float *)&temp_v1->_center[0];
    *(float *)&arg0->_position[1] = (float) *(float *)&temp_v1->_center[1];
    *(float *)&arg0->_position[2] = (float) *(float *)&temp_v1->_center[2];
    *(float *)&arg0->_lastPosition[0] = (float) *(float *)&temp_v1->_center[0];
    *(float *)&arg0->_lastPosition[1] = (float) *(float *)&temp_v1->_center[1];
    *(float *)&arg0->_lastPosition[2] = (float) *(float *)&temp_v1->_center[2];
    *(float *)&arg0->_collisionPosition[0] = (float) *(float *)&temp_v1->_center[0];
    *(float *)&arg0->_collisionPosition[1] = (float) *(float *)&temp_v1->_center[1];
    *(float *)&arg0->_collisionPosition[2] = (float) *(float *)&temp_v1->_center[2];
    arg0->_radius = (float) temp_v1->_radius;
}

