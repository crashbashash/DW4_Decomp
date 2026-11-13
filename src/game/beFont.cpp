#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"

/* beFont's load state (beBaseInfoRam::_st0). */
enum beFontState {
    kFontStateInitialize = 0,
    kFontStateReady = 1,
    kFontStateFailed = 10000
};

/* The "Message" enum of beFont's messages. */
enum beFontMessage {
    kFontMessageInitialize = 0,
    kFontMessageTextSet = 1,
    kFontMessageAlign = 2,
    kFontMessageSwitch = 3,
    kFontMessageSetPosition = 4,
    kFontMessageColor = 5,
    kFontMessageDefaultColor = 6,
    kFontMessageCancelColor = 7,
    kFontMessageReplaceUnknown = 8
};

/* igObject with its vtable as a real vptr, laid out as igAttrSet (igGroup and igSwitch share the
 * prefix up to _childList). Slot 20 returns the class's meta object; slot 30 is igColorAttr's colour
 * setter. */
class igNodeView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual int getMetaObject();
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25();
    virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void setColor(void *color);
    unsigned int _refCount;
    int _name;
    int _bound;
    igObjectList *_parentList;
    int _flags;
    int _handle;
    igObjectList *_childList;
    igObjectList *_attributes;
};

/* An igVertexArray subclass instance: slot 22 sets the vertex format and count, slots 25 and 26 lock
 * and unlock one vertex component. */
struct igVertexArrayLock {
    int firstVertex;
    int component;
    int componentIndex;
    unsigned int count;
    char *data;
    int stride;
    int reserved;
};
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

/* beFontImage's virtuals: slot 22 writes the glyph quads of a UTF-16 text into a vertex array, slot 23
 * returns the triangles one character draws (0 when the font has no glyph for it). */
class beFontImageView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21();
    virtual void buildVertices(igVertexArrayView *vertices, int text);
    virtual int countTriangles(int character);
};

/* igGeometryAttr's slot 37 sets the primitive type, primitive count and first index. */
class igGeometryAttrView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24();
    virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34();
    virtual void d35(); virtual void d36();
    virtual void configure(int primType, int primCount, int offset);
};

struct igColor4f { float r; float g; float b; float a; };
/* Alchemy's three-float vector, with the members beFont_AlignLines uses. */
struct igVec3f {
    float x, y, z;
    igVec3f(float x_, float y_, float z_) { x = x_; y = y_; z = z_; }
    igVec3f &operator+=(const igVec3f &other) { x += other.x; y += other.y; z += other.z; return *this; }
};

/* One row of the Shift-JIS to UTF-16 table; a row of 0xffff ends it. */
struct SjisUnicodePair { unsigned short unicode; unsigned short sjis; };
struct SjisUnicodeTable { SjisUnicodePair entries[425]; };

/* _lineFeedList and _alignList with typed element arrays. */
struct UnsignedIntListView { char header[8]; int count; int capacity; int *data; int getCount() const { return count; } };
struct FloatListView { char header[8]; int count; int capacity; float *data; int getCount() const { return count; } };
union FloatBits { float f; struct { unsigned char b0, b1, b2; unsigned char high : 7; unsigned char sign : 1; } bits; };

extern "C" {
void Gap__Bec__beFont__vfunc_23(void);
void Gap__Bec__beFont__vfunc_24(beFont *self);
void Gap__Bec__beFont__vfunc_29(beFont *self, int receiver);
void Gap__Bec__beFont__vfunc_32(beFont *self);
int Gap__Bec__beFont__vfunc_30(void);
void Gap__Bec__beFont__vfunc_31(void);
int Gap__Bec__beFont__vfunc_34(beFont *self, beBaseInfoRam *ram, beMessengerWork *work);
void beFont_AddFontImages(beFont *self, igNamedObjectInfo *info);
igSmartPointer<beUnicodeObj> beFont_ConvertToUnicode(beFont *self, const char *text);
int beFont_FindFontIndex(beFont *self, int name);
void beFont_SetText(beFont *self, beBaseInfoRam *ram, igNodeView *text, int index);
void beFont_ReplaceVertexArray(beFont *self, igGeometryAttr *geometry, int fontIndex, int vertexCount);
void beFont_PrepareGeometry(beFont *self, igGeometryAttr *geometry, int text, int wide);
void beFont_LayoutLines(beFont *self, unsigned short *text, int entry, igVertexArrayLock *positions);
void beFont_AlignLines(beFont *self, int text, beFontInfoData *entry, igVertexArrayLock *positions);
void beFont_LockVertexArray(beFont *self, igVertexArrayView *vertices, igVertexArrayLock *positions, igVertexArrayLock *texCoords);
int beFont_FindFirstLayoutEntry(beFont *self, beBaseInfoRam *ram, int dataName, int setName);
int beFont_FindNextLayoutEntry(beFont *self, beBaseInfoRam *ram);
int Gap__Bec__beFont__vfunc_20(void);
void Gap__Bec__beUnicodeObj__vfunc_08(beUnicodeObj *self);
void beUnicodeObj_AllocateBuffer(beUnicodeObj *self, int length);
int Gap__Bec__beUnicodeObj__vfunc_20(void);

void Gap__Core__igObject__vfunc_23(void);
int Gap__Core__igObject__vfunc_24(beFont *);
int Gap__Core__igObject__userDestruct(beUnicodeObj *);
void *igObject_GetAllocator(...);
void *Memory_GetAllocatorBySelector(...);
int igObject_IsKindOf(void *, int);
int List_Reserve(int, int, int);
void List_Resize(void *, int, int);
void List_RemoveWordAt(void *, int);
void ObjectList_AppendRetainedList(void *, void *);
void ObjectList_AppendRetained(void *, void *);
int StringPool_Allocate(int);
int StringPool_Construct(int);
int StringPool_Intern(...);
void StringChunk_ReleaseHeader(...);
int igStringObj_Clear(...);
int igStringObj_Insert(igStringObj *, char *, int, int);
void igStringObj_Set(void *, void *);
int beMessenger_RegisterReceiver(int, int, int *, int, int);
int beMessenger_ResolveEnumValue(int, int, int);
void beMessenger_SelectGroup(int, void *);
void beMessenger_AppendString(int, void *);
void beMessenger_DispatchSelected(int, void *);
int beMessenger_GetBoolCount(int);
int beMessenger_GetStringCount(int);
int beMessenger_GetIntCount(int);
int beMessenger_GetObjectCount(int);
int beMessenger_GetInt(int, int);
void *beMessenger_GetObject(int, int);
int beMessenger_GetString(int, int);
void beMessenger_GetVec3(void *, int, int);
int beFont_GetMessageEnum(...);
int beFont_GetAlignEnum(...);
int beFont_GetSwitchEnum(...);
beFontGeomAttrPair *beFontGeomAttrPair_Create(void *);
igGeometryAttr *igGeometryAttr_Create(void *);
igVertexArrayView *igVertexArray_Create(...);
int igVertexArrayLock_Init(igVertexArrayLock *);
beUnicodeObj *beUnicodeObj_Create(int);
int beFontImage_CountTriangles(int, int);
int beFontImage_CountTrianglesWide(int, int);
void igSwitch_EnableChild(void *, int);
void igSwitch_DisableChild(void *, int);
void Color4f_Unpack(void *, int, int);
void Matrix44_SetTranslation(void *, void *);
unsigned int Memory_GetBufferSize(...);
int Memory_FreeBufferWithAllocator(int, int);
int Memory_AllocateAlignedWithAllocator(unsigned int, int, int);
int memset(int, int, unsigned int);
int strlen(const char *);
int strcmp(...);

extern int TEXTCTL[4];
extern int LAYERCTL_2[4];
extern int FONT[4];
extern int GETLAYERNODE[4];
extern int g_emptyTextPlaceholder[4];
extern char text_igStringObj[16];
extern char text_beUnicodeObj[16];
extern char ALL_3[];
extern const char *g_stringObjEmptyText[4];
extern const SjisUnicodeTable g_sjisToUnicodeTable;
extern int emptyString[4];
extern int g_stringPool[4];
extern int g_defaultAllocatorSelector[4];
extern unsigned char g_useOwnerAllocator;
extern int g_beFont_metaObject[4];
extern int g_beFontInfo_metaObject[4];
extern int g_beFontImage_metaObject[4];
extern int g_beUnicodeObj_metaObject[4];
extern int g_igColorAttr_metaObject[4];
extern int g_igGroup_metaObject[4];
extern int g_igAttrSet_metaObject[4];
}

