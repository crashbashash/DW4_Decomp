# The movie controller (`beMovie`)

`src/game/beMovie.cpp` is one whole-file unit (`bec_beMovie`, `0x3a6950` up to `0x3a921c`). Besides the
`beMovie` methods at its end it holds the `beCriAudio` voice methods and the `beCriVolume` fades
([sound-format.md](sound-format.md#besound-runtime-play-stop-commands-and-the-voice-pool)) and the
`beBaseInfoRam` named-timer group ([action2-timing.md](action2-timing.md#named-timer)).

## Methods

| Slot | Role |
|---|---|
| `Gap::Bec::beMovie::vfunc_20` | the class's meta object |
| `Gap::Bec::beMovie::vfunc_29` | registers the controller with its messenger under the name `MOVIE` |
| `Gap::Bec::beMovie::vfunc_30` | the info class it reads, `beMovieInfo` |
| `Gap::Bec::beMovie::vfunc_31` | the per-frame update below |
| `Gap::Bec::beMovie::vfunc_32` | takes a reference to the insight's `igMovieManager` into `_movie` |

## Per-frame update

Nothing happens while `_playingName` is null. Otherwise player 0's pressed buttons (`bePadData._trigger`)
are read, and Start (`0x0008`) or Cross (`0x4000`) calls the movie manager's slot 26 (`igMovieManager::vfunc_26`),
which walks the manager's movie list (read as stopping playback). The movie counts as finished when there is no manager or its slot 30
(`igMovieManager::vfunc_30`) returns 2 for the playing name (it also returns 2 for a name it does not hold).
Once finished, the controller walks the `beMovieInfoData` list of the
ram's `beMovieInfo` (`ram->_parentInfo->_dataList`), runs the Lua chunk named by `_callLuaName` of the entry whose
`_name` equals the playing name, and replaces `_playingName` with the interned empty string. The walk stops early, and
the name is left set, at the first entry that is not a `beMovieInfoData`.

The out-of-line destructor at `0x3a9190` (`MovieObjectRef`, a holder of one object reference) is emitted at the end of the
file and has no caller in retail.

## Open questions

- What slot 26 does to each movie is read from its loop only; the name `stopAll` in the source is that reading.
- Which message sets `_playingName` is not read here; no function of this unit writes a non-empty name.
- The holder class whose destructor sits at `0x3a9190` is not identified; `MovieObjectRef` is the source's name for the
  ABI shape only.
- `beCriAudio_Suspend` passes the voice's audio type and the ADX-file flag on to `igAdxAudio_GetOutVolume`, which reads
  only the handle: retail leaves them in the argument registers, and the source reproduces that with a two-argument
  declaration. The same holds for the flag passed to `igAdxAudio_GetStatus`.
