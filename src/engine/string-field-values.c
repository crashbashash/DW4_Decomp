/* Scalar string value operations of igStringMetaField (vtable 0x533180) and the
 * igStringArrayMetaField slots that share its bodies. A string value is a pointer to interned text
 * (a token) owned by the shared StringPool. The pool header sits in front of the text: the owner
 * at token - 8 and a 32-bit reference count at token - 4. When the count reaches zero the header
 * goes back to its owner through StringChunk_ReleaseHeader. */
int igStringMetaField_AssignRetainedToken();
int StringPool_Construct();
void *StringPool_Intern();
int FUN_002eb010();
int StringChunk_ReleaseHeader();
extern int g_stringPool[4];
int igStrCmp(int, int);
#include "dw4/reflected.h"

typedef struct StringTokenHeader {
    int owner;
    int refCount;
} StringTokenHeader;

/* Interns the text behind *textCell (null stays null), stores the token via
 * igStringMetaField_AssignRetainedToken, then drops the temporary reference. The shared pool is
 * created on first use. */
void igStringMetaField_AssignText(igStringMetaField *self, int object, int *textCell) {
    void *token;
    StringTokenHeader *header;
    int text;
    int count;
    int pool;
    void *interned;

    text = *textCell;
    if (text == 0) {
        interned = 0;
    } else {
        if (g_stringPool[0] == 0) {
            pool = FUN_002eb010(0x10);
            if (pool != 0) {
                pool = StringPool_Construct(pool);
            }
            g_stringPool[0] = pool;
        }
        interned = StringPool_Intern(g_stringPool[0], text);
    }
    token = interned;
    igStringMetaField_AssignRetainedToken(self, object, &token);
    if (token != 0) {
        header = (StringTokenHeader *)token - 1;
        count = header->refCount - 1;
        header->refCount = count;
        if (count == 0) {
            StringChunk_ReleaseHeader(header->owner, header);
        }
    }
}

/* Output-first retained copy: *output = *sourceCell, taking one more reference on the token. */
void Gap__Core__igStringMetaField__vfunc_57(void **output, void *field, void **sourceCell) {
    void *token;
    StringTokenHeader *header;

    *output = *sourceCell;
    token = *output;
    if (token != 0) {
        header = (StringTokenHeader *)token - 1;
        header->refCount = header->refCount + 1;
    }
}

/* Value storage size: one pointer. */
int igStringMetaField_GetTypeSize(void) {
    return 4;
}

/* no-op value hook. */
void igStringMetaField_SwapValue(void) {

}

/* no-op value hook. */
void Gap__Core__igStringMetaField__vfunc_53(void) {

}

/* Null-aware lexical comparison: two nulls compare equal, null sorts before non-null, otherwise
 * igStrCmp. */
int Gap__Core__igStringMetaField__vfunc_44(igStringArrayMetaField *self, int objectA, int objectB) {
    int tokenA;
    int tokenB;
    int offset;

    offset = self->_offset;
    tokenA = *(int *)(objectA + offset);
    tokenB = *(int *)(objectB + offset);
    if (tokenA == 0) {
        return -(tokenB != 0);
    }
    if (tokenB == 0) {
        return 1;
    }
    return igStrCmp(tokenA, tokenB);
}

void igStringMetaField_ConstructValue(void) {

}

/* When the field is flagged _destruct, assigns a null token to the object's member, which releases
 * the string it held. */
void igStringMetaField_DestructValue(igStringMetaField *self, int object) {
    void *token;
    StringTokenHeader *header;
    int count;
    if (self->_destruct != 0) {
        token = 0;
        igStringMetaField_AssignRetainedToken(self, object, &token);
        if (token != 0) {
            header = (StringTokenHeader *)token - 1;
            count = header->refCount - 1;
            header->refCount = count;
            if (count == 0) {
                StringChunk_ReleaseHeader(header->owner, header);
            }
        }
    }
}
