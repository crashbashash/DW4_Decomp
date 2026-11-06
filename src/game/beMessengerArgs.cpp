/* src/game/beMessengerArgs.cpp - beMessenger argument append and string getters
 *
 * Siblings of the result-channel accessors in beMessengerResults.cpp: each
 * Append* grows one typed list of the messenger's beMessengerArgData
 * (bool/int/float/vec3/matrix/string) by one element.  The unit is C++ with
 * exceptions on (retail keeps an exception index record for every function
 * here), built by the combat compiler with `-O3,p` (config/SLUS-20836/units.tsv); the
 * ordinary compiler lacks the original branch-alignment word after the
 * in-capacity increment.  The C-ABI names stay unmangled through the
 * extern "C" block.
 *
 * AppendInt/AppendFloat re-read the list count for the in-capacity increment
 * (retail loads it a second time rather than reusing the index), which is
 * spelled with a volatile read.  Functions are in retail address order. */
#include "dw4/reflected.h"

/* Header in front of every interned string token: the owning chunk, then the
 * token's reference count (docs/engine/messenger-results.md).  A token points
 * just past this header. */
typedef struct StringTokenHeader {
    int owner;
    int refCount;
} StringTokenHeader;

extern "C" {
void List_Resize(void *list, int newCount, int elementSize);
void Matrix44_Copy(void *, void *);
void StringList_CopyRetained(void *, void *, int);
int FUN_002eb010(int);   /* allocator for the 16-byte string pool object */
int StringPool_Construct(int);
int StringPool_Intern(int, int);
void StringChunk_ReleaseHeader(int, void *);
/* The shared string pool, created on first use (finding #1035,
 * docs/engine/messenger-results.md). */
extern int g_stringPool[4];
void beMessenger_AppendBool(beMessenger *self, char value);
void beMessenger_AppendInt(beMessenger *self, int value);
void beMessenger_AppendFloat(beMessenger *self, float value);
void beMessenger_AppendVec3(beMessenger *self, float *value);
void beMessenger_AppendMatrix(beMessenger *self, void *value);
void beMessenger_AppendString(beMessenger *self, const char *text);
int beMessenger_GetString(beMessenger *self, int index);
}

/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at p[-2]):
 * releases the token on scope exit.  AppendString binds one to the list-append call as a temporary;
 * the out-of-line copy its exception table names is the retail body StringRef_Destruct_00130720
 * (config/SLUS-20836/unit-objects.json, duplicate __dt__9StringRefFv). */
class StringRef {
public:
    int p;
    StringRef(int s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
/* The list takes its own reference to the token it is handed. */
extern "C" void StringList_AppendRetained(void *, const StringRef &);

/* 0x0038f150: append value to the messenger's bool list, growing it when full. */
void beMessenger_AppendBool(beMessenger *self, char value)
{
    int index;
    igCharList *list;

    list = (igCharList *)((beMessengerArgData *)self->_argData)->_boolList;
    index = list->_count;
    if (index < list->_capacity)
        list->_count = index + 1;
    else
        List_Resize(list, index + 1, 1);
    ((char *)list->_data)[index] = value;
}

/* 0x0038f250: append value to the messenger's int list, growing it when full. */
void beMessenger_AppendInt(beMessenger *self, int value)
{
    int index;
    igIntList *list;

    list = (igIntList *)((beMessengerArgData *)self->_argData)->_intList;
    index = list->_count;
    if (index < list->_capacity)
        list->_count = *(volatile int *)&list->_count + 1;
    else
        List_Resize(list, index + 1, 4);
    ((int *)list->_data)[index] = value;
}

/* 0x0038f350: append value to the messenger's float list, growing it when full. */
void beMessenger_AppendFloat(beMessenger *self, float value)
{
    int index;
    igFloatList *list;

    list = (igFloatList *)((beMessengerArgData *)self->_argData)->_floatList;
    index = list->_count;
    if (index < list->_capacity)
        list->_count = *(volatile int *)&list->_count + 1;
    else
        List_Resize(list, index + 1, 4);
    ((float *)list->_data)[index] = value;
}

/* 0x0038f4b0: append value to the messenger's vec3 list (copies three floats), growing it when full. */
void beMessenger_AppendVec3(beMessenger *self, float *value)
{
    int index;
    igVec3fList *list;
    float *slot;

    list = (igVec3fList *)((beMessengerArgData *)self->_argData)->_vec3fList;
    index = list->_count;
    if (index < list->_capacity)
        list->_count = index + 1;
    else
        List_Resize(list, index + 1, 12);
    slot = (float *)list->_data + index * 3;
    slot[0] = value[0];
    slot[1] = value[1];
    slot[2] = value[2];
}

/* 0x0038f5b0: append value to the messenger's matrix list (copies 64 bytes with Matrix44_Copy), growing it when full. */
void beMessenger_AppendMatrix(beMessenger *self, void *value)
{
    int index;
    igMatrix44fList *list;

    list = (igMatrix44fList *)((beMessengerArgData *)self->_argData)->_matrix44fList;
    index = list->_count;
    if (index < list->_capacity)
        list->_count = index + 1;
    else
        List_Resize(list, index + 1, 64);
    Matrix44_Copy((char *)list->_data + index * 64, value);
}

/* 0x0038f830: intern the text in the shared string pool, append the token to
 * the string list (which takes its own reference) and drop the temporary one
 * when the StringRef bound to the call goes out of scope. */
void beMessenger_AppendString(beMessenger *self, const char *text)
{
    int token;
    int pool;

    if (text == 0) {
        token = 0;
    } else {
        if (g_stringPool[0] == 0) {
            pool = FUN_002eb010(16);
            if (pool)
                pool = StringPool_Construct(pool);
            g_stringPool[0] = pool;
        }
        token = StringPool_Intern(g_stringPool[0], (int)text);
    }
    StringList_AppendRetained((void *)((beMessengerArgData *)self->_argData)->_stringList, StringRef(token));
}

/* 0x0038f8f0: return the string token at index.  The list copy is retained
 * and released again here, so the result is borrowed from the list. */
int beMessenger_GetString(beMessenger *self, int index)
{
    int slot;
    int token;
    StringTokenHeader *header;
    int refCount;

    StringList_CopyRetained(&slot, (void *)((beMessengerArgData *)self->_argData)->_stringList, index);
    token = slot;
    if (token) {
        header = (StringTokenHeader *)(token - 8);
        refCount = header->refCount - 1;
        header->refCount = refCount;
        if (!refCount)
            StringChunk_ReleaseHeader(header->owner, header);
    }
    return token;
}
