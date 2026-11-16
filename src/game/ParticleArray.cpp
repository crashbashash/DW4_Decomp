#include "dw4/reflected.h"
#include "dw4/igTDataList.h"
#include "dw4/igVec3f.h"
#include "dw4/igMath.h"
#include "dw4/igVertexArrayLock.h"
#include "dw4/igSmartPointer.h"

#pragma push
#pragma readonly_strings on

extern "C" double fmod(double, double);
extern "C" int igObject_IsKindOf(igObject *object, igMetaObject *meta);
extern "C" int igObject_GetAllocator(void *object);
extern "C" int igTraversal_RegisterFunction(int table, igMetaObject *meta, int (*function)(igObject *, igObject *));
extern "C" igMetaObject *ParticleTimer_GetMetaObject(void);
extern "C" void Gap__Sg__igNode__resetFields(void);
extern "C" int igCommonTraversal_TraverseGeometry(igCommonTraversal *traversal, ParticleTimer *timer);
extern "C" void igObjectPool_Grow(igTimeAttrPool *pool, igObject *(*create)(int));
extern "C" igObject *igTimeAttr_CreateInstance(int allocator);
extern "C" void igAttrStackManager_MarkStackChanged(igAttrStackManager *manager, igAttrStack *stack, int index);
extern "C" void Gap__Gfx__igParticleArray__resetFields(void);
extern "C" int igParticleArray_Update(ParticleArray *self, unsigned int num, unsigned int offset, int *status, float time);
extern "C" igObject *igVisualContext_FindFirst(void);
extern "C" igObject *igVertexArray_Create(int allocator);
extern "C" void igVertexArrayLock_Init(igVertexArrayLock *lock);
extern "C" igMetaObject *g_igCommonTraversal_metaObject;
extern "C" igMetaObject *g_ParticleArray_metaObject;
extern "C" igMetaObject *g_ParticleTimer_metaObject;
extern "C" int g_igCommonTraversal_travProcs;

extern "C" {
int ParticleTimer_TraversalFunction(igObject *traversal, igObject *node);
void ParticleTimer_RegisterTraversalFunction(void);
void ParticleTimer_resetFields(void);
int ParticleTimer_Traverse(ParticleTimer *timer, igCommonTraversal *traversal);
void ParticleArray_resetFields(ParticleArray *self);
int ParticleArray_UsesBaseUpdate(ParticleArray *self);
int ParticleArray_Update(ParticleArray *self, unsigned int num, unsigned int offset, int *status, float time);
igMetaObject *ParticleArray_GetMeta(void);
igMetaObject *ParticleTimer_GetMeta(void);
}

/* igCommonTraversal's time stack: slot 24 reads the current time, slot 30 pushes a time and slot 31
 * pops it. */
class igCommonTraversalSlots {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual long long getTime();
    virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void pushTime(long long time);
    virtual void popTime();
};

typedef void (*igAttrPopProc)(igObject *attr, int data, void *proc);

/* Interpolation of one particle attribute over the particle's life (IG_GFX_PARTICLE_COORD). */
enum igGfxParticleCoord {
    IG_GFX_PARTICLE_COORD_NONE,
    IG_GFX_PARTICLE_COORD_CONSTANT,
    IG_GFX_PARTICLE_COORD_LINEAR,
    IG_GFX_PARTICLE_COORD_QUADRATIC
};

/* One particle: each attribute's start value with its velocity and acceleration. */
struct Particle {
    igVec3f position;
    igVec3f velocity;
    igVec3f acceleration;
    igVec4f color;
    igVec4f colorVelocity;
    igVec4f colorAcceleration;
    igVec2f size;
    igVec2f sizeVelocity;
    igVec2f sizeAcceleration;
    igVec2f texCoord0;
    igVec2f texCoord1;
    char f124[20];
    float timeOffset;
    igVec2f texCoord0Velocity;
    igVec2f texCoord0Acceleration;
    igVec2f texCoord1Velocity;
    igVec2f texCoord1Acceleration;
};

/* The vertex layout the point sprites build their arrays with. */
struct igVertexFormat {
    unsigned int bits;
    void setHasPositions(bool on) { if (on) bits |= 1; else bits &= ~1; }
    void setHasColors(bool on) { if (on) bits |= 4; else bits &= ~4; }
    void setTextureCoordCount(unsigned int count) { bits &= ~0xF0000; bits |= (count & 0xF) << 16; }
    void setPointSize(unsigned int size) { bits &= ~0x300000; bits |= (size & 3) << 20; }
};

