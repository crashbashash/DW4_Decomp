#ifndef DW4_STRINGPOOL_H
#define DW4_STRINGPOOL_H

/* The interned-string pool. An interned string is preceded by an 8-byte header: the owning chunk,
 * then the reference count; the last release hands the header back to its chunk. */
struct StringPool;
struct StringChunk;
struct StringTokenHeader;

#ifdef __cplusplus
extern "C" {
#endif

/* The shared pool, created on first use. */
extern struct StringPool *g_stringPool;

void *StringPool_Allocate(int size);
struct StringPool *StringPool_Construct(struct StringPool *pool);
char *StringPool_Intern(struct StringPool *pool, const char *name);
void StringChunk_ReleaseHeader(struct StringChunk *self, struct StringTokenHeader *header);

#ifdef __cplusplus
}
#endif

#endif
