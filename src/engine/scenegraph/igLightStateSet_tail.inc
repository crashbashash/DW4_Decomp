void Gap__Sg__igLightStateSet__vfunc_31(igLightStateSetView *self) {
    unsigned int n;
    unsigned int i;

    n = self->lights->count;
    for (i = 0; i < n; i++) {
        self->lights->data[i]->apply();
    }
}

RangeRefObject *FUN_001d0520(RangeLookup *self, float t) {
    int lo;
    int hi;
    int count;
    float *data;
    int refCount;
    float start = self->start;
    if (!(t < start) && t < self->end) {
        return self->current;
    }
    {
        RangeRefList *refs;
        RangeFloatList *times;
        times = self->times;
        refs = self->refs;
        count = times->count;
        if (refs != 0) {
            refCount = refs->count;
        } else {
            refCount = 0;
        }
        data = times->data;
        if (t < start) {
            lo = self->index;
            goto below;
            do {
                lo--;
below:
                hi = lo + 1;
                if (lo < 0) {
                    break;
                }
            } while (t < data[lo]);
            self->index = lo;
        } else {
            hi = self->index + 2;
            goto above;
            do {
                hi++;
above:
                lo = hi - 1;
                if (!(count > hi)) {
                    break;
                }
            } while (!(t < data[hi]));
            self->index = lo;
        }
        if (lo >= 0) {
            self->start = data[lo];
            if (refCount > lo) {
                RangeRefObject *o = self->refs->data[lo];
                if (o != 0) {
                    o->_refCount = o->_refCount + 1;
                }
                dropCurrent(self);
                self->current = o;
            } else {
                dropCurrent(self);
                self->current = 0;
            }
        } else {
            self->start = 0.0f;
            dropCurrent(self);
            self->current = 0;
        }
        if (count > hi) {
            self->end = data[hi];
        } else {
            self->end = 3.40282347e+38f;
        }
        if (self->blends != 0) {
            RangeFloatList *b = self->blends;
            int n = b->count;
            if (n > lo && lo >= 0) {
                float v;
                float r = sqrtf(self->start);
                v = b->data[lo];
                self->start = self->start + (v * v - 2.0f * v * r);
            }
            if (n > hi) {
                float v;
                float r = sqrtf(self->end);
                v = self->blends->data[hi];
                self->end = self->end + (v * v + 2.0f * v * r);
            }
        }
    }
    return self->current;
}

