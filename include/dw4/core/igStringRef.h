#ifndef DW4_IGSTRINGREF_H
#define DW4_IGSTRINGREF_H
#include "dw4/core/StringPool.h"

/* igStringRef: a counted reference to a string interned in the shared pool, with the token header
 * the pool keeps in front of each string. */

static inline void retainString(const char *string) {
    if (string != 0) {
        StringTokenHeader *header = (StringTokenHeader *)string - 1;
        header->refCount = header->refCount + 1;
    }
}
static inline void releaseString(const char *string) {
    if (string != 0) {
        StringTokenHeader *header = (StringTokenHeader *)string - 1;
        int count = header->refCount - 1;
        header->refCount = count;
        if (count == 0) {
            StringChunk_ReleaseHeader((StringChunk *)header->owner, (StringTokenHeader *)header);
        }
    }
}
/* The shared intern pool g_stringPool, created on first use. */
struct InternedStrings {
    static inline StringPool *get() {
        if (g_stringPool == 0) {
            StringPool *pool = (StringPool *)StringPool_Allocate(16);
            if (pool != 0) {
                pool = StringPool_Construct(pool);
            }
            g_stringPool = pool;
        }
        return (StringPool *)g_stringPool;
    }
};
/* A reference to a string interned in the shared pool. Constructing or assigning from characters
 * interns them; copies share the token and count it. */
struct igStringRef {
    char *p;
    igStringRef() : p(0) {}
    igStringRef(const char *chars) {
        char *interned;
        if (chars == 0) {
            interned = 0;
        } else {
            interned = (char *)StringPool_Intern(InternedStrings::get(), chars);
        }
        p = interned;
    }
    igStringRef(const igStringRef &other) : p(other.p) { retainString(p); }
    /* Written compactly: MWCC's bottom-up inliner weighs an inline's size, and retail inlines this two base
     * destructors deep (igObjectRefArrayMetaField's vtable probe releases _poolName and _fieldName inline). */
    ~igStringRef() {
        if (p != 0) {
            StringTokenHeader *header = (StringTokenHeader *)p - 1;
            if (--header->refCount == 0) {
                StringChunk_ReleaseHeader((StringChunk *)header->owner, header);
            }
        }
    }
    igStringRef &operator=(const igStringRef &other) {
        retainString(other.p);
        releaseString(p);
        p = other.p;
        return *this;
    }
    igStringRef &operator=(const char *chars) {
        char *interned = (char *)StringPool_Intern(InternedStrings::get(), chars);
        releaseString(p);
        p = interned;
        return *this;
    }
    /* The holder as the list services take it: a pointer to the string word. */
    char *const *ref() const { return &p; }
};

/* The out-of-line igStringRef constructor (empty) and assignment other units call by name, and the
 * list read that hands out an igStringRef with a reference taken for it. */
struct igStringRefList;
extern "C" {
igStringRef *igStringRef_Construct(igStringRef *self);
igStringRef *igStringRef_Assign(igStringRef *self, const igStringRef &other);
igStringRef StringList_CopyRetained(struct igStringRefList *list, int index);
}

#endif
