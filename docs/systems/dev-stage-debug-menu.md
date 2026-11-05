# The developer stage (`stag0000`) and its debug-NPC menu

**Status:** mapped, captured, translated
**Evidence:** in-game captures — 90 translated debug-menu screens (45 dialogue/menu + 40
stage-list captures) plus the original frames.

## 1. What `stag0000` is

`stag0000` is a **developer/debug world** present in the shipped retail disc. It is not a
playable area: a wireframe-grid floor over a pink void, with debug characters and objects
floating in the air, no generator entries loaded, and no level geometry beyond the grid.
It loads cleanly by cold warp (verified in a 20-destination sweep) and is the only stage measured
so far that is safe to enter from anywhere.

It appears exactly **once** as a `NEXTSTAGE` literal in the whole decompiled corpus, and
it is *not* reachable through normal play — the hub's gate menu offers the four worlds,
not this.

**It is a debug sandbox built around a menu of debug NPCs (§3).** Everything the debug
build could do at runtime is exposed here as an in-world character you talk to.

## 2. Getting in (three routes)

| route | how | notes |
|---|---|---|
| **savestate** (most reliable) | load a state captured while standing in the dev world | verified by the engine's current-stage field `0x006FF148` = `stag0000`. A state does not re-read the disc, so it works on any build |
| the eleven NPC states | one state per debug NPC | each stands the player in front of one NPC |
| patched disc | rewrite the single `"stagML11"` literal in the character-select packs' `dm-run` (AFS entries 808/810/812) to `"stag0000"` | a normal boot after character select then lands in the dev world; **blocked on a valid memcard** — see §7 |

The RAM route that produced the state: the gate menu keeps pre-built `STAGECTL NEXTSTAGE`
command records; re-point the record's `+0x00` (stage-name pointer) at another interned
name and confirm the menu entry.

## 3. The NPC roster

Six of the NPCs are the same model and share the on-screen name **デジルフ** — in
romanised form "Digi-elf"; it is a debug mascot, not a Digimon. The seventh is
**レオモン (Leomon)**, and two of the "NPCs" are rocks.

| state | on-screen | role | first line (JP → EN) |
|---|---|---|---|
| `digi-elf-1` | デジルフ | **text/font size test** | 「もじをみたのか？…サイズをえらびな!!」→ "Did you see the characters? … Choose the SIZE!!" |
| `digi-elf-2` | デジルフ | **stage select — a working warp menu** | 「ステージせんたくするよ！ほかのステージにどうする？」→ "Let's select a stage! What about another stage?" |
| `digi-elf-3` | デジルフ | **play mode / difficulty** | 「プレイするモードをせんたくします」→ "Select the mode to play." |
| `digi-elf-4` | デジルフ | **TIME flag editor** | 「TIMEフラグをへんこうします」→ "Change the TIME flag." |
| `digi-elf-5` | デジルフ | **evolution-arts unlock** | 「しんかワザをおぼえます」→ "Learn evolution arts." |
| `digi-elf-6` | デジルフ | **EXP / level cheat** | 「すきなLVまでのEXPをあげますよ…」→ "I'll give you EXP up to any LV you like…" |
| `leomon-1` | レオモン (**Leomon**) | **leave debug mode → the lobby** | 「デバッグをしゅうりょうして ML11にてんそうします」→ "Finish debug and transport to ML11." |
| `rock-1` | — | **item cheat** | 「--アイテム MAX-- アイテム すべてx9 になりました」 |
| `rock-2` | — | **money cheat** | 「--おかね MAX-- BITが 9999999 になりました」 |
| `goblin-1/2` | — | **enemies, attack only** (no dialogue) | ゴブリモン — see §5 |

## 4. Each menu, in full

