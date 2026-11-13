#include "src/engine/audio/AudioLibrary.h"

/* Constructed by __sinit_AudioLibrary.cpp. */
igSmartPointer<igPsx2AudioSourceList> g_audioTableOwner(0, kRetainReference);

#include "src/engine/audio/LibraryFront.inc"
#include "src/engine/audio/igAudioContext.inc"
#include "src/engine/audio/igPsx2AudioContext.inc"
#include "src/engine/audio/igPsx2AudioSourceList.inc"
#include "src/engine/audio/igPsx2AudioContext_tail.inc"
#include "src/engine/audio/igPsx2Thread.inc"
#include "src/engine/audio/igPsx2AudioContext_tail2.inc"
#include "src/engine/audio/igPsx2AudioSourceList_tail.inc"
