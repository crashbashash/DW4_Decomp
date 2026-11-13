#include "dw4/reflected.h"
#include "dw4/igobject_release.h"

/* An RGBA colour in floats, as Color4f_Unpack writes it. */
struct Color4f { float x, y, z, w; };

/* The override attributes FLASHSET and FADESET put on a node (igColorAttr, igBlendStateAttr,
 * igTextureStateAttr, igLightingStateAttr) all take their value through slot 30. */
class OverrideAttr {
public:
    virtual void vfunc_00(); virtual void vfunc_01(); virtual void vfunc_02(); virtual void vfunc_03();
    virtual void vfunc_04(); virtual void vfunc_05(); virtual void vfunc_06(); virtual void vfunc_07();
    virtual void vfunc_08(); virtual void vfunc_09(); virtual void vfunc_10(); virtual void vfunc_11();
    virtual void vfunc_12(); virtual void vfunc_13(); virtual void vfunc_14(); virtual void vfunc_15();
    virtual void vfunc_16(); virtual void vfunc_17(); virtual void vfunc_18(); virtual void vfunc_19();
    virtual void vfunc_20(); virtual void vfunc_21(); virtual void vfunc_22(); virtual void vfunc_23();
    virtual void vfunc_24(); virtual void vfunc_25(); virtual void vfunc_26(); virtual void vfunc_27();
    virtual void vfunc_28(); virtual void vfunc_29();
    virtual void SetValue(void *value);
};

/* The system's random source; slot 22 returns the next number. */
class RandomSource {
public:
    virtual void vfunc_00(); virtual void vfunc_01(); virtual void vfunc_02(); virtual void vfunc_03();
    virtual void vfunc_04(); virtual void vfunc_05(); virtual void vfunc_06(); virtual void vfunc_07();
    virtual void vfunc_08(); virtual void vfunc_09(); virtual void vfunc_10(); virtual void vfunc_11();
    virtual void vfunc_12(); virtual void vfunc_13(); virtual void vfunc_14(); virtual void vfunc_15();
    virtual void vfunc_16(); virtual void vfunc_17(); virtual void vfunc_18(); virtual void vfunc_19();
    virtual void vfunc_20(); virtual void vfunc_21();
    virtual unsigned Next();
};

/* matching construct: igObjectList-shaped component list with a pointer-typed buffer; reflected
 * igObjectList._data (int) changes retail register allocation */
struct Action2ComponentList {
    char _pad0[8];
    int _count;
    int _capacity;
    struct Action2Component **_data;
};

/* A beAction2Data component; only slot 20 (GetMetaObject) is called. */
class Action2Component {
public:
    virtual void vfunc_00(); virtual void vfunc_01(); virtual void vfunc_02(); virtual void vfunc_03();
    virtual void vfunc_04(); virtual void vfunc_05(); virtual void vfunc_06(); virtual void vfunc_07();
    virtual void vfunc_08(); virtual void vfunc_09(); virtual void vfunc_10(); virtual void vfunc_11();
    virtual void vfunc_12(); virtual void vfunc_13(); virtual void vfunc_14(); virtual void vfunc_15();
    virtual void vfunc_16(); virtual void vfunc_17(); virtual void vfunc_18(); virtual void vfunc_19();
    virtual int GetMetaObject();
};

/* matching construct: the guard reads the list through its own view, so its load stays apart from
 * the loads in the loop. */
struct Action2DataGuardView : beAction2Data {};

/* igObject and igActor calls the message handler makes through their vtables. */
class VirtualObject {
public:
    virtual void vfunc_00(); virtual void vfunc_01(); virtual void vfunc_02(); virtual void vfunc_03();
    virtual void vfunc_04(); virtual void vfunc_05(); virtual void vfunc_06(); virtual void vfunc_07();
    virtual void vfunc_08(); virtual void vfunc_09(); virtual void vfunc_10(); virtual void vfunc_11();
    virtual void vfunc_12(); virtual void vfunc_13(); virtual void vfunc_14(); virtual void vfunc_15();
    virtual void vfunc_16(); virtual void vfunc_17(); virtual void vfunc_18(); virtual void vfunc_19();
    virtual int GetMetaObject();
    virtual void vfunc_21(); virtual void vfunc_22(); virtual void vfunc_23(); virtual void vfunc_24();
    virtual int FindBoneIndex(int name);
    virtual int GetBoneMatrix(int index);
};

/* Owning stack reference to a freshly created override attribute (colour 0, blend state 1,
 * lighting state 2, texture state 3); one class per kind so each gets its own out-of-line
 * destructor. */
