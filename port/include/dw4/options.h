/* dw4/options.h -- the title's Option screen settings (the manual's two: "Dungeon camera" Near/Far and
 * "Light" Soft/Hard).  They are held here so the rest of the port can read them; nothing consumes them
 * yet. The native host persists confirmed values separately in config.ini. */
#ifndef DW4_OPTIONS_H
#define DW4_OPTIONS_H

typedef struct {
    int camera_far;     /* Dungeon camera: 0 = Near, 1 = Far */
    int light_hard;     /* Light: 0 = Soft, 1 = Hard (the power-on default, as captured) */
} dw4_options;

dw4_options *dw4_options_get(void);
/* Resolve storage and load config (portable = userdata beside executable).
 * Missing files are created with defaults. Errors return -1 and report the path. */
int dw4_options_init(int portable);
/* Explicit path seam for tests/embedding; NULL disables persistence. */
int dw4_options_load(const char *path);
/* Persist only settings changed since load/last successful write. */
int dw4_options_save(void);
const char *dw4_options_path(void);

#endif /* DW4_OPTIONS_H */