/* ParticleArray's virtuals: slot 21 configures the array for a format, slot 24 returns a particle,
 * slot 30 the format, and slot 38 whether igParticleArray's own update is enough. */
class ParticleArraySlots {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20();
    virtual void configure(int format, unsigned int maxNum, void *context, float lifeStart, float lifeEnd);
    virtual void d22(); virtual void d23();
    virtual Particle *getParticle(unsigned int index);
    virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual igParticleFormat *getParticleFormat();
    virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37();
    virtual int usesBaseUpdate();
};

/* The visual context's slot 24 looks an extension up by name. */
class igVisualContextSlots {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual igObject *getExtension(const char *name);
};

/* igPointSpriteExt's per-sprite setters. */
class igPointSpriteExtSlots {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void d30(); virtual void d31();
    virtual void setSpriteSizeSpace(int space);
    virtual void configure(igObject *vertexArray, igVertexFormat *format, unsigned int maxNum, int mode);
    virtual void setPosition(unsigned int index, const igVec3f *position);
    virtual void getPosition(unsigned int index, igVec3f *position);
    virtual void setColor(unsigned int index, unsigned int color);
    virtual void d37(); virtual void d38(); virtual void d39();
    virtual void setTexCoord(int unit, unsigned int index, const igVec2f *texCoord);
};

extern "C" unsigned int igVec4f_PackColor(const igVec4f *color, int format);
extern "C" void igPointSpriteExt_SetSize(igPointSpriteExt *sprite, unsigned int index, igVec2f size);

/* Stores a new reference to `object` in an object-reference field, releasing the one it held. */
static inline void assignReference(int &field, igObject *object) {
    if (object != 0) object->_refCount = object->_refCount + 1;
    igRelease((igObject *)field);
    field = (int)object;
}

/* Gives the point-sprite interface the vertex array it writes the sprites into. */
static inline void setSpriteVertexArray(ParticleArray *self, igObject *array) {
    igPointSpriteExt *sprite = (igPointSpriteExt *)self->_pointSpriteInterface;
    if (array != 0) array->_refCount = array->_refCount + 1;
    igRelease((igObject *)sprite->_vertexArray);
    sprite->_vertexArray = (int)array;
}

static inline igPointSpriteExtSlots *pointSprite(ParticleArray *self) {
    return (igPointSpriteExtSlots *)self->_pointSpriteInterface;
}

static inline igParticleFormat *particleFormat(ParticleArray *self) {
    return (igParticleFormat *)self->_particleFormat;
}

/* Whether an attribute moves over the particle's life rather than keeping its start value. */
static inline bool isAnimated(igGfxParticleCoord coord) {
    return coord > IG_GFX_PARTICLE_COORD_CONSTANT;
}

/* Finds the visual context, and the point-sprite extension when the format draws sprites. */
static inline void createContext(ParticleArray *self) {
    if (self->_context == 0) {
        assignReference(self->_context, igVisualContext_FindFirst());
        if (self->_configured && particleFormat(self)->_spriteType != 0 && self->_pointSpriteInterface == 0) {
            assignReference(self->_pointSpriteInterface, ((igVisualContextSlots *)self->_context)->getExtension("igPointSpriteExt"));
        }
    }
}

int ParticleTimer_TraversalFunction(igObject *traversal, igObject *node) {
    igCommonTraversal *common;
    ParticleTimer *timer;
    if (traversal != 0 && igObject_IsKindOf(traversal, g_igCommonTraversal_metaObject) != 0) {
        common = (igCommonTraversal *)traversal;
    } else {
        common = 0;
    }
    if (node != 0 && igObject_IsKindOf(node, g_ParticleTimer_metaObject) != 0) {
        timer = (ParticleTimer *)node;
    } else {
        timer = 0;
    }
    return (common != 0 && timer != 0) ? ParticleTimer_Traverse(timer, common) : 0;
}

void ParticleTimer_RegisterTraversalFunction(void) {
    igTraversal_RegisterFunction(g_igCommonTraversal_travProcs, ParticleTimer_GetMetaObject(), ParticleTimer_TraversalFunction);
}

void ParticleTimer_resetFields(void)
{
    Gap__Sg__igNode__resetFields();
}

