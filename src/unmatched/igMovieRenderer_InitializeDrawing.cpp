/* On first use (no movie manager yet, flag byte clear) probes the platform with FUN_00308320 and
 * latches the flag when it answers 2, then hands the renderer's visual context to the movie
 * manager (FUN_00339110) through a counted reference that this call releases afterwards. */
#include "dw4/igSmartPointer.h"
extern "C" {
int FUN_00308320(int *);
extern int DAT_005012f0[4];
extern unsigned char GPR_00554e4c;
void igMovieRenderer_InitializeDrawing(igMovieRenderer *arg0);
}
/* Counted reference to an igObject: takes a reference on construction and drops it on scope exit
 * (reference count in the low 23 bits of _refCount). */

extern "C" int FUN_00339110(int, igSmartPointer<igObject>);
void igMovieRenderer_InitializeDrawing(igMovieRenderer *arg0) {
    int temp_v0;

    if ((arg0->_movieManager == 0) && (GPR_00554e4c == 0)) {
        temp_v0 = FUN_00308320(&DAT_005012f0[0]);
        if ((temp_v0 != 1) && (temp_v0 == 2)) {
            GPR_00554e4c = 1;
        }
    }
    FUN_00339110(arg0->_movieManager, igSmartPointer<igObject>((igObject *)arg0->_visualContext, kRetainReference));
}
