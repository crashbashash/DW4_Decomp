/* Host PCM playback. Clips are immutable; retain them until their device is closed
 * or the voice is stopped. ffmpeg supplies 48 kHz signed-16 stereo PCM. */
#ifndef DW4_AUDIO_H
#define DW4_AUDIO_H
#include <stddef.h>
#include <stdint.h>
typedef struct dw4_audio dw4_audio;
typedef struct {
    int16_t *pcm;
    size_t frames, loop_start, loop_end;
} dw4_audio_clip;
/* Startup default for subsequently opened devices; clocks/voices still advance. */
void dw4_audio_set_muted(int muted);
dw4_audio *dw4_audio_open(void); /* paused; NULL on unavailable device/backend */
void dw4_audio_resume(dw4_audio *);
void dw4_audio_close(dw4_audio *);
void dw4_audio_play(dw4_audio *, unsigned voice, const dw4_audio_clip *, float gain);
void dw4_audio_stop(dw4_audio *, unsigned voice);
/* Change gain without stopping the sample cursor; false for an ended voice. */
int dw4_audio_voice_gain(dw4_audio *,unsigned voice,float gain);
/* 1 while the voice still has a clip to play (a looping clip never ends). The mixer has 64 voices. */
int dw4_audio_voice_active(dw4_audio *,unsigned voice);
double dw4_audio_seconds(dw4_audio *); /* device sample clock, including silence */
int dw4_audio_decode(const char *path, dw4_audio_clip *);
int dw4_audio_decode_blob(const uint8_t *, size_t, dw4_audio_clip *);
int dw4_audio_from_mono(const int16_t *, size_t frames, int rate, dw4_audio_clip *);
void dw4_audio_clip_free(dw4_audio_clip *);
#endif
