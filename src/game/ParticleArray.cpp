#include "dw4/support/reflected.h"
#include "dw4/core/igTDataList.h"
#include "dw4/maths/igVec3f.h"
#include "dw4/maths/igMath.h"
#include "dw4/gfx/igVertexArrayLock.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/scenegraph/igCommonTraversalDispatchView.h"
#include "dw4/gfx/igVisualContextDispatchView.h"
#include "dw4/game/ParticleTimer.h"
#include "dw4/game/ParticleArray.h"
#include "dw4/scenegraph/igAttrStackManager.h"
#include "dw4/scenegraph/igFrustCullTraversal.h"
#include "dw4/scenegraph/igNode.h"
#include "dw4/core/igObject.h"
#include "dw4/scenegraph/igObjectPool.h"
#include "dw4/gfx/igParticleArray.h"
#include "dw4/attrs/igTimeAttr.h"
#include "dw4/scenegraph/igTraversal.h"
#include "dw4/gfx/igVertexArray.h"
#include "dw4/gfx/igVisualContext.h"
#include <math.h>
#include "dw4/maths/igVec4f.h"
#include "dw4/scenegraph/igCommonTraversal.h"
#include "dw4/gfx/igPointSpriteExt.h"

#pragma push
#pragma readonly_strings on


extern "C" {
int ParticleTimer_TraversalFunction(igObject *traversal, igObject *node);
void ParticleTimer_resetFields(ParticleTimer *self, int flags);
int ParticleTimer_Traverse(ParticleTimer *timer, igCommonTraversal *traversal);
void ParticleArray_resetFields(ParticleArray *self);
int ParticleArray_UsesBaseUpdate(ParticleArray *self);
int ParticleArray_Update(ParticleArray *self, unsigned int num, unsigned int offset, int *status, float time);
igMetaObject *ParticleArray_GetMeta(void);
igMetaObject *ParticleTimer_GetMeta(void);
}

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
 * slot 30 the format, and slot 38 whether igParticleArray's own update is enough.
 * ABI view only: never instantiated. */
class igParticleArrayDispatchView : public igObjectDispatchView {
public:
    virtual void configure(int format, unsigned int maxNum, void *context, float lifeStart, float lifeEnd);
    virtual void d22(); virtual void d23();
    virtual Particle *getParticle(unsigned int index);
    virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual igParticleFormat *getParticleFormat();
    virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37();
    virtual int usesBaseUpdate();
};

/* igPointSpriteExt's per-sprite setters.
 * ABI view only: never instantiated. */
class igPointSpriteExtDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void d30(); virtual void d31();
    virtual void setSpriteSizeSpace(int space);
    virtual void configure(igObject *vertexArray, igVertexFormat *format, unsigned int maxNum, int mode);
    virtual void setPosition(unsigned int index, const igVec3f *position);
    virtual void getPosition(unsigned int index, igVec3f *position);
    virtual void setColor(unsigned int index, unsigned int color);
    virtual void d37(); virtual void d38(); virtual void d39();
    virtual void setTexCoord(int unit, unsigned int index, const igVec2f *texCoord);
};


/* Stores a new reference to `object` in an object-reference field, releasing the one it held. */
static inline void assignReference(int &field, igObject *object) {
    if (object != 0) object->_refCount = object->_refCount + 1;
    igObject::release((igObject *)field);
    field = (int)object;
}

/* Gives the point-sprite interface the vertex array it writes the sprites into. */
static inline void setSpriteVertexArray(ParticleArray *self, igObject *array) {
    igPointSpriteExt *sprite = (igPointSpriteExt *)self->_pointSpriteInterface;
    if (array != 0) array->_refCount = array->_refCount + 1;
    igObject::release((igObject *)sprite->_vertexArray);
    sprite->_vertexArray = (int)array;
}

static inline igPointSpriteExtDispatchView *pointSprite(ParticleArray *self) {
    return (igPointSpriteExtDispatchView *)self->_pointSpriteInterface;
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
            assignReference(self->_pointSpriteInterface, ((igVisualContextDispatchView *)self->_context)->GetExtension("igPointSpriteExt"));
        }
    }
}

int ParticleTimer_TraversalFunction(igObject *traversal, igObject *node) {
    igCommonTraversal *common;
    ParticleTimer *timer;
    if (traversal != 0 && ((Gap::Core::igObject *)traversal)->isOfType(g_igCommonTraversal_metaObject) != 0) {
        common = (igCommonTraversal *)traversal;
    } else {
        common = 0;
    }
    if (node != 0 && ((Gap::Core::igObject *)node)->isOfType(g_ParticleTimer_metaObject) != 0) {
        timer = (ParticleTimer *)node;
    } else {
        timer = 0;
    }
    return (common != 0 && timer != 0) ? ParticleTimer_Traverse(timer, common) : 0;
}

