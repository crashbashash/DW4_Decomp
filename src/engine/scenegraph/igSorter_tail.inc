void FUN_001da6e0(igSorter *arg0) {
    igDataList *h;
    int n;
    struct Obj_1da6e0 **arr;
    struct Pair *p;
    int b;
    h = (igDataList *)arg0->_opaquePackageIndices;
    n = h->_count;
    if (n > 2) {
        FUN_001da220(arg0, 0, n - 1);
        return;
    }
    if (n == 2) {
        int m, t;
        p = (struct Pair *)h->_data;
        b = p->b;
        arr = ((struct Tbl * *)DAT_005629f8)[0]->arr;
        if (arr[b]->key < arr[p->a]->key) {
            m = count_of_1da6e0(h);
            if (m != 0 && 0 < m && m > 1) {
                t = a_of(p);
                p->a = b;
                p->b = t;
            }
        }
    }
}

void FUN_001da790(SorterOpaqueView *o) {
    int c;
    unsigned int prev;
    int start;
    unsigned int key;
    int j;
    int i;
    int *p;
    int n;
    SorterIndexListView *l;
    n = o->_opaquePackageIndices->_count;
    start = 1;
    if (n < 2) { return; }
    while (start > 0) {
        j = start - 1;
        prev = ((SorterPackageListView *)DAT_005629f8[0])->_data[o->_opaquePackageIndices->_data[j]]->key;
        i = start;
        start = 0;
        for (; i < n; i++) {
            l = o->_opaquePackageIndices;
            p = &l->_data[i];
            key = ((SorterPackageListView *)DAT_005629f8[0])->_data[*p]->key;
            if (key < prev) {
                c = l->_count;
                if (c != 0 && i >= 0 && c > i) {
                    j = i - 1;
                    if (j >= 0 && c > j) {
                        const int *value = p;
                        int t = *value;
                        *p = p[-1];
                        p[-1] = t;
                    }
                }
                prev = key;
                if (start == 0) {
                    start = (i > 1) ? i - 1 : 1;
                }
            }
            prev = key;
        }
    }
}

void igSorter_userConstruct(SorterState *o, int arg1) {
    int s3;
    SorterList *s2;
    SorterList *s0;
    SorterList *l;
    if (arg1 == 0) {
        FUN_001db500((A_1db500 *)o);
        o->a->f30(0);
        o->b->f30(1);
        o->b->f31(1);
        o->c->f30(0);
        o->c->f31(1);
        o->l80->cap = o->l80->count;
        s2 = o->l84;
        s3 = s2->count;
        s0 = o->l80;
        if (s3 < s2->cap) {
            s2->count = s2->getCount() + 1;
        } else {
            ((Gap::Core::igDataList *)s2)->resizeAndSetCount(s3 + 1, 4);
        }
        s2->items[s3] = (int)s0;
        l = o->l88;
        if (l->cap > 0) {
            l->count = 1;
        } else {
            ((Gap::Core::igDataList *)l)->resizeAndSetCount(1, 4);
        }
        setRef(o->l88, 0, DAT_0048dae8[0]);
    }
}

void FUN_001db500(A_1db500 *arg0) {
    int temp_s0;
    int temp_s0_2;
    int temp_s2_2;
    int temp_s3;
    L_1db500 *temp_s1;
    L_1db500 *temp_s2;

    temp_s0 = arg0->f36;
    temp_s2 = arg0->f8->f12;
    temp_s3 = temp_s2->count;
    if (temp_s3 < temp_s2->cap) {
        temp_s2->count = count_of_1db500(temp_s2) + 1;
    } else {
        ((Gap::Core::igDataList *)temp_s2)->resizeAndSetCount(temp_s3 + 1, 4);
    }
    temp_s2->data[temp_s3] = temp_s0;
    temp_s0_2 = arg0->f40;
    temp_s1 = arg0->f8->f12;
    temp_s2_2 = temp_s1->count;
    if (temp_s2_2 < temp_s1->cap) {
        temp_s1->count = count_of_1db500(temp_s1) + 1;
    } else {
        ((Gap::Core::igDataList *)temp_s1)->resizeAndSetCount(temp_s2_2 + 1, 4);
    }
    temp_s1->data[temp_s2_2] = temp_s0_2;
}

