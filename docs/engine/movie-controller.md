# The movie controller (`beMovie`)

`src/game/beMovie.cpp` is one whole-file unit (`bec_beMovie`, `0x3a6950` up to `0x3a921c`). Besides the
`beMovie` methods at its end it holds the `beCriAudio` voice methods and the `beCriVolume` fades
([sound-format.md](sound-format.md#besound-runtime-play-stop-commands-and-the-voice-pool)) and the
`beBaseInfoRam` named-timer group ([action2-timing.md](action2-timing.md#named-timer)).

## Methods

| Slot | Function | Role |
|---|---|---|
| 20 | `beMovie_GetMeta` | the class's meta object |
| 29 | `beMovie_OnAddRam` | registers the controller with its messenger under the name `MOVIE` |
| 30 | `beMovie_GetInfoMeta` | the info class it reads, `beMovieInfo` |
| 31 | `beMovie_UpdateRam` | the per-frame update below |
| 32 | `beMovie_Prepare` | takes a reference to the insight's `igMovieManager` into `_movie` |
| 34 | `beMovie_OnMessage` | the message handler below |

## Per-frame update

Nothing happens while `_playingName` is null. Otherwise player 0's pressed buttons (`bePadData._trigger`)
are read, and Start (`0x0008`) or Cross (`0x4000`) calls the movie manager's slot 26 (`igMovieManager_RemoveAllInfo`),
which runs the manager's slot 28 (`igMovieManager_StopMovie`) over its movie list. The movie counts as finished when
there is no manager or its slot 30 (`igMovieManager_GetMovieState`) returns 2 for the playing name (it also returns 2
for a name it does not hold). Once finished, the controller walks the `beMovieInfoData` list of the
ram's `beMovieInfo` (`ram->_parentInfo->_dataList`), runs the Lua chunk named by `_callLuaName` of the entry whose
`_name` equals the playing name, and replaces `_playingName` with the interned empty string. The walk stops early, and
the name is left set, at the first entry that is not a `beMovieInfoData`.

## Message handler

`beMovie_OnMessage` resolves the message through the controller's own message enum, which has four values; only
value 1 does anything, and an unknown value returns 0. Value 1 takes the movie name from the message's first string
and does nothing while `_playingName` is already set. Otherwise it walks the `beMovieInfoData` list of the ram's
`beMovieInfo` for the entry with that `_name` and stops, returning 1, at the first entry that is not a
`beMovieInfoData`. For the matching entry, when the controller holds a movie manager, it

1. creates an `igMovieInfo` named `Movie Player` with the codec type `igCriMovieCodec` and the entry's name as its
   path, and offers it to the insight core (`igInsightCore_AddInfo`, which reaches the manager's slot 25);
2. asks `LAYERCTL` for the node of the entry's `_parentLayer` (`GETLAYERNODE`) and takes that layer's first child as
   an `igAttrSet`;
3. takes the new movie's scene graph as an `igAttrSet`, appends it to the layer node and removes it from the viewer's
   scene.

Each step that fails ends the message with 1 and no name set. On success, or when there is no manager, the entry's
name is interned into `_playingName`.

The out-of-line destructor at `0x3a9190` is `igSmartPointer<igMovieInfo>`'s, emitted at the end of the file for the
holder the message handler keeps its new movie in.

## Open questions

- What the manager's slot 26 does to each movie is read from its loop only; the name `stopAll` in the source is that
  reading.
- The message enum's four names are not read here, so which message is value 1 is open; no Lua script was traced to
  it.
- `beCriAudio_Suspend` passes the voice's audio type and the ADX-file flag on to `igAdxAudio_GetOutVolume`, which reads
  only the handle: retail leaves them in the argument registers, and the source reproduces that with a two-argument
  declaration. The same holds for the flag passed to `igAdxAudio_GetStatus`.