static inline igNodeView *nodeAt(igObjectList *list, int index) { return ((igNodeView **)list->_data)[index]; }
static inline int countOf(igObjectList *list) { if (list != 0) return list->_count; return 0; }
static inline igNodeView *asAttrSet(igNodeView *node) {
    if (node != 0 && igObject_IsKindOf(node, g_igAttrSet_metaObject[0]) != 0) return node; else return 0;
}

/* Marks the load as failed, so the font ignores every later message. */
static inline void abandonLoad(beBaseInfoRam *ram) {
    ram->_st0 = kFontStateFailed;
    ram->_st3 = 0;
    ram->_st2 = 0;
    ram->_st1 = 0;
}

/* The interned copy of `text` in the global string pool, creating the pool on first use. */
static inline int internString(int text) {
    if (g_stringPool[0] == 0) {
        int pool = StringPool_Allocate(0x10);
        if (pool != 0) {
            pool = StringPool_Construct(pool);
        }
        g_stringPool[0] = pool;
    }
    return StringPool_Intern(g_stringPool[0], text);
}

/* Drops one reference to an interned string (its count is the word before the text). */
static inline void releaseString(int text) {
    if (text != 0) {
        int *header = (int *)(text - 8);
        int refs = *(int *)(text - 4) - 1;
        *(int *)(text - 4) = refs;
        if (refs == 0) {
            StringChunk_ReleaseHeader(*header, header);
        }
    }
}

/* Replaces a pooled string field of the pair being named with the interned copy of `text` (the
 * empty string for null). */
#define SET_POOLED_STRING(object, field, text) { \
    const char *value_ = (text) ? (const char *)(text) : (const char *)emptyString; \
    int interned_; \
    pair = (object); \
    interned_ = internString((int)value_); \
    releaseString(pair->field); \
    pair->field = interned_; \
}

/* Tail call to the base-class slot 23 (igObject::vfunc_23). The receiver stays in the argument
 * register, which is why the declaration takes no parameters. */
void Gap__Bec__beFont__vfunc_23(void)
{
    Gap__Core__igObject__vfunc_23();
}

void Gap__Bec__beFont__vfunc_24(beFont *self) {
    beFontImageList *fonts;
    int count;
    int clearCount;
    int i;
    int j;
    igObject *font;

    fonts = (beFontImageList *)self->_fonts;
    count = fonts->_count;
    for (i = 0; i < count; i++) {
        font = ((igObject **)fonts->_data)[i];
        igRelease(font);
    }
    clearCount = fonts->_count;
    for (j = 0; j < clearCount; j++) {
        ((igObject **)fonts->_data)[j] = 0;
    }
    fonts->_count = 0;
    Gap__Core__igObject__vfunc_24(self);
}

/* Registers `receiver` with the font's messenger under the "TEXTCTL" group string, with a null
 * text argument and -1 as the last argument. */
void Gap__Bec__beFont__vfunc_29(beFont *self, int receiver)
{
    beMessenger_RegisterReceiver(self->_messenger, receiver, &TEXTCTL[0], 0, -1);
}

static inline int count(const beFontGeomAttrPairList *list) { return list->_count; }

