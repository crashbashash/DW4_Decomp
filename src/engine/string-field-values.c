/* src/engine/string-field-values.c — scalar string value operations of
 * igStringMetaField (vtable 0x533180) and the igStringArrayMetaField slots
 * that share its bodies.  Recovered from retail instructions; see
 * docs/engine/string-fields.md and finding #877.
 *
 * One translation unit: 8 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time.
 *
 * A string value is a pointer to interned text ("token") owned by the
 * shared StringPool.  The pool header sits in front of the text: the
 * owner at token - 8 and a full 32-bit reference count at token - 4.
 * When the count reaches zero the header goes back to its owner through
 * StringChunk_ReleaseHeader. */
int igStringMetaField_AssignRetainedToken();
int StringPool_Construct();
void *StringPool_Intern();
int FUN_002eb010();
int StringChunk_ReleaseHeader();
extern int g_stringPool[4];
int igStrCmp(int, int);
#include "dw4/reflected.h"

/* Header stored in front of every interned string token (see above). */
typedef struct StringTokenHeader {
    int owner;
    int refCount;
} StringTokenHeader;

/* 0x0030a910
 * Interns the text behind *textCell (null stays null) and stores the token
 * into the object's string member via igStringMetaField_AssignRetainedToken,
 * then drops the temporary reference.  The shared pool at 0x586f20 is created
 * on first use. */
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
            pool = FUN_002eb010(0x10); /* allocate the 16-byte StringPool object */
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

/* 0x0030a9d0
 * Output-first retained copy: *output = *sourceCell, taking one more
 * reference on the token (shared slot of igStringArrayMetaField). */
void Gap__Core__igStringArrayMetaField__vfunc_57(void **output, void *field, void **sourceCell) {
    void *token;
    StringTokenHeader *header;

    *output = *sourceCell;
    token = *output;
    if (token != 0) {
        header = (StringTokenHeader *)token - 1;
        header->refCount = header->refCount + 1;
    }
}

/* 0x0030aa00 — value storage size: one pointer. */
int igStringMetaField_GetTypeSize(void) {
    return 4;
}

/* 0x0030ae90 — no-op value hook (docs/engine/string-fields.md). */
void igStringMetaField_SwapValue(void) {

}

/* 0x0030aea0 — no-op value hook (docs/engine/string-fields.md). */
void Gap__Core__igStringArrayMetaField__vfunc_53(void) {

}

/* 0x0030b060
 * Null-aware lexical comparison of the string members of two objects:
 * two nulls compare equal, null sorts before non-null, otherwise igStrCmp. */
int Gap__Core__igStringArrayMetaField__vfunc_44(igStringArrayMetaField *self, int objectA, int objectB) {
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

/* 0x0030b0b0 — no-op value construction (the member starts out zeroed). */
void igStringMetaField_ConstructValue(void) {

}

/* 0x0030b0c0
 * When the field is flagged _destruct, assigns a null token to the object's
 * member, which releases the string it held. */
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
