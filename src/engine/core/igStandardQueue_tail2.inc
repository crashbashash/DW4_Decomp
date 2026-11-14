void igStandardQueue_InitDefaults(igStandardQueueView *self) {
    self->_insertLock->create();
    self->_removeLock->create();
    self->_queueSema->setInitialCount(0);
    self->_queueSema->setMaximumCount(0x7FFFFFFF);
    self->_queueSema->create();
}

void igStandardQueue_ReleaseDefaults(igStandardQueueView *self) {
    if (self->isCreated() != 0) {
        self->destroy();
    }
    thunk_igStandardQueue_StopServiceThreads((int)self);
}

void igStandardQueue_Create(igStandardQueue *self) {
    self->_data = igObject_AllocateStorage((int)self, self->_capacity * 4);
}

void igStandardQueue_Destroy(igStandardQueue *self) {
    igObject_FreeMemory((int)self, self->_data);
    self->_data = 0;
}

/* Predicate: true once the queue's element storage (`_data`, igMemoryRefMetaField, +36) has been
 * allocated. */
int igStandardQueue_IsCreated(igStandardQueue *self) {
    return self->_data != 0;
}

igResult igStandardQueue_Insert(igStandardQueueView *self, int val, int block)
{
    unsigned a;
    unsigned b;
    if (self->isFull() != 0 && self->getCount() > self->_maxCapacity && block == 0) {
        return igResult(g_resultFailure.v);
    }
    while (((self->isFull() != 0) ^ 1) == 0 && self->getCount() > self->_maxCapacity) {
        g_threadManager[0]->_threadList->_data[0]->sleep(0x05F5E100);
    }
    if (self->_insertLock->wait(block) != g_resultSuccess) {
        return igResult(g_resultFailure.v);
    }
    if (self->isFull() != 0) {
        if (self->_removeLock->wait(block) != g_resultSuccess) {
            return igResult(g_resultFailure.v);
        }
        if (self->isFull() != 0) {
            a = self->_maxCapacity;
            b = self->_capacity * 2;
            igStandardQueue_Resize(self, (int)((a < b) ? a : b));
        }
        self->_removeLock->signal();
    }
    self->_data[self->_insertElement] = val;
    self->_insertElement = (self->_insertElement + 1) % self->_capacity;
    self->_insertLock->signal();
    self->_queueSema->signal();
    return igResult(g_resultSuccess.v);
}

int igStandardQueue_IsFull(igStandardQueueView *self) {
    return self->_capacity == self->_queueSema->getCount();
}

igResult igStandardQueue_Remove(igStandardQueueView *self, int *out, int block)
{
    if (self->_queueSema->wait(block) != g_resultSuccess) {
        return igResult(g_resultFailure.v);
    }
    if (self->_removeLock->wait(block) != g_resultSuccess) {
        return igResult(g_resultFailure.v);
    }
    *out = self->_data[self->_removeElement];
    self->_removeElement = (self->_removeElement + 1) % self->_capacity;
    self->_removeLock->signal();
    return igResult(g_resultSuccess.v);
}

int igStandardQueue_GetCount(igStandardQueueView *self)
{
    return self->_queueSema->getCount();
}

void igStandardQueue_Resize(igStandardQueueView *queue, int capacity) {
    int s0;
    int s3;
    unsigned a2;
    unsigned v0;
    if (capacity != queue->_capacity) {
        s0 = igObject_AllocateStorage((int)queue, capacity * 4);
        a2 = queue->_removeElement;
        v0 = queue->_insertElement;
        if (a2 < v0) {
            memmove(s0, (int)(queue->_data + a2), (v0 - a2) * 4);
        } else {
            s3 = (queue->_capacity - a2) * 4;
            memmove(s0, (int)(queue->_data + a2), s3);
            memmove(s0 + s3, (int)queue->_data, queue->_insertElement * 4);
        }
        igObject_FreeMemory((int)queue, (int)queue->_data);
        queue->_data = (int *)s0;
        queue->_insertElement = queue->getCount();
        queue->_removeElement = 0;
        queue->_capacity = capacity;
    }
}

igResult igStandardQueue_SetCapacity(igStandardQueueView *self, unsigned n)
{
    if (n > self->_maxCapacity || n < self->getCount()) {
        return igResult(g_resultFailure.v);
    }
    if (self->_data == 0) {
        self->_capacity = n;
    } else {
        self->_removeLock->wait(1);
        self->_insertLock->wait(1);
        igStandardQueue_Resize(self, (int)n);
        self->_insertLock->signal();
        self->_removeLock->signal();
    }
    return igResult(g_resultSuccess.v);
}

/* Accessor: returns the queue's current `_capacity` (igUnsignedIntMetaField, +24). */
int igStandardQueue_GetCapacity(igStandardQueue *self) {
    return self->_capacity;
}

void igStandardQueue_SetMaxCapacity(int *out, igStandardQueueView *self, unsigned a) {
    igResult t[5];
    if (a >= self->_capacity || self->_data == 0) {
        self->_maxCapacity = a;
        *out = g_resultSuccess.v;
    } else {
        t[4] = self->_insertLock->wait(1);
        if (a < self->getCount()) {
            t[3] = self->_insertLock->signal();
            *out = g_resultFailure.v;
        } else {
            t[2] = self->_removeLock->wait(1);
            igStandardQueue_Resize(self, a);
            self->_maxCapacity = self->_capacity;
            t[1] = self->_insertLock->signal();
            t[0] = self->_removeLock->signal();
            *out = g_resultSuccess.v;
        }
    }
}

/* Accessor: returns the queue's `_maxCapacity` (igUnsignedIntMetaField, +40). */
int igStandardQueue_GetMaxCapacity(igStandardQueue *self) {
    return self->_maxCapacity;
}

int **SystemAllocatorBase_Construct(int **arg0) {
    *arg0 = &g_vtable[0];
    return arg0;
}