void Gap__Bec__beFont__vfunc_32(beFont *self) {
    beFontGeomAttrPairList *pairs;
    int pairCount;
    int clearCount;
    int i;
    int j;
    igObject *pair;
    igObject *root;

    root = (igObject *)self->_root;
    igRelease(root);
    self->_root = 0;
    pairs = (beFontGeomAttrPairList *)self->_gaPairList;
    if (count(pairs) > 0) {
        pairCount = pairs->_count;
        for (i = 0; i < pairCount; i++) {
            pair = ((igObject **)pairs->_data)[i];
            igRelease(pair);
        }
        clearCount = pairs->_count;
        for (j = 0; j < clearCount; j++) {
            ((igObject **)pairs->_data)[j] = 0;
        }
        pairs->_count = 0;
        if (!(0 < ((beFontGeomAttrPairList *)self->_gaPairList)->_count)) {
            List_Reserve(self->_gaPairList, 0, 4);
        }
    }
    igStringObj_Clear(self->_convertData);
}

int Gap__Bec__beFont__vfunc_30(void)
{
    return g_beFontInfo_metaObject[0];
}

void Gap__Bec__beFont__vfunc_31(void)
{
}

/* Message handler. INITIALIZE asks the layer controller for the font's layer node, keeps its
 * attribute set as _root and pairs every panel of every category with a new geometry attribute;
 * the other messages act on every layout entry the first two string arguments select. */
