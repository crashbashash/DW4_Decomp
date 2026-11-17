extern "C" igSmartPointer<igObject> igMetaObject_CreateInstanceDefaultRef(int meta);
extern "C" void igVolume_ExtendBy(void *volume, void *other);
extern "C" igObject *FUN_00227460(igMemoryPoolView *allocator);
extern "C" void FUN_0022ab90(igObject *iterator, igNode *root, igMetaObject *metaObject);
extern "C" igNode *FUN_0022ac00(igObject *iterator);
extern "C" void FUN_0022ac70(igObject *iterator, igMetaObject *metaObject);
extern "C" void FUN_0022b0a0(float *matrix, igObject *iterator);

extern "C" igMetaObject *g_igAABox_metaObject;
extern "C" char emptyString[];
static inline igAABox *asAABox(igObject *o) {
    if (o != 0 && igObject_IsKindOf(o, g_igAABox_metaObject) != 0) return (igAABox *)o;
    return 0;
}

static inline void assignObject(int &slot, igObject *object) {
    if (object != 0) object->_refCount = object->_refCount + 1;
    igRelease((igObject *)slot);
    slot = (int)object;
}

static inline void createGrid(int &slot) {
    /* matching construct: a tag made inside the inline takes the frame slot below the caller's temporaries */
    AdoptReference tag = AdoptReference();
    igRelease((igObject *)slot);
    slot = (int)FUN_0023a040(0);
}
static inline igObject *newSphereMaker() {
    /* matching construct: as in createGrid */
    AdoptReference tag = AdoptReference();
    return FUN_0023a9d0(0);
}

static inline void setBound(igCollisionGroup *group, igObject *bound) {
    if (bound != 0) bound->_refCount = bound->_refCount + 1;
    igRelease((igObject *)group->_bound);
    group->_bound = (int)bound;
}

/* Builds the collision grid over `root`: sized to the scene's bound, with one static collision group
 * per collidable geometry, each bounded by its sphere in world space; writes the database when named. */
extern "C" int Gap__igCreateCollisionDatabase__vfunc_28(igCreateCollisionDatabase *self, igNode **root);
int Gap__igCreateCollisionDatabase__vfunc_28(igCreateCollisionDatabase *self, igNode **root) {
    if (*root == 0) return 0;
    igAABox *bound = asAABox((igObject *)(*root)->_bound);
    if (bound == 0) return 0;
    if (self->_staticGroupType == 0 || igMetaObject_IsOfType((igMetaObject *)self->_staticGroupType, igCollisionGroup_GetMetaObject()) == 0) {
        assignObject(self->_staticGroupType, (igObject *)igCollisionGroup_GetMetaObject());
    }
    if (self->_gridType != 0 && igMetaObject_IsOfType((igMetaObject *)self->_gridType, igCollisionGrid_GetMetaObject()) != 0) {
        igSmartPointer<igObject> grid = igMetaObject_CreateInstanceDefaultRef(self->_gridType);
        assignObject(self->_grid, grid.get());
    } else {
        createGrid(self->_grid);
    }
    if (self->_sizeX <= 0) self->_sizeX = 1;
    if (self->_sizeY <= 0) self->_sizeY = 1;
    if (self->_sizeZ <= 0) self->_sizeZ = 1;
    FUN_0023b410((int *)self->_grid, self->_sizeX, self->_sizeY, self->_sizeZ);
    G *grid = (G *)self->_grid;
    B *box = grid->box;
    float *max = &box->v[0] + 3;
    box->v[0] = box->v[1] = box->v[2] = 3.402823466e+38f;
    max[0] = max[1] = max[2] = -3.402823466e+38f;
    igVolume_ExtendBy(grid->box, bound);
    FUN_0023b430((igCollisionGrid *)self->_grid);
    igMetaObject *geometryMeta = g_igGeometry_metaObject;
    igSmartPointer<igObject> iterator(FUN_00227460(igObject_GetAllocator(self)));
    for (FUN_0022ab90(iterator.get(), *root, geometryMeta); FUN_0022ac00(iterator.get()) != 0; FUN_0022ac70(iterator.get(), geometryMeta)) {
        igNode *geometry = FUN_0022ac00(iterator.get());
        if ((geometry->_flags & 0x10) == 0) continue;
        igSmartPointer<igObject> sphere;
        {
            igSmartPointer<igObject> maker(newSphereMaker());
            sphere = FUN_0023b270((ObjectSlotOwner *)maker.get(), (int)geometry);
        }
        if (sphere.get() != 0) {
            float world[16];
            FUN_0022b0a0(world, iterator.get());
            FUN_0018d630(sphere.get(), world);
            igSmartPointer<igCollisionGroup> group = igMetaObject_CreateInstanceDefaultRef(self->_staticGroupType);
            const char *name = (const char *)geometry->_name;
            igNamedObject_SetName((igNamedObject *)group.get(), name != 0 ? name : emptyString);
            setBound(group.get(), sphere.get());
            FUN_0023bc30(group.get());
            FUN_0023b820((Grid *)self->_grid, (Arg1 *)group.get());
        }
    }
    if (self->_fileName != 0) FUN_0023c250((int *)self);
    return 1;
}

int Gap__igCreateCollisionDatabase__vfunc_31(void) {
    return 1;
}

int Gap__igCreateCollisionDatabase__vfunc_33(void) {
    return 1;
}

/* Selects the constructor that takes over the factory's reference. */

void FUN_0023c250(int *arg0) {    igSmartPointer<Rc> a(igIGBFile_Create(0), AdoptReference());
    igDirectory_SetName(a.get(), arg0[13]);
    igSmartPointer<Rc> b(FUN_002397a0(0), AdoptReference());
    {
    Rc *s1 = (Rc *)arg0[14];
    Inst *s0 = (Inst *)b.get();
    if (s1) s1->_refCount = s1->_refCount + 1;
    Rc *t = s0->f20;
    if (t) { t->_refCount = t->_refCount - 1; if ((t->_refCount & 0x7FFFFF) == 0) igObject_Destroy(t); }
    s0->f20 = s1;
    }
    igDirectory_AddInfo(a.get(), b.get());
    ((Obj_23c250 *)a.get())->vX(arg0[13]);
}

