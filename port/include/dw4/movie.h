/* dw4/movie.h — the front-end's Sofdec movies as a frame source (P3.6).
 *
 * The boot opens with a CRI Sofdec movie (`aus_opening.sfd`, `AREA.AFS`), which the decompilation
 * side has already settled as **MPEG-1 video + ADX audio**.  The project's FMV
 * route is ffmpeg (`dw4asset media`), so this decodes the movie's video stream to raw frames and
 * hands them to the caller a frame at a time — the seam the native MPEG-1/ADX decoders will
 * replace without the caller changing. Windowed playback decodes ADX audio through
 * ffmpeg and plays it through SDL2, pacing video to the host audio sample clock.
 */
#ifndef DW4_MOVIE_H
#define DW4_MOVIE_H

#include <stdint.h>

typedef struct dw4_movie dw4_movie;

/* Open a movie by manifest name (e.g. "aus_opening.sfd") out of `roms_dir`'s archives.  On
 * success `*w`/`*h` are the video stream's own size.  Returns NULL when the name does not
 * resolve or the decoder cannot start. */
dw4_movie *dw4_movie_open(const char *roms_dir, const char *name, int *w, int *h);

/* Read the next frame as RGBA8888 (row-major, `w*h*4`, top-down).  Returns 0, or -1 at the
 * end of the stream (or on a short read). */
int dw4_movie_frame(dw4_movie *mv, uint8_t *rgba);

/* Play a movie to the end, presenting through the host window when `use_window` is set (and
 * silently decoding when it is not).  Paced to the stream's own frame rate, so a decode that runs
 * faster than real time still plays at the movie's speed.  Returns 0 when at least one frame
 * played.
 *
 * `input_script` is the run's frame-indexed input timeline (see `dw4/input.h`); when it is not
 * NULL it is applied to each movie frame, so a scripted `cross` skips the FMV the same way the
 * keyboard does. */
int dw4_movie_play(const char *roms_dir, const char *name, int use_window, int headless,
                   int software_reference,int show_fps, const char *input_script);

/* The same, but presenting into a window/swapchain the caller already owns — the boot shares its
 * own window with the opening FMV, so the whole front-end is one window (and closing it during the
 * movie ends the run).  Either handle may be NULL (no presentation).  Returns 0 when it played,
 * 1 when nothing played, and -1 when the user closed the window.  The opening FMV is skippable:
 * Cross (Space or Enter on the keyboard) stops it and returns 0 with at least one frame played. */
struct dw4_window;
struct dw4_vk;
int dw4_movie_play_in(const char *roms_dir, const char *name, struct dw4_window *win,
                      struct dw4_vk *vk, int show_fps, const char *input_script);

void dw4_movie_close(dw4_movie *mv);

#endif /* DW4_MOVIE_H */