int Gap__Bec__beFont__vfunc_34(beFont *self, beBaseInfoRam *ram, beMessengerWork *work) {
    beFontInfo *info;
    int message;
    igNodeView *group;
    igNodeView *layers;
    /* matching construct: `pair` also holds the layer attribute set; one variable for both keeps
       retail's register assignment */
    beFontGeomAttrPair *pair;
    int childCount;
    igObjectList *list;
    int i;
    int j;
    igNodeView *category;
    igNodeView *categorySwitch;
    igNodeView *panel;
    int index;
    int visible;
    unsigned int bitCount;
    int state;
    int result;
    int categoryCount;
    int categories;

    if (((beFontImageList *)self->_fonts)->_count <= 0) { result = 1; goto end; }
    info = (beFontInfo *)ram->_parentInfo;
    message = beMessenger_ResolveEnumValue(self->_messenger, beFont_GetMessageEnum(), work->_message);
    state = ram->_st0;
    switch (state) {
    case kFontStateInitialize:
        switch (message) { case kFontMessageInitialize:
        {
        if (((beFontImageList *)self->_fonts)->_count <= 0) { abandonLoad(ram); result = 1; goto end; }
        beMessenger_SelectGroup(self->_messenger, LAYERCTL_2);
        beMessenger_AppendString(self->_messenger, FONT);
        beMessenger_DispatchSelected(self->_messenger, GETLAYERNODE);
        if (beMessenger_GetBoolCount(self->_messenger) <= 0) { abandonLoad(ram); result = 1; goto end; }
        group = (igNodeView *)beMessenger_GetObject(self->_messenger, 0);
        if (g_igGroup_metaObject[0] != group->getMetaObject()) { abandonLoad(ram); result = 1; goto end; }
        list = group->_childList;
        childCount = 0;
        if (list != 0) childCount = list->_count;
        if (childCount <= 0) { abandonLoad(ram); result = 1; goto end; }
        pair = (beFontGeomAttrPair *)nodeAt(list, 0);
        if (g_igAttrSet_metaObject[0] != ((igNodeView *)pair)->getMetaObject()) { abandonLoad(ram); result = 1; goto end; }
        if (pair) pair->_refCount = pair->_refCount + 1;
        {
            igNodeView *old = (igNodeView *)self->_root;
            igRelease((igObject *)old);
        }
        self->_root = (int)pair;
        layers = nodeAt(((igNodeView *)self->_root)->_childList, 0);
        i = 0;
        goto nextCategory;
        do {
            category = nodeAt((igObjectList *)categories, i);
            categorySwitch = nodeAt(category->_childList, 0);
            ObjectList_AppendRetainedList(category->_attributes, (void *)((beFontImage **)((beFontImageList *)self->_fonts)->_data)[beFont_FindFontIndex(self, (int)(categorySwitch->_name ? (const char *)categorySwitch->_name : (const char *)emptyString))]->_attrList);
            j = 0;
            while (j < countOf(categorySwitch->_childList)) {
                panel = asAttrSet(nodeAt(categorySwitch->_childList, j));
                {
                    void *allocator = igObject_GetAllocator(self);
                    void *creator;
                    if (g_useOwnerAllocator != 0) creator = allocator; else creator = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                    igSmartPointer<beFontGeomAttrPair> newPair(beFontGeomAttrPair_Create(creator));
                    SET_POOLED_STRING(newPair.p, _category, category->_name)
                    SET_POOLED_STRING(newPair.p, _panel, panel->_name)
                    allocator = igObject_GetAllocator(self);
                    if (g_useOwnerAllocator != 0) creator = allocator; else creator = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                    igSmartPointer<igGeometryAttr> geometry(igGeometryAttr_Create(creator));
                    ObjectList_AppendRetained((void *)newPair.p->_geomAttrs, geometry.p);
                    ObjectList_AppendRetained((void *)self->_gaPairList, newPair.p);
                }
                j++;
            }
            i++;
        nextCategory:
            list = layers->_childList;
            if (list != 0) categoryCount = list->_count; else categoryCount = 0;
            categories = (int)list;
        } while (i < categoryCount);
        ram->_st0 = ram->_st0 + 1;
        ram->_st3 = 0;
        ram->_st2 = 0;
        ram->_st1 = 0;
        { result = 1; goto end; }
        }
        }
        goto unhandled;
    }
    result = 1;
    switch (state) {
    case kFontStateReady:
        switch (message) {
        case kFontMessageTextSet: {
            int dataName = beMessenger_GetString(self->_messenger, 0);
            int setName = beMessenger_GetString(self->_messenger, 1);
            igSmartPointer<igObject> text((igObject *)0, kRetainReference);
            igSmartPointer<igStringObj> scratch((igStringObj *)((beSystem *)self->_system)->_globalStrObj, kRetainReference);
            if (beMessenger_GetStringCount(self->_messenger) > 2) {
                if (beMessenger_GetString(self->_messenger, 2) != 0) { igStringObj *target = scratch.p; igStringObj_Set(target, (void *)beMessenger_GetString(self->_messenger, 2)); }
                else igStringObj_Set(scratch.p, g_emptyTextPlaceholder);
                text = scratch;
            } else if (beMessenger_GetIntCount(self->_messenger) > 0) {
                int k = beMessenger_GetInt(self->_messenger, 0);
                igObjectList *unicodeList = (igObjectList *)info->_unicodeList;
                if (unicodeList != 0 && k < unicodeList->_count) {
                    text = ((igObject **)unicodeList->_data)[k];
                }
            } else if (beMessenger_GetObjectCount(self->_messenger) > 0) {
                igNodeView *object = (igNodeView *)beMessenger_GetObject(self->_messenger, 0);
                object->getMetaObject();
                if (g_beUnicodeObj_metaObject[0] == object->getMetaObject()) {
                    text = (igObject *)object;
                } else {
                    igStringObj_Set(scratch.p, g_emptyTextPlaceholder);
                    text = scratch;
                }
            }
            if (text.p != 0) {
                index = beFont_FindFirstLayoutEntry(self, ram, dataName, setName);
                if (index != -1) {
                    do {
                        beFont_SetText(self, ram, (igNodeView *)text.p, index);
                        index = beFont_FindNextLayoutEntry(self, ram);
                    } while (index != -1);
                }
            }
            return 1;
        }
        case kFontMessageAlign: {
            int dataName = beMessenger_GetString(self->_messenger, 0);
            int setName = beMessenger_GetString(self->_messenger, 1);
            int align = beMessenger_GetString(self->_messenger, 2);
            align = beMessenger_ResolveEnumValue(self->_messenger, beFont_GetAlignEnum(), align);
            index = beFont_FindFirstLayoutEntry(self, ram, dataName, setName);
            if (index != -1) {
                do {
                    ((beFontInfoData **)((igObjectList *)info->_dataList)->_data)[index]->_align = align;
                    index = beFont_FindNextLayoutEntry(self, ram);
                } while (index != -1);
            }
            { result = 1; goto end; }
        }
        case kFontMessageSwitch: {
            int dataName = beMessenger_GetString(self->_messenger, 0);
            int setName = beMessenger_GetString(self->_messenger, 1);
            igObjectList *dataList;
            igNodeView *layerSwitch;
            igBitMask *categoryMask;
            int k;
            if (beMessenger_GetStringCount(self->_messenger) > 2) {
                bitCount = beMessenger_GetString(self->_messenger, 2);
                switch (beMessenger_ResolveEnumValue(self->_messenger, beFont_GetSwitchEnum(), bitCount)) {
                case 1:
                    visible = 1;
                    break;
                case 0:
                    visible = 0;
                    break;
                }
            } else if (beMessenger_GetIntCount(self->_messenger) > 0) {
                visible = beMessenger_GetInt(self->_messenger, 0);
            }
            dataList = (igObjectList *)info->_dataList;
            index = beFont_FindFirstLayoutEntry(self, ram, dataName, setName);
            if (index != -1) {
                do {
                    beFontInfoData *data = ((beFontInfoData **)dataList->_data)[index];
                    int categoryBit = data->_cbitNo;
                    int panelBit = data->_tbitNo;
                    igNodeView *rootSwitch = nodeAt(((igNodeView *)self->_root)->_childList, 0);
                    if (visible != 0) igSwitch_EnableChild(rootSwitch, categoryBit);
                    {
                        igNodeView *panelSwitch = nodeAt(nodeAt(rootSwitch->_childList, categoryBit)->_childList, 0);
                        if (visible != 0) igSwitch_EnableChild(panelSwitch, panelBit); else igSwitch_DisableChild(panelSwitch, panelBit);
                    }
                    index = beFont_FindNextLayoutEntry(self, ram);
                } while (index != -1);
            }
            k = 0;
            layerSwitch = nodeAt(((igNodeView *)self->_root)->_childList, 0);
            categoryMask = (igBitMask *)((igSwitch *)layerSwitch)->_childMask;
            while (k < countOf(layerSwitch->_childList)) {
                igBitMask *panelMask = (igBitMask *)((igSwitch *)nodeAt(nodeAt(layerSwitch->_childList, k)->_childList, 0))->_childMask;
                if ((1 << (k & 31)) & ((int *)categoryMask->_data)[(unsigned int)k >> 5]) {
                    unsigned char anyPanel = 0;
                    unsigned int bit;
                    bitCount = panelMask->_bitCount;
                    for (bit = 0; bit < bitCount; bit++) {
                        if ((1 << (bit & 31)) & ((int *)panelMask->_data)[bit >> 5]) anyPanel = 1;
                    }
                    if (!anyPanel) igSwitch_DisableChild(layerSwitch, k);
                } else {
                    unsigned char anyPanel = 0;
                    unsigned int bit;
                    bitCount = panelMask->_bitCount;
                    for (bit = 0; bit < bitCount; bit++) {
                        if ((1 << (bit & 31)) & ((int *)panelMask->_data)[bit >> 5]) anyPanel = 1;
                    }
                    if (anyPanel) igSwitch_EnableChild(layerSwitch, k);
                }
                k++;
            }
            { result = 1; goto end; }
        }
        case kFontMessageSetPosition: {
            int dataName = beMessenger_GetString(self->_messenger, 0);
            int setName = beMessenger_GetString(self->_messenger, 1);
            igColor4f position;
            beMessenger_GetVec3(&position, self->_messenger, 0);
            index = beFont_FindFirstLayoutEntry(self, ram, dataName, setName);
            if (index != -1) {
                do {
                    igNodeView *attrSet = (igNodeView *)((beFontInfoData **)((igObjectList *)info->_dataList)->_data)[index]->_attrSet;
                    Matrix44_SetTranslation(((igTransform *)nodeAt(attrSet->_childList, 0))->_m, &position);
                    index = beFont_FindNextLayoutEntry(self, ram);
                } while (index != -1);
            }
            { result = 1; goto end; }
        }
        case kFontMessageColor:
        case kFontMessageDefaultColor:
        case kFontMessageCancelColor: {
            int dataName = beMessenger_GetString(self->_messenger, 0);
            int setName = beMessenger_GetString(self->_messenger, 1);
            float red;
            float green;
            float blue;
            igColor4f requested;
            if (message == kFontMessageDefaultColor) {
                blue = green = red = 0.9f;
            } else if (message == kFontMessageCancelColor) {
                blue = green = red = 0.5f;
            } else {
                beMessenger_GetVec3(&requested, self->_messenger, 0);
                red = requested.r;
                green = requested.g;
                blue = requested.b;
            }
            index = beFont_FindFirstLayoutEntry(self, ram, dataName, setName);
            if (index != -1) {
                do {
                    int a;
                    igNodeView *attribute;
                    igObjectList *attributes = ((igNodeView *)((beFontInfoData **)((igObjectList *)info->_dataList)->_data)[index]->_attrSet)->_attributes;
                    a = 0;
                    if (0 < attributes->_count) {
                        do {
                        attribute = ((igNodeView **)attributes->_data)[a];
                        if (g_igColorAttr_metaObject[0] == attribute->getMetaObject()) {
                            igColor4f color;
                            Color4f_Unpack(&color, 1, ((igColorAttr *)attribute)->_colorPacked);
                            color.r = red;
                            color.g = green;
                            color.b = blue;
                            attribute->setColor(&color);
                        }
                        a++;
                        } while (a < attributes->_count);
                    }
                    index = beFont_FindNextLayoutEntry(self, ram);
                } while (index != -1);
            }
            { result = 1; goto end; }
        }
        case kFontMessageReplaceUnknown: {
            if (beMessenger_GetObjectCount(self->_messenger) <= 0) { result = 1; goto end; }
            if (beMessenger_GetIntCount(self->_messenger) <= 0) { result = 1; goto end; }
            {
                beUnicodeObj *text = (beUnicodeObj *)beMessenger_GetObject(self->_messenger, 0);
                int replacement = beMessenger_GetInt(self->_messenger, 0);
                beFontImageView *font = ((beFontImageView **)((beFontImageList *)self->_fonts)->_data)[0];
                unsigned short *p = (unsigned short *)text->_buffer;
                unsigned int length = Memory_GetBufferSize(p) >> 1;
                int c;
                for (c = 0; c < (int)length; c++, p++) {
                    unsigned short character = *p;
                    if (character == 0) break;
                    if (!(0 < font->countTriangles(character))) *p = replacement;
                }
            }
            { result = 1; goto end; }
        }
        default:
            goto unhandled;
        }
    }
    goto end;
unhandled:
    result = 0;
end:
    return result;
}

