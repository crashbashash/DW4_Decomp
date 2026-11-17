#ifndef DW4_IGMOVIEMANAGERDISPATCHVIEW_H
#define DW4_IGMOVIEMANAGERDISPATCHVIEW_H
#include "dw4/core/igObjectDispatchView.h"

/* igMovieManager's virtual functions as the movie manager and the movie controller call them:
 * slot 26 stops every movie, slot 28 stops one, slot 29 builds a movie's scene, and slot 30
 * returns the state of the playing movie with a path (2 once it has finished or is not playing).
 * ABI view only: never instantiated. */
class igMovieManagerDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25();
    virtual void stopAllMovies();                                           /* slot 26 */
    virtual void d27();
    virtual int stopMovie(igObject *movie);                                 /* slot 28 */
    virtual int buildScene(igMovieInfo *movie);                             /* slot 29 */
    virtual int getMovieState(const char *path);                            /* slot 30 */
};

#endif
