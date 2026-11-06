/* platform.h -- the platform seam (porting P2.1).
 *
 * The engine is written against **generic** platform classes and the PS2 implementations sit under
 * them, so a port implements the generic side and everything above it runs unchanged.  The seam is
 * recovered from `data/class-hierarchy.tsv` + `data/reflection.json` in the decompilation repo and
 * inventoried in `docs/engine/platform-seam.md`: **32 `igPsx2*` classes, 31 of them under 30 generic
 * interfaces carrying 153 fields** (`igPsx2IopRpcConnection` derives from `igObject` -- it is the
 * RPC seam itself and is deleted on a port).
 *
 * This table is the port's copy of that inventory, so the port knows the seam without depending on
 * the decompilation repo's data at build time.  `tools/verify_platform.py` (in `make check`) pins
 * the numbers, so if the recovered seam ever changes the mismatch shows up as a failing check
 * rather than as a stale belief.
 */
#ifndef DW4_PLATFORM_H
#define DW4_PLATFORM_H
#include <stdint.h>

typedef enum {
    DW4_IF_STUB = 0,   /* declared, not implemented: the caller gets a refusal */
    DW4_IF_HOST = 1,   /* implemented natively over host facilities */
    DW4_IF_INPUT = 2,  /* implemented as the host input source (the pad the window fills) */
} dw4_if_status;

typedef struct {
    const char *igpsx2;     /* the PS2 class the engine instantiates */
    const char *iface;      /* the generic interface it sits under -- what a port implements */
    uint16_t    fields;     /* serialised fields of the generic interface (recovered) */
    uint8_t     status;
} dw4_iface;

extern const dw4_iface dw4_ifaces[];
extern const unsigned  dw4_nifaces;

/* The seam as a whole.  `dw4_platform_status` returns the number of interfaces a host build has to
 * provide that are still stubs, and prints them when `verbose`. */
unsigned dw4_platform_status(int verbose);
unsigned dw4_platform_ifaces(void);   /* distinct generic interfaces in the table */

#endif /* DW4_PLATFORM_H */
