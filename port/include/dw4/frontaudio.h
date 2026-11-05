#ifndef DW4_FRONTAUDIO_H
#define DW4_FRONTAUDIO_H
#include "dw4/mount.h"
#include "dw4/script.h"
typedef struct dw4_frontaudio dw4_frontaudio;
/* Title soundtrack and menu cues, resolved through the retail sound metadata. */
dw4_frontaudio *dw4_frontaudio_open(dw4_mount *);
/* Live session variant: caller executes snd_j_startback.lua on its own VM. */
dw4_frontaudio *dw4_frontaudio_open_session(dw4_mount *);
/* The same, split: prepare_work (a dw4_loadjob work function taking the dw4_mount) decodes the clips on a worker; open_session_prepared
 * takes its result, opens the output device and starts the title track. NULL in, NULL out. */
void *dw4_frontaudio_prepare_work(void *mount);
dw4_frontaudio *dw4_frontaudio_open_session_prepared(dw4_frontaudio *);
int dw4_frontaudio_script_service(void *, const char *, const dw4_script_value *,
    size_t, dw4_script_value *, char *, size_t);
/* CPU-only preparation; safe in the loading worker. Start on the main thread. */
dw4_frontaudio *dw4_frontaudio_prepare_lobby(dw4_mount *);
/* The same for a named hub stage: stagML02 (the Commander Room) prepares its own bank and alternative music; other stages
 * (and NULL) use the shared lobby set. */
dw4_frontaudio *dw4_frontaudio_prepare_lobby_stage(dw4_mount *,const char *stage);
/* Clip index playing on a voice (-1 when silent) and its VOLUMECTL2 gain multiplier; the clip's name. Test/inspection aid. */
int dw4_frontaudio_voice_clip(const dw4_frontaudio *,unsigned voice,float *level);
const char *dw4_frontaudio_clip_name(const dw4_frontaudio *,int clip);
void dw4_frontaudio_start_lobby(dw4_frontaudio *);
/* CPU-only: the named clips of a stage's sound bank (e.g. "stagml14.igb", DM_EVOLV/AM_EVOLV), no cues, no device. */
dw4_frontaudio *dw4_frontaudio_prepare_stage(dw4_mount *,const char *stage,const char *const *names,unsigned count);
/* CPU-only: a gameplay stage's whole catalogue (every effect and streamed track its sound pack names), resolved by name for the
 * typed SCSound leaf, cues and SOUND PLAY. Cues that cannot decode stay silent. NULL when the stage has no sound pack. */
dw4_frontaudio *dw4_frontaudio_prepare_gameplay(dw4_mount *,const char *stage);
/* SOUND receiver for such a stage: PLAYatPAUSE, querySD ISALLREADY, PAUSEOFF. */
int dw4_frontaudio_stage_service(void *,const char *,const dw4_script_value *,size_t,dw4_script_value *,char *,size_t);
/* 1 once the named stage clip was started (decoded and released by PAUSEOFF). */
int dw4_frontaudio_stage_playing(const dw4_frontaudio *,const char *name);
/* Open the device without issuing music commands; original start.lua owns PLAY. */
int dw4_frontaudio_start_scripted(dw4_frontaudio *);
/* Main-thread commit: move an existing mixer and replay prepared PLAY state.
 * Both owners survive failure; no source clip is borrowed after success. */
int dw4_frontaudio_adopt_device(dw4_frontaudio *,dw4_frontaudio *);
void dw4_frontaudio_tick(dw4_frontaudio *, unsigned title_frame);
/* Supply simulation time; held/paused clocks retain the same SE deadline. */
void dw4_frontaudio_set_clock(dw4_frontaudio *, uint64_t clock_ns);
/* 1 when queued; 0 for unavailable clips/devices or a suppressed SE repeat. */
int dw4_frontaudio_cue(dw4_frontaudio *, const char *);
/* Original zero-delay beSeData mapping; unknown actions are silent. */
const char *dw4_frontaudio_action_sound(const dw4_frontaudio *, const char *model, const char *action);
void dw4_frontaudio_action(dw4_frontaudio *, const char *model, const char *action);
/* Typed SCSound leaf: exact 64-bit native token plus the authored sound type.
 * Zero handle means suppressed/no device; an unknown clip returns -1. DOWN
 * targets only that voice generation and applies the retail ten-frame fade. */
int dw4_frontaudio_model_play(dw4_frontaudio *,const char *,int64_t *handle,int *type);
int dw4_frontaudio_model_down(dw4_frontaudio *,int64_t handle);
/* Sound PLAY requests seen (typed SCSound and script SOUND PLAY/PAUSEOFF), how many named no prepared clip, and the last such
 * name (NULL when none). Inspection aid. */
/* The current BGM name (retail GETCURRENTBGM, set by a music PLAY, cleared by BGMSTOP), streamed tracks started by SOUND PLAY in a
 * gameplay set, and a clip's playback gain by name (-1 when unknown). Inspection aids. */
const char *dw4_frontaudio_current_bgm(const dw4_frontaudio *);
unsigned dw4_frontaudio_stream_starts(const dw4_frontaudio *);
float dw4_frontaudio_clip_gain(const dw4_frontaudio *,const char *name);
/* The name of the index-th PLAY request (the first 16 are kept), NULL past them. Inspection aid for flow checks. */
const char *dw4_frontaudio_request_name(const dw4_frontaudio *,unsigned index);
void dw4_frontaudio_model_stats(const dw4_frontaudio *,unsigned *requests,unsigned *unresolved,const char **last);
void dw4_frontaudio_close(dw4_frontaudio *);
#endif