**`digi-elf-1` — text size.** `NORMALでおねがいします` / `MINIMUMでおねがいします` /
`スミマセン、みるのやめます` ("NORMAL please" / "MINIMUM please" / "Sorry, I'll stop
looking"). Choosing either size then **ends the conversation** — the visible effect is a
global text-size flag, so the NPC becomes silent afterwards.

**`digi-elf-3` — play mode / difficulty.** `へんこうしません` / `ハード` / `ベリーハード`
("Don't change" / "Hard" / "Very Hard"). This is the retail difficulty setting the debug
build lets you set directly.

**`digi-elf-4` — TIME flags.** `は、へんこうします` / `いいえ、へんこうしません`
("Yes, change it" / "No") then a paged flag list:
`つぎのページ` (Next page) + `TIME00 TIME01 TIME02` → `TIME03 TIME04 TIME05` →
`TIME06`, `フィールドクエスト` (Field Quest), `やっぱり へんこうしません`
("On second thought, don't change"). Useful: these are **named debug flags**, and the
`TIME*` family is a lead for the in-game clock/time-of-day logic.

**`digi-elf-5` — evolution arts (`しんかワザ`) unlock.** `つぎのページ` + either
`ぜんぶのしんかワザをおぼえます` ("learn ALL") or one Digimon at a time. Six pages, the
full playable roster:

| page | entries |
|---|---|
| 1 | アグモン Agumon · ブイモン V-mon |
| 2 | ギルモン Guilmon · ドルモン Dorumon · ワーガルモン Wargarurumon |
| 3 | ヘラクルカブテリモン HerakleKabuterimon · ウォーグレイモン WarGreymon · クラビスエンジェモン ClavisAngemon |
| 4 | ベルセブモンBM Beelzemon Blast Mode · アルファモン Alphamon · BLウォーグレイモン BlackWarGreymon |
| 5 | IPドラモンFM Imperialdramon Fighter Mode · IPドラモンPM Paladin Mode · メタルガルルモン MetalGarurumon |
| 6 | デュークモンCM Dukemon Crimson Mode · スサノオモン Susanoomon · おぼえません (learn none) |

Selecting one confirms, e.g. 「デュークモンCMをおぼえました」 ("Learned Dukemon CM"). **This
is the authoritative list of which Digimon have evolution arts in this build.**

**`digi-elf-6` — EXP / level.** Dialogue: 「ちぇ、、、すきなLVまでのEXPをあげますよ、、、
LV いくつになりたいですか？」("Che…, I'll give you EXP up to any LV you like… what LV do
you want to be?"). Three pages of targets — `LV16/36/46`, `LV76/106/999`, `LV50/100/200`,
plus `やめます` (stop). Setting a level then produces §5's line.

**`leomon-1` (Leomon) — exit debug.** `は、てんそうします` / `いいえ、てんそうしません`
("Yes, transport me" / "No"). Confirming transports to **ML11**, the main lobby — i.e. the
supported way to leave the dev stage and return to normal play with whatever the debug
menu just changed.

## 5. The two goblins are level-up fodder

`digi-elf-6`'s level cheat does not apply the level directly. After granting the EXP it
says:

> 「EXPをふやしたので、、、となりのゴブリモンをなぐってくださいよ、、、LVが1あがりますから、、、」
> *"I raised your EXP, so… please punch the Goblimon next to you… your LV will go up by 1…"*

That is why exactly two ゴブリモン (**Goblimon**) stand beside it — they have no dialogue
and exist to be attacked so the pending level-up resolves. Any future save-editing work
should note the same mechanic: **level is applied through combat, not by the cheat itself.**

## 6. The stage-select menu (`digi-elf-2`) — the supported warp

Talking to this NPC prints its two lines and then shows a **full screen of eleven stage
IDs at once**, with an extra `つぎのページ` ("next page") line on top. Selecting that line
advances to the next screen. **It is the engine's own stage-ID enumeration**, and it covers
**every one of the 97 stages** — nine screens, 11 entries each except the last (9).

> The whole eleven-entry screen is rendered at once (it is not three entries per page); the
> 40 stage-list captures are the same nine screens grabbed more than once. Page order is
> script order, i.e. screens 1→9 below.

### Screen order (AFS entry 603, one Lua script per screen)

| # | script | entries |
|---|---|---|
| 1 | `048-msg-80106.lua` | `stag0001`, `stag0101`, `stag0102`, `stag0103`, `stag0104`, `stag0201`, `stag0202`, `stag0203`, `stag0204`, `stag0205`, `stag0301` |
| 2 | `049-msg-80118.lua` | `stag0302`, `stag0303`, `stag0304`, `stag0401`, `stag0403`, `stag0404`, `stagBS01`, `stagBS02`, `stagBS03`, `stagBS04`, `stagBS05` |
| 3 | `050-msg-80129.lua` | `stagBS06`, `stagGF01`, `stagGF02`, `stagGF03`, `stagGF04`, `stagIS07`, `stagIS08`, `stagIS09`, `stagIS10`, `stagIS11`, `stagIS12` |
| 4 | `065-msg-80140.lua` | `stagIS13`, `stagIS20`, `stagML02`, `stagML11`, `stagML12`, `stagML13`, `stagML14`, `dng101b1`, `dng101b2`, `dng102b1`, `dng102b2` |
| 5 | `066-msg-80151.lua` | `dng102b3`, `dng103f1`, `dng103f2`, `dng204b1`, `dng204b2`, `dng205b1`, `dng205b2`, `dng205b3`, `dng206f1`, `dng206f2`, `dng307b1` |
| 6 | `067-msg-80162.lua` | `dng307b2`, `dng308b1`, `dng308b2`, `dng308b3`, `dng309b1`, `dng309b2`, `dng309b3`, `dng309b4`, `dng310f1`, `dng310f2`, `dng310f3` |
| 7 | `068-msg-80173.lua` | `dng411b1`, `dng411b2`, `dng411b3`, `dng412b1`, `dng412b2`, `dng412b3`, `dng412b4`, `dngq1b1e`, `dngq1b2e`, `dngq2b1e`, `dngq2b2e` |
| 8 | `069-msg-80184.lua` | `dngq2b2h`, `dngq3b1e`, `dngq3b2e`, `dngq4b1e`, `dngq4b1h`, `dngq4b1v`, `dngq4b2e`, `dngq4b2h`, `dngq4b2v`, `dngq5b1e`, `dngq5b1h` |
| 9 | `070-msg-80216.lua` | `dngq5b1v`, `dngq6b01`, `dngq7b1e`, `dngq7b2e`, `dngq8b1e`, `dngq8b2e`, `dngq8b3e`, `dngq8b3h`, `dngq8b3v` |

Each screen is one `msg-80xxx.lua` script: a `SELECTCTRL i_stcursor01` cursor plus a
`DMcase(0..10)` list whose cases `NEXTSTAGE` to the stage. The cursor starts on
`つぎのページ`, so **entry *k* of a screen is `k+1` cursor steps down from the start**.

### Recipe (verified, loads real stages)

```sh
pad run &
pcsx2 start --statefile ../local/testing/states/dev-world/digi-elf-2.p2s "<any disc>"
# talk, then advance the two dialogue lines
input press Cross --backend pad --ms 250          # x3
# walk to screen N:  Cross on つぎのページ, once per screen (N-1 times)
input press Cross --backend pad --ms 200          # = one screen forward
# move the cursor down k+1 times (0.10 s flick = exactly one step)
input stick l 0 1.0 --backend pad --ms 100
input neutral --backend pad
# confirm -> engine loads that stage
input press Cross --backend pad --ms 200
```

* **Drive the menu with the stick.** Retail menus accept the D-pad on a working pad (title and STATUS), but this dev
  menu has not been tested with one, so keep using the stick, which is known to work.
* Loading is a normal stage load (~12 s to the banner). `stagGF01` shows the
  **"Guard Room / Goblin Fortress"** banner, so the destination is self-verifying.
* **Confirming a name does warp there**, and the entry
  position is the `I<0>` in `PLAYERPOINT SETGENERATEPOS` next to each `NEXTSTAGE` (every
  screen here uses `I<0>`; the randomiser's `(name, pos)` question is about gate records,
  not this menu).
* It is ASCII, so it needs no translation; the annotated captures carry a header only.
* **Automating this menu** (to load a stage for a RAM dump) means talk → page forward →
  cursor down → select, then confirming from the game's own load log that the requested
  stage loaded; the pitfalls are in [`drop-tables.md`](drop-tables.md) §9.

## 7. The memcard dead end (why the patched disc can't be used normally)

"Call Digimon." answers *"This memory card (PS2) contains no Digimon World 4 game file."*
That message is **correct**: `Mcd001.ps2` and `Mcd002.ps2` both contain the bytes
`BASLUS-20836savedata`, but the directory entry at that offset is **all zeroes** — a
stale/deleted record, not a live save. No valid DW4 save exists on either card, so the
`[devworld].iso` route cannot reach the world until one is installed from
a generated probe save.
Reloading the emulator does not change this. **Savestates are the working route.**

## 8. Capture method (reproducible)

```sh
nohup pad run &                       # exactly ONE server, or input is silently dead
pcsx2 start --statefile <state> "<disc>"
pad status | tail -2                  # must say "player id 0"
# per state: cp to sstate slot 20 -> pine loadstate --slot 20 -> sleep 9
input press Cross --backend pad --ms 250      # talk / advance one line
input stick l 0 1.0 --backend pad --hold      # menu one step: hold 0.10 s, then neutral
```

* **A 0.10 s stick flick = exactly one menu step.** Longer holds auto-repeat and skip
  options (0.2 s = two steps, 0.7 s = several). The stick's **Y axis is inverted in
  menus**: `+1.0` moves the cursor *down*.
* **The D-pad is untested here on a working pad** (retail menus accept it on the title and STATUS screens). Drive
  every menu with `input stick`, which is known to work.
* **The dialogue window is detected by the full-width cyan rule at y≈472**; its text
  occupies **y 478–636, x 236–905** of the 1280×960 display grab. The bottom border
  (y 642–663) must be excluded or it reads as a text line.
* **Unhighlighted menu options are drawn dimmer** than the selected one and fall under a
  bright-pixel threshold of ~150 — at that threshold some menus appear to have a single
  line. Threshold ≈110 finds them.
* The translated images reproduce the Japanese by **cropping the game's own text pixels**
  and putting the English beside them, because no CJK font was available to the image
  tooling (it resolved Japanese to DejaVu). Do not try to render Japanese as text.

## 9. Files

| artifact | what |
|---|---|
| captures | raw 1280×960 grabs of every press, plus **90 translated images** — every text screen: 45 dialogue/menu + 40 stage-list captures (+ repeats) |
| savestates | one per debug NPC, plus a free-roam dev-world state |

The captures and savestates are working artifacts of the survey, not part of this repo.

## 10. Open questions

1. What do the `TIME00…TIME06` flags actually gate, and where are they read? (The
   decompiled corpus has the flag-setter but not obviously a reader.)
2. `digi-elf-1`'s size setting — which text does it affect? It is global; find the
   consumer to learn whether it changes dialogue, menus, or both.
3. `digi-elf-3`'s play mode: locate the difficulty variable it writes, and whether it is
   the same variable the retail "difficulty" option uses.
4. `stag0000` also appears once as a `NEXTSTAGE` destination in normal scripts — find which
   script, and whether it is a leftover or a reachable path.
