/* Stage sound catalogue (dw4/stagesound.h) and the gameplay adapter (dw4_frontaudio_prepare_gameplay) against the retail assets.
 * The whole-game numbers below were measured from every shipped igb with a sound pack (39 stag* stages and 57 dng* dungeons); a change in them means the reader changed. */
#define _DEFAULT_SOURCE
#include "dw4/frontaudio.h"
#include "dw4/sfp.h"
#include "dw4/stagesound.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define SD(cmd, ...) do { dw4_script_value a_[] = {{DW4_SCRIPT_STRING, 0, "SOUND", 5}, {0}, {DW4_SCRIPT_NUMBER, -1, NULL, 0}, \
                          {DW4_SCRIPT_STRING, 0, cmd, strlen(cmd)}, ##__VA_ARGS__}; \
                          assert(!dw4_frontaudio_script_service(a, "sd", a_, sizeof a_ / sizeof *a_, &r0, err, sizeof err)); } while (0)
#define NAME(n) {DW4_SCRIPT_STRING, 0, n, strlen(n)}

int main(int argc, char **argv)
{
    dw4_mount m;
    unsigned streams = 0, files = 0, packs = 0, cues = 0, ok = 0, bad_file = 0, noseq = 0, nowave = 0, nobank = 0, nostream = 0, open2 = 0;
    assert(!dw4_mount_open(&m, argc > 1 ? argv[1] : "../../local/extracted"));
    /* The reference scanner must not overflow on a long digit run (it used to, on non-stage files). */
    {
        const uint8_t junk[] = "x[3333333333333.1]y[0.99999999999999]z[1.2] ";
        const uint8_t ok[] = "pad [0.620] pad";
        dw4_ref r[4];
        assert(dw4_mount_scan_refs(junk, sizeof junk - 1, r, 4) == 1 && r[0].pt == 1 && r[0].entry == 2);
        assert(dw4_mount_scan_refs(ok, sizeof ok - 1, r, 4) == 1 && r[0].pt == 0 && r[0].entry == 620);
    }
    for (uint32_t i = 0; i < m.man.nfiles; i++) {
        const char *n = m.man.files[i].name;
        size_t len = n ? strlen(n) : 0;
        dw4_stagesound *s;
        if (!n || len < 5 || strcasecmp(n + len - 4, ".igb")) continue;
        files++;
        s = dw4_stagesound_open(&m, n);
        if (!s) continue;
        packs++;
        for (unsigned k = 0; k < dw4_stagesound_count(s); k++) {
            const dw4_stagesound_entry *e = dw4_stagesound_at(s, k);
            dw4_audio_clip c = {0};
            int rc;
            cues++;
            if (!e->file[0]) bad_file++;
            if (e->type == 1 || e->type == 2) {
                /* Streamed tracks: the ADX entry must exist with a valid header (decoding them is covered by the title/lobby checks). */
                int pt, entry;
                uint32_t size;
                const uint8_t *p;
                assert(sscanf(e->file, "[%d.%d]", &pt, &entry) == 2);
                p = dw4_mount_entry(&m, pt, entry, &size, NULL);
                assert(p && size > 0x38 && p[0] == 0x80 && p[1] == 0);
                streams++;
                continue;
            }
            rc = dw4_stagesound_decode(s, &m, e, &c, NULL);
            if (!rc) { ok++; assert(c.pcm && c.frames); }
            else if (rc == DW4_STAGESOUND_NOSEQ) { noseq++; if (!strcmp(e->name, "WINDOW_OPEN2")) open2++; }
            else if (rc == DW4_STAGESOUND_NOWAVE) nowave++;
            else if (rc == DW4_STAGESOUND_NOBANK) nobank++;
            else nostream++;
            dw4_audio_clip_free(&c);
        }
        dw4_stagesound_close(s);
    }
    printf("stagesound: %u igb files, %u with a sound pack, %u cues (%u streams with an ADX entry), %u resident decode, %u unresolved file names\n",
           files, packs, cues, streams, ok, bad_file);
    printf("stagesound: undecoded: sequence %u (WINDOW_OPEN2 %u), waveform %u, bank %u, stream %u\n", noseq, open2, nowave, nobank, nostream);
    assert(files == 2076 && packs == 96 && cues == 8855 && bad_file == 0);
    assert(streams == 326 && ok == 8433 && noseq == 96 && open2 == 96 && nowave == 0 && nobank == 0 && nostream == 0);   /* one WINDOW_OPEN2 per pack */

    /* stag0403's bank has 48 kHz records inside its 24 kHz table: all nine entries are listed (the walk used to stop at four). */
    {
        uint32_t size;
        const uint8_t *pack = dw4_mount_entry(&m, 0, 715, &size, NULL);
        dw4_sfp_bank banks[8];
        dw4_sfp_entry e[16];
        unsigned nb;
        assert(pack && (nb = dw4_sfp_scan(pack, size, banks, 8)) == 3);
        assert(dw4_sfp_entries(pack, size, &banks[2], e, 16) == 9);
        for (unsigned k = 0; k < 9; k++) assert(e[k].rate == (k == 4 ? 48000u : 24000u) && e[k].end > e[k].start);
        assert(dw4_sfp_entries(pack, size, &banks[0], e, 16) == 4);   /* common_blst: unchanged */
    }
    /* The cannon banks of stag0401 share a size, so their names can land on each other's bank; the cue's group tag still finds it. */
    {
        dw4_stagesound *s = dw4_stagesound_open(&m, "stag0401.igb");
        const char *const cues[] = {"cmBLST01", "cmWIT2ON", "csBLST01", "csWIT2ON"};
        assert(s);
        for (unsigned k = 0; k < 4; k++) {
            const dw4_stagesound_entry *e = dw4_stagesound_find(s, cues[k]);
            dw4_audio_clip c = {0};
            assert(e && strstr(e->file, "cannon.sfp") && !dw4_stagesound_decode(s, &m, e, &c, NULL) && c.frames);
            dw4_audio_clip_free(&c);
        }
        dw4_stagesound_close(s);
    }
    /* stag0102: the first mission stage. */
    {
        dw4_stagesound *s = dw4_stagesound_open(&m, "stag0102.igb");
        unsigned types[8] = {0};
        const dw4_stagesound_entry *e;
        assert(s && dw4_stagesound_count(s) == 101);
        for (unsigned k = 0; k < dw4_stagesound_count(s); k++) types[dw4_stagesound_at(s, k)->type & 7]++;
        assert(types[1] == 2 && types[2] == 1 && types[3] == 83 && types[4] == 15);
        e = dw4_stagesound_find(s, "AM_VALLE");
        assert(e && e->type == 2 && e->volume == -130 && e->base_volume == -30 && !strcmp(e->file, "[0.23]"));
        e = dw4_stagesound_find(s, "goDEAD01");
        assert(e && e->type == 3 && strstr(e->file, "e_goburi.sfp"));
        e = dw4_stagesound_find(s, "PC_JUMP");
        assert(e && e->type == 3 && strstr(e->file, "allse.sfp"));
        assert(!dw4_stagesound_find(s, "no_such_cue") && !dw4_stagesound_find(s, NULL));
        assert(!dw4_stagesound_at(s, 101) && dw4_stagesound_count(NULL) == 0);
        dw4_stagesound_close(s);
    }
    assert(!dw4_stagesound_open(&m, "stag0000.igb") && !dw4_stagesound_open(&m, "nosuchstage.igb"));

    /* The velocity byte after the note: 0x69 for the warp cue in the shared bank, while the two-event window sound stays unsupported. */
    {
        uint32_t size, wave;
        unsigned velocity = 0;
        const uint8_t *bank_data = dw4_mount_entry(&m, 0, 897, &size, NULL);
        dw4_sfp_bank bank[2];
        assert(bank_data && dw4_sfp_scan(bank_data, size, bank, 2) == 1);
        assert(!dw4_sfp_resolve_note(bank_data, size, bank, 0x000d00a9, &wave, &velocity) && velocity == 0x69);
        assert(!dw4_sfp_resolve_note(bank_data, size, bank, 0x000102a9, &wave, &velocity) && velocity == 0x7f && wave == 29);
        assert(dw4_sfp_resolve_note(bank_data, size, bank, 0x000702a9, &wave, &velocity));
    }

    /* The adapter: names resolve from the catalogue, effects play with a device, undecodable and unknown names fail explicitly. */
    {
        dw4_frontaudio *a = dw4_frontaudio_prepare_gameplay(&m, "stag0102.igb");
        int64_t handle = 7;
        int type = 7;
        assert(a);
        assert(dw4_frontaudio_model_play(a, "no_such_cue", &handle, &type) == -1 && handle == 0);
        assert(dw4_frontaudio_model_play(a, "WINDOW_OPEN2", &handle, &type) == -1);   /* two-event sequence: left silent */
        assert(dw4_frontaudio_model_play(a, "PC_JUMP", &handle, &type) == 0 && type == 3 && handle == 0);   /* no device yet */
        assert(dw4_frontaudio_model_play(a, "goDEAD01", &handle, &type) == 0 && type == 3);
        assert(dw4_frontaudio_model_play(a, "plWARP01", &handle, &type) == 0 && type == 3);
        assert(dw4_frontaudio_action_sound(a, "no_model", "no_action") == NULL);
        if (!getenv("DW4_TEST_NO_DEVICE")) {
            assert(!setenv("SDL_AUDIODRIVER", "dummy", 1));
            if (!dw4_frontaudio_start_scripted(a)) {
                dw4_frontaudio_set_clock(a, 1000000000ull);
                assert(dw4_frontaudio_model_play(a, "PC_JUMP", &handle, &type) == 0 && type == 3 && handle > 0);
                /* the same cue inside the 49,999,998 ns repeat window is suppressed, a different one is not */
                dw4_frontaudio_set_clock(a, 1010000000ull);
                assert(dw4_frontaudio_model_play(a, "PC_JUMP", &handle, &type) == 0 && handle == 0);
                assert(dw4_frontaudio_model_play(a, "goDEAD01", &handle, &type) == 0 && handle > 0);
                dw4_frontaudio_set_clock(a, 1060000000ull);
                assert(dw4_frontaudio_model_play(a, "PC_JUMP", &handle, &type) == 0 && handle > 0);
                {
                    dw4_script_value args[] = {{DW4_SCRIPT_STRING, 0, "SOUND", 5}, {0}, {DW4_SCRIPT_NUMBER, -1, NULL, 0},
                        {DW4_SCRIPT_STRING, 0, "PLAY", 4}, {DW4_SCRIPT_STRING, 0, "AM_VALLE", 8}}, result = {0};
                    char error[128];
                    float level;
                    assert(!dw4_frontaudio_script_service(a, "sd", args, 5, &result, error, sizeof error));
                    assert(dw4_frontaudio_voice_clip(a, 1, &level) >= 0 && !strcmp(dw4_frontaudio_clip_name(a, dw4_frontaudio_voice_clip(a, 1, &level)), "AM_VALLE"));
                }
                /* The retail effect pool: 48 sound-bank handles and 4 ADX handles (voices 12..59 and 8..11), reuse by priority when all are busy. */
                {
                    dw4_stagesound *cat = dw4_stagesound_open(&m, "stag0102.igb");
                    const char *longcue[64];
                    unsigned nlong = 0;
                    dw4_script_value r0 = {0};
                    char err[128];
                    float lvl;
                    assert(cat);
                    for (unsigned k = 0; k < dw4_stagesound_count(cat) && nlong < 64; k++) {
                        const dw4_stagesound_entry *e = dw4_stagesound_at(cat, k);
                        dw4_audio_clip c = {0};
                        if ((e->type != 3 && e->type != 4) || e->file[0] == '[' || dw4_stagesound_find(cat, e->name) != e) continue;
                        if (!dw4_stagesound_decode(cat, &m, e, &c, NULL) && c.frames >= 24000) longcue[nlong++] = e->name;   /* at least 0.5 s */
                        dw4_audio_clip_free(&c);
                    }
                    assert(nlong >= 49);
                    dw4_frontaudio_set_clock(a, 10000000000ull);
                    SD("SESTOP");   /* start from a free pool: the earlier checks left a few effects playing */
                    for (unsigned k = 0; k < 12; k++) assert(dw4_frontaudio_model_play(a, longcue[k], &handle, &type) == 0 && handle > 0);
                    {   /* twelve effects sound at once: more than the five rotating voices the title and lobby sets use */
                        unsigned active = 0;
                        for (unsigned v = 12; v < 60; v++) active += dw4_frontaudio_voice_clip(a, v, &lvl) >= 0;
                        assert(active == 12);
                    }
                    for (unsigned k = 12; k < 48; k++) assert(dw4_frontaudio_model_play(a, longcue[k], &handle, &type) == 0 && handle > 0);
                    {
                        unsigned active = 0;
                        for (unsigned v = 12; v < 60; v++) active += dw4_frontaudio_voice_clip(a, v, &lvl) >= 0;
                        assert(active == 48);
                    }
                    /* the 49th cue finds every sound-bank handle busy at the same priority and reuses the oldest one (the first cue's) */
                    assert(dw4_frontaudio_model_play(a, longcue[48], &handle, &type) == 0 && handle > 0);
                    {
                        int first = dw4_frontaudio_voice_clip(a, 12, &lvl);
                        assert(first >= 0 && !strcmp(dw4_frontaudio_clip_name(a, first), longcue[48]));
                        for (unsigned v = 13; v < 60; v++) assert(strcmp(dw4_frontaudio_clip_name(a, dw4_frontaudio_voice_clip(a, v, &lvl)), longcue[0]));
                    }
                    /* an effect whose file is an ADX entry takes one of the 4 ADX handles and the stream level */
                    assert(dw4_frontaudio_model_play(a, "BT_WIN03", &handle, &type) == 0 && type == 3 && handle > 0);
                    {
                        unsigned adx = 0;
                        for (unsigned v = 8; v < 12; v++) {
                            int c = dw4_frontaudio_voice_clip(a, v, &lvl);
                            adx += c >= 0 && !strcmp(dw4_frontaudio_clip_name(a, c), "BT_WIN03");
                        }
                        assert(adx == 1);
                        assert(dw4_frontaudio_clip_gain(a, "BT_WIN03") > 0.7f && dw4_frontaudio_clip_gain(a, "BT_WIN03") < 0.71f);   /* 181/256 */
                        assert(dw4_frontaudio_clip_gain(a, "PC_JUMP") == 1.0f);
                    }
                    /* SESTOP stops the effect handles and clears the pool; ENVSTOP the ambience; BGMSTOP the music and the current name */
                    SD("SESTOP");
                    for (unsigned v = 8; v < 60; v++) assert(dw4_frontaudio_voice_clip(a, v, &lvl) < 0);
                    dw4_frontaudio_set_clock(a, 10100000000ull);   /* past the 49,999,998 ns repeat window of the first plays */
                    assert(dw4_frontaudio_model_play(a, longcue[0], &handle, &type) == 0 && handle > 0);   /* the pool is free again */
                    /* music: a repeat PLAY of the current BGM does not restart it; BGMSTOP needs no name and clears it */
                    {
                        unsigned starts = dw4_frontaudio_stream_starts(a);
                        SD("PLAY", NAME("BT_SBOSS"));
                        assert(dw4_frontaudio_stream_starts(a) == starts + 1 && !strcmp(dw4_frontaudio_current_bgm(a), "BT_SBOSS"));
                        SD("PLAY", NAME("BT_SBOSS"));
                        assert(dw4_frontaudio_stream_starts(a) == starts + 1);
                        /* a different music request finds the slot busy: BT_SBOSS fades down (10 frames) and the request is retried 11 frames
                         * later, when the old track has stopped */
                        dw4_frontaudio_set_clock(a, 30000000000ull);
                        SD("PLAY", NAME("ST_DEATH"));
                        assert(dw4_frontaudio_stream_starts(a) == starts + 1 && !strcmp(dw4_frontaudio_current_bgm(a), "BT_SBOSS"));
                        assert(dw4_frontaudio_voice_clip(a, 0, &lvl) >= 0 && !strcmp(dw4_frontaudio_clip_name(a, dw4_frontaudio_voice_clip(a, 0, &lvl)), "BT_SBOSS"));
                        dw4_frontaudio_set_clock(a, 30050000000ull);   /* 3 frames: still fading, not yet stopped */
                        assert(dw4_frontaudio_voice_clip(a, 0, &lvl) >= 0 && lvl > 0.0f && lvl < 1.0f);
                        dw4_frontaudio_set_clock(a, 30200000000ull);   /* past the retry: BT_SBOSS stopped, ST_DEATH started */
                        assert(dw4_frontaudio_stream_starts(a) == starts + 2 && !strcmp(dw4_frontaudio_current_bgm(a), "ST_DEATH"));
                        assert(dw4_frontaudio_voice_clip(a, 0, &lvl) >= 0 && !strcmp(dw4_frontaudio_clip_name(a, dw4_frontaudio_voice_clip(a, 0, &lvl)), "ST_DEATH") && lvl == 1.0f);
                        SD("BGMSTOP");
                        assert(!dw4_frontaudio_current_bgm(a) && dw4_frontaudio_voice_clip(a, 0, &lvl) < 0);
                        SD("PLAY", NAME("ST_DEATH"));
                        assert(dw4_frontaudio_stream_starts(a) == starts + 3);
                        SD("PLAY", NAME("AM_VALLE"));   /* ambience has no current name and is stopped by ENVSTOP */
                        assert(dw4_frontaudio_voice_clip(a, 1, &lvl) >= 0);
                        /* a stream fade follows the retail ease-table ramp: 0.90 when armed and 0.625 a frame later; AM_VALLE rests at level -160, so
                         * the fade-down passes -209 on frame 2 and beCri::vfunc_27 stops the stream */
                        dw4_frontaudio_set_clock(a, 20000000000ull);
                        SD("VOLUMECTL2", NAME("AM_VALLE/F<1>/F<0>/F<10>"));
                        assert(dw4_frontaudio_voice_clip(a, 1, &lvl) >= 0 && lvl > 0.89f && lvl < 0.91f);
                        dw4_frontaudio_set_clock(a, 20016666667ull);
                        assert(dw4_frontaudio_voice_clip(a, 1, &lvl) >= 0 && lvl > 0.624f && lvl < 0.626f);
                        dw4_frontaudio_set_clock(a, 20033333334ull);   /* frame 2 */
                        assert(dw4_frontaudio_voice_clip(a, 1, &lvl) < 0);
                        SD("PLAY", NAME("AM_VALLE"));
                        assert(dw4_frontaudio_voice_clip(a, 1, &lvl) >= 0 && lvl == 1.0f);
                        SD("ENVSTOP");
                        assert(dw4_frontaudio_voice_clip(a, 1, &lvl) < 0 && dw4_frontaudio_voice_clip(a, 0, &lvl) >= 0);
                    }
                    dw4_stagesound_close(cat);
                }
            } else puts("stagesound: no audio device; device checks skipped");
        }
        dw4_frontaudio_close(a);
    }
    assert(!dw4_frontaudio_prepare_gameplay(&m, "stag0000.igb"));
    dw4_mount_close(&m);
    puts("stagesound: OK");
    return 0;
}
