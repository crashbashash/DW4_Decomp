void igStandardQueue_InitDefaults(igStandardQueueView *self) {
    self->_insertLock->Create();
    self->_removeLock->Create();
    self->_queueSema->SetInitialCount(0);
    self->_queueSema->SetMaximumCount(0x7FFFFFFF);
    self->_queueSema->Create();
}

void igStandardQueue_ReleaseDefaults(igStandardQueueView *self) {
    if (self->IsCreated() != 0) {
        self->Destroy();
    }
    igQueue_ReleaseDefaults((int)self);
}

void igStandardQueue_Create(igStandardQueue *self) {
    self->_data = (int)igObject_AllocateStorage((igObject *)self, self->_capacity * 4);
}

void igStandardQueue_Destroy(igStandardQueue *self) {
    igObject_FreeMemory((igObject *)self, (void *)self->_data);
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
    if (self->IsFull() != 0 && self->GetCount() > self->_maxCapacity && block == 0) {
        return igResult(g_resultFailure.v);
    }
    while (((self->IsFull() != 0) ^ 1) == 0 && self->GetCount() > self->_maxCapacity) {
        g_threadManager->_threadList->_data[0]->Sleep(0x05F5E100);
    }
    if (self->_insertLock->Wait(block) != g_resultSuccess) {
        return igResult(g_resultFailure.v);
    }
    if (self->IsFull() != 0) {
        if (self->_removeLock->Wait(block) != g_resultSuccess) {
            return igResult(g_resultFailure.v);
        }
        if (self->IsFull() != 0) {
            a = self->_maxCapacity;
            b = self->_capacity * 2;
            igStandardQueue_Resize(self, (int)((a < b) ? a : b));
        }
        self->_removeLock->Signal();
    }
    self->_data[self->_insertElement] = val;
    self->_insertElement = (self->_insertElement + 1) % self->_capacity;
    self->_insertLock->Signal();
    self->_queueSema->Signal();
    return igResult(g_resultSuccess.v);
}

int igStandardQueue_IsFull(igStandardQueueView *self) {
    return self->_capacity == self->_queueSema->GetCount();
}

igResult igStandardQueue_Remove(igStandardQueueView *self, int *out, int block)
{
    if (self->_queueSema->Wait(block) != g_resultSuccess) {
        return igResult(g_resultFailure.v);
    }
    if (self->_removeLock->Wait(block) != g_resultSuccess) {
        return igResult(g_resultFailure.v);
    }
    *out = self->_data[self->_removeElement];
    self->_removeElement = (self->_removeElement + 1) % self->_capacity;
    self->_removeLock->Signal();
    return igResult(g_resultSuccess.v);
}

int igStandardQueue_GetCount(igStandardQueueView *self)
{
    return self->_queueSema->GetCount();
}

void igStandardQueue_Resize(igStandardQueueView *queue, int capacity) {
    int s0;
    int s3;
    unsigned a2;
    unsigned v0;
    if (capacity != queue->_capacity) {
        s0 = (int)igObject_AllocateStorage((igObject *)queue, capacity * 4);
        a2 = queue->_removeElement;
        v0 = queue->_insertElement;
        if (a2 < v0) {
            memmove((void *)s0, (void *)(int)(queue->_data + a2), (v0 - a2) * 4);
        } else {
            s3 = (queue->_capacity - a2) * 4;
            memmove((void *)s0, (void *)(int)(queue->_data + a2), s3);
            memmove((void *)(s0 + s3), (void *)(int)queue->_data, queue->_insertElement * 4);
        }
        igObject_FreeMemory((igObject *)queue, (void *)queue->_data);
        queue->_data = (int *)s0;
        queue->_insertElement = queue->GetCount();
        queue->_removeElement = 0;
        queue->_capacity = capacity;
    }
}

igResult igStandardQueue_SetCapacity(igStandardQueueView *self, unsigned n)
{
    if (n > self->_maxCapacity || n < self->GetCount()) {
        return igResult(g_resultFailure.v);
    }
    if (self->_data == 0) {
        self->_capacity = n;
    } else {
        self->_removeLock->Wait(1);
        self->_insertLock->Wait(1);
        igStandardQueue_Resize(self, (int)n);
        self->_insertLock->Signal();
        self->_removeLock->Signal();
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
        t[4] = self->_insertLock->Wait(1);
        if (a < self->GetCount()) {
            t[3] = self->_insertLock->Signal();
            *out = g_resultFailure.v;
        } else {
            t[2] = self->_removeLock->Wait(1);
            igStandardQueue_Resize(self, a);
            self->_maxCapacity = self->_capacity;
            t[1] = self->_insertLock->Signal();
            t[0] = self->_removeLock->Signal();
            *out = g_resultSuccess.v;
        }
    }
}

/* Accessor: returns the queue's `_maxCapacity` (igUnsignedIntMetaField, +40). */
int igStandardQueue_GetMaxCapacity(igStandardQueue *self) {
    return self->_maxCapacity;
}

int **SystemAllocatorBase_Construct(int **self) {
    *self = &g_vtable[0];
    return self;
}

