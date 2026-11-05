/* Look an enum value up by its name; 0x002fba30, 260 bytes.
 * Walks the names list, comparing each retained name with igStrCmp. On a hit the
 * matching entry of the values list is stored through `value` and the success
 * status is written to `status`; otherwise the not-found status is written. */
#include "dw4/reflected.h"

typedef struct NameList {
    char pad[8];
    int count;
    int capacity;
    int *data;
} NameList;

void StringList_CopyRetained(int *out, void *list, int index);
int igStrCmp(const char *, const char *);
int StringChunk_ReleaseHeader(int, void *);
extern int DAT_004fb410[4]; /* found status */
extern int DAT_004fb418[4]; /* not-found status */

void igMetaEnum_GetValueByName(int *status, igMetaEnum *meta, const char *name, int *value)
{
    int count;
    int match;
    int index;
    int retained;
    int *header;

    if ((NameList *)meta->_names) {
        count = ((NameList *)meta->_names)->count;
        for (index = 0; index < count; ++index) {
            StringList_CopyRetained(&retained, (void *)meta->_names, index);
            match = igStrCmp((const char *)retained, name) == 0;
            if (retained) {
                header = (int *)(retained - 8);
                if (--*(int *)(retained - 4) == 0) {
                    StringChunk_ReleaseHeader(*header, header);
                }
            }
            if (match) {
                *value = ((NameList *)meta->_values)->data[index];
                *status = DAT_004fb410[0];
                return;
            }
        }
    }
    *status = DAT_004fb418[0];
}