int ParticleTimer_Traverse(ParticleTimer *timer, igCommonTraversal *traversal)
{
    long long now;
    long long elapsed;
    igTimeAttrPool *pool;
    igAttrStackManager *stacks;
    igTimeAttr *attr;
    int index;
    igTDataList<igTimeAttr *> *stack;
    int stackIndex;
    int result;
    int popIndex;
    igAttrStack *popStack;
    igAttrPopProc pop;
    igObject *top;
    int topIndex;
    igObject **attrs;
    short *attrIndex;
    short *unitID;

    now = ((igCommonTraversalSlots *)traversal)->getTime();
    if (timer->_time == -1) {
        timer->_timeBias = now;
    }
    if (timer->_timeRunning == 0) {
        timer->_timeBias = timer->_timeBias + (now - timer->_time);
    }
    timer->_time = now;
    elapsed = timer->_time - timer->_timeBias;
    pool = (igTimeAttrPool *)traversal->_timePool;
    stacks = (igAttrStackManager *)traversal->_attrStack;
    if (pool->_freeIndex >= pool->_count) {
        igObjectPool_Grow(pool, igTimeAttr_CreateInstance);
    }
    index = pool->_freeIndex;
    pool->_freeIndex = index + 1;
    attr = ((igTimeAttr **)pool->_data)[index];
    attr->_time = elapsed;
    ((igCommonTraversalSlots *)traversal)->pushTime(elapsed);
    attrIndex = &attr->_cachedAttrIndex;
    unitID = &attr->_cachedUnitID;
    stack = (igTDataList<igTimeAttr *> *)stacks->_attrStacks;
    stackIndex = *attrIndex;
    stackIndex = *unitID + ((int *)stacks->_attrStackIndexTable)[stackIndex];
    stack = ((igTDataList<igTimeAttr *> **)stack->_data)[stackIndex];
    stack->append(attr);
    igAttrStackManager_MarkStackChanged(stacks, (igAttrStack *)stack, stackIndex);
    result = igCommonTraversal_TraverseGeometry(traversal, timer);
    popIndex = *unitID + ((int *)stacks->_attrStackIndexTable)[*attrIndex];
    popStack = ((igAttrStack **)((igAttrStackList *)stacks->_attrStacks)->_data)[popIndex];
    topIndex = popStack->_count - 1;
    attrs = (igObject **)popStack->_data;
    pop = (igAttrPopProc)popStack->_popProc;
    top = attrs[topIndex];
    if (pop != 0) {
        pop(top, stacks->_popProcData, (void *)pop);
    }
    popStack->_count = popStack->_count - 1;
    igAttrStackManager_MarkStackChanged(stacks, popStack, popIndex);
    ((igCommonTraversalSlots *)traversal)->popTime();
    return result;
}

void ParticleArray_resetFields(ParticleArray *self) {
    Gap__Gfx__igParticleArray__resetFields();
    if (self->_particleDataSize == 0) {
        self->_particleDataSize = sizeof(Particle);
    }
}

int ParticleArray_UsesBaseUpdate(ParticleArray *self) {
    int extended = self->_hasTextureCoordinates != 0;
    if (!extended) extended = self->_continuousTime != 0;
    return extended ^ 1;
}