void Gap__Sg__igSorter__vfunc_24(Sorter *arg0) {
    int i;
    List_1db5d0 *l;
    EL *e;
    if (arg0->f112 != 0) { arg0->f112 = 0; }
    arg0->f128 = 0;
    i = 0;
    arg0->f32->f8 = 0;
    arg0->f24->f8 = 0;
    arg0->f28->f8 = 0;
    for (; i < arg0->f16->f8; i++) {
        l = arg0->f16->f16[i]->f28;
        if (0 <= l->f12) { l->f8 = 0; } else { ((Gap::Core::igDataList *)l)->resizeAndSetCount(0, 4); }
    }
    arg0->f16->f20 = 0;
    arg0->f40->vX();
    arg0->f44->vX();
    arg0->f48->vX();
    arg0->f92->vX();
    arg0->f96->vX();
    arg0->f36->vX();
    arg0->f8->vX();
    FUN_001db500((A_1db500 *)arg0);
    arg0->f104->f8 = 0;
    arg0->f108->f8 = 0;
    arg0->f124 = 0;
}

extern "C" void FUN_00190200(void *bound, float *center);
extern "C" void FUN_001dc160(igRenderPackage *package, igGeometry *geometry, igAttrStackManager *manager);
typedef igTDataList<igAttr *> AttrPointerList;
typedef igTDataList<igRenderPackage *> RenderPackagePointerList;
static inline igAttrStack *attrStackOf(igAttrStackManager *manager, igMetaObject *meta) {
    return ((igAttrStack **)((igAttrStackList *)manager->_attrStacks)->_data)[((int *)manager->_attrStackIndexTable)[meta->_id]];
}

static inline igAttr *currentAttr(igAttrStack *stack) {
    if (stack->_cachedOverride >= 0) return ((igAttr **)stack->_data)[stack->_cachedOverride];
    if (stack->_count != 0) return ((igAttr **)stack->_data)[(unsigned int)(stack->_count - 1)];
    return (igAttr *)stack->_default;
}

static inline igAttr *lastAttr(igAttrStack *stack) {
    int count = stack->_count;
    if (count == 0) return 0;
    return ((igAttr **)stack->_data)[(unsigned int)(count - 1)];
}

static inline igRenderPackage *nextPackage(igRenderPackagePool *pool) {
    int index;
    if (pool->_freeIndex >= pool->_count) {
        igObjectPool_Grow((igObjectPool *)pool, (igObject *(*)(int))&Gap::Sg::igRenderPackage::_instantiateFromPool);
    }
    index = pool->_freeIndex;
    pool->_freeIndex = index + 1;
    return ((igRenderPackage **)pool->_data)[index];
}

/* Sorts a geometry into the render packages: straight into the display list when nothing needs sorting, else into
 * the cached package or a new one, with its view distance when packages are sorted by depth.
 * A geometry flagged 0xC appends its set attribute (which takes the geometry's attribute list on first use), any
 * other its attributes: one or two singly, more through append4.
 * matching construct: saved-register colours of the appends (simplify order follows the allocator ids, K = 25).
 * Each append is the kit's igTDataList<T>::append(const T &) written out, as in FUN_001dc610. In the three
 * geometry appends `attributes`, `firstCount` (the count of the first of the two-attribute appends, the one count
 * that is live beside `attributes`) and `retained` are declared ahead of `list`, which is declared at its
 * assignment: their ids fall below the list's, they are pushed before it and it before the appended values, so
 * the values colour s0, the list s1 and the counts s2 as in retail. With the list declared first, one count
 * variable for all four appends, or the list as an inline's parameter, the list is pushed last and takes s0. */
