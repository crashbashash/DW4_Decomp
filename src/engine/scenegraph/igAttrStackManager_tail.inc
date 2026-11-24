void FUN_001af860(igAttrStack *arg0) {
    arg0->_count = 0;
    arg0->_cachedOverride = -1;
    arg0->_lastIncrementalFlushedAttr = arg0->_default;
    arg0->_hasChangedFromLastIncrementalFlush = 0;
    arg0->_hasChangedFromRoot = 0;
    arg0->_cachedRenderPackage = 0;
}

namespace Gap {
namespace Sg {

void igAttrStackManager::reset() {
    int i;
    if (_numAttrStacks > 0) {
        for (i = 0; i < _numAttrStacks; i++) {
            FUN_001af860((::igAttrStack *)_attrStacks->get(i));
        }
        _attrIncrementalUpdateList->_count = 0;
        _attrRootUpdateList->_count = 0;
        clearLightHandles();
        _updateLightAttrs->_count = 0;
        _lightDisableAttrPool->_freeIndex = 0;
    }
}

void igAttrStackManager::userConstruct(int flag) {
    bool simpleLightMgr;
    igMemoryPoolView *pool;
    int index;
    Gap::Core::igRegistry *registry;
    igNonRefCountedAttrStackManagerList *managers;
    Gap::Core::igObject::userConstruct(flag);
    if (flag == 0) {
        if (DAT_00562580[0] == 0) {
            pool = getMemoryPool();
            pool = g_useOwnerAllocator != 0 ? pool : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleAttribute);
            DAT_00562580[0] = igNonRefCountedAttrStackManagerList::_instantiateFromPool(pool);
        }
        managers = DAT_00562580[0];
        index = managers->getCount();
        if (index < managers->_capacity) {
            managers->_count = managers->_count + 1;
        } else {
            managers->resizeAndSetCount(index + 1, 4);
        }
        ((igAttrStackManager **)managers->_data)[index] = this;
        registry = (Gap::Core::igRegistry *)g_objectSystem->configRegistry;
        simpleLightMgr = _simpleLightMgr;
        registry->getValue(7, "simpleLightManagementState", (unsigned char &)simpleLightMgr, 0, 0);
        _simpleLightMgr = simpleLightMgr;
    }
}

void igAttrStackManager::userDestruct() {
    int index;
    igNonRefCountedAttrStackManagerList *managers;
    K key((void *)this);
    index = Finder::Find((AttrStackList *)DAT_00562580[0], key);
    if (index >= 0) {
        List_RemoveWordAt((::igDataList *)DAT_00562580[0], index);
    }
    managers = DAT_00562580[0];
    if (managers->_count == 0) {
        managers->release();
        DAT_00562580[0] = 0;
    }
    Gap::Core::igObject::userDestruct();
}

void igAttrStackManager::userUnregister() {
    ::igMetaObjectList *attrMetas;
    attrMetas = DAT_00562578[0];
    if (attrMetas != 0) {
        ((Gap::Core::igObject *)attrMetas)->release();
    }
    DAT_00562578[0] = 0;
}

void igAttrStackManager::registerClass(igMetaObject *meta) {
    int count;
    int i;
    int index;
    if (igMetaObject_IsOfType(meta, Gap::Attrs::igAttr::getClassTypeSafe()) != 0 && meta->_abstractState == 0) {
        if (DAT_00562578[0] == 0) {
            DAT_00562578[0] = (::igMetaObjectList *)igMetaObjectList_Create((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
        }
        K key(meta);
        index = Finder_1afb60::Find((RefObj *)DAT_00562578[0], key);
        if (index < 0) {
            ((Gap::Core::igObjectList *)DAT_00562578[0])->append((Gap::Core::igObject *)meta);
            if (DAT_00562580[0] != 0) {
                count = DAT_00562580[0]->_count;
                for (i = 0; i < count; i++) {
                    DAT_00562580[0]->get(i)->registerAttribute(meta);
                }
            }
        }
    }
}

void igAttrStackManager::registerAttribute(igMetaObject *meta) {
    if (_defaultManager != 0 && _capabilityManager != 0) {
        int units;
        int end;
        int first;
        int i;
        int id;
        id = meta->_id;
        if (id >= _attrStackIndexTableSize) {
            _attrStackIndexTableSize = id + 4;
            _attrStackIndexTable = (int *)realloc(_attrStackIndexTable, _attrStackIndexTableSize * 4);
        }
        units = FUN_001d8270((int)(meta));
        if (units <= 0) {
            igSmartPointer<igAttr> def = _defaultManager->getSharedDefaultAttr(meta, 0);
            units = def->getUnitCount(_capabilityManager);
            if (units <= 0) {
                units = 1;
            }
        }
        first = _numAttrStacks;
        end = first + units;
        _attrDefaults->setCount(end);
        _attrStacks->setCount(end);
        _attrStackIndexTable[id] = first;
        _numAttrStacks = end;
        for (i = 0; i < units; i++, first++) {
            igSmartPointer<igAttr> def = _defaultManager->getSharedDefaultAttr(meta, i);
            igSmartPointer<igAttrStack> stack(igAttrStack::_instantiateFromPool(getMemoryPool()));
            stack->_default = def;
            stack->_popProc = 0;
            stack->_lastIncrementalFlushedAttr = (int)def.get();
            _attrStacks->set(first, stack);
            _attrDefaults->set(first, def);
        }
    }
}

/* Binds the default and capability managers and rebuilds one stack for every registered attribute
 * type; the root type is unused. */
void igAttrStackManager::setup(igMetaObject *rootMeta, igAttrDefaultManager *defaultManager, igCapabilityManager *capabilityManager)
{
    int count;
    int i;
    _defaultManager = defaultManager;
    _capabilityManager = capabilityManager;
    reset();
    _attrDefaults->removeAll();
    _attrStacks->removeAll();
    _numAttrStacks = 0;
    count = DAT_00562578[0]->_count;
    for (i = 0; i < count; i++) {
        registerAttribute((igMetaObject *)((Gap::Core::igObjectList *)DAT_00562578[0])->get(i));
    }
}

void igAttrStackManager::flushUpdateAttrsNoReset(igNonRefCountedAttrList *al) {
    igIntList *updates;
    igAttr **out;
    int updateCount;
    int lightCount;
    int top;
    igAttr *attr;
    int outCount;
    int *indices;
    igAttrStack *stack;
    igAttrStackList *stackList;
    igAttrStack **stacks;
    int total;
    int start;
    igAttr **lights;
    int i;
    start = al->_count;
    outCount = 0;
    updateCount = _attrIncrementalUpdateList->_count;
    total = updateCount + start;
    if (_simpleLightMgr == 0) {
        al->setCount(total);
        out = (igAttr **)al->_data + start;
    } else {
        lightCount = _updateLightAttrs->_count;
        total = total + lightCount;
        al->setCount(total);
        lights = (igAttr **)_updateLightAttrs->_data;
        out = (igAttr **)al->_data + start;
        for (; outCount < lightCount; outCount++) out[outCount] = lights[outCount];
        _updateLightAttrs->_count = 0;
    }
    updates = _attrIncrementalUpdateList;
    indices = (int *)updates->_data;
    stackList = _attrStacks;
    stacks = (igAttrStack **)stackList->_data;
    for (i = 0; i < updateCount; i++) {
        stack = stacks[indices[i]];
        if (stack->_cachedOverride >= 0) attr = ((igAttr **)stack->_data)[stack->_cachedOverride];
        else if ((top = stack->_count) != 0) { top = top - 1; attr = ((igAttr **)stack->_data)[top]; }
        else attr = stack->_default;
        stack->_hasChangedFromLastIncrementalFlush = 0;
        if ((int)attr != stack->_lastIncrementalFlushedAttr) {
            out[outCount++] = attr;
            stack->_lastIncrementalFlushedAttr = (int)attr;
        }
    }
    total = outCount + start;
    al->setCount(total);
    _attrIncrementalUpdateList->_count = 0;
}

void igAttrStackManager::flushUpdateAttrs(igNonRefCountedAttrList *al) {
    al->_count = 0;
    flushUpdateAttrsNoReset(al);
}

void igAttrStackManager::flushAttrs(igNonRefCountedAttrList *al) {
    igIntList *next;
    int count, outCount;
    igAttr **attrs;
    int *handles;
    int *nextHandles;
    igAttrStack **stacks;
    int i;
    al->_count = 0;
    count = _attrRootUpdateList->_count;
    next = _nextAttrUpdateList;
    next->setCount(count);
    outCount = 0;
    al->setCount(count);
    handles = (int *)_attrRootUpdateList->_data;
    nextHandles = (int *)_nextAttrUpdateList->_data;
    attrs = (igAttr **)al->_data;
    stacks = (igAttrStack **)_attrStacks->_data;
    for (i = 0; i < count; i++) {
        int handle = handles[i];
        igAttrStack *stack = stacks[handle];
        igAttr *attr;
        int stackCount;
        if (stack->_cachedOverride >= 0) attr = ((igAttr **)stack->_data)[stack->_cachedOverride];
        else { stackCount = stack->_count; if (stackCount != 0) { int top = stackCount - 1; attr = ((igAttr **)stack->_data)[top]; } else attr = stack->_default; }
        if (attr != stack->_default) {
            nextHandles[outCount] = handle;
            attrs[outCount] = attr;
            outCount++;
        } else {
            stack->_hasChangedFromRoot = 0;
        }
    }
    al->setCount(outCount);
    _nextAttrUpdateList->setCount(outCount);
    {
        igSmartPointer<igIntList> swapped(_nextAttrUpdateList);
        _nextAttrUpdateList = _attrRootUpdateList;
        _attrRootUpdateList = swapped;
    }
    _stackChanged = false;
}

void igAttrStackManager::pushLightState(igLightStateAttr *ls, bool override) {
    int slot;
    int index;
    int stackIndex;
    igLightAttr *key;
    igLightAttr *light = ls->getLight();
    if (light == 0) {
        return;
    }
    if (_simpleLightMgr == 1) {
        int n;
        igTDataList<igLightStateAttr *> *updates = (igTDataList<igLightStateAttr *> *)_updateLightAttrs.get();
        n = updates->getCount();
        if (n < updates->_capacity) {
            updates->_count = updates->_count + 1;
        } else {
            ((Gap::Core::igDataList *)updates)->resizeAndSetCount(n + 1, 4);
        }
        updates->_data[n] = ls;
        return;
    }
    key = light;
    {
        igTDataList<igLightAttr *> *lights = (igTDataList<igLightAttr *> *)_lightAttrAddrs.get();
        index = lights->sortedFind(&key);
    }
    if (index != -1) {
        /* matching construct: the offset list read through the pointer word, not operator-> (register order). */
        slot = ((int *)_lightAttrStackAddrs.p->_data)[index] + _attrStackIndexTable[ls->_cachedAttrIndex];
    } else {
        stackIndex = _lightAttrAddrs->_count;
        if (stackIndex >= getSgMaxLightStateCount()) {
            return;
        }
        index = ((LightAttrAddrList *)_lightAttrAddrs.get())->sortedAdd((::igLightAttr *)light);
        List_InsertWords((::igDataList *)_lightAttrStackAddrs.get(), index, 1, &stackIndex);
        slot = stackIndex + _attrStackIndexTable[ls->_cachedAttrIndex];
        igLightStateAttr *defaults = ((igTDataList<igLightStateAttr *> *)_attrDefaults.get())->_data[slot];
        defaults->_light = light;
        ((igTDataList<igLightStateAttr *> *)_attrDefaults.get())->_data[slot]->setState(false);
    }
    if (override) {
        fastPushOverride((::igAttrStackManager *)this, (::igObject *)ls, slot);
    } else {
        fastPushAttr((::igAttrStackManager *)this, (::igObject *)ls, slot);
    }
}

void igAttrStackManager::popLightState(igLightStateAttr *ls, bool override) {
    igLightAttr *key;
    int slot;
    AttrObjectStack *stack;
    int index;
    igLightAttr *light = ls->_light;
    if (light == 0) {
        return;
    }
    if (_simpleLightMgr == 1) {
        /* matching construct: the pool read through the pointer word, not get() (register order). */
        igLightStateAttr *undo = (igLightStateAttr *)takePooled((::igObjectPool *)_lightDisableAttrPool.p, (void *)Gap::Attrs::igLightStateAttr::_instantiateFromPool);
        int n;
        igTDataList<igLightStateAttr *> *updates;
        light = ls->_light;
        undo->_light = light;
        undo->setState(!ls->_enabled);
        updates = (igTDataList<igLightStateAttr *> *)_updateLightAttrs.get();
        n = updates->getCount();
        if (n < updates->_capacity) {
            updates->_count = updates->_count + 1;
        } else {
            ((Gap::Core::igDataList *)updates)->resizeAndSetCount(n + 1, 4);
        }
        updates->_data[n] = undo;
        return;
    }
    key = light;
    {
        igTDataList<igLightAttr *> *lights = (igTDataList<igLightAttr *> *)_lightAttrAddrs.get();
        index = lights->sortedFind(&key);
    }
    if (index == -1) {
        return;
    }
    /* matching construct: the offset list read through the pointer word, not operator-> (register order). */
    slot = ((int *)_lightAttrStackAddrs.p->_data)[index] + _attrStackIndexTable[ls->_cachedAttrIndex];
    if (override) {
        ::igObject *top;
        void (*pop)(::igObject *, int);
        stack = ((AttrObjectStackList *)_attrStacks.get())->_data[slot];
        top = stack->get(stack->_count - 1);
        pop = stack->_popProc;
        if (pop != 0 && top == (::igObject *)ls) {
            pop(top, (int)_popProcData);
        }
        stack->_count = stack->_count - 1;
        if (stack->_count == stack->_cachedOverride) {
            stack->_cachedOverride = -1;
        }
        igAttrStackManager_MarkStackChanged((::igAttrStackManager *)this, (::igAttrStack *)stack, slot);
    } else {
        ::igObject *top;
        void (*pop)(::igObject *, int);
        stack = ((AttrObjectStackList *)_attrStacks.get())->_data[slot];
        top = stack->get(stack->_count - 1);
        pop = stack->_popProc;
        if (pop != 0) {
            pop(top, (int)_popProcData);
        }
        stack->_count = stack->_count - 1;
        igAttrStackManager_MarkStackChanged((::igAttrStackManager *)this, (::igAttrStack *)stack, slot);
    }
}

void igAttrStackManager::clearLightHandles() {
    int count, i;
    count = _lightAttrAddrs->_count;
    for (i = 0; i < count; i++) {
        igAttrStack *stack = _attrStacks->get(i + _attrStackIndexTable[Gap::Attrs::igLightStateAttr::getClassMeta()->_id]);
        /* matching construct: the light pointer is reached through its address, as retail keeps it in a register. */
        igSmartPointer<igLightAttr> *defaultLight = &((igLightStateAttr *)stack->_default.get())->_light;
        defaultLight->clear();
    }
    _lightAttrAddrs->_count = 0;
    _lightAttrStackAddrs->_count = 0;
}

bool igAttrStackManager::getLightState(igLightAttr *light) {
    if (light == 0) {
        return false;
    }
    int index;
    igLightAttr *key = light;
    igTDataList<igLightAttr *> *lights = (igTDataList<igLightAttr *> *)_lightAttrAddrs.get();
    index = lights->sortedFind(&key);
    if (index != -1) {
        int base = ((int *)_lightAttrStackAddrs->_data)[index];
        igMetaObject *meta = Gap::Attrs::igLightStateAttr::getClassTypeSafe();
        AttrObjectStack *stack = (AttrObjectStack *)_attrStacks->get(base + _attrStackIndexTable[meta->_id]);
        igLightStateAttr *state;
        int current = stack->_cachedOverride;
        if (current >= 0) {
            state = (igLightStateAttr *)stack->_data[current];
        } else {
            int count = stack->_count;
            if (count != 0) {
                int last = count - 1;
                state = (igLightStateAttr *)stack->_data[last];
            } else {
                state = (igLightStateAttr *)stack->_default;
            }
        }
        return state->_enabled;
    }
    return false;
}

void igAttrStackManager::pushAttr(const igAttr *attribute) {
    /* matching construct: one variable holds the stack list, then the stack (retail's register choice). */
    AttrObjectStack *stack = (AttrObjectStack *)_attrStacks.get();
    int slot = attribute->_cachedAttrIndex;
    slot = attribute->_cachedUnitID + _attrStackIndexTable[slot];
    stack = (AttrObjectStack *)stack->_data[slot];
    stack->append((::igObject *)attribute);
    igAttrStackManager_MarkStackChanged((::igAttrStackManager *)this, (::igAttrStack *)stack, slot);
}

void igAttrStackManager::popAttr(const igAttr *attribute) {
    void (*pop)(igAttr *, void *);
    int slot;
    igAttrStack *stack;
    igAttr *top; int last; igAttr **data;

    slot = _attrStackIndexTable[attribute->_cachedAttrIndex] + attribute->_cachedUnitID;
    stack = _attrStacks->get(slot);
    last = stack->_count - 1; data = (igAttr **)stack->_data; top = data[last];
    pop = (void (*)(igAttr *, void *))stack->_popProc;
    if (pop != 0) {
        pop(top, _popProcData);
    }
    stack->_count = stack->_count - 1;
    igAttrStackManager_MarkStackChanged((::igAttrStackManager *)this, (::igAttrStack *)stack, slot);
}

void igAttrStackManager::popAttr(igMetaObject *meta) {
    void (*pop)(igAttr *, void *);
    int slot;
    igAttrStack *stack;
    igAttr *top; int last; igAttr **data;

    slot = _attrStackIndexTable[meta->_id];
    stack = _attrStacks->get(slot);
    last = stack->_count - 1; data = (igAttr **)stack->_data; top = data[last];
    pop = (void (*)(igAttr *, void *))stack->_popProc;
    if (pop != 0) {
        pop(top, _popProcData);
    }
    stack->_count = stack->_count - 1;
    igAttrStackManager_MarkStackChanged((::igAttrStackManager *)this, (::igAttrStack *)stack, slot);
}

void igAttrStackManager::popAttr(igMetaObject *meta, int unitID) {
    void (*pop)(igAttr *, void *);
    int slot;
    igAttrStack *stack;
    igAttr *top; int last; igAttr **data;

    slot = unitID + _attrStackIndexTable[meta->_id];
    stack = _attrStacks->get(slot);
    last = stack->_count - 1; data = (igAttr **)stack->_data; top = data[last];
    pop = (void (*)(igAttr *, void *))stack->_popProc;
    if (pop != 0) {
        pop(top, _popProcData);
    }
    stack->_count = stack->_count - 1;
    igAttrStackManager_MarkStackChanged((::igAttrStackManager *)this, (::igAttrStack *)stack, slot);
}

void igAttrStackManager::pushOverride(const igAttr *override) {
    /* matching construct: one variable holds the stack list, then the stack (retail's register choice). */
    AttrObjectStack *stack = (AttrObjectStack *)_attrStacks.get();
    int slot = override->_cachedAttrIndex;
    slot = override->_cachedUnitID + _attrStackIndexTable[slot];
    stack = (AttrObjectStack *)stack->_data[slot];
    if (stack->_cachedOverride < 0) {
        stack->_cachedOverride = stack->_count;
    }
    stack->append((::igObject *)override);
    igAttrStackManager_MarkStackChanged((::igAttrStackManager *)this, (::igAttrStack *)stack, slot);
}

void igAttrStackManager::popOverride(const igAttr *override) {
    void (*pop)(igAttr *, void *);
    int slot;
    igAttrStack *stack;
    int last; igAttr **data; igAttr *top;

    slot = override->_cachedUnitID + _attrStackIndexTable[override->_cachedAttrIndex];
    stack = _attrStacks->get(slot);
    last = stack->_count - 1; data = (igAttr **)stack->_data; top = data[last];
    pop = (void (*)(igAttr *, void *))stack->_popProc;
    if ((pop != 0) && (top == override)) {
        pop(top, _popProcData);
    }
    stack->_count = stack->_count - 1;
    if (stack->_count == stack->_cachedOverride) {
        stack->_cachedOverride = -1;
    }
    igAttrStackManager_MarkStackChanged((::igAttrStackManager *)this, (::igAttrStack *)stack, slot);
}
}
}

void igAttrStackManager_MarkStackChanged(igAttrStackManager *manager, igAttrStack *stack, int index) {
    int c1;
    int c2;
    struct L_1b1490 *l1;
    struct L_1b1490 *l2;

    if (stack->_hasChangedFromLastIncrementalFlush == 0) {
        l1 = (struct L_1b1490 *)manager->_attrIncrementalUpdateList;
        c1 = l1->n;
        if (c1 < l1->cap) {
            l1->n = n_of_1b1490(l1) + 1;
        } else {
            ((Gap::Core::igDataList *)l1)->resizeAndSetCount(c1 + 1, 4);
        }
        l1->arr[c1] = index;
        stack->_hasChangedFromLastIncrementalFlush = 1U;
    }
    if (stack->_hasChangedFromRoot == 0) {
        l2 = (struct L_1b1490 *)manager->_attrRootUpdateList;
        c2 = l2->n;
        if (c2 < l2->cap) {
            l2->n = n_of_1b1490(l2) + 1;
        } else {
            ((Gap::Core::igDataList *)l2)->resizeAndSetCount(c2 + 1, 4);
        }
        l2->arr[c2] = index;
        stack->_hasChangedFromRoot = 1U;
    }
    manager->_stackChanged = 1;
}

namespace Gap {
namespace Sg {

/* Turns the billboard to face the camera: `matrix` gets the billboard's rotation for its mode and the
 * model-view position moved by the billboard's origin. */
void igBillboard::computeTransform(igMatrix44f *result, const igMatrix44f *modelMat, const igMatrix44f *viewMatInv) {
    float *matrix = (float *)result;
    const float *modelView = (const float *)modelMat;
    const float *view = (const float *)viewMatInv;
    igVec3f position;
    igVec3f up;
    igVec3f origin;
    igMatrix44f_GetTranslation(modelView, position.vec);
    Vec3f_TransformDirection(origin.vec, _origin.vec, modelView);
    position.add(origin);
    igVec3f viewPosition(view[12], view[13], view[14]);
    igVec3f direction = viewPosition - position;
    switch (_mode) {
    case 1:
        Vec3f_TransformDirection(up.vec, _axis.vec, modelView);
        break;
    case 2: {
        igVec3f side;
        up[0] = 0.0f;
        up[1] = 1.0f;
        up[2] = 0.0f;
        FUN_00192dd0(side.vec, up.vec, direction.vec);
        FUN_00192dd0(up.vec, direction.vec, side.vec);
        break;
    }
    case 3:
        if (view != 0) {
            igVec3f viewUp;
            igVec3f side;
            viewUp[0] = 0.0f;
            viewUp[1] = 1.0f;
            viewUp[2] = 0.0f;
            Vec3f_TransformDirection(viewUp.vec, viewUp.vec, view);
            FUN_00192dd0(side.vec, viewUp.vec, direction.vec);
            side.scale(1.0f / sqrtf(side.dot(side)));
            FUN_00192dd0(up.vec, direction.vec, side.vec);
            up.scale(1.0f / sqrtf(up.dot(up)));
        }
        break;
    case 0:
    default:
        up[0] = 0.0f;
        up[1] = 1.0f;
        up[2] = 0.0f;
        break;
    }
    FUN_001b1590(matrix, up.vec, direction.vec);
    igMatrix44f_SetTranslation(matrix, position.vec);
}
}
}

void igBitMask_SetAll(igBitMask *mask) {
    igDataList *arg0 = (igDataList *)mask;
    unsigned int temp_a2;
    int *temp_a0;

    temp_a2 = arg0->_count;
    temp_a0 = (int *)arg0->_data;
    switch (temp_a2) {
    case 16:
        temp_a0[15] = -1;
        
    case 15:
        temp_a0[14] = -1;
        
    case 14:
        temp_a0[13] = -1;
        
    case 13:
        temp_a0[12] = -1;
        
    case 12:
        temp_a0[11] = -1;
        
    case 11:
        temp_a0[10] = -1;
        
    case 10:
        temp_a0[9] = -1;
        
    case 9:
        temp_a0[8] = -1;
        
    case 8:
        temp_a0[7] = -1;
        
    case 7:
        temp_a0[6] = -1;
        
    case 6:
        temp_a0[5] = -1;
        
    case 5:
        temp_a0[4] = -1;
        
    case 4:
        temp_a0[3] = -1;
        
    case 3:
        temp_a0[2] = -1;
        
    case 2:
        temp_a0[1] = -1;
        
    case 1:
        temp_a0[0] = -1;
        break;
    case 0:
        break;
    default:
        memset(temp_a0, 0xFF, temp_a2 * 4);
        break;
    }
}

void igBitMask_ClearAll(igBitMask *mask) {
    igDataList *arg0 = (igDataList *)mask;
    unsigned int temp_a2;
    int *temp_a0;

    temp_a2 = arg0->_count;
    temp_a0 = (int *)(arg0->_data);
    switch (temp_a2) {
    case 16:
        temp_a0[15] = 0;
        
    case 15:
        temp_a0[14] = 0;
        
    case 14:
        temp_a0[13] = 0;
        
    case 13:
        temp_a0[12] = 0;
        
    case 12:
        temp_a0[11] = 0;
        
    case 11:
        temp_a0[10] = 0;
        
    case 10:
        temp_a0[9] = 0;
        
    case 9:
        temp_a0[8] = 0;
        
    case 8:
        temp_a0[7] = 0;
        
    case 7:
        temp_a0[6] = 0;
        
    case 6:
        temp_a0[5] = 0;
        
    case 5:
        temp_a0[4] = 0;
        
    case 4:
        temp_a0[3] = 0;
        
    case 3:
        temp_a0[2] = 0;
        
    case 2:
        temp_a0[1] = 0;
        
    case 1:
        temp_a0[0] = 0;
    case 0:
        break;
    default:
        memset(temp_a0, 0, temp_a2 * 4);
        break;
    }
}

void igBitMask_SetBitCount(igBitMask *arg, unsigned int bits) {
    igBitMaskWords *m;
    unsigned int old;
    int partial;
    int i;
    int n;
    m = (igBitMaskWords *)arg;
    old = m->_bitCount;
    if (bits <= old) {
        m->_bitCount = bits;
        m->setCount((bits + 31) >> 5);
    } else {
        i = m->_count;
        partial = old & 31;
        m->_bitCount = bits;
        m->setCount((bits + 31) >> 5);
        if (partial != 0) {
            unsigned int mask = ((1 << partial) - 1) & m->getWord(i - 1);
            m->setWord(i - 1, mask);
        }
        n = m->_count;
        for (; i < n; i++) {
            m->setWord(i, DAT_0048d8d0);
        }
    }
}

