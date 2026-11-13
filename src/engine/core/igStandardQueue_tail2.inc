void Gap__Core__igStandardQueue__vfunc_11(S_328590 *arg0) {
    arg0->f0c->vA();
    arg0->f10->vA();
    arg0->f14->vB(0);
    arg0->f14->vC(0x7FFFFFFF);
    arg0->f14->vA();
}

void Gap__Core__igStandardQueue__vfunc_12(void **self) {
    if (((DW4VC_100_0 *)(self))->vX() != 0) {
        ((DW4VC_96_0 *)(self))->vX();
    }
    thunk_FUN_00305000((int)self);
}

void Gap__Core__igStandardQueue__vfunc_23(igStandardQueue *self) {
    self->_data = igObject_AllocateStorage((int)self, self->_capacity * 4);
}

void Gap__Core__igStandardQueue__vfunc_24(struct S_3286a0 *arg0) {
    FUN_00300f50((int)arg0, arg0->f);
    arg0->f = 0;
}

/* Predicate: true once the queue's element storage (`_data`, igMemoryRefMetaField, +36) has been
 * allocated. */
int Gap__Core__igStandardQueue__vfunc_25(igStandardQueue *self) {
    return self->_data != 0;
}

R_3286e0 Gap__Core__igStandardQueue__vfunc_26(Self_3286e0 *self, int val, int block)
{
    unsigned a;
    unsigned b;
    if (self->v27() != 0 && self->v26() > self->f40 && block == 0) {
        return R_3286e0(g_allocatorFailureStatus.v);
    }
    while (((self->v27() != 0) ^ 1) == 0 && self->v26() > self->f40) {
        Q23 *t = (Q23 *)**(int **)(*(int *)((char *)((int * *)g_threadManager)[0] + 8) + 16);
        t->v23(0x05F5E100);
    }
    int c = self->q12->v31(block).Code();
    if (c != g_statusSucceeded.v) {
        return R_3286e0(g_allocatorFailureStatus.v);
    }
    if (self->v27() != 0) {
        int c2 = self->q16->v31(block).Code();
        if (c2 != g_statusSucceeded.v) {
            return R_3286e0(g_allocatorFailureStatus.v);
        }
        if (self->v27() != 0) {
            a = self->f40;
            b = self->cap * 2;
            FUN_00328ab0((Q_328ab0 *)self, (int)((a < b) ? a : b));
        }
        self->q16->v29();
    }
    self->buf[self->head] = val;
    self->head = (self->head + 1) % self->cap;
    self->q12->v29();
    self->q20->v29();
    return R_3286e0(g_statusSucceeded.v);
}

int Gap__Core__igStandardQueue__vfunc_29(igStandardQueue *self) {
    void **queueSema;

    queueSema = (void **)(self->_queueSema);
    return self->_capacity == ((SemaphoreVtable *)(queueSema))->vX();
}

R_328970 Gap__Core__igStandardQueue__vfunc_27(Self_328970 *self, int *out, int block)
{
    int c = ((Q33 *)self->q20)->v33(block).Code();
    if (c != g_statusSucceeded.v) {
        return R_328970(g_allocatorFailureStatus.v);
    }
    int c2 = ((Q33 *)self->q16)->v33(block).Code();
    if (c2 != g_statusSucceeded.v) {
        return R_328970(g_allocatorFailureStatus.v);
    }
    *out = self->buf[self->tail];
    self->tail = (self->tail + 1) % self->cap;
    ((Q31 *)self->q16)->v31();
    return R_328970(g_statusSucceeded.v);
}

void Gap__Core__igStandardQueue__vfunc_28(igStandardQueueView *self)
{
    self->_queueSema->vfunc_28();
}

void FUN_00328ab0(Q_328ab0 *arg0, int arg1) {
    int s0;
    int s3;
    int off;
    unsigned a2;
    unsigned v0;
    if (arg1 != arg0->cap) {
        s0 = igObject_AllocateStorage((int)arg0, arg1 * 4);
        a2 = arg0->head;
        v0 = arg0->cnt;
        if (a2 < v0) {
            memmove(s0, arg0->buf + a2 * 4, (v0 - a2) * 4);
        } else {
            s3 = (arg0->cap - a2) * 4;
            off = a2 * 4;
            memmove(s0, arg0->buf + off, s3);
            memmove(s0 + s3, arg0->buf, arg0->cnt * 4);
        }
        FUN_00300f50((int)arg0, arg0->buf);
        arg0->buf = s0;
        arg0->cnt = arg0->getCount();
        arg0->head = 0;
        arg0->cap = arg1;
    }
}

R_328ba0 Gap__Core__igStandardQueue__vfunc_30(Self_328ba0 *o, unsigned n)
{
    if (n > o->f40 || n < o->v26()) {
        return R_328ba0(g_allocatorFailureStatus.v);
    }
    if (o->f36 == 0) {
        o->f24 = n;
    } else {
        o->q16->v31(1);
        o->q12->v31(1);
        FUN_00328ab0((Q_328ab0 *)o, (int)n);
        o->q12->v29();
        o->q16->v29();
    }
    return R_328ba0(g_statusSucceeded.v);
}

/* Accessor: returns the queue's current `_capacity` (igUnsignedIntMetaField, +24). */
int Gap__Core__igStandardQueue__vfunc_31(igStandardQueue *self) {
    return self->_capacity;
}

void Gap__Core__igStandardQueue__vfunc_32(int *out, Q_328cb0 *q, unsigned a) {
    R_328cb0 t[5];
    if (a >= q->cap || q->f36 == 0) {
        q->f40 = a;
        *out = g_statusSucceeded.v;
    } else {
        t[4] = q->s3->v31(1);
        if (a < q->v26()) {
            t[3] = q->s3->v29();
            *out = g_allocatorFailureStatus.v;
        } else {
            t[2] = q->s4->v31(1);
            FUN_00328ab0((Q_328ab0 *)q, a);
            q->f40 = q->cap;
            t[1] = q->s3->v29();
            t[0] = q->s4->v29();
            *out = g_statusSucceeded.v;
        }
    }
}

/* Accessor: returns the queue's `_maxCapacity` (igUnsignedIntMetaField, +40). */
int Gap__Core__igStandardQueue__vfunc_33(igStandardQueue *self) {
    return self->_maxCapacity;
}

int **FUN_00328de0(int **arg0) {
    *arg0 = &g_vtable[0];
    return arg0;
}

