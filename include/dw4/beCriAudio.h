#ifndef DW4_BECRIAUDIO_H
#define DW4_BECRIAUDIO_H

struct beCriAudio;

#ifdef __cplusplus
extern "C" {
#endif

int beCriAudio_GetStatus(struct beCriAudio *self);
int beCriAudio_IsPaused(struct beCriAudio *self);
void beCriAudio_Pause(struct beCriAudio *self, unsigned char pause);
int beCriAudio_PlayFile(struct beCriAudio *self, const char *name);
int beCriAudio_PlayMemory(struct beCriAudio *self, void *data, int size);
int beCriAudio_PlaySfp(struct beCriAudio *self, int requestId, long long sequence);
void beCriAudio_Release(struct beCriAudio *self);
void beCriAudio_Resume(struct beCriAudio *self);
void beCriAudio_SetVolume(struct beCriAudio *self, int volume);
int beCriAudio_Setup(struct beCriAudio *self, int channels);
void beCriAudio_Stop(struct beCriAudio *self);
void beCriAudio_Suspend(struct beCriAudio *self);

#ifdef __cplusplus
}
#endif

#endif