/* igObjectList with a typed element array. */
struct igObjectListView { char header[8]; int count; int capacity; igNodeView **data; };
/* igNamedObjectInfo with its object list typed. */
struct igNamedObjectInfoView { char header[20]; igObjectListView *objects; igObjectListView *getObjects() const { return objects; } };
static inline int objectCount(igObjectListView *list) { return list->count; }
static inline igNodeView *objectAt(igObjectListView *list, int index) { return list->data[index]; }

/* Adds every beFontImage among the info's objects to the font's images. */
void beFont_AddFontImages(beFont *self, igNamedObjectInfo *info) {
    igNamedObjectInfoView *named = (igNamedObjectInfoView *)info;
    int i;
    for (i = 0; i < objectCount(named->getObjects()); i++) {
        igNodeView *object = objectAt(named->objects, i);
        int fontImageMeta = g_beFontImage_metaObject[0];
        if (fontImageMeta == object->getMetaObject()) {
            ObjectList_AppendRetained((void *)self->_fonts, object);
        }
    }
}

/* Converts Shift-JIS text to a new beUnicodeObj. The first pass counts the characters the table
 * knows and keeps the text in _convertData; carriage returns are dropped, and a line feed is kept
 * once text has started. */
igSmartPointer<beUnicodeObj> beFont_ConvertToUnicode(beFont *self, const char *text) {
    SjisUnicodeTable table = g_sjisToUnicodeTable;
    char lead;
    char trail;
    char single;
    int length = 0;
    unsigned i = 0;
    int allocator;
    while (i < (unsigned)strlen(text)) {
        const char *p = text + i;
        unsigned c = (unsigned char)*p;
        if (c == '\n') {
            if (length > 0) length++;
            i++;
        } else if (c == '\r') {
            i++;
        } else if (c & 0x80) {
            unsigned short high = (unsigned char)c << 8;
            unsigned short sjis = high | (unsigned char)p[1];
            const char *second = p + 1;
            SjisUnicodePair *entry = table.entries;
            if (entry->unicode != 0xffff) {
                do {
                    if (sjis == entry->sjis) { length++; break; }
                    entry++;
                } while (entry->unicode != 0xffff);
            }
            igStringObj_Clear((igStringObj *)self->_convertData);
            lead = *p;
            igStringObj_Insert((igStringObj *)self->_convertData, &lead, ((igStringObj *)self->_convertData)->_length, 1);
            trail = *second;
            igStringObj_Insert((igStringObj *)self->_convertData, &trail, ((igStringObj *)self->_convertData)->_length, 1);
            i += 2;
        } else {
            unsigned char ch = c;
            unsigned short sjis = ch;
            SjisUnicodePair *entry = table.entries;
            if (entry->unicode != 0xffff) {
                do {
                    if (sjis == entry->sjis) { length++; break; }
                    entry++;
                } while (entry->unicode != 0xffff);
            }
            igStringObj_Clear((igStringObj *)self->_convertData);
            single = *p;
            igStringObj_Insert((igStringObj *)self->_convertData, &single, ((igStringObj *)self->_convertData)->_length, 1);
            i++;
        }
    }
    allocator = ((int)igObject_GetAllocator(self));
    allocator = g_useOwnerAllocator ? allocator : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
    igSmartPointer<beUnicodeObj> result(beUnicodeObj_Create(allocator));
    beUnicodeObj_AllocateBuffer(result.p, length);
    unsigned short *out = (unsigned short *)result.p->_buffer;
    int written = 0;
    unsigned j = 0;
    while (j < (unsigned)strlen(text)) {
        const char *p = text + j;
        unsigned c = (unsigned char)*p;
        if (c == '\n') {
            if (written > 1) out[written++] = c;
            j++;
        } else if (c == '\r') {
            j++;
        } else if (c & 0x80) {
            unsigned short high = (unsigned char)c << 8;
            unsigned short sjis = high | (unsigned char)p[1];
            int k = 0;
            SjisUnicodePair *entry = table.entries;
            if (entry->unicode != 0xffff) {
                do {
                    if (sjis == entry->sjis) { out[written++] = table.entries[k].unicode; break; }
                    entry++;
                    k++;
                } while (entry->unicode != 0xffff);
            }
            j += 2;
        } else {
            unsigned char ch = c;
            unsigned short sjis = ch;
            SjisUnicodePair *entry = table.entries;
            if (entry->unicode != 0xffff) {
                do {
                    if (sjis == entry->sjis) { out[written++] = ch; break; }
                    entry++;
                } while (entry->unicode != 0xffff);
            }
            j++;
        }
    }
    out[written] = 0;
    return result;
}