void FUN_001db720(igSorter *sorter, igGeometry *geometry, igAttrStackManager *manager) {
    bool transparent;
    bool sortByDistance;
    igRenderPackage *package;
    if (geometry == 0) {
        FUN_001d9bb0(sorter, (int)manager);
        return;
    }
    if (manager == 0) {
        return;
    }
    transparent = false;
    if (sorter->_mode & 0xD) {
        static igMetaObject *blendMeta = Gap::Attrs::igBlendStateAttr::getClassTypeSafe();
        if (((igBlendStateAttr *)currentAttr(attrStackOf(manager, blendMeta)))->_enabled == 1) {
            transparent = true;
        }
    }
    if (sorter->_forceNoSeparate) {
        transparent = true;
    }
    if (!(sorter->_mode & 0x72) && !sorter->_isCompoundPackageOpen && !transparent) {
        AttrPointerList *attributes;
        int firstCount;
        igObject *retained;
        FUN_001b0250((PendingValueCollector *)manager, (PendingIntList *)((igDisplayListAttr *)sorter->_dlist)->_contents);
        AttrPointerList *list = (AttrPointerList *)((igDisplayListAttr *)sorter->_dlist)->_contents;
        if (geometry->_flags & 0xC) {
            igGeometrySetAttr *set = *(igGeometrySetAttr **)((char *)geometry + ((igMetaField *)DAT_00562768[0])->_offset);
            if (set->_geometryAttrList == 0) {
                retained = (igObject *)geometry->_attributes;
                if (retained != 0) {
                    retained->_refCount = retained->_refCount + 1;
                }
                igObject::release((igObject *)set->_geometryAttrList);
                set->_geometryAttrList = (int)retained;
            }
            {
                int count;
                igAttr *item = (igAttr *)set;
                count = list->getCount();
                if (count < list->_capacity) {
                    list->_count++;
                } else {
                    ((Gap::Core::igDataList *)list)->resizeAndSetCount(count + 1, sizeof(igAttr *));
                }
                list->_data[count] = item;
            }
        } else {
            attributes = (AttrPointerList *)geometry->_attributes;
            switch (attributes->_count) {
            case 1:
                {
                    int count;
                    igAttr *item = attributes->_data[0];
                    count = list->getCount();
                    if (count < list->_capacity) {
                        list->_count++;
                    } else {
                        ((Gap::Core::igDataList *)list)->resizeAndSetCount(count + 1, sizeof(igAttr *));
                    }
                    list->_data[count] = item;
                }
                break;
            case 2:
                {
                    igAttr *item = attributes->_data[0];
                    firstCount = list->getCount();
                    if (firstCount < list->_capacity) {
                        list->_count++;
                    } else {
                        ((Gap::Core::igDataList *)list)->resizeAndSetCount(firstCount + 1, sizeof(igAttr *));
                    }
                    list->_data[firstCount] = item;
                }
                {
                    int count;
                    igAttr *item = attributes->_data[1];
                    count = list->getCount();
                    if (count < list->_capacity) {
                        list->_count++;
                    } else {
                        ((Gap::Core::igDataList *)list)->resizeAndSetCount(count + 1, sizeof(igAttr *));
                    }
                    list->_data[count] = item;
                }
                break;
            default:
                List_AppendWords((igDataList *)list, attributes->_count, (const int *)attributes->_data);
                break;
            }
        }
        return;
    }
    sortByDistance = (sorter->_mode & 0x50) > 0 || ((sorter->_mode & 4) > 0 && transparent);
    package = 0;
    if (!manager->_stackChanged && sorter->_cachedPackage != 0) {
        igRenderPackage *cached = (igRenderPackage *)sorter->_cachedPackage;
        if (!sortByDistance) {
            AttrPointerList *attributes;
            int firstCount;
            igObject *retained;
            AttrPointerList *list = (AttrPointerList *)cached->_geomAttrs;
            if (geometry->_flags & 0xC) {
                igGeometrySetAttr *set = *(igGeometrySetAttr **)((char *)geometry + ((igMetaField *)DAT_00562768[0])->_offset);
                if (set->_geometryAttrList == 0) {
                    retained = (igObject *)geometry->_attributes;
                    if (retained != 0) {
                        retained->_refCount = retained->_refCount + 1;
                    }
                    igObject::release((igObject *)set->_geometryAttrList);
                    set->_geometryAttrList = (int)retained;
                }
                {
                    int count;
                    igAttr *item = (igAttr *)set;
                    count = list->getCount();
                    if (count < list->_capacity) {
                        list->_count++;
                    } else {
                        ((Gap::Core::igDataList *)list)->resizeAndSetCount(count + 1, sizeof(igAttr *));
                    }
                    list->_data[count] = item;
                }
            } else {
                attributes = (AttrPointerList *)geometry->_attributes;
                switch (attributes->_count) {
                case 1:
                    {
                        int count;
                        igAttr *item = attributes->_data[0];
                        count = list->getCount();
                        if (count < list->_capacity) {
                            list->_count++;
                        } else {
                            ((Gap::Core::igDataList *)list)->resizeAndSetCount(count + 1, sizeof(igAttr *));
                        }
                        list->_data[count] = item;
                    }
                    break;
                case 2:
                    {
                        igAttr *item = attributes->_data[0];
                        firstCount = list->getCount();
                        if (firstCount < list->_capacity) {
                            list->_count++;
                        } else {
                            ((Gap::Core::igDataList *)list)->resizeAndSetCount(firstCount + 1, sizeof(igAttr *));
                        }
                        list->_data[firstCount] = item;
                    }
                    {
                        int count;
                        igAttr *item = attributes->_data[1];
                        count = list->getCount();
                        if (count < list->_capacity) {
                            list->_count++;
                        } else {
                            ((Gap::Core::igDataList *)list)->resizeAndSetCount(count + 1, sizeof(igAttr *));
                        }
                        list->_data[count] = item;
                    }
                    break;
                default:
                    List_AppendWords((igDataList *)list, attributes->_count, (const int *)attributes->_data);
                    break;
                }
            }
            return;
        }
        package = nextPackage((igRenderPackagePool *)sorter->_renderPackagePool);
        package->_cachedStateAttrs = package->_stateAttrs;
        ((AttrPointerList *)package->_geomAttrs)->_count = 0;
        AttrPointerList *attributes;
        int firstCount;
        igObject *retained;
        AttrPointerList *list = (AttrPointerList *)package->_geomAttrs;
        if (geometry->_flags & 0xC) {
            igGeometrySetAttr *set = *(igGeometrySetAttr **)((char *)geometry + ((igMetaField *)DAT_00562768[0])->_offset);
            if (set->_geometryAttrList == 0) {
                retained = (igObject *)geometry->_attributes;
                if (retained != 0) {
                    retained->_refCount = retained->_refCount + 1;
                }
                igObject::release((igObject *)set->_geometryAttrList);
                set->_geometryAttrList = (int)retained;
            }
            {
                int count;
                igAttr *item = (igAttr *)set;
                count = list->getCount();
                if (count < list->_capacity) {
                    list->_count++;
                } else {
                    ((Gap::Core::igDataList *)list)->resizeAndSetCount(count + 1, sizeof(igAttr *));
                }
                list->_data[count] = item;
            }
        } else {
            attributes = (AttrPointerList *)geometry->_attributes;
            switch (attributes->_count) {
            case 1:
                {
                    int count;
                    igAttr *item = attributes->_data[0];
                    count = list->getCount();
                    if (count < list->_capacity) {
                        list->_count++;
                    } else {
                        ((Gap::Core::igDataList *)list)->resizeAndSetCount(count + 1, sizeof(igAttr *));
                    }
                    list->_data[count] = item;
                }
                break;
            case 2:
                {
                    igAttr *item = attributes->_data[0];
                    firstCount = list->getCount();
                    if (firstCount < list->_capacity) {
                        list->_count++;
                    } else {
                        ((Gap::Core::igDataList *)list)->resizeAndSetCount(firstCount + 1, sizeof(igAttr *));
                    }
                    list->_data[firstCount] = item;
                }
                {
                    int count;
                    igAttr *item = attributes->_data[1];
                    count = list->getCount();
                    if (count < list->_capacity) {
                        list->_count++;
                    } else {
                        ((Gap::Core::igDataList *)list)->resizeAndSetCount(count + 1, sizeof(igAttr *));
                    }
                    list->_data[count] = item;
                }
                break;
            default:
                List_AppendWords((igDataList *)list, attributes->_count, (const int *)attributes->_data);
                break;
            }
        }
        package->_cachedStateAttrs = ((igRenderPackage *)sorter->_cachedPackage)->_cachedStateAttrs;
        package->_sortingCache = ((igRenderPackage *)sorter->_cachedPackage)->_sortingCache;
    }
    if (package == 0) {
        package = nextPackage((igRenderPackagePool *)sorter->_renderPackagePool);
        package->_cachedStateAttrs = package->_stateAttrs;
        FUN_001dc160(package, geometry, manager);
    }
    sorter->_cachedPackage = (int)package;
    if (sortByDistance) {
        void *bound = (void *)geometry->_bound;
        igModelViewMatrixAttr *modelView;
        igVec3f center;
        igVec3f view;
        static igMetaObject *modelViewMeta = Gap::Attrs::igModelViewMatrixAttr::getClassTypeSafe();
        modelView = (igModelViewMatrixAttr *)lastAttr(attrStackOf(manager, modelViewMeta));
        if (bound != 0) {
            FUN_00190200(bound, center.vec);
        } else {
            center = g_vec3Zero;
        }
        if (modelView != 0) {
            Vec3f_TransformProjective(view.vec, center.vec, modelView->_m);
        } else {
            view = center;
        }
        if (sorter->_useZSort) {
            package->_distance = view[2] * view[2];
        } else {
            package->_distance = view.length2();
        }
    }
    if (sorter->_isCompoundPackageOpen) {
        int count;
        RenderPackagePointerList *packages = (RenderPackagePointerList *)((igRenderPackage *)sorter->_compoundPackage)->_theMass;
        igRenderPackage *item = package;
        count = packages->getCount();
        if (count < packages->_capacity) {
            packages->_count++;
        } else {
            ((Gap::Core::igDataList *)packages)->resizeAndSetCount(count + 1, sizeof(igRenderPackage *));
        }
        packages->_data[count] = item;
    } else if (transparent) {
        int count;
        RenderPackagePointerList *packages = (RenderPackagePointerList *)sorter->_transpPackages;
        igRenderPackage *item = package;
        count = packages->getCount();
        if (count < packages->_capacity) {
            packages->_count++;
        } else {
            ((Gap::Core::igDataList *)packages)->resizeAndSetCount(count + 1, sizeof(igRenderPackage *));
        }
        packages->_data[count] = item;
    } else {
        int count;
        RenderPackagePointerList *packages = (RenderPackagePointerList *)sorter->_opaquePackages;
        igRenderPackage *item = package;
        count = packages->getCount();
        if (count < packages->_capacity) {
            packages->_count++;
        } else {
            ((Gap::Core::igDataList *)packages)->resizeAndSetCount(count + 1, sizeof(igRenderPackage *));
        }
        packages->_data[count] = item;
    }
}

