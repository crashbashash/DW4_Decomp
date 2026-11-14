void thunk_igPsx2Semaphore_GetMetaObject(void) {
    igPsx2Semaphore_GetMetaObject();
}

ObjectRefWord *FUN_002ba7f0(ObjectRefWord *self,int delete_storage) {
    if(self) {
        igObject *object=self->value;
        if(object) {
            --object->_refCount;
            if(((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL)==0)
                igObject_Destroy((void *)object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

void **FUN_002ba870(void **arg0, int arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)(*arg0);
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void **FUN_002ba8f0(void **arg0, short arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)*arg0;
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void **FUN_002ba970(igObject **self, short flag) {
    igObject *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            ((igRefCountWord *)&p->_refCount)->word = ((igRefCountWord *)&p->_refCount)->word - 1;
            if (((igRefCountWord *)&p->_refCount)->bits.count == 0) igObject_Destroy(p);
        }
        if (flag > 0) __dl__FPv(self);
    }
    return (void **)self;
}