void ParticleTimer_RegisterTraversalFunction(void) {
    igTraversal_RegisterFunction((igTraversalFunctionList *)g_igCommonTraversal_travProcs, ParticleTimer_GetMetaObject(), (void *)ParticleTimer_TraversalFunction);
}

void ParticleTimer_resetFields(ParticleTimer *self, int flags)
{
    Gap__Sg__igNode__resetFields((igNode *)self, flags);
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

    now = ((igCommonTraversalDispatchView *)traversal)->getTime();
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
        igObjectPool_Grow((igObjectPool *)pool, (igObject *(*)(int))Gap::Attrs::igTimeAttr::_instantiateFromPool);
    }
    index = pool->_freeIndex;
    pool->_freeIndex = index + 1;
    attr = ((igTimeAttr **)pool->_data)[index];
    attr->_time = elapsed;
    ((igCommonTraversalDispatchView *)traversal)->pushTime(elapsed);
    attrIndex = &attr->_cachedAttrIndex;
    unitID = &attr->_cachedUnitID;
    stack = (igTDataList<igTimeAttr *> *)stacks->_attrStacks;
    stackIndex = *attrIndex;
    stackIndex = *unitID + ((int *)stacks->_attrStackIndexTable)[stackIndex];
    stack = ((igTDataList<igTimeAttr *> **)stack->_data)[stackIndex];
    stack->append(attr);
    igAttrStackManager_MarkStackChanged(stacks, (igAttrStack *)stack, stackIndex);
    result = igCommonTraversal_TraverseGeometry(traversal, (igGeometry *)timer);
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
    ((igCommonTraversalDispatchView *)traversal)->popTime();
    return result;
}

void ParticleArray_resetFields(ParticleArray *self) {
    Gap__Gfx__igParticleArray__resetFields((igParticleArray *)self);
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
    if (((igParticleArrayDispatchView *)self)->usesBaseUpdate()) {
        return igParticleArray_Update((igParticleArray *)self, num, offset, status, self->_currentTime);
    }
    if (self->_context == 0) {
        createContext(self);
        if (self->_context != 0) {
            if (!self->_configured) {
                ((igParticleArrayDispatchView *)self)->configure(self->_particleFormat, self->_maxNum, (void *)self->_context, self->_particleLifeStart, self->_particleLifeEnd);
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
        assignReference(self->_pointSpriteInterface, ((igVisualContextDispatchView *)self->_context)->GetExtension("igPointSpriteExt"));
    }
    if (self->_vertexArray1 == 0) {
        int allocator = (int)((Gap::Core::igObject *)self)->getMemoryPool();
        igObject::release((igObject *)self->_vertexArray1);
        self->_vertexArray1 = (int)Gap::Gfx::igVertexArray::_instantiateFromPool((igMemoryPoolView *)allocator);
        allocator = (int)((Gap::Core::igObject *)self)->getMemoryPool();
        igObject::release((igObject *)self->_vertexArray2);
        self->_vertexArray2 = (int)Gap::Gfx::igVertexArray::_instantiateFromPool((igMemoryPoolView *)allocator);
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
    int sizeSpace = ((igParticleArrayDispatchView *)self)->getParticleFormat()->_spriteSpace;
    pointSprite(self)->setSpriteSizeSpace(sizeSpace);
    for (unsigned int i = offset; i < offset + num; i++) {
        Particle *particle = ((igParticleArrayDispatchView *)self)->getParticle(i);
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
            pointSprite(self)->setColor(i, igVec4f_PackColor((const float *)&color, 1));
        }
        if (*constantsWritten == 0 || isAnimated((igGfxParticleCoord)particleFormat(self)->_width) || isAnimated((igGfxParticleCoord)particleFormat(self)->_height)) {
            size = particle->size + particle->sizeVelocity * age + particle->sizeAcceleration * age2;
            igPointSpriteExt_SetSize((igPointSpriteExt *)self->_pointSpriteInterface, i, size);
        }
        if (*constantsWritten == 0 || isAnimated((igGfxParticleCoord)particleFormat(self)->_textureCoord)) {
            texCoord0 = particle->texCoord0 + particle->texCoord0Velocity * age + particle->texCoord0Acceleration * age2;
            float count = self->_xImageCount;
            if (!(count <= 1.0f)) texCoord0[0] -= fmod(texCoord0[0], 1.0f / count);
            count = self->_yImageCount;
            if (!(count <= 1.0f)) texCoord0[1] -= fmod(texCoord0[1], 1.0f / count);
            pointSprite(self)->setTexCoord(0, i, &texCoord0);
            texCoord1 = particle->texCoord1 + particle->texCoord1Velocity * age + particle->texCoord1Acceleration * age2;
            count = self->_xImageCount;
            if (!(count <= 1.0f)) texCoord1[0] -= fmod(texCoord1[0], 1.0f / count);
            count = self->_yImageCount;
            if (!(count <= 1.0f)) texCoord1[1] -= fmod(texCoord1[1], 1.0f / count);
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