/* Index of the font image called `name`; the first font when none is, or `name` is null. */
int beFont_FindFontIndex(beFont *self, int name) {
    int i;
    int *fontName;
    if (name == 0) {
        return 0;
    }
    i = 0;
    if (0 < ((beFontImageList *)self->_fonts)->_count) {
        do {
            fontName = (int *)(((beFontImage **)((beFontImageList *)self->_fonts)->_data)[i])->_name;
            fontName = fontName ? fontName : &emptyString[0];
            if (strcmp(name, fontName) == 0) {
                return i;
            }
            i += 1;
        } while (i < ((beFontImageList *)self->_fonts)->_count);
    }
    return 0;
}

/* Builds the text geometry of layout entry `index` from an igStringObj (Shift-JIS) or a
 * beUnicodeObj, then swaps it into the entry's attribute set. */
void beFont_SetText(beFont *self, beBaseInfoRam *ram, igNodeView *text, int index) {
    beFontInfoData *entry = ((beFontInfoData **)((igObjectList *)((beFontInfo *)ram->_parentInfo)->_dataList)->_data)[index];
    igNodeView *target = nodeAt(nodeAt(((igNodeView *)entry->_attrSet)->_childList, 0)->_childList, 0);
    void *spare = nodeAt(target->_attributes, 0);
    igSmartPointer<beUnicodeObj> unicode((beUnicodeObj *)0, kRetainReference);
    igMetaObject *meta;
    meta = (igMetaObject *)text->getMetaObject();
    if (strcmp((const char *)meta->_name, text_igStringObj) == 0) {
        const char *buffer = (const char *)((igStringObj *)text)->_buffer;
        const char *sjis;
        if (buffer == 0) sjis = g_stringObjEmptyText[0]; else sjis = buffer;
        igSmartPointer<beUnicodeObj> converted(beFont_ConvertToUnicode(self, sjis));
        unicode = converted;
    } else if (strcmp((const char *)meta->_name, text_beUnicodeObj) == 0) {
        unicode = (beUnicodeObj *)text;
    } else {
        return;
    }
    /* matching construct: declaration-order search — the order of these locals sets which argument registers the search loop uses */
    beFontGeomAttrPair *pair = 0;
    int i;
    beFontGeomAttrPair *candidate;
    int offset;
    beFontGeomAttrPairList *pairs = (beFontGeomAttrPairList *)self->_gaPairList;
    beFontGeomAttrPairList *list = pairs;
    if (list->_count > 0) {
        i = 0;
        if (i < list->_count) {
            offset = 0;
            do {
                candidate = (beFontGeomAttrPair *)((int *)((char *)list->_data + offset))[0];
                const int *category = (const int *)entry->_name;
                const int *categoryName;
                if (category != 0) categoryName = category; else categoryName = emptyString;
                if ((int)categoryName == candidate->_category) {
                    const int *panel = (const int *)((igAttrSet *)entry->_attrSet)->_name;
                    const int *panelName;
                    if (panel != 0) panelName = panel; else panelName = emptyString;
                    if ((int)panelName == candidate->_panel) { pair = candidate; break; }
                }
                list = pairs;
                i++;
                offset += 4;
            } while (i < *(int *)&list->_count);
        }
    }
    int characters = unicode.p->_buffer;
    self->_fontIdx = beFont_FindFontIndex(self, entry->_kind);
    igGeometryAttr *geometry = (igGeometryAttr *)nodeAt((igObjectList *)pair->_geomAttrs, 0);
    beFont_PrepareGeometry(self, geometry, characters, 1);
    igVertexArrayView *vertices = (igVertexArrayView *)geometry->_vertexArray;
    ((beFontImageView **)((beFontImageList *)self->_fonts)->_data)[self->_fontIdx]->buildVertices(vertices, characters);
    igVertexArrayLock positions;
    igVertexArrayLock texCoords;
    igVertexArrayLock_Init(&positions);
    igVertexArrayLock_Init(&texCoords);
    beFont_LockVertexArray(self, vertices, &positions, &texCoords);
    beFont_LayoutLines(self, (unsigned short *)characters, (int)entry, &positions);
    if (entry->_align == 1 || entry->_align == 2) beFont_AlignLines(self, characters, entry, &positions);
    vertices->unlock(&texCoords, 0);
    vertices->unlock(&positions, 0);
    ObjectList_AppendRetained((void *)pair->_geomAttrs, spare);
    igObjectList *targetAttributes = target->_attributes;
    if (geometry != 0) ++geometry->_refCount;
    igGeometryAttr *old = (igGeometryAttr *)((int *)targetAttributes->_data)[0];
    igRelease(old);
    int slot = 0;
    if (targetAttributes->_count != 0 && slot >= 0 && slot < targetAttributes->_count) ((int *)targetAttributes->_data)[0] = (int)geometry;
    igObjectList *pairGeometry = (igObjectList *)pair->_geomAttrs;
    igGeometryAttr *taken = (igGeometryAttr *)((int *)pairGeometry->_data)[0];
    igRelease(taken);
    List_RemoveWordAt(pairGeometry, 0);
    ((int *)pairGeometry->_data)[pairGeometry->_count] = 0;
}

