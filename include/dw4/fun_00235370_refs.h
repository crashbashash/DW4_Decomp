#ifndef FUN_00235370_REFS_H
#define FUN_00235370_REFS_H

/* The inlined string smart-pointer destructor (retail expands it at every use site;
 * MWCC at this flag set does not inline functions).  The object release is the shared
 * IG_OBJECT_RELEASE in dw4/igobject_release.h. */
#define ReleaseString(str) \
    do { \
        char *_s = (str); \
        if (_s != 0) { \
            StringHeader *_h = (StringHeader *)_s - 1; \
            if (--_h->refCount == 0) { \
                StringChunk_ReleaseHeader(_h->owner, _h); \
            } \
        } \
    } while (0)

#endif