void FUN_001dc400(igSorter *arg0, igGroup *arg1, igAttrStackManager *arg2) {
    igAttrStack *e;
    int v;
    int n;
    struct L_1dc400 *l;
    e = ((igAttrStack **)((igAttrStackList *)arg2->_attrStacks)->_data)[((int *)arg2->_attrStackIndexTable)[Gap::Attrs::igModelViewMatrixAttr::getClassMeta()->_id]];
    if (e->_count == 0) {
        v = 0;
    } else {
        v = *(int *)((char *)e->_data + (e->_count - 1) * 4);
    }
    l = ((struct LA_1dc400 *)arg0->_lightAttrs)->l;
    n = l->cnt;
    if (n < l->cap) {
        l->cnt = cnt_of(l) + 1;
    } else {
        ((Gap::Core::igDataList *)l)->resizeAndSetCount(n + 1, 4);
    }
    l->data[n] = v;
    List_AppendWords((igDataList *)(((struct LA_1dc400 *)arg0->_lightAttrs)->l), ((igNodeList *)arg1->_childList)->_count, (const int *)(((igNodeList *)arg1->_childList)->_data));
}

void FUN_001dc500(A_1dc500 *arg0, unsigned char arg1, int arg2) {
    int temp_a0;
    L_1dc500 *temp_s0;
    X_1dc500 *temp_s0_2;
    X_1dc500 *t;
    L2 *temp_a0_3;

    arg0->f120 = arg0->f120 + 1;
    if (arg0->f112 == 0) {
        arg0->f112 = 1;
        arg0->f113 = arg1;
        arg0->f114 = arg2;
        temp_s0 = arg0->f16;
        if (temp_s0->f20 >= temp_s0->f8) {
            igObjectPool_Grow((igObjectPool *)temp_s0, (igObject *(*)(int))&Gap::Sg::igRenderPackage::_instantiateFromPool);
        }
        temp_a0 = temp_s0->f20;
        temp_s0->f20 = temp_a0 + 1;
        temp_s0_2 = temp_s0->f16[temp_a0];
        temp_s0_2->f12 = temp_s0_2->f8;
        if (temp_s0_2 != 0) {
            temp_s0_2->f4 = temp_s0_2->f4 + 1;
        }
        t = arg0->f116;
        if (t != 0) {
            t->f4 = t->f4 - 1;
            if (((unsigned long long) ((long long) t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)t);
            }
        }
        arg0->f116 = temp_s0_2;
        temp_a0_3 = arg0->f116->f28;
        if (0 <= temp_a0_3->f12) {
            temp_a0_3->f8 = 0;
            return;
        }
        ((Gap::Core::igDataList *)temp_a0_3)->resizeAndSetCount(0, 4);
    }
}

