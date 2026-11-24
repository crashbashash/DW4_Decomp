namespace Gap {
namespace Core {

/* Adds object to the list, in front of the first listed object that the order ranks after it. An
 * object the order does not rank goes at the end, and with `unique` set one already listed is left
 * alone. */
void igDependencyOrderedList::internalAppend(igObject *object, bool unique)
{
    int rank = _order->find(object);
    if (rank < 0) {
        if (unique)
            _objectList->appendUnique(object);
        else
            _objectList->append(object);
        return;
    }
    int j = 0;
    for (int i = 0; i < _objectList->getCount(); i++) {
        igObject *listed = _objectList->get(i);
        if (unique && listed == object)
            return;
        while (j < rank && listed != _order->get(j))
            j++;
        if (!(j < rank)) {
            _objectList->insert(i, object);
            return;
        }
    }
    _objectList->append(object);
}

/* The kit's igTDataList<igDependency>::append, written out by field: retail numbers the count before the list
 * (the inline's list parameter would come first, and an int copy of getCount() last) and reloads the count for
 * the increment. */
void igDependencyOrderedList::appendDependency(const void *before, const void *after)
{
    int count;
    igDependencyList *dependencies = _dependencies;
    count = dependencies->_count;
    if (count < dependencies->_capacity)
        dependencies->_count = dependencies->getCount() + 1;
    else
        dependencies->resizeAndSetCount(count + 1, sizeof(igDependency));
    dependencies->get(count) = igDependency(before, after);
    igDependencyOrderedList_TopologicalSort((::igDependencyOrderedList *)this);
    reOrderObjects();
}

void igDependencyOrderedList::reOrderObjects()
{
    igSmartPointer<igObjectList> copy(igObjectList::_instantiateFromPool(getMemoryPool()));
    copy->concatenate(_objectList);
    _objectList->removeAll();
    for (int i = 0; i < copy->getCount(); i++)
        internalAppend(copy->get(i), false);
}

void igDependencyOrderedList::removeAll()
{
    _objectList->removeAll();
}

igResult igDependencyOrderedList::remove(igObject *object)
{
    return _objectList->removeByValue(object, 0);
}

igResult igDependencyOrderedList::removeDependency(const void *before, const void *after)
{
    int index = _dependencies->find(igDependency(before, after));
    igResult result;
    if (index >= 0) {
        _dependencies->remove(index);
        result = g_resultSuccess;
    } else {
        result = g_resultFailure;
    }
    if (_hasCircularDependencies) {
        igDependencyOrderedList_TopologicalSort((::igDependencyOrderedList *)this);
        reOrderObjects();
    }
    return result;
}

void igDependencyOrderedList::removeAllDependencies(const void *object)
{
    for (int i = _dependencies->getCount() - 1; i >= 0; i--) {
        igDependency dependency = _dependencies->get(i);
        if (dependency._before == object || dependency._after == object)
            _dependencies->remove(i);
    }
    if (_hasCircularDependencies) {
        igDependencyOrderedList_TopologicalSort((::igDependencyOrderedList *)this);
        reOrderObjects();
    }
}

void igDependencyOrderedList::appendCheckPoint(const char *name) {
    void *checkPoint;
    int *header;
    int references;
    int pool;
    void *interned;

    if (name == 0) {
        interned = (void *)(0);
    } else {
        if (g_stringPool == 0) {
            pool = ((int)StringPool_Allocate(0x10));
            if (pool != 0) {
                pool = ((int)StringPool_Construct((StringPool *)pool));
            }
            g_stringPool = (StringPool *)pool;
        }
        interned = (void *)(StringPool_Intern((StringPool *)g_stringPool, name));
    }
    checkPoint = (void *)(interned);
    StringList_AppendRetained(_checkPoints, (char *const *)&checkPoint);
    if (checkPoint != 0) {
        header = (int *)((char *)checkPoint - 8);
        references = *(int *)((char *)(checkPoint) - 4) - 1;
        *(int *)((char *)(checkPoint) - 4) = references;
        if (references == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
        }
    }
}
}
}

