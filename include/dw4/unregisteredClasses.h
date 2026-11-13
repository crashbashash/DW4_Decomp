#ifndef DW4_UNREGISTERED_CLASSES_H
#define DW4_UNREGISTERED_CLASSES_H
#include "dw4/reflected.h"

/* Alchemy classes the PS2 build never registers, so data/reflection.json has no record of them; only
 * the libraries' static smart pointers to them survive. The GameCube build registers them: the names
 * and bases are its registration calls' (docs/engine/emitted-functions.md, Static initialisers). */
typedef struct igCustomVectorStateList : public igObjectList {} igCustomVectorStateList;
typedef struct igCustomMatrixStateList : public igObjectList {} igCustomMatrixStateList;
typedef struct igNodeUsageObjectDefinitionList : public igObjectList {} igNodeUsageObjectDefinitionList;

#endif