template <int kind> struct AttrRef {
    igObject *p;
    AttrRef(igObject *o) : p(o) {}
    ~AttrRef() {
        igObject *object = p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};

/* The message handler's owning reference to the action's work record; its release is inlined at
 * each return. */
struct WorkRef {
    beAction2InfoWork *p;
    inline ~WorkRef();
};

/* Clears or sets bit n of a bit mask, ignoring a word outside the mask. */
static inline void ClearMaskBit(igBitMask *mask, unsigned int n) {
    unsigned int word = n >> 5;
    int bit = 1 << (n & 0x1F);
    int *pw = (int *)mask->_data + word;
    int count = mask->_count;
    int next = ~bit & *pw;
    if (count != 0 && (int)word >= 0 && (int)word < count) {
        *pw = next;
    }
}

static inline void SetMaskBit(igBitMask *mask, unsigned int n) {
    unsigned int word = n >> 5;
    int bit = 1 << (n & 0x1F);
    int *pw = (int *)mask->_data + word;
    int count = mask->_count;
    int next = bit | *pw;
    if (count != 0 && (int)word >= 0 && (int)word < count) {
        *pw = next;
    }
}

extern "C" {
int beMessenger_RegisterReceiverFromInfo(int messenger, beAction2InfoRam *ram, int *name);
int beBaseInfoRam_IsTimerExpired(beAction2InfoRam *ram, int *name);
int beBaseInfoRam_RemoveTimer(beAction2InfoRam *ram, int *name);
int beBaseInfoRam_StartTimer(beAction2InfoRam *ram, int *name, long long duration);
float beBaseInfoRam_GetTimerFrameDelta(beAction2InfoRam *ram, int *name);
int beBaseInfoRam_SetAllTimerScales(beAction2InfoRam *ram, float scale);
int beBaseInfoRam_RemoveAllTimers(beAction2InfoRam *ram);
int ObjectList_RemoveFirstRetained(int *result, int list, int object, int start);
int ObjectList_AppendRetained(int list, igObject *object);
int igObject_Destroy(void *object);
int igObject_GetAllocator(void *object);
int igObject_IsKindOf(void *object, int meta);
int Memory_GetAllocatorBySelector(int selector);
void Memory_FreeBuffer(int buffer);
void Color4f_Unpack(Color4f *out, unsigned int format, unsigned int packed);
void *igTextureStateAttr_CreateInstance(int allocator);
void *igLightingStateAttr_CreateInstance(int allocator);
void *igColorAttr_CreateInstance(int allocator);
void *igBlendStateAttr_CreateInstance(int allocator);
void *beAction2InfoWork_CreateInstance(void *allocator);
long long beModelCtrlNode2_LocalTime(int node, long long now);
int UnsignedDivMod64_Cached(long long dividend, long long divisor, long long *remainder);
void igAnimationState_UpdateLocalTime(void *state, long long now);
long long __fixsfdi(float);
int igAnimationCombiner_Update(void *combiner, long long now);
void *igProperty_FindByName(int list, int field, int name);
int igAnimationCombiner_AddAnimationBlend(void *combiner, void *animation, int combineMode, int transitionMode, int status, int *priority, int perBone, long long transitionTime, float startRatio, float endRatio, int startTime);
int igAnimationCombiner_ResetToPose(void *combiner, void *from);
int igAnimationCombiner_RemoveAllStates(int combiner);
int igAnimationCombiner_AddAnimation(void *combiner, int animation, int combineMode, int transitionMode, int status);
int igActor_SetAnimationSystem(void *actor, void *combiner);
int beAction2_GetMessageEnum(void);
unsigned int beMessenger_ResolveEnumValue(int messenger, int enumeration, void *name);
void beMessenger_AppendBool(int messenger, unsigned char value);
int beMessenger_AppendObject(int messenger, int object);
int beMessenger_AppendMatrix(int messenger, int matrix);
int beMessenger_AppendString(int messenger, void *text);
int beMessenger_GetString(int messenger, int index);
int beMessenger_SendNamed(int messenger, void *message, void *sender, int ramNo, void *name);
int strcmp(void *, void *);
int List_Reserve(void *list, int count, int capacity);
void *igMetaObject_FindFieldByName(int meta, void *name);

void beAction2_Prepare(void);
int beAction2_GetInfoMeta(void);
void beAction2_RegisterReceiver(beAction2 *self, beAction2InfoRam *ram);
void beAction2FLASHSET_Update(beAction2 *manager, beAction2InfoRam *ram);
int beAction2FLASHSET_Start(beAction2 *manager, beAction2InfoRam *ram, beAction2FLASHSET *component);
void beAction2WAITCHECK_Update(beAction2 *manager, beAction2InfoRam *ram);
int beAction2WAITCHECK_Start(beAction2 *manager, beAction2InfoRam *ram, beAction2WAITCHECK *component);
void beAction2FADESET_Update(beAction2 *manager, beAction2InfoRam *ram);
int beAction2FADESET_Start(beAction2 *manager, beAction2InfoRam *ram, beAction2FADESET *component);
void beAction2JOINTSET_Update(beAction2 *manager, beAction2InfoRam *ram);
int beAction2JOINTSET_Start(beAction2 *manager, beAction2InfoRam *ram, beAction2JOINTSET *component);
void beAction2MOTIONSET_Update(beAction2 *manager, beAction2InfoRam *ram);
int beAction2MOTIONSET_Start(beAction2 *manager, beAction2InfoRam *ram, beAction2MOTIONSET *component);
void beAction2_StartComponents(beAction2 *manager, beAction2InfoRam *ram);
void beAction2_Update(beAction2 *self, beAction2InfoRam *ram);
int beAction2_OnMessage(beAction2 *self, beAction2InfoRam *ram, void *name);
int beAction2_GetMeta(void);
void Gap__Core__igObject__vfunc_28(void);
int Gap__Core__igObject__vfunc_34(void);

extern int g_beAction2Info_metaObject[4];
extern int g_beAction2_metaObject[4];
extern int g_beAction2FLASHSET_metaObject[4];
extern int g_beAction2WAITCHECK_metaObject[4];
extern int g_beAction2FADESET_metaObject[4];
extern int g_beAction2JOINTSET_metaObject[4];
extern int g_beAction2MOTIONSET_metaObject[4];
extern int g_igEnbayaTransformSource_metaObject[4];
extern int g_propertyNameField[4];
extern int g_defaultAllocatorSelector[4];
extern unsigned char g_useOwnerAllocator;
extern float g_enbayaPlayOnceEndOffset[4];
extern float g_randomWaitMinimum[4];
extern int emptyString[4];
extern int ACTION[4];
extern int FLASH[4];
extern int WAIT[4];
extern int FADE[4];
extern int NDSP[4];
extern int boneMatrixCacheArray[4];
extern int blendMatrixCacheArray[4];
extern int ACTION_BROADCAST[4];
}

/* Slot 32, called before the manager starts and before it drops its infos: nothing to do here. */
void beAction2_Prepare(void)
{
}

int beAction2_GetInfoMeta(void)
{
    return g_beAction2Info_metaObject[0];
}

/* Registers the ram as the receiver of ACTION messages and clears its running flag. */
void beAction2_RegisterReceiver(beAction2 *self, beAction2InfoRam *ram) {
    beMessenger_RegisterReceiverFromInfo(self->_messenger, ram, ACTION);
    ram->_isRun = 0;
    g_enbayaPlayOnceEndOffset[0] = -1.0f / 30.0f;
}

/* When the FLASH timer runs out, takes the flash's override attributes back off the node. */
void beAction2FLASHSET_Update(beAction2 *manager, beAction2InfoRam *ram) {
    int removed2;
    int removed1;
    int removed0;
    beAction2InfoWork *work;
    int list;
    igObject *attr;
    work = (beAction2InfoWork *)ram->_work;
    switch (work->_flashSt0) {
    case 0:
        break;
    case 1:
        if (beBaseInfoRam_IsTimerExpired(ram, &FLASH[0]) != 0) {
            list = ((beModelCtrlNode2 *)ram->_node)->_overrideAttrList;
            if (work->_blendStateAttr == 0) {
                ObjectList_RemoveFirstRetained(&removed2, list, work->_colorAttr, 0);
                attr = (igObject *)work->_colorAttr;
                IG_OBJECT_RELEASE(attr);
                work->_colorAttr = 0;
                ObjectList_RemoveFirstRetained(&removed1, list, work->_lightingStateAttr, 0);
                attr = (igObject *)work->_lightingStateAttr;
                IG_OBJECT_RELEASE(attr);
                work->_lightingStateAttr = 0;
            }
            ObjectList_RemoveFirstRetained(&removed0, list, work->_textureStateAttr, 0);
            attr = (igObject *)work->_textureStateAttr;
            IG_OBJECT_RELEASE(attr);
            work->_textureStateAttr = 0;
            beBaseInfoRam_RemoveTimer(ram, &FLASH[0]);
            work->_flashSt0 = 0;
        }
    }
}

/* Puts colour, texture-state and lighting-state overrides on the node (creating the missing ones),
 * sets the colour's red and green to full with texturing and lighting off, and flashes for four
 * frames. */
int beAction2FLASHSET_Start(beAction2 *manager, beAction2InfoRam *ram, beAction2FLASHSET *component) {
    beAction2InfoWork *work = (beAction2InfoWork *)ram->_work;
    int list = ((beModelCtrlNode2 *)ram->_node)->_overrideAttrList;
    if (work->_colorAttr == 0) {
        int ownerAllocator = igObject_GetAllocator(manager);
        int allocator = g_useOwnerAllocator ? ownerAllocator : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        AttrRef<0> created((igObject *)igColorAttr_CreateInstance(allocator));
        igObject *attr;
        igObject *old;
        ObjectList_AppendRetained(list, created.p);
        attr = created.p;
        if (attr != 0) attr->_refCount = attr->_refCount + 1;
        old = (igObject *)work->_colorAttr;
        IG_OBJECT_RELEASE(old);
        work->_colorAttr = (int)attr;
    }
    if (work->_textureStateAttr == 0) {
        int ownerAllocator = igObject_GetAllocator(manager);
        int allocator = g_useOwnerAllocator ? ownerAllocator : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        AttrRef<3> created((igObject *)igTextureStateAttr_CreateInstance(allocator));
        igObject *attr;
        igObject *old;
        ObjectList_AppendRetained(list, created.p);
        attr = created.p;
        if (attr != 0) attr->_refCount = attr->_refCount + 1;
        old = (igObject *)work->_textureStateAttr;
        IG_OBJECT_RELEASE(old);
        work->_textureStateAttr = (int)attr;
    }
    if (work->_lightingStateAttr == 0) {
        int ownerAllocator = igObject_GetAllocator(manager);
        int allocator = g_useOwnerAllocator ? ownerAllocator : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        AttrRef<2> created((igObject *)igLightingStateAttr_CreateInstance(allocator));
        igObject *attr;
        igObject *old;
        ObjectList_AppendRetained(list, created.p);
        attr = created.p;
        if (attr != 0) attr->_refCount = attr->_refCount + 1;
        old = (igObject *)work->_lightingStateAttr;
        IG_OBJECT_RELEASE(old);
        work->_lightingStateAttr = (int)attr;
    }
    Color4f color;
    Color4f_Unpack(&color, 1, ((igColorAttr *)work->_colorAttr)->_colorPacked);
    color.y = 1.0f;
    color.x = 1.0f;
    ((OverrideAttr *)work->_colorAttr)->SetValue(&color);
    ((OverrideAttr *)work->_textureStateAttr)->SetValue(0);
    ((OverrideAttr *)work->_lightingStateAttr)->SetValue(0);
    work->_flashSt0 = 1;
    beBaseInfoRam_StartTimer(ram, &FLASH[0], 66666668);
    return 1;
}

/* Waits for the pending WAITCHECK condition (1 the WAIT timer, 2 the motion's end, 3 the JOINTSET
 * end), then clears it and resumes the component list. */
void beAction2WAITCHECK_Update(beAction2 *manager, beAction2InfoRam *ram) {
    unsigned long long duration;
    beAction2InfoWork *work;
    igAnimationState *state;
    long long startTime;
    long long offset;
    igAnimation *animation;
    beAction2Info *info;
    igAnimationStateList *states;
    work = (beAction2InfoWork *)ram->_work;
    info = (beAction2Info *)ram->_parentInfo;
    switch (work->_waitSt0) {
    case 1:
        if (beBaseInfoRam_IsTimerExpired(ram, &WAIT[0]) != 0) {
            work->_waitSt0 = 0;
            beAction2_StartComponents(manager, ram);
        }
        break;
    case 2:
        states = (igAnimationStateList *)((igAnimationCombiner *)((int *)((igObjectList *)((igAnimationDatabase *)info->_animationDatabase)->_combinerList)->_data)[ram->_ramNo])->_animationStateList;
        if (states->_count == 1) {
            state = (igAnimationState *)((int *)states->_data)[0];
            animation = (igAnimation *)state->_animation;
            offset = state->_localTime - animation->_keyFrameTimeOffset;
            duration = animation->_duration;
            startTime = animation->_startTime;
            if (duration != 0) {
                long long remainder;
                UnsignedDivMod64_Cached(offset - startTime, duration, &remainder);
                remainder += startTime;
            }
            igAnimationState_UpdateLocalTime(state, beModelCtrlNode2_LocalTime(ram->_node, ((igInsightCore *)manager->_insight)->_worldTime));
            if (duration <= state->_localTime) {
                work->_waitSt0 = 0;
                beAction2_StartComponents(manager, ram);
            }
        }
        break;
    case 3:
        if (work->_jointIsEnd != 0) {
            work->_waitSt0 = 0;
            beAction2_StartComponents(manager, ram);
        }
        break;
    }
}

/* Arms the wait the component's type names: Frame (a WAIT timer of the given frames), Motion, Joint,
 * or Random (a timer of a random length between the stored minimum and the given frames; RandomSet
 * stores the minimum and lets the list continue). */
int beAction2WAITCHECK_Start(beAction2 *manager, beAction2InfoRam *ram, beAction2WAITCHECK *component) {
    beAction2InfoWork *work = (beAction2InfoWork *)ram->_work;
    const char *name = (const char *)component->_name;
    float frames = component->_waitTime;
    const char *type = name ? name : ((char *)emptyString);
    switch (*type) {
    case 'R': {
        const char *random = name ? name : ((char *)emptyString);
        unsigned r, range;
        if (random[3] == 'S') {
            g_randomWaitMinimum[0] = frames;
            return 1;
        }
        range = (int)(100.0f * frames - 100.0f * g_randomWaitMinimum[0]);
        r = ((RandomSource *)((beSystem *)manager->_system)->_random)->Next() % range;
        frames = g_randomWaitMinimum[0] + (float)r / 100.0f;
    }
    case 'F':
        beBaseInfoRam_StartTimer(ram, WAIT, __fixsfdi(1e9f * frames / 60.0f));
        work->_waitSt0 = 1;
        break;
    case 'M':
        work->_waitSt0 = 2;
        break;
    case 'J':
        work->_waitSt0 = 3;
        break;
    default:
        break;
    }
    return 0;
}

/* The work record's fade limit, read as its class's const getter reads it. Converting work to a
 * pointer to const makes the limit an operand the compiler evaluates before the faded alpha, which
 * gives retail's register order for the comparison. */
static inline float fadeLimit(const beAction2InfoWork *work) { return work->_fadeLimitValue; }

/* Steps the fade by the frames the FADE timer advanced: state 1 fades in up to the limit, then
 * takes the override attributes off the node; state 2 fades out to zero. Both end in state 3. */
void beAction2FADESET_Update(beAction2 *manager, beAction2InfoRam *ram) {
    beAction2InfoWork *work = (beAction2InfoWork *)ram->_work;
    switch (work->_fadeSt0) {
    case 1: {
        float frames;
        Color4f color;
        float *alpha;
        int list;
        int removed0, removed1, removed2;
        igObject *attr;
        frames = beBaseInfoRam_GetTimerFrameDelta(ram, &FADE[0]);
        if (frames != 0.0f) {
            Color4f_Unpack(&color, 1, ((igColorAttr *)work->_colorAttr)->_colorPacked);
            alpha = &color.w;
            *alpha = work->_fadeValue + frames * work->_fadeAddValue;
            ((OverrideAttr *)work->_colorAttr)->SetValue(&color);
            work->_fadeValue = *alpha;
            if (*alpha >= fadeLimit(work)) {
                list = ((beModelCtrlNode2 *)ram->_node)->_overrideAttrList;
                if (work->_textureStateAttr == 0) {
                    ObjectList_RemoveFirstRetained(&removed0, list, work->_colorAttr, 0);
                    attr = (igObject *)work->_colorAttr;
                    IG_OBJECT_RELEASE(attr);
                    work->_colorAttr = 0;
                    ObjectList_RemoveFirstRetained(&removed1, list, work->_lightingStateAttr, 0);
                    attr = (igObject *)work->_lightingStateAttr;
                    IG_OBJECT_RELEASE(attr);
                    work->_lightingStateAttr = 0;
                }
                ObjectList_RemoveFirstRetained(&removed2, list, work->_blendStateAttr, 0);
                attr = (igObject *)work->_blendStateAttr;
                IG_OBJECT_RELEASE(attr);
                work->_blendStateAttr = 0;
                beBaseInfoRam_RemoveTimer(ram, &FADE[0]);
                work->_fadeSt0 = 3;
            }
        }
        break;
    }
    case 2: {
        float frames;
        Color4f color;
        float *alpha;
        float next;
        frames = beBaseInfoRam_GetTimerFrameDelta(ram, &FADE[0]);
        if (frames != 0.0f) {
            Color4f_Unpack(&color, 1, ((igColorAttr *)work->_colorAttr)->_colorPacked);
            next = work->_fadeValue - frames * work->_fadeAddValue;
            alpha = &color.w;
            *alpha = next;
            if (next < 0.0f) *alpha = 0.0f;
            ((OverrideAttr *)work->_colorAttr)->SetValue(&color);
            work->_fadeValue = *alpha;
            if (*alpha <= 0.0f) {
                beBaseInfoRam_RemoveTimer(ram, &FADE[0]);
                work->_fadeSt0 = 3;
            }
        }
        break;
    }
    }
}

/* A name starting with H hides the ram's child of the info's switch. Otherwise puts colour,
 * blend-state and lighting-state overrides on the node and starts a fade over the given frames:
 * In fades the alpha up from zero to the given value, anything else fades it down from it. */
int beAction2FADESET_Start(beAction2 *manager, beAction2InfoRam *ram, beAction2FADESET *component) {
    beAction2InfoWork *work = (beAction2InfoWork *)ram->_work;
    int list = ((beModelCtrlNode2 *)ram->_node)->_overrideAttrList;
    char *name = (char *)component->_name;
    name = name != 0 ? name : (char *)emptyString;
    if (*name == 'H') {
        beAction2Info *info = (beAction2Info *)ram->_parentInfo;
        igBitMask *mask = (igBitMask *)((igSwitch *)info->_switch)->_childMask;
        ClearMaskBit(mask, ram->_ramNo);
    } else {
        if (work->_colorAttr == 0) {
            int ownerAllocator = igObject_GetAllocator(manager);
            int allocator = g_useOwnerAllocator ? ownerAllocator : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
            igObject *attr;
            igObject *old;
            AttrRef<0> created((igObject *)igColorAttr_CreateInstance(allocator));
            ObjectList_AppendRetained(list, created.p);
            attr = created.p;
            if (attr != 0) attr->_refCount = attr->_refCount + 1;
            old = (igObject *)work->_colorAttr;
            IG_OBJECT_RELEASE(old);
            work->_colorAttr = (int)attr;
        }
        if (work->_blendStateAttr == 0) {
            int ownerAllocator = igObject_GetAllocator(manager);
            int allocator = g_useOwnerAllocator ? ownerAllocator : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
            igObject *attr;
            igObject *old;
            AttrRef<1> created((igObject *)igBlendStateAttr_CreateInstance(allocator));
            ObjectList_AppendRetained(list, created.p);
            attr = created.p;
            if (attr != 0) attr->_refCount = attr->_refCount + 1;
            old = (igObject *)work->_blendStateAttr;
            IG_OBJECT_RELEASE(old);
            work->_blendStateAttr = (int)attr;
        }
        if (work->_lightingStateAttr == 0) {
            int ownerAllocator = igObject_GetAllocator(manager);
            int allocator = g_useOwnerAllocator ? ownerAllocator : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
            igObject *attr;
            igObject *old;
            AttrRef<2> created((igObject *)igLightingStateAttr_CreateInstance(allocator));
            ObjectList_AppendRetained(list, created.p);
            attr = created.p;
            if (attr != 0) attr->_refCount = attr->_refCount + 1;
            old = (igObject *)work->_lightingStateAttr;
            IG_OBJECT_RELEASE(old);
            work->_lightingStateAttr = (int)attr;
        }
        char *mode = (char *)component->_name;
        mode = mode != 0 ? mode : (char *)emptyString;
        if (*mode == 'I') {
            Color4f color;
            Color4f_Unpack(&color, 1, ((igColorAttr *)work->_colorAttr)->_colorPacked);
            color.w = 0.0f;
            ((OverrideAttr *)work->_colorAttr)->SetValue(&color);
            ((OverrideAttr *)work->_blendStateAttr)->SetValue((void *)1);
            ((OverrideAttr *)work->_lightingStateAttr)->SetValue((void *)0);
            work->_fadeValue = 0.0f;
            work->_fadeLimitValue = component->_fadeValue;
            work->_fadeAddValue = component->_fadeValue / component->_fadeTime;
            work->_fadeSt0 = 1;
        } else {
            Color4f color;
            Color4f_Unpack(&color, 1, ((igColorAttr *)work->_colorAttr)->_colorPacked);
            color.w = component->_fadeValue;
            ((OverrideAttr *)work->_colorAttr)->SetValue(&color);
            ((OverrideAttr *)work->_blendStateAttr)->SetValue((void *)1);
            ((OverrideAttr *)work->_lightingStateAttr)->SetValue((void *)0);
            work->_fadeValue = component->_fadeValue;
            work->_fadeLimitValue = component->_fadeValue;
            work->_fadeAddValue = component->_fadeValue / component->_fadeTime;
            work->_fadeSt0 = 2;
        }
        beBaseInfoRam_StartTimer(ram, &FADE[0], 0);
    }
    return 1;
}

/* Past the end of the joint range, loops back by the range (state 1) or holds at its end (state 2),
 * rebasing the node clock to the new time and flagging the end. */
void beAction2JOINTSET_Update(beAction2 *manager, beAction2InfoRam *ram) {
    beAction2InfoWork *work = (beAction2InfoWork *)ram->_work;
    switch (work->_jointSt0) {
    case 0:
        break;
    case 1:
    case 2: {
        long long now = beModelCtrlNode2_LocalTime(ram->_node, ((igInsightCore *)manager->_insight)->_worldTime);
        long long end = work->_jointEndTimeL;
        bool changed = false;
        while (now > end) {
            switch (work->_jointSt0) {
            case 1:
                changed = true;
                now += work->_jointStartTimeL - end;
                break;
            case 2:
                now = end;
                changed = true;
                break;
            }
        }
        if (changed) {
            beModelCtrlNode2 *node = (beModelCtrlNode2 *)ram->_node;
            float ticks = (float)(unsigned int)(int)(((igInsightCore *)manager->_insight)->_worldTime >> 18);
            ticks = ticks * node->_timeScale;
            node->_timeBias = now - (__fixsfdi(ticks) << 18);
            work->_jointIsEnd = 1;
        }
        break;
    }
    }
}

/* Converts the component's frame range to nanoseconds, picks loop (L) or one-shot, and rebases the
 * node clock so it reads the start of the range now. */
int beAction2JOINTSET_Start(beAction2 *manager, beAction2InfoRam *ram, beAction2JOINTSET *component) {
    long long start;
    beAction2InfoWork *work;
    beModelCtrlNode2 *node;
    long long clockTicks;
    float ticks;

    work = (beAction2InfoWork *)ram->_work;
    if (*(char *)component->_loopMode == 'L') {
        work->_jointSt0 = 1;
    } else {
        work->_jointSt0 = 2;
    }
    float seconds = component->_startTime;
    float scaled = 1e9f * seconds;
    work->_jointStartTimeL = __fixsfdi(scaled / 60.0f);
    seconds = component->_endTime;
    scaled = 1e9f * seconds;
    seconds = scaled / 60.0f;
    work->_jointEndTimeL = __fixsfdi(seconds);
    clockTicks = (int)(((igInsightCore *)manager->_insight)->_worldTime >> 18);
    node = (beModelCtrlNode2 *)ram->_node;
    ticks = (float)(unsigned int)(int)clockTicks;
    ticks = ticks * node->_timeScale;
    start = work->_jointStartTimeL;
    node->_timeBias = start - (__fixsfdi(ticks) << 18);
    work->_jointIsEnd = 0;
    return 1;
}

/* State 1 waits one frame. State 2 brings the combiner up to the node's time while the transition
 * has more than one state, then, with one state left, moves that state onto the node's time scale
 * without a jump and ends. */
void beAction2MOTIONSET_Update(beAction2 *manager, beAction2InfoRam *ram) {
    igAnimationCombiner *combiner;
    int count;
    int i;
    beAction2InfoWork *work;
    igAnimationStateList *states;
    igAnimationState *first;
    float ticks;
    float scale;
    beModelCtrlNode2 *node;
    long long now;
    long long scaled;
    long bias; /* matching construct: decomp-permuter — the saved time bias is a `long` (igLong, 64-bit under mwccps2), not `long long` */

    work = (beAction2InfoWork *)ram->_work;
    switch (work->_motionSt0) {
    case 1:
        work->_motionSt0 = 2;
        return;
    case 2:
        combiner = ((igAnimationCombiner **)((igObjectList *)((igAnimationDatabase *)((beAction2Info *)ram->_parentInfo)->_animationDatabase)->_combinerList)->_data)[ram->_ramNo];
        states = (igAnimationStateList *)combiner->_animationStateList;
        if (states->_count != 1) {
            now = beModelCtrlNode2_LocalTime(ram->_node, ((igInsightCore *)manager->_insight)->_worldTime);
            igAnimationCombiner_Update(combiner, now);
            count = ((igAnimationStateList *)combiner->_animationStateList)->_count;
            i = 0;
            while (i < count) {
                ((igAnimationState **)((igAnimationStateList *)combiner->_animationStateList)->_data)[i]->_new = 0;
                i++;
            }
        }
        if (states->_count == 1) {
            if (((igAnimationState **)states->_data)[0]->_timeScale != ((beModelCtrlNode2 *)ram->_node)->_timeScale) {
                now = beModelCtrlNode2_LocalTime(ram->_node, ((igInsightCore *)manager->_insight)->_worldTime);
                node = (beModelCtrlNode2 *)ram->_node;
                scale = node->_timeScale;
                first = ((igAnimationState **)states->_data)[0];
                ticks = (float)(unsigned int)(int)(now >> 18);
                scaled = __fixsfdi(ticks * first->_timeScale);
                bias = first->_timeBias;
                first->_timeBias = (scaled << 18) + bias;
                first->_timeBias = first->_timeBias - (__fixsfdi(ticks * scale) << 18);
                first->_timeScale = scale;
            }
            work->_motionSt0 = 0;
        }
        break;
    }
}

/* Plays the named animation on the ram's combiner, blending in over the hokan (transition) frames
 * unless the ram asked for no transition. Hokan mode S at [0]/[1] freezes the outgoing/incoming
 * state; loop mode L loops the animation's sources, anything else plays them once. */
int beAction2MOTIONSET_Start(beAction2 *manager, beAction2InfoRam *ram, beAction2MOTIONSET *component) {
    beAction2Info *info = (beAction2Info *)ram->_parentInfo;
    beAction2InfoWork *work = (beAction2InfoWork *)ram->_work;
    int animations = ((igAnimationDatabase *)info->_animationDatabase)->_animationList;
    int name = component->_name;
    int nameOrEmpty;
    if (name != 0) nameOrEmpty = name; else nameOrEmpty = (int)emptyString;
    igAnimation *animation = (igAnimation *)igProperty_FindByName(animations, g_propertyNameField[0], nameOrEmpty);
    igAnimationCombiner *combiner = ((igAnimationCombiner **)((igAnimationCombinerList *)((igAnimationDatabase *)info->_animationDatabase)->_combinerList)->_data)[ram->_ramNo];
    long biasOld; /* matching construct: decomp-permuter (found on beAction2MOTIONSET_Update) — the saved time bias is a `long` (igLong, 64-bit under mwccps2), not `long long` */
    float zero = 0.0f;
    float blend;
    long long transitionTime;
    if (work->_isNoHokan != 0 || component->_hokanTime == 0.0f) {
        blend = 1.0f;
        work->_isNoHokan = 0;
        transitionTime = 1;
    } else {
        transitionTime = __fixsfdi(1e9f * component->_hokanTime / 60.0f);
        blend = 0.0f;
    }
    if (((igAnimationStateList *)combiner->_animationStateList)->_count >= 2) igAnimationCombiner_ResetToPose(combiner, 0);
    int priority = animation->_priority;
    igAnimationCombiner_AddAnimationBlend(combiner, animation, 1, 1, 1, &priority, 0, transitionTime, blend, 1.0f, 0);
    long long now = beModelCtrlNode2_LocalTime(ram->_node, ((igInsightCore *)manager->_insight)->_worldTime);
    igAnimationCombiner_Update(combiner, now);
    if (((char *)component->_hokanMode)[0] == 'S') {
        igAnimationState *state = ((igAnimationState **)((igAnimationStateList *)combiner->_animationStateList)->_data)[0];
        float ticks = (float)(unsigned int)(int)(((igInsightCore *)manager->_insight)->_worldTime >> 18);
        long long scaled = __fixsfdi(ticks * state->_timeScale);
        biasOld = state->_timeBias;
        state->_timeBias = (scaled << 18) + biasOld;
        state->_timeBias -= __fixsfdi(ticks * zero) << 18;
        state->_timeScale = zero;
    }
    if (((char *)component->_hokanMode)[1] == 'S') {
        igAnimationStateList *states = (igAnimationStateList *)combiner->_animationStateList;
        int last = states->_count - 1;
        igAnimationState *state = ((igAnimationState **)states->_data)[last];
        float ticks = (float)(unsigned int)(int)(((igInsightCore *)manager->_insight)->_worldTime >> 18);
        long long scaled = __fixsfdi(ticks * state->_timeScale);
        biasOld = state->_timeBias;
        state->_timeBias = (scaled << 18) + biasOld;
        state->_timeBias -= __fixsfdi(ticks * zero) << 18;
        state->_timeScale = zero;
    }
    igAnimationTrackList *tracks = (igAnimationTrackList *)animation->_trackList;
    int isLoop = ((char *)component->_loopMode)[0] == 'L';
    int j;
    for (j = 0; j < tracks->_count; j++) {
        void *source = (void *)((igAnimationTrack **)tracks->_data)[j]->_source;
        if (source != 0) {
            if (igObject_IsKindOf(source, g_igEnbayaTransformSource_metaObject[0]) != 0) {
                igEnbayaAnimationSource *enbaya = (igEnbayaAnimationSource *)((igEnbayaTransformSource *)source)->_enbayaAnimationSource;
                if (isLoop) enbaya->_playMode = 0; else enbaya->_playMode = 4;
                break;
            } else if (isLoop) {
                igCompressedAnimationSequenceQS *sequence = (igCompressedAnimationSequenceQS *)source;
                if (sequence->_playMode == 3) break;
                sequence->_playMode = 3;
            } else {
                igCompressedAnimationSequenceQS *sequence = (igCompressedAnimationSequenceQS *)source;
                if (sequence->_playMode == 1) break;
                sequence->_playMode = 1;
            }
        }
    }
    work->_motionSt0 = 1;
    work->_isMotion = 1;
    return 1;
}

/* Resumes at work._comIndex and starts components until one handler returns false or the list is
 * exhausted, then saves the position back into work._comIndex. The component kind is identified by
 * comparing its virtual GetMetaObject() result with the published metadata handle of each *_Start
 * handler's class. */
void beAction2_StartComponents(beAction2 *manager, beAction2InfoRam *ram)
{
    beAction2Data *data;
    beAction2InfoWork *work;
    int index;
    unsigned char keepGoing;
    Action2Component *component;

    work = (beAction2InfoWork *)ram->_work;
    data = (beAction2Data *)work->_comData;
    index = work->_comIndex;
    if (index != ((Action2ComponentList *)((Action2DataGuardView *)data)->_comList)->_count) {
        do {
            keepGoing = true;
            component = (((Action2ComponentList *)data->_comList)->_data)[index];
            if (g_beAction2MOTIONSET_metaObject[0] == component->GetMetaObject()) {
                keepGoing = beAction2MOTIONSET_Start(manager, ram, (beAction2MOTIONSET *)component) & 0xFF;
                index += 1;
            } else if (g_beAction2JOINTSET_metaObject[0] == component->GetMetaObject()) {
                keepGoing = beAction2JOINTSET_Start(manager, ram, (beAction2JOINTSET *)component) & 0xFF;
                index += 1;
            } else if (g_beAction2FADESET_metaObject[0] == component->GetMetaObject()) {
                keepGoing = beAction2FADESET_Start(manager, ram, (beAction2FADESET *)component) & 0xFF;
                index += 1;
            } else if (g_beAction2WAITCHECK_metaObject[0] == component->GetMetaObject()) {
                keepGoing = beAction2WAITCHECK_Start(manager, ram, (beAction2WAITCHECK *)component) & 0xFF;
                index += 1;
            } else if (g_beAction2FLASHSET_metaObject[0] == component->GetMetaObject()) {
                keepGoing = beAction2FLASHSET_Start(manager, ram, (beAction2FLASHSET *)component) & 0xFF;
                index += 1;
            }
        } while ((keepGoing & 0xFF) && index != ((Action2ComponentList *)data->_comList)->_count);
    }
    work->_comIndex = index;
}

/* Slot 31, per frame for each running, unfrozen ram: updates each active component kind. */
void beAction2_Update(beAction2 *self, beAction2InfoRam *ram) {
    beAction2InfoWork *work;

    if (ram->_isRun == 0) {
        return;
    }
    work = (beAction2InfoWork *)ram->_work;
    if (work->_isFreeze != 0) {
        return;
    }
    if (work->_motionSt0 != 0) {
        beAction2MOTIONSET_Update(self, ram);
    }
    if (work->_jointSt0 != 0) {
        beAction2JOINTSET_Update(self, ram);
    }
    if (work->_fadeSt0 != 0) {
        beAction2FADESET_Update(self, ram);
    }
    if (work->_waitSt0 != 0) {
        beAction2WAITCHECK_Update(self, ram);
    }
    if (work->_flashSt0 != 0) {
        beAction2FLASHSET_Update(self, ram);
    }
}

inline WorkRef::~WorkRef() {
    beAction2InfoWork *held = p;
    if (held != 0) {
        held->_refCount = held->_refCount - 1;
        if ((held->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(held);
        }
    }
}

/* Slot 33: answers ISCOMEND, ISRUN, GETNAMELIST, GETAPPEARANCELIST and GETBONEMATRIX, freezes and
 * unfreezes the action on ONFREEZE and OFFREEZE, stops it on NDSP and starts any other name as the
 * action's data. */
int beAction2_OnMessage(beAction2 *self, beAction2InfoRam *ram, void *name)
{
    WorkRef workRef;
    beAction2Info *info;
    unsigned int ramNo;
    igBitMask *mask;

    workRef.p = (beAction2InfoWork *)ram->_work;
    if (workRef.p != 0) {
        workRef.p->_refCount = workRef.p->_refCount + 1;
    }
    info = (beAction2Info *)ram->_parentInfo;
    ramNo = ram->_ramNo;
    switch (beMessenger_ResolveEnumValue(self->_messenger, beAction2_GetMessageEnum(), name)) {
    case 1: /* ISRUN */
        beMessenger_AppendBool(self->_messenger, ram->_isRun);
        break;
    case 0: { /* ISCOMEND */
        beAction2InfoWork *work = workRef.p;
        beAction2Data *data = (beAction2Data *)work->_comData;
        int index = work->_comIndex;
        if (work->_waitSt0 == 0 && index == ((igObjectList *)data->_comList)->_count) {
            beMessenger_AppendBool(self->_messenger, 1);
        } else {
            beMessenger_AppendBool(self->_messenger, 0);
        }
        break;
    }
    case 3: /* GETAPPEARANCELIST */
        if (ram->_isRun != 0) {
            beMessenger_AppendObject(self->_messenger, ram->_appearanceList);
            beMessenger_AppendObject(self->_messenger, ((int *)((igObjectList *)((igAnimationDatabase *)info->_animationDatabase)->_skeletonList)->_data)[0]);
        }
        break;
    case 4: /* GETBONEMATRIX */
        if (ram->_isRun != 0) {
            int boneName = beMessenger_GetString(self->_messenger, 0);
            igActor *actor = (igActor *)((int *)((igObjectList *)ram->_actorList)->_data)[0];
            int bone = ((VirtualObject *)((igAnimationCombiner *)actor->_animationSystem)->_animHierarchy)->FindBoneIndex(boneName);
            int matrix;
            if (actor->_actorCacheUsed != 0) {
                matrix = actor->_boneMatrixCacheArray + (bone << 6);
            } else {
                matrix = ((VirtualObject *)actor->_animationSystem)->GetBoneMatrix(bone);
            }
            beMessenger_AppendMatrix(self->_messenger, matrix);
        }
        break;
    case 2: { /* GETNAMELIST */
        igObjectList *list = (igObjectList *)info->_dataList_;
        int count = list->_count;
        int i;
        for (i = 0; i < count; i++) {
            void *dataName = (void *)((beAction2Data *)((int *)list->_data)[i])->_name;
            void *text;
            if (dataName != 0) text = dataName; else text = &emptyString[0];
            beMessenger_AppendString(self->_messenger, text);
        }
        break;
    }
    case 5: /* ONFREEZE */
        if (workRef.p != 0) {
            beModelCtrlNode2 *node;
            float ticks;
            int clockTicks;
            float scale = 0.0f;
            beBaseInfoRam_SetAllTimerScales(ram, scale);
            clockTicks = (int)(((igInsightCore *)self->_insight)->_worldTime >> 0x12);
            node = (beModelCtrlNode2 *)ram->_node;
            ticks = (float)(unsigned int)clockTicks;
            {
                long long bias = __fixsfdi(ticks * node->_timeScale);
                bias <<= 18;
                bias += node->_timeBias;
                node->_timeBias = bias;
            }
            node->_timeBias -= __fixsfdi(ticks * scale) << 18;
            node->_timeScale = scale;
            workRef.p->_isFreeze = 1;
        }
        break;
    case 6: /* OFFREEZE */
        if (workRef.p != 0) {
            beModelCtrlNode2 *node;
            float ticks;
            int clockTicks;
            float scale = 1.0f;
            beBaseInfoRam_SetAllTimerScales(ram, scale);
            clockTicks = (int)(((igInsightCore *)self->_insight)->_worldTime >> 0x12);
            node = (beModelCtrlNode2 *)ram->_node;
            ticks = (float)(unsigned int)clockTicks;
            {
                long long bias = __fixsfdi(ticks * node->_timeScale);
                bias <<= 18;
                bias += node->_timeBias;
                node->_timeBias = bias;
            }
            node->_timeBias -= __fixsfdi(ticks * scale) << 18;
            node->_timeScale = scale;
            workRef.p->_isFreeze = 0;
        }
        break;
    default:
        mask = (igBitMask *)((igSwitch *)info->_switch)->_childMask;
        if (strcmp(name, &NDSP[0]) == 0) {
            igObjectList *list = (igObjectList *)((beModelCtrlNode2 *)ram->_node)->_overrideAttrList;
            int count = list->_count;
            int i;
            int count2;
            int j;
            for (i = 0; i < count; i++) {
                { igObject *held = (igObject *)((int *)list->_data)[i]; IG_OBJECT_RELEASE(held); }
            }
            j = 0;
            count2 = list->_count;
            for (; j < count2; j++) {
                ((int *)list->_data)[j] = 0;
            }
            list->_count = 0;
            int nonEmpty = ((igObjectList *)((beModelCtrlNode2 *)ram->_node)->_overrideAttrList)->_count > 0;
            if (!nonEmpty) {
                List_Reserve((void *)((beModelCtrlNode2 *)ram->_node)->_overrideAttrList, 0, 4);
            }
            ClearMaskBit(mask, ramNo);
            { igObject *held = (igObject *)ram->_work; IG_OBJECT_RELEASE(held); }
            ram->_work = 0;
            beBaseInfoRam_RemoveAllTimers(ram);
            ram->_isRun = 0;
            if (info->_animationDatabase != 0) {
                igObjectList *combiners = (igObjectList *)((igAnimationDatabase *)info->_animationDatabase)->_combinerList;
                int actorCount;
                int k;
                igMetaField *field;
                igMetaField *field2;
                VirtualObject *actor;
                int buffer;
                int buffer2;
                if (combiners != 0) {
                    igAnimationCombiner_RemoveAllStates(((int *)combiners->_data)[ram->_ramNo]);
                }
                actorCount = ((igObjectList *)ram->_actorList)->_count;
                for (k = 0; k < actorCount; k++) {
                    actor = (VirtualObject *)((int *)((igObjectList *)ram->_actorList)->_data)[k];
                    field = (igMetaField *)igMetaObject_FindFieldByName(actor->GetMetaObject(), &boneMatrixCacheArray[0]);
                    buffer = *(int *)((char *)actor + field->_offset);
                    if (buffer != 0) {
                        Memory_FreeBuffer(buffer);
                        *(int *)((char *)actor + field->_offset) = 0;
                    }
                    field2 = (igMetaField *)igMetaObject_FindFieldByName(actor->GetMetaObject(), &blendMatrixCacheArray[0]);
                    buffer2 = *(int *)((char *)actor + field2->_offset);
                    if (buffer2 != 0) {
                        Memory_FreeBuffer(buffer2);
                        *(int *)((char *)actor + field2->_offset) = 0;
                    }
                }
            }
            return 1;
        }
        if (workRef.p == 0) {
            void *allocator = ((void *)igObject_GetAllocator(self));
            beAction2InfoWork *created;
            allocator = g_useOwnerAllocator ? allocator : ((void *)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
            { beAction2InfoWork *held = workRef.p; IG_OBJECT_RELEASE(held); }
            workRef.p = (beAction2InfoWork *)beAction2InfoWork_CreateInstance(allocator);
            created = workRef.p;
            if (created != 0) created->_refCount = created->_refCount + 1;
            { igObject *held = (igObject *)ram->_work; IG_OBJECT_RELEASE(held); }
            ram->_work = (int)created;
        }
        if (ram->_isRun == 0) {
            ram->_isRun = 1;
            workRef.p->_motionSt0 = 0;
            workRef.p->_fadeSt0 = 0;
            workRef.p->_waitSt0 = 0;
            SetMaskBit(mask, ramNo);
            workRef.p->_isNoHokan = 1;
            if (info->_animationDatabase != 0) {
                igObjectList *combiners = (igObjectList *)((igAnimationDatabase *)info->_animationDatabase)->_combinerList;
                if (combiners != 0) {
                    igAnimationCombiner *combiner = (igAnimationCombiner *)((int *)combiners->_data)[ram->_ramNo];
                    int actorCount;
                    int k;
                    combiner->_animationStateTime = 100000000;
                    actorCount = ((igObjectList *)ram->_actorList)->_count;
                    for (k = 0; k < actorCount; k++) {
                        igActor *actor = (igActor *)((int *)((igObjectList *)ram->_actorList)->_data)[k];
                        int hasCache = actor->_boneMatrixCacheArray != 0;
                        if (hasCache) break;
                        igActor_SetAnimationSystem(actor, combiner);
                    }
                    igAnimationCombiner_AddAnimation(combiner, ((int *)((igObjectList *)((igAnimationDatabase *)info->_animationDatabase)->_animationList)->_data)[0], 0, 4, 0);
                }
            }
        } else {
            SetMaskBit(mask, ramNo);
            workRef.p->_isNoHokan = 0;
        }
        {
            int data = (int)igProperty_FindByName(info->_dataList_, g_propertyNameField[0], (int)name);
            beAction2InfoWork *work = workRef.p;
            if (work->_comData != data) {
                if (data != 0) ((igObject *)data)->_refCount = ((igObject *)data)->_refCount + 1;
                { igObject *held = (igObject *)work->_comData; IG_OBJECT_RELEASE(held); }
                work->_comData = data;
                workRef.p->_comIndex = 0;
                beAction2_StartComponents(self, ram);
                int ramNumber = ram->_ramNo;
                void *infoName;
                if (info->_name != 0) infoName = (void *)info->_name; else infoName = &emptyString[0];
                beMessenger_SendNamed(self->_messenger, &ACTION_BROADCAST[0], infoName, ramNumber, name);
            }
        }
        break;
    }
    return 1;
}

int beAction2_GetMeta(void)
{
    return g_beAction2_metaObject[0];
}

/* Shared default virtual slots that almost every class inherits, so most are empty or return a
 * constant. The slot number is the only name evidence, so the bodies are documented by what they
 * do. */

/* Slot 28 default: empty. */
void Gap__Core__igObject__vfunc_28(void)
{
}

/* Slot 34 default: always 0. */
int Gap__Core__igObject__vfunc_34(void) {
    return 0;
}
