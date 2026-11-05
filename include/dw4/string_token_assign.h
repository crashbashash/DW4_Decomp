/* string_token_assign.h - the interned-string member assignment used by FUN_002f31b0.
 * (Header because tools/units.py cannot split a unit around a file-scope multi-line macro.
 * Expects the caller to declare: const char *text; StringToken *token, *old; StringTokenHeader *header; int poolObj;
 * and the extern pool/token declarations.) */
/* handle.field = interned(text), releasing the previous token (shared pool created on first use) */
#define ASSIGN_TOKEN(field, source)                                           \
    text = (source);                                                          \
    if (DAT_00586f20[0] == 0) {                                               \
        poolObj = FUN_002eb010(16);                                           \
        if (poolObj != 0) {                                                   \
            poolObj = StringPool_Construct(poolObj);                          \
        }                                                                     \
        DAT_00586f20[0] = poolObj;                                            \
    }                                                                         \
    token = StringPool_Intern(DAT_00586f20[0], text);          \
    old = (field);                                                            \
    if (old != 0) {                                                           \
        header = (StringTokenHeader *)old - 1;                                \
        count = header->refCount - 1;                                         \
        header->refCount = count;                                             \
        if (count == 0) {                                                     \
            StringChunk_ReleaseHeader(header->owner, header);                 \
        }                                                                     \
    }                                                                         \
    (field) = token

/* Same, but the text expression is evaluated at the intern call (no earlier load). */
#define ASSIGN_TOKEN_DIRECT(field, source)                                           \
    if (DAT_00586f20[0] == 0) {                                               \
        poolObj = FUN_002eb010(16);                                           \
        if (poolObj != 0) {                                                   \
            poolObj = StringPool_Construct(poolObj);                          \
        }                                                                     \
        DAT_00586f20[0] = poolObj;                                            \
    }                                                                         \
    token = StringPool_Intern(DAT_00586f20[0], (source));          \
    old = (field);                                                            \
    if (old != 0) {                                                           \
        header = (StringTokenHeader *)old - 1;                                \
        count = header->refCount - 1;                                         \
        header->refCount = count;                                             \
        if (count == 0) {                                                     \
            StringChunk_ReleaseHeader(header->owner, header);                 \
        }                                                                     \
    }                                                                         \
    (field) = token

