#ifndef DW4_IGVERTEXARRAYLOCK_H
#define DW4_IGVERTEXARRAYLOCK_H

/* One component of a vertex array locked for writing: igVertexArrayLock_Init clears it, the caller
 * picks the component and vertex range, and the array's lock slot fills in the data and stride. */
struct igVertexArrayLock {
    int firstVertex;
    int component;
    int componentIndex;
    unsigned int count;
    char *data;
    unsigned int stride;
    int reserved;
    char *getData() { return data; }
    unsigned int getStride() { return stride; }
};

/* An igVertexArray subclass instance: slot 22 sets the vertex format and count, slots 25 and 26 lock
 * and unlock one vertex component. */
class igVertexArrayView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21();
    virtual void configure(unsigned &format, int vertexCount, int, int);
    virtual void d23(); virtual void d24();
    virtual int lock(igVertexArrayLock *lock, int);
    virtual void unlock(igVertexArrayLock *lock, int);
};

#endif
