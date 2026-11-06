/* Generic igDataList data-pointer getter: igDataList (base of every typed list, e.g.
 * igStringRefList) holds the igMemoryRef _data at +16. */
#include "dw4/reflected.h"

int FUN_00406da0(igDataList *p)
{
    return p->_data;
}
