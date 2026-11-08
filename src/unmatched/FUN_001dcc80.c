int FUN_001002f0(double, double);
double dpsub(double, double);
double floor(double);
int dptoli(double);
typedef struct KeyTimeListView { int _vtable; unsigned int _refCount; int _count; int _capacity; double *_data; } KeyTimeListView;
typedef struct KeyValueListView { int _vtable; unsigned int _refCount; int _count; int _capacity; int *_data; } KeyValueListView;
typedef struct KeyTrackView { char pad[28]; KeyValueListView *_values; KeyTimeListView *_times; double _startTime; int _mode; } KeyTrackView;
int FUN_001dce70(KeyTimeListView *, double);
int FUN_001dcc80(KeyTrackView *o, double t) {
    int n;
    double rel;
    double dur;
    double q;
    int k;
    double v;
    if (FUN_001002f0(o->_startTime, 0.0)) { o->_startTime = t; }
    n = o->_values->_count;
    if (n == 0) { return 0; }
    rel = dpsub(t, o->_startTime);
    if (FUN_001002f0(rel, 0.0)) { rel = 0.0; }
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
        int index = FUN_001dce70(o->_times, v);
        KeyValueListView *vl = o->_values;
        return vl->_data[index];
    }
}