/* igSorter::endCompoundRenderPackage (alchemy-kit_202309 igSg/igSorter.h): closes the open compound render package
 * once its nesting count falls to zero. The package takes the sorting key and distance of its first member, drops
 * its geometry and state attributes, and joins the transparent, first or opaque package list.
 * matching construct: regalloc.py — each append is the kit's igTDataList<T>::append(const T &) written out with
 * the count declared ahead of the list: as the inline's parameter the list takes an allocator id below the count's,
 * is pushed after the sorter and colours s1, the sorter s2 (retail: sorter s1, lists s2). */
void FUN_001dc610(igSorter *sorter) {
    if (sorter->_compoundPackageNestCount != 0) {
        if (--sorter->_compoundPackageNestCount <= 0) {
            sorter->_isCompoundPackageOpen = 0;
            igRenderPackage *package = (igRenderPackage *)sorter->_compoundPackage;
            if (((igTDataList<igRenderPackage *> *)package->_theMass)->getCount() != 0) {
                igRenderPackage *first = ((igTDataList<igRenderPackage *> *)package->_theMass)->get(0);
                ((igTDataList<igAttr *> *)package->_geomAttrs)->setCount(0);
                ((igTDataList<igAttr *> *)((igRenderPackage *)sorter->_compoundPackage)->_stateAttrs)->setCount(0);
                ((igRenderPackage *)sorter->_compoundPackage)->_sortingCache = first->_sortingCache;
                ((igRenderPackage *)sorter->_compoundPackage)->_distance = first->_distance;
                if (sorter->_isCompoundPackageTransparent) {
                    int count;
                    igTDataList<igRenderPackage *> *packages = (igTDataList<igRenderPackage *> *)sorter->_transpPackages;
                    count = packages->getCount();
                    igRenderPackage *item = (igRenderPackage *)sorter->_compoundPackage;
                    if (count < packages->_capacity) {
                        packages->_count++;
                    } else {
                        ((Gap::Core::igDataList *)packages)->resizeAndSetCount(count + 1, sizeof(igRenderPackage *));
                    }
                    packages->_data[count] = item;
                } else if (sorter->_isCompoundPackageFirst) {
                    int count;
                    igTDataList<igRenderPackage *> *packages = (igTDataList<igRenderPackage *> *)sorter->_firstPackages;
                    count = packages->getCount();
                    igRenderPackage *item = (igRenderPackage *)sorter->_compoundPackage;
                    if (count < packages->_capacity) {
                        packages->_count++;
                    } else {
                        ((Gap::Core::igDataList *)packages)->resizeAndSetCount(count + 1, sizeof(igRenderPackage *));
                    }
                    packages->_data[count] = item;
                } else {
                    int count;
                    igTDataList<igRenderPackage *> *packages = (igTDataList<igRenderPackage *> *)sorter->_opaquePackages;
                    count = packages->getCount();
                    igRenderPackage *item = (igRenderPackage *)sorter->_compoundPackage;
                    if (count < packages->_capacity) {
                        packages->_count++;
                    } else {
                        ((Gap::Core::igDataList *)packages)->resizeAndSetCount(count + 1, sizeof(igRenderPackage *));
                    }
                    packages->_data[count] = item;
                }
                igObject::release((igObject *)sorter->_compoundPackage);
                sorter->_compoundPackage = 0;
            }
        }
    }
}

