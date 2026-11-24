namespace Gap {
namespace Sg {

bool igSwitch::insertChild(int index, igNode *child)
{
    bool inserted = igGroup::insertChild(index, child);
    igBitMask_SetBitCount(_childMask, getChildCount());
    return inserted;
}

igNode *igSwitch::removeChild(int index)
{
    igNode *removed = igGroup::removeChild(index).p;
    igBitMask_SetBitCount(_childMask, getChildCount());
    return removed;
}
}
}

void igObjectPool_Grow(igObjectPool *pool, igObject *(*create)(int)) {
    List_1dca40 *arg0 = (List_1dca40 *)pool;
    Obj_1dca40 *(*arg1)(int) = (Obj_1dca40 *(*)(int))create;
    int n;
    int alloc;
    int i;
    int c;
    Obj_1dca40 *o;
    Obj_1dca40 *old;
    int off;
    c = count_of_1dca40(arg0);
    n = arg0->f24 + c;
    ((Gap::Core::igObjectList *)((igTDataList<igObject *> *)arg0))->setCount(n);
    alloc = (int)((Gap::Core::igObject *)arg0)->getMemoryPool();
    i = arg0->f20;
    for (; i < n; i++) {
        o = arg1(alloc);
        if (o != 0) {
            o->references = o->references + 1;
        }
        off = i * 4;
        old = *(Obj_1dca40 **)((char *)arg0->data + off);
        if (old != 0) {
            old->references = old->references - 1;
            if (((unsigned long long)((long long)old->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)old);
            }
        }
        if (arg0->count != 0 && i >= 0 && i < arg0->count) {
            *(Obj_1dca40 **)((char *)arg0->data + off) = o;
        }
        o->references = o->references - 1;
        if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
            igObject_Destroy((igObject *)o);
        }
    }
}

void FUN_001dcb80(ObjectPool *pool, igObject *object) {
    int index = pool->find(object);
    if (index >= 0) {
        if (pool->_resetOnRelease != 0) {
            igObject_ResetFields((igObjectDispatchView *)object);
        }
        pool->_activeCount = pool->_activeCount - 1;
        int last = pool->_activeCount;
        if (last != index) {
            int count = pool->_count;
            if (count != 0 && last >= 0 && last < count && index >= 0 && index < count) {
                igObject **data = pool->_data;
                igObject *t = data[last];
                data[last] = data[index];
                data[index] = t;
            }
        }
    }
}

int FUN_001dcc80(KeyTrackView *o, double t) {
    int n;
    double rel;
    double dur;
    double q;
    int k;
    double v;
    if (_dpflt(o->_startTime, 0.0)) { o->_startTime = t; }
    n = o->_values->_count;
    if (n == 0) { return 0; }
    rel = dpsub(t, o->_startTime);
    if (_dpflt(rel, 0.0)) { rel = 0.0; }
    {
        KeyTimeListView *tl = o->_times;
        int last = n - 1;
        dur = tl->_data[last];
    }
    q = rel / dur;
    k = dptoli(floor(q));
    switch (o->_mode) {
    case 0:
        v = dur * dpsub(q, k);
        break;
    case 1:
        q = rel;
        if (k > 1) { q = dur; }
    case 2:
        if (k % 2 != 0) {
            v = dpsub(dur, dur * dpsub(q, k));
        } else {
            v = dur * dpsub(q, k);
        }
        break;
    default:
        v = dur * dpsub(q, k);
        break;
    }
    {
        int index = FUN_001dce70((struct S_1dce70 *)o->_times, v);
        KeyValueListView *vl = o->_values;
        return vl->_data[index];
    }
}

int FUN_001dce70(struct S_1dce70 *arg0, double arg1) {
    int var_s3;
    int var_s2;
    int temp_s1;
    int temp_s0;

    var_s3 = 0;
    temp_s0 = arg0->f8;
    var_s2 = temp_s0 - 1;
    while (var_s3 < var_s2) {
        temp_s1 = (var_s2 + var_s3 + 1) >> 1;
        if (_dpflt(arg1, arg0->f16[temp_s1]) != 0) {
            var_s2 = temp_s1 - 1;
        } else {
            var_s3 = temp_s1;
        }
    }
    if (temp_s0 != 0) {
        if (_dpflt(arg0->f16[var_s3], arg1) != 0) {
            var_s3 += 1;
        }
    }
    return var_s3;
}

