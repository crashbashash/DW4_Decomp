#include "dw4/reflected.h"

extern "C" {
int FUN_00390320(void *node, igCommonTraversal *traversal, void *data);
int FUN_003902f0(igCommonTraversal *traversal, void *node);
}

int FUN_003902f0(igCommonTraversal *traversal, void *node)
{
    return FUN_00390320(node, traversal, node);
}
