/* newlib's malloc statistics, as its malloc.h declares them. */
#ifndef NEWLIB_MALLINFO_H
#define NEWLIB_MALLINFO_H

#ifdef __cplusplus
extern "C" {
#endif

struct mallinfo { int arena; int ordblks; int smblks; int hblks; int hblkhd; int usmblks; int fsmblks; int uordblks; int fordblks; int keepcost; };

/* The allocator's current totals: `arena` bytes taken from the system, `uordblks` of them in use. */
struct mallinfo mallinfo(void);

#ifdef __cplusplus
}
#endif

#endif
