void igPsx2Semaphore_GetMetaObjectFunction(void) {
    igPsx2Semaphore_GetMetaObject();
}

igSmartPointer<igObject> *igSmartPointer_igCallStackTracer_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if(self) {
        igObject *object=self->p;
        if(object) {
            --object->_refCount;
            if(((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL)==0)
                igObject_Destroy((igObject *)object);
        }
        if((short)delete_storage>0) operator delete(self);
    }
    return self;
}

void **igSmartPointer_igLocationTable_Destruct(void **pointer, int flags) {
    int *table;

    if (pointer != 0) {
        table = (int *)(*pointer);
        if (table != 0) {
            table[1] = table[1] - 1;
            if ((table[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)table);
            }
        }
        if ((short)flags > 0) {
            operator delete(pointer);
        }
    }
    return pointer;
}

void **igSmartPointer_igCallStackTable_Destruct(void **pointer, short flags) {
    int *table;

    if (pointer != 0) {
        table = (int *)*pointer;
        if (table != 0) {
            table[1] = table[1] - 1;
            if ((table[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)table);
            }
        }
        if (flags > 0) {
            operator delete(pointer);
        }
    }
    return pointer;
}

void **igSmartPointer_igSemaphore_Destruct(igObject **self, short flag) {
    igObject *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            ((igRefCountWord *)&p->_refCount)->word = ((igRefCountWord *)&p->_refCount)->word - 1;
            if (((igRefCountWord *)&p->_refCount)->bits.count == 0) igObject_Destroy(p);
        }
        if (flag > 0) operator delete(self);
    }
    return (void **)self;
}