int ParticleArray_Update(ParticleArray *self, unsigned int num, unsigned int offset, int *status, float time) {
    if (self->_loopTime) time = fmod(time, self->_startOffset + self->_particleLifeEnd);
    self->_currentTime = time;
    float start = self->_startOffset;
    if (!(time <= start + self->_particleLifeEnd)) {
        *status = 1;
        return 1;
    }
    if (time < start) {
        *status = 2;
        return 1;
    }
    self->_currentTime -= start;
    if (((ParticleArraySlots *)self)->usesBaseUpdate()) {
        return igParticleArray_Update(self, num, offset, status, self->_currentTime);
    }
    if (self->_context == 0) {
        createContext(self);
        if (self->_context != 0) {
            if (!self->_configured) {
                ((ParticleArraySlots *)self)->configure(self->_particleFormat, self->_maxNum, (void *)self->_context, self->_particleLifeStart, self->_particleLifeEnd);
            }
        } else {
            *status = 1;
            return 0;
        }
    }
    self->_particleNum = num;
    self->_particleOffset = offset;
    self->_aliveParticleNum = num;
    if (self->_pointSpriteInterface == 0) {
        assignReference(self->_pointSpriteInterface, ((igVisualContextSlots *)self->_context)->getExtension("igPointSpriteExt"));
    }
    if (self->_vertexArray1 == 0) {
        int allocator = igObject_GetAllocator(self);
        igRelease((igObject *)self->_vertexArray1);
        self->_vertexArray1 = (int)igVertexArray_Create(allocator);
        allocator = igObject_GetAllocator(self);
        igRelease((igObject *)self->_vertexArray2);
        self->_vertexArray2 = (int)igVertexArray_Create(allocator);
        igVertexFormat format;
        format.bits = 0;
        format.setHasPositions(true);
        format.setHasColors(true);
        if (particleFormat(self)->_textureCoord != IG_GFX_PARTICLE_COORD_NONE) format.setTextureCoordCount(1);
        format.setPointSize(2);
        pointSprite(self)->configure((igObject *)self->_vertexArray1, &format, self->_maxNum, 4);
        pointSprite(self)->configure((igObject *)self->_vertexArray2, &format, self->_maxNum, 4);
        setSpriteVertexArray(self, (igObject *)self->_vertexArray1);
        assignReference(self->_internalVertexArray, (igObject *)self->_vertexArray1);
    }
    igVertexArrayLock lock;
    igVertexArrayLock_Init(&lock);
    lock.component = 0;
    lock.firstVertex = 0;
    ((igVertexArrayView *)self->_internalVertexArray)->lock(&lock, 1);
    ((igVertexArrayView *)self->_internalVertexArray)->unlock(&lock, 2);
    self->_whichVertexArray = !self->_whichVertexArray;
    int &nextArray = self->_whichVertexArray ? self->_vertexArray2 : self->_vertexArray1;
    assignReference(self->_internalVertexArray, (igObject *)nextArray);
    unsigned char *constantsWritten = self->_whichVertexArray ? &self->_setConstant2 : &self->_setConstant1;
    setSpriteVertexArray(self, (igObject *)self->_internalVertexArray);
    int sizeSpace = ((ParticleArraySlots *)self)->getParticleFormat()->_spriteSpace;
    pointSprite(self)->setSpriteSizeSpace(sizeSpace);
    for (unsigned int i = offset; i < offset + num; i++) {
        Particle *particle = ((ParticleArraySlots *)self)->getParticle(i);
        igVec3f position;
        igVec4f color;
        igVec2f size;
        igVec2f texCoord0;
        igVec2f texCoord1;
        float age = particle->timeOffset ? (float)fmod(self->_currentTime + particle->timeOffset, self->_particleLifeEnd) : self->_currentTime;
        float age2 = age * age;
        position = particle->position + particle->velocity * age + particle->acceleration * age2;
        pointSprite(self)->setPosition(i, &position);
        if (*constantsWritten == 0 || isAnimated((igGfxParticleCoord)particleFormat(self)->_color)) {
            color = particle->color + particle->colorVelocity * age + particle->colorAcceleration * age2;
            pointSprite(self)->setColor(i, igVec4f_PackColor(&color, 1));
        }
        if (*constantsWritten == 0 || isAnimated((igGfxParticleCoord)particleFormat(self)->_width) || isAnimated((igGfxParticleCoord)particleFormat(self)->_height)) {
            size = particle->size + particle->sizeVelocity * age + particle->sizeAcceleration * age2;
            igPointSpriteExt_SetSize((igPointSpriteExt *)self->_pointSpriteInterface, i, size);
        }
        if (*constantsWritten == 0 || isAnimated((igGfxParticleCoord)particleFormat(self)->_textureCoord)) {
            texCoord0 = particle->texCoord0 + particle->texCoord0Velocity * age + particle->texCoord0Acceleration * age2;
            float count = self->_xImageCount;
            if (!(count <= 1.0f)) texCoord0.x -= fmod(texCoord0.x, 1.0f / count);
            count = self->_yImageCount;
            if (!(count <= 1.0f)) texCoord0.y -= fmod(texCoord0.y, 1.0f / count);
            pointSprite(self)->setTexCoord(0, i, &texCoord0);
            texCoord1 = particle->texCoord1 + particle->texCoord1Velocity * age + particle->texCoord1Acceleration * age2;
            count = self->_xImageCount;
            if (!(count <= 1.0f)) texCoord1.x -= fmod(texCoord1.x, 1.0f / count);
            count = self->_yImageCount;
            if (!(count <= 1.0f)) texCoord1.y -= fmod(texCoord1.y, 1.0f / count);
            pointSprite(self)->setTexCoord(1, i, &texCoord1);
        }
    }
    setSpriteVertexArray(self, 0);
    *constantsWritten = 1;
    *status = 0;
    return 1;
}

igMetaObject *ParticleArray_GetMeta(void)
{
    return g_ParticleArray_metaObject;
}

igMetaObject *ParticleTimer_GetMeta(void)
{
    return g_ParticleTimer_metaObject;
}

#pragma pop