/* Gives `geometry` a new vertex array of `vertexCount` vertices in the font image's vertex format,
 * with format bit 2 cleared. */
void beFont_ReplaceVertexArray(beFont *self, igGeometryAttr *geometry, int fontIndex, int vertexCount) {
    igSmartPointer<igVertexArray> vertices((igVertexArray *)geometry->_vertexArray); /* matching construct: declared first so it takes the retail slot above format */
    unsigned format;
    void *allocator;
    igVertexArray *held;
    igVertexArray *created;
    held = vertices.p;
    if (held != 0) {
        held->_refCount = held->_refCount + 1;
    }
    allocator = igObject_GetAllocator(self);
    allocator = (g_useOwnerAllocator != 0) ? allocator : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
    held = vertices.p;
    if (held != 0) {
        held->_refCount = held->_refCount - 1;
        if ((held->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(held);
        }
    }
    vertices.p = (igVertexArray *)igVertexArray_Create(allocator);
    format = ((beFontImage **)((beFontImageList *)self->_fonts)->_data)[fontIndex]->_vertexFlags;
    format = format & ~4u;
    ((igVertexArrayView *)vertices.p)->configure(format, vertexCount, 0, 0);
    created = vertices.p;
    if (created != 0) {
        created->_refCount = created->_refCount + 1;
    }
    held = (igVertexArray *)geometry->_vertexArray;
    if (held != 0) {
        held->_refCount = held->_refCount - 1;
        if ((held->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(held);
        }
    }
    geometry->_vertexArray = (int)created;
}

/* Sizes `geometry` for `text` as a triangle list (two extra triangles for UTF-16 text), replacing
 * its vertex array when that is missing or too small. */
void beFont_PrepareGeometry(beFont *self, igGeometryAttr *geometry, int text, int wide) {
    int triangles;
    unsigned vertexCount;
    igVertexArray *held;
    if (wide != 0) {
        triangles = beFontImage_CountTrianglesWide(((int *)((igObjectList *)self->_fonts)->_data)[self->_fontIdx], text);
        vertexCount = (triangles + 2) * 3;
    } else {
        triangles = beFontImage_CountTriangles(((int *)((igObjectList *)self->_fonts)->_data)[self->_fontIdx], text);
        vertexCount = triangles * 3;
    }
    ((igGeometryAttrView *)geometry)->configure(3, triangles, 0);
    {
        igSmartPointer<igVertexArray> vertices((igVertexArray *)geometry->_vertexArray);
        held = vertices.p;
        if (held != 0) {
            held->_refCount = held->_refCount + 1;
        }
        held = vertices.p;
        if (held != 0) {
            if (held->_numVerts < vertexCount) {
                goto replace;
            }
        } else {
replace:
            beFont_ReplaceVertexArray(self, geometry, self->_fontIdx, (int)vertexCount);
        }
    }
}

/* Moves each glyph quad (six vertices) onto its line, and records in _lineFeedList the vertex where
 * each line ends and in _alignList its width. */
void beFont_LayoutLines(beFont *self, unsigned short *text, int entry, igVertexArrayLock *positions) {
    float z;
    unsigned short ch;
    int lastLine;
    unsigned i;
    FloatBits start;
    int lastWidth;
    char *base;
    float *vertex;
    float y;
    unsigned end;
    int line;
    unsigned vertexIndex;
    UnsignedIntListView *lineEnds;
    float x;
    int width;
    FloatListView *lineWidths;
    int character;
    vertexIndex = 0;
    x = 0.0f;
    z = 0.0f;
    ((UnsignedIntListView *)self->_lineFeedList)->count = 0;
    ((FloatListView *)self->_alignList)->count = 0;
    ch = *text;
    base = positions->data;
    y = x;
    if (ch != 0) {
        do {
            character = ch;
            switch (character) {
            case '\r':
                break;
            case '\n':
                if (vertexIndex != 0) {
                    lineEnds = ((UnsignedIntListView *)self->_lineFeedList);
                    line = lineEnds->count;
                    vertex = (float *)(base + positions->stride * vertexIndex);
                    if (line < lineEnds->capacity) lineEnds->count = lineEnds->getCount() + 1; else List_Resize(lineEnds, line + 1, 4);
                    lineEnds->data[line] = vertexIndex;
                    start.f = x;
                    start.bits.sign = 0;
                    lineWidths = ((FloatListView *)self->_alignList);
                    width = lineWidths->count;
                    x = *vertex - start.f;
                    if (width < lineWidths->capacity) lineWidths->count = lineWidths->getCount() + 1; else List_Resize(lineWidths, width + 1, 4);
                    lineWidths->data[width] = x;
                    x = -*vertex;
                    y = y - ((beFontImage **)((beFontImageList *)self->_fonts)->_data)[self->_fontIdx]->_height;
                }
                break;
            default:
                end = vertexIndex + 6;
                i = vertexIndex;
                if (vertexIndex < end) {
                  if (i < end) {
                    do {
                        vertex = (float *)(base + positions->stride * i);
                        i++;
                        vertex[0] = vertex[0] + x;
                        vertex[1] = vertex[1] + y;
                        vertex[2] = vertex[2] + z;
                    } while (i < end);
                  }
                }
                vertexIndex += 6;
                break;
            }
            text++;
            ch = *text;
        } while (ch != 0);
    }
    positions->count = vertexIndex;
    lineEnds = ((UnsignedIntListView *)self->_lineFeedList);
    lastLine = lineEnds->count;
    if (lastLine < lineEnds->capacity) lineEnds->count = lineEnds->getCount() + 1; else List_Resize(lineEnds, lastLine + 1, 4);
    lineEnds->data[lastLine] = vertexIndex;
    lineWidths = ((FloatListView *)self->_alignList);
    lastWidth = lineWidths->count;
    if (lastWidth < lineWidths->capacity) lineWidths->count = lineWidths->getCount() + 1; else List_Resize(lineWidths, lastWidth + 1, 4);
    lineWidths->data[lastWidth] = *vertex;
}

/* Shifts each line's glyph quads right by the line's spare width (alignment 1) or half of it
 * (alignment 2). The shift is an igVec3f added with its inline operator+=; that inlined member is why
 * retail keeps an exception record for this frameless function. */
void beFont_AlignLines(beFont *self, int text, beFontInfoData *entry, igVertexArrayLock *positions) {
    float width = entry->_width;
    int align = entry->_align;
    igVec3f shift(0.0f, 0.0f, 0.0f);
    char *base = positions->data;
    unsigned vertexIndex = 0;
    int line;
    igVec3f *vertex;
    unsigned end;
    unsigned i;
    for (line = 0; line < ((UnsignedIntListView *)self->_lineFeedList)->count; line++) {
        end = ((UnsignedIntListView *)self->_lineFeedList)->data[line];
        switch (align) {
        case 1:
            shift.x = width - ((FloatListView *)self->_alignList)->data[line];
            break;
        case 2:
            shift.x = (width - ((FloatListView *)self->_alignList)->data[line]) / 2.0f;
            break;
        }
        while (vertexIndex < end) {
            for (i = vertexIndex; i < vertexIndex + 6; i++) {
                vertex = (igVec3f *)(base + positions->stride * i);
                *vertex += shift;
            }
            vertexIndex += 6;
        }
    }
}

/* Locks the positions (component 0) and the first texture-coordinate set (component 3) of every
 * vertex. */
void beFont_LockVertexArray(beFont *self, igVertexArrayView *vertices, igVertexArrayLock *positions, igVertexArrayLock *texCoords) {
    unsigned int vertexCount;

    positions->component = 0;
    positions->firstVertex = 0;
    positions->componentIndex = 0;
    texCoords->component = 3;
    texCoords->firstVertex = 0;
    texCoords->componentIndex = 0;
    vertexCount = ((igVertexArray *)vertices)->_numVerts;
    texCoords->count = vertexCount;
    positions->count = vertexCount;
    vertices->lock(positions, 1);
    vertices->lock(texCoords, 1);
}

/* Starts a layout-entry search: entries whose name is `dataName` (or every entry for "ALL") and
 * whose attribute set is `setName`. */
int beFont_FindFirstLayoutEntry(beFont *self, beBaseInfoRam *ram, int dataName, int setName) {
    dataName = internString(dataName);
    releaseString(self->_condition00);
    self->_condition00 = dataName;
    setName = internString(setName);
    releaseString(self->_condition01);
    self->_condition01 = setName;
    self->_history = 0;
    return beFont_FindNextLayoutEntry(self, ram);
}

/* Next layout entry from _history on that matches _condition00/_condition01, or -1. */
int beFont_FindNextLayoutEntry(beFont *self, beBaseInfoRam *ram) {
    int j;
    const char *name;
    int found;
    int i;
    igAttrSet *attrSet;
    const char *wanted;
    beFontInfoData *data;
    int offset;
    beBaseInfoDataList *list;
    int offset2;

    found = -1;
    list = (beBaseInfoDataList *)((beFontInfo *)ram->_parentInfo)->_dataList;
    if (strcmp((const char *)self->_condition00, ALL_3) == 0) {
        i = self->_history;
        offset = i * 4;
        if (i < list->_count) {
            do {
                wanted = (const char *)self->_condition01;
                name = (const char *)((igAttrSet *)((beFontInfoData *)*(int *)(list->_data + offset))->_attrSet)->_name;
                if (strcmp(name != 0 ? name : ((char *)emptyString), wanted) == 0) {
                    found = i;
                    break;
                }
                i += 1;
                offset += 4;
            } while (i < list->_count);
        }
    } else {
        j = self->_history;
        offset2 = j * 4;
        if (j < list->_count) {
            do {
                data = (beFontInfoData *)*(int *)(list->_data + offset2);
                name = (const char *)data->_name;
                attrSet = (igAttrSet *)data->_attrSet;
                wanted = (const char *)self->_condition00;
                if (strcmp(name != 0 ? name : ((char *)emptyString), wanted) == 0) {
                    name = (const char *)attrSet->_name;
                    wanted = (const char *)self->_condition01;
                    if (strcmp(name != 0 ? name : ((char *)emptyString), wanted) == 0) {
                        found = j;
                        break;
                    }
                }
                j += 1;
                offset2 += 4;
            } while (j < list->_count);
        }
    }
    if (found != -1) {
        self->_history = found + 1;
    }
    return found;
}

void Gap__Bec__beUnicodeObj__vfunc_08(beUnicodeObj *self) {
    if (self->_buffer != 0) {
        Memory_FreeBufferWithAllocator(self->_buffer, ((int)igObject_GetAllocator()));
    }
    Gap__Core__igObject__userDestruct(self);
}

/* Makes the buffer hold `length` UTF-16 characters and a terminator, and clears it. */
void beUnicodeObj_AllocateBuffer(beUnicodeObj *self, int length) {
    unsigned int need;
    if (self->_buffer != 0) {
        need = (length + 1) * 2;
        if (Memory_GetBufferSize(self->_buffer) < need) {
            Memory_FreeBufferWithAllocator(self->_buffer, ((int)igObject_GetAllocator(self)));
            self->_buffer = Memory_AllocateAlignedWithAllocator(need, 0x10, ((int)igObject_GetAllocator(self)));
        }
    } else {
        self->_buffer = Memory_AllocateAlignedWithAllocator((length + 1) * 2, 0x10, ((int)igObject_GetAllocator(self)));
    }
    memset(self->_buffer, 0, Memory_GetBufferSize(self->_buffer));
}

int Gap__Bec__beUnicodeObj__vfunc_20(void)
{
    return g_beUnicodeObj_metaObject[0];
}

int Gap__Bec__beFont__vfunc_20(void)
{
    return g_beFont_metaObject[0];
}