namespace Gap {
namespace Sg {

void igSwitch::activateChild(unsigned int index)
{
    /* igBitMask's inline bit setter, open-coded (the class is still flat): the word is read before its index is checked */
    ::igBitMask *mask = _childMask;
    unsigned int word = index >> 5;
    int *slot = (int *)(mask->_data + word * 4);
    int count = mask->_count;
    int value = (1 << (index & 0x1F)) | *slot;
    if (count != 0 && (int)word >= 0 && (int)word < count) {
        *slot = value;
    }
}

void igSwitch::activateAllChildren()
{
    igBitMask_SetAll(_childMask);
}

void igSwitch::deactivateChild(unsigned int index)
{
    /* igBitMask's inline bit clearer, open-coded (the class is still flat) */
    ::igBitMask *mask = _childMask;
    unsigned int word = index >> 5;
    int *slot = (int *)(mask->_data + word * 4);
    int count = mask->_count;
    int value = ~(1 << (index & 0x1F)) & *slot;
    if (count != 0 && (int)word >= 0 && (int)word < count) {
        *slot = value;
    }
}

void igSwitch::deactivateAllChildren()
{
    igBitMask_ClearAll(_childMask);
}

int igSwitch::appendChild(igNode *child)
{
    int index = igGroup::appendChild(child);
    igBitMask_SetBitCount(_childMask, getChildCount());
    return index;
}
}
}

