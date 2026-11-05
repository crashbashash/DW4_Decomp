/* Survey of every sound-pack stage file's catalogue (stag*.igb and the dng*.igb dungeons) (dw4/stagesound.h): which stages carry a sound pack, how many cues, which
 * types and files. With a stage name it lists that stage's cues. Diagnostic only. */
#include "dw4/stagesound.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

int main(int argc, char **argv)
{
    dw4_mount m;
    if (dw4_mount_open(&m, argc > 1 ? argv[1] : "../../local/extracted")) { fprintf(stderr, "mount failed\n"); return 1; }
    if (argc > 2 && !strcmp(argv[2], "--names")) {
        /* Every cue of every sound-pack file, no decoding: "<file> <cue> <type> <channel> <priority> <volume>" per line (verify_stagesound_lua.py reads it). */
        for (uint32_t i = 0; i < m.man.nfiles; i++) {
            const char *n = m.man.files[i].name;
            size_t len = n ? strlen(n) : 0;
            dw4_stagesound *s;
            if (!n || len < 5 || strcasecmp(n + len - 4, ".igb")) continue;
            s = dw4_stagesound_open(&m, n);
            if (!s) continue;
            for (unsigned k = 0; k < dw4_stagesound_count(s); k++) { const dw4_stagesound_entry *e = dw4_stagesound_at(s, k); printf("%s %s %d %d %d %d\n", n, e->name, e->type, e->channel, e->priority, e->volume); }
            dw4_stagesound_close(s);
        }
        return 0;
    }
    if (argc > 2) {
        dw4_stagesound *s = dw4_stagesound_open(&m, argv[2]);
        if (!s) { printf("%s: no sound pack\n", argv[2]); return 0; }
        for (unsigned i = 0; i < dw4_stagesound_count(s); i++) {
            const dw4_stagesound_entry *e = dw4_stagesound_at(s, i);
            dw4_audio_clip c = {0};
            int rc = dw4_stagesound_decode(s, &m, e, &c, "survey");
            printf("%-28s pack %d type %d vol %4d(+%d) ch %d prio %d seq %u/%u  %s%s\n", e->name, e->pack, e->type, e->volume,
                   e->base_volume, e->channel, e->priority, e->memory_idx >> 16, e->memory_idx & 0xffff, e->file, rc ? (rc == DW4_STAGESOUND_NOBANK ? "  [DECODE FAILED: no bank]" : rc == DW4_STAGESOUND_NOSEQ ? "  [DECODE FAILED: sequence]" : rc == DW4_STAGESOUND_NOWAVE ? "  [DECODE FAILED: waveform]" : "  [DECODE FAILED: file]") : "");
            if (rc == DW4_STAGESOUND_NOSEQ) {
                const uint8_t *ev; size_t av;
                if (!dw4_stagesound_events(s, e, &ev, &av)) { printf("    events:"); for (size_t k = 0; k < 40 && k < av; k++) printf(" %02x", ev[k]); printf("\n"); }
                else printf("    events: unresolvable selector\n");
            }
            dw4_audio_clip_free(&c);
        }
        dw4_stagesound_close(s);
        return 0;
    }
    for (uint32_t i = 0; i < m.man.nfiles; i++) {
        const char *n = m.man.files[i].name;
        size_t len = n ? strlen(n) : 0;
        if (!n || len < 5 || strcasecmp(n + len - 4, ".igb")) continue;
        dw4_stagesound *s = dw4_stagesound_open(&m, n);
        unsigned cnt = dw4_stagesound_count(s), types[8] = {0}, bad = 0;
        if (!s) continue;
        for (unsigned k = 0; k < cnt; k++) {
            const dw4_stagesound_entry *e = dw4_stagesound_at(s, k);
            if (e->type >= 0 && e->type < 8) types[e->type]++;
            if (!e->file[0]) bad++;
        }
        printf("%-16s %3u cues  types", n, cnt);
        for (int t = 0; t < 8; t++) if (types[t]) printf(" %d:%u", t, types[t]);
        printf("  unresolved-file %u\n", bad);
        dw4_stagesound_close(s);
    }
    return 0;
}
