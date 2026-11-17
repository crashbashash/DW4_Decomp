#ifndef DW4_IGADXAUDIO_H
#define DW4_IGADXAUDIO_H

struct igMetaObject;
struct igAdxAudio;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igAdxAudio_metaObject;
struct igAdxAudio *igAdxAudio_Create(int allocator);
void igAdxAudio_EnsureRegistered(void);
struct igMetaObject *igAdxAudio_GetOrCreateMetaObject(void);
int igAdxAudio_Initialize(struct igAdxAudio *audio, int maxChannels, int type, int maxStreams, int maxFrequency);
int igAdxAudio_CreateHandle(struct igAdxAudio *audio, int maxChannels, int type, int maxStreams, int maxFrequency, int initialize);
int igAdxAudio_StartMemory(struct igAdxAudio *audio, void *data, int size);
unsigned char igAdxAudio_StartFile(struct igAdxAudio *audio, const char *name);
void igAdxAudio_Stop(struct igAdxAudio *audio);
void igAdxAudio_Pause(struct igAdxAudio *audio, int pause);
int igAdxAudio_GetPauseState(struct igAdxAudio *audio);
void igAdxAudio_SetOutVolume(struct igAdxAudio *audio, int volume);
int igAdxAudio_GetOutVolume(struct igAdxAudio *audio);
int igAdxAudio_GetStatus(struct igAdxAudio *audio);
void igAdxAudio_Shutdown(struct igAdxAudio *audio);

#ifdef __cplusplus
}
#endif

#endif
