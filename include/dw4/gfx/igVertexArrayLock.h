#ifndef DW4_IGVERTEXARRAYLOCK_H
#define DW4_IGVERTEXARRAYLOCK_H

/* The vertex components (alchemy-kit_202309 igGfx/igGfx.h). */
enum IG_GFX_VERTEX_COMPONENT {
    IG_GFX_POSITION,
    IG_GFX_NORMAL,
    IG_GFX_COLOR,
    IG_GFX_TEXTURE_COORD,
    IG_GFX_BLEND_WEIGHT,
    IG_GFX_BLEND_INDEX,
    IG_GFX_POINT_SPRITE_SIZE,
    IG_GFX_BINORMAL,
    IG_GFX_TANGENT
};

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
    int getComponentIndex() const { return componentIndex; }
    /* The kit's igVertexComponent::setType (alchemy-kit_202309 igGfx/igVertexArray.h): the lock's first two words
     * are the kit's igVertexComponent, the component's index then its type, and setType stores the type first. */
    void setType(IG_GFX_VERTEX_COMPONENT type, unsigned int index = 0) {
        component = type;
        firstVertex = index;
    }
};

extern "C" igVertexArrayLock *igVertexArrayLock_Init(igVertexArrayLock *lock);

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
