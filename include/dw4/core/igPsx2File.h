#ifndef DW4_IGPSX2FILE_H
#define DW4_IGPSX2FILE_H
#include "dw4/core/igResult.h"

/* The PS2 file system's start-up settings, set before the object system starts. */
extern "C" {
extern int g_igPsx2_useCdrom;
extern const char *g_igPsx2_iopImagePath;
extern unsigned char g_igPsx2_resetIopServices;

/* Takes the "atfile:<host>," prefix from a program argument as the default file prefix; fails for
 * any other argument. */
igResult igPsx2_SetAtfilePrefix(const char *path);
/* Loads an IOP module from the directory `kind` selects, passing `argLength` bytes of `args`. */
igResult igPsx2_LoadIopModule(char *name, int kind, int argLength, const char *args);
}

#endif
