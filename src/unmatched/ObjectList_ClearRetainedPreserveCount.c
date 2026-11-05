int memset();
int igObject_Destroy();
struct R { int w0; int refs; };
struct L { int p0; int p1; int count; int p3; struct R **data; };
void ObjectList_ClearRetainedPreserveCount(struct L *arg0) {
    int n;
    int i;
    struct R *o;

    n = arg0->count;
    for (i = 0; i < n; i++) {
        o = arg0->data[i];
        if (o != 0) {
            o->refs = o->refs - 1;
            if ((o->refs & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    if (arg0->count != 0) {
        memset(arg0->data, 0, arg0->count * 4);
    }
}
