/* Build configuration of lvm.c for Digimon World 4. Retail reads hvalue(t) a second time for the
 * primitive get in luaV_gettable: the argument reaches MWCC through a const lvalue, which its common
 * subexpression pass does not share with the plain read in the tag test. The only call in lvm.c. */
#include "ltable.h"
#define luaH_get(L,t,key)	(luaH_get)(L, *(struct Hash *const *)&(t), key)
