# Digimon World 4 (SLUS-20836) — game reference for decomp / dynamic analysis

Sources (both in `../local/`):

| File | What it is | Extractability |
| --- | --- | --- |
| `US_PS2_Game_Manual.pdf` | 24-page US PS2 manual, scanned — **image only, no text layer** | 12 PDF pages, each a 2-page spread, one 1360×1088 JPEG per page |
| `DW4_Walkthrough.pdf` | GameFAQs FAQ v1.1 (2006-03-25) by Unlimiting/divinedragonslayer, 54 pages | real text layer |

Identity: **SLUS-20836**, disc CRC used by PCSX2 sstate naming: **B871C1D0**.
Game supports **up to 4 players** (multitap, controller ports 1A–1D) — expect
player struct arrays of size 4.

---

## 1. PS2 controls (canonical, from manual p.3)

| Input | In world / menus |
| --- | --- |
| D-pad | Menu selection |
| Left analog stick | Player movement / status-screen selection |
| **Cross** | **Confirm / Attack** |
| **Circle** | **Cancel / Jump** |
| **Square** | **Guard** |
| Triangle | Emergency recovery (auto-uses strongest HP item) |
| START | Open status screen / open menu |
| SELECT | nothing |
| L1 | Open/close Item Window |
| R1 | Open/close MP Technique Window |
| R2 | Open/close Status Effects Window |
| L2 | (unused) |

Analog-only game ("analog controller exclusive"; LED stays on). No vibration.
In-game on-screen prompts are `◇ Select`, `⊗ Confirm`, `○ Cancel` — i.e. Cross
confirms, Circle cancels.

> **Measured on retail (PCSX2, pad D-pad via the agent controller):** menus accept D-pad *and* stick, world movement is
> stick-only. In the world the D-pad moves the player **0.000** units for 45-frame holds in all four directions while the
> stick moves it ~26 units; in the title and STATUS menus the D-pad moves the cursor exactly as the stick does, and on
> the main menu Up/Down move the highlight between `Game Start` and `Option` (captures `padstart-03-dpad-down.png` /
> `padstart-04-dpad-up.png`). The native port matches this (`dw4_input_walk_axes`).
>
> Movement is on/off with no walk/run. Menu overlays: L1/R1 toggle, R2 opens status, Square opens a disk-list
> overlay.
>
> A virtual pad whose D-pad is not a real hat (`ABS_HAT0X`/`ABS_HAT0Y`) cannot deliver a D-pad press at all, which
> reads as "the D-pad does nothing in menus"; a measurement on such a pad does not support that conclusion.

Advanced moves (manual p.8–9):
- **Slam Attack** — while guarding, double-tap left stick in a direction; pushes/crushes enemies.
- **Spiral Attack** — rotate left stick 360° + Cross; AoE around the player.
- **MP Techniques** — R1 → up/down → Cross. **Items** — L1 → up/down → Cross.
- Basic controls are taught by the in-game tutorial (not in the manual).

### Xbox / GameCube equivalence (walkthrough p.12, for cross-referencing guides)
`PS2 X ↔ Xbox A`, `PS2 O ↔ Xbox B`, `PS2 Triangle ↔ Xbox Y`,
`PS2 Square ↔ Xbox X`, `PS2 R1 ↔ RT`, `PS2 L1 ↔ LT`.
The walkthrough is written for the **Xbox** version, so its button names must
be translated (e.g. its "B = Jump" is PS2 Circle).

---

## 2. Game screens / UI structure

### Title screen (manual p.4)
`Game Start`, `Options`. Options = **Dungeon camera** (Near/Far) and
**Light** (Soft = normal, Hard = darker shadows).

### Character create / call screen (manual p.6; verified live)
Four save slots presented as numbered cards; each holds **one Digimon**
("Saves are done separately for each Digimon", manual p.15).

- `Create Digimon.` → choose one of **Agumon, Veemon, Guilmon, Dorumon** →
  name entry (up/down = letter case, left/right = letter, Cross = add letter,
  START = end) → START logs into the Digital World.
- `Call Digimon.` → choose MEMORY CARD slot (8 MB) → choose save data.
- Note the on-screen label is literally `Call Digimon.` (load), not "Load".

### HUD / heads-up display (manual p.7)
Elements: **(1) HP gauge, (2) Digimon icon, (3) Level, (4) MP, (5) HP,
(6) area information, (7) player number, (8) Item Window, (9) MP Technique
Window** (plus R2 = Status Effects Window). HUD shows current/max as e.g.
`140 / 160 70`, `Lv 1`, and context text such as `Gate to Outside World`.

### Status screen (manual p.18) — the field layout to mirror in a struct
```
Lv. / Digimon name            | Equipment / Folder / Techniques
HP  cur / max                 | ◇ Select  ⊗ Confirm  ○ Cancel
MP  cur / max                 |
Strength                      |
Defense                       |
Wisdom                        |
Spirit                        |
Speed                         |
Resist <fire>                 |
Resist <ice>                  |
Resist <lightning>            |
Resist <darkness>             |
Data                          |
BITS                          |
Next Level  <exp remaining>   |  [exp progress bar]
```
Manual p.19 defines the values:

| Field | Meaning |
| --- | --- |
| Strength | +damage with Weapon Units |
| Defense | −damage from enemy Weapon Units |
| Wisdom | +MP Technique effects |
| Spirit | −damage from enemy MP-related attacks |
| Speed | +accuracy with Weapon Units, +evade |
| Resist ×4 | −damage from Fire / Ice / Lightning / Darkness |
| Data | amount of **X Data** held |

So the "digimon record" has 7 core stats + 4 element resists + Data + BITS +
EXP-to-next-level, plus level and both name strings (player name and Digimon
name are separate fields).

### Equip window / folders (manual p.20)
- **Weapon Slot** — 3 active Weapon Units (only 3; swapping in anything else
  requires the Digi Lab).
- **Armor Slot** — `⊗` Armor Boards (Main Slot).
- **Sub Slot** — `∨` Armor Boards.
- **Folder** — `Device Folder` (weapons, armor boards, ability chips),
  `Key Folder` (key items, cannot be given away or broken),
  `Disk Folder` (disks, booster packs, key chains; can be broken),
  `Bits Folder` (money; can be given to other players).
- **Techniques** — Digivolve Technique, Technique (skill levels), MP Technique.
  `↑` = skill the Digimon excels at, `↓` = skill it is bad at.

### Home Server (Yamato Server) — manual p.10–13
Areas/keepers, useful as a name list for NPC/keeper entities and menu code:

| Keeper / node | Function |
| --- | --- |
| Terminal Area | passageways, Gate Circle, Heal Circle, Call a Digimon |
| Commander Room | Commander **Ophanimon**, Digi-Elves (mission briefings) |
| Digi Lab Attendant | Digivolve; exchange/equip Weapon Units; edit mod slots; remove equipment; **"Initiate Digimon Change"** commits changes |
| Appraiser | identifies items shown as `??????????` for BITS |
| Bank Keeper | deposit/withdraw BITS and items (any bank serves any other) |
| X Data Keeper | spend X Data to raise Digimon parameters or Ability Chip parameters (cost differs per parameter; some chips cannot be strengthened) |
| Save Keeper | save game data; per-Digimon files; asks before overwrite; needs 8 MB card, ≥120 KB free |
| Card Keeper | open Booster Packs, view album |
| Weapon Shop / Armor Shop / Chip Shop / Disk Shop | buy gear; shops stock better gear in multiplayer |
| Junk Shop | run by **MetalEtemon**, special hand-made items for BITS |
| Heal Circle / Gate Circle / Emergency Gate Circle / Start Point | HP+MP restore; travel; return point |

Emergency Gate note (manual p.11): using a Gate Disk at the Security Hole
returns you to the Emergency Gate; the Security-Gate↔Emergency-Gate *link* is
explicitly **not saved**.

### Outside Server rules (manual p.17)
- Stage gimmicks: **Treasure Boxes** (destroy for items/BITS), **Shrubs/Rocks**
  (destroy with a charge attack), **ID Keys** (dropped by area boss, open
  doors/switches), **Doors/Bridges** (may appear only after all enemies in an
  area are dead).
- **HP reaches 0** → return to Home Server, drop a **Back-Up Chip** at the
  death location; all carried BITS are lost and EXP decreases. Using a Raise
  Disk (or the `Raise` MP technique) on the chip recovers them. Only **one**
  Back-Up Chip can exist at a time; dying before recovering loses its contents.
- Multiplayer: a standing teammate can Raise-Disk a player at 0 HP.

---

## 3. Systems to expect in the binaries

### Skills / technique taxonomy
Five weapon skill types: **Blunt, Slash, Stab, Bash, Shot, Crush**
(6 listed; starters use Blunt/Slash/Stab/Bash). Each Digimon specialises:

| Starter | Specialist | Starting weapon | Signature weapon |
| --- | --- | --- | --- |
| Agumon | Blunt | Blunt Axe | Judgement |
| Veemon | Slash | Slash Sword | Light Bringer |
| Guilmon | Stab | Stab Dagger | Data Destroyer |
| Dorumon | Bash | Bash Katana | Hyakki Yako |

Each weapon has a **Tech Needed** threshold — you cannot equip a Weapon Unit
until the matching skill level is high enough (table in walkthrough §9,
e.g. Beam Magnum A needs Shot 90). Three starting weapons (Shot Pistol, Crush
Arm, and the specialist weapon) implies Shot and Crush are also real skills.

### MP techniques
Three families: **Blast** (attack/element), **Heal** (Heal Lt / Aura / Raise /
Cure Lt), **Force** (Power Up, Power Down, Resist, Speed Up, Freeze, Sleep,
Venom). Learned at **level 1, 12, 22**; the 4 starters get Blast at 1, Force at
12, Petty Heal Lt at 22. Techniques rank up with use through the ladder
`Petty → Mega → Giga → Terra → ?`. Costs: Petty Fire/Ice/Dark/Bolt = 8 MP,
Petty Heal Lt ≈ 12, Petty Aura ≈ 20, Petty Cure Lt = 8 (walkthrough §11 —
partly incomplete).

Elements seen: **Fire, Ice, Lightning (Bolt/Thunder), Darkness**, plus
non-elemental Impact. Resist chips exist for fire/ice/darkness/lightning.

### Progression / gating (useful for triggering states)
- Level up via EXP; new MP technique at Lv 12 and Lv 22.
- **Digivolve** at the Digi Lab once a Digivolve Technique is learned;
  digivolving resets Weapon Units (best equippable one is auto-equipped),
  detaches Armor from both slots, and changes the stat caps.
- The four starters become each other at **Lv 16** at the Digi Lab
  (Agumon→Guilmon→Veemon→Dorumon→Agumon).
- Cross-mode unlock: clearing Normal unlocks **Beta** chips and Hard mode;
  clearing Hard unlocks **Gamma** chips and Very Hard. Item suffixes:
  `A = Alpha`, `B = Beta`, `Y = Gamma`, `S = Delta`, `E = Epsilon`.
- Armor Core/Board tiers gate on level: **1 / 22 / 37** (Cipher, Brave,
  Element) and **61 / 78 / 93** (Spirit, Astral, Aegis); boards at 1 / 61;
  Talis of Order/Chaos at 93 (Junk Shop).
- Recommended levels per zone (Normal / Hard / Very Hard) run 1–3 → 95–100,
  so the level cap is at least 100.

### Digivolutions (16 forms total, 4 per starter)
Full list from walkthrough §1: Agumon, Veemon, Guilmon, Dorumon, WereGarurumon,
H-Kabuterimon (HerculesKabuterimon), WarGreymon, Cl-Angemon (ClavisAngemon),
Beelzemon BM, Alphamon, BK WarGreymon (BlackWarGreymon), IPDramonFM
(Imperialdramon Fighter Mode), IPDramonPM (Paladin Mode), MetalGarurumon,
Gallantmon CM (Chaos Mode), Susanomon. Unlocked by side quests; each starter
maps to a *different* form per quest, so the unlock tables are
(quest, mode, starter) → digimon id — a good target for reverse engineering.
Side quests that gate them: Undead Yard, Dungeon of Doom, Captive Dungeon,
Barbaric Cave, Forbidden Dungeon, ShogunGekomon, Legendary Coliseum,
Trading Hall, Item Road, Final Sidequest.

**How the unlock is actually recorded** (see
[`docs/systems/digivolution-and-sidequests.md`](../systems/digivolution-and-sidequests.md)):
each form is one byte in the `BASE_ISUSE` array (save `+0x76c`, 16 × u8), set by
`SYSctlShinka("SETSHINKA", player, form)`. Form index = the model/species order
(agumon=0 … susanoo=15). Side quest *completion* itself uses transient flags plus
persisted `COUNTER` values, so the durable result of a side quest is the
digivolution byte. Full detail, grant sites and open items in that document.

---

## 4. World / level data (names to match against strings)

| Zone | Regions | Dungeons | Bosses |
| --- | --- | --- | --- |
| **Death Valley** | Goblin Pass, Abyss of Grief, Numenume River, Dome Base | Humid Cave, Cliff Dungeon, Goblin Fortress, Doom Dome | Blossomon, Mammothmon, Mecha Rogue (Type-3), Apokarimon (zone boss) |
| **Dry Land** | Mummy Desert, Grief Wasteland, Storm Train, Power Plant, Station X | Sand Labyrinth, Ancient Ruins, Virus Lab | SkullGreymon, Scorpiomon, Malomyotismon |
| **Venom Jungle** | GekoGeko Land, Mangrove Forest, Venom Swamp, Dread Note | Geko Path, Vine Tunnel, Vein, Dread Bridge | ShogunGekomon, Mecha Rogue (Type-4), Diaboromon, Lucemon |
| **Machine Pit** | Battle Arena, Black Core, Inside the Black Core | Machine Pit, Electro Mine, Item Road (side quest), Mecha Nest | Mecha Rogue (Type-5), LordKnightmon, **Mecha Rogue X** (final boss) |

Other named playfields: Apokarimon's Space, Geko Path, Vein, Barbaric Cave,
Forbidden Dungeon, Undead Yard, Captive Dungeon, Legendary Coliseum, Trading
Hall, Junk Shop areas.

Enemy sets per area (walkthrough §4) — handy for mapping spawn tables:

| Area | Enemies |
| --- | --- |
| Goblin Pass | Goburimon, Numemon, Ogremon |
| Humid Cave / Cliff Dungeon | Goburimon, Numemon, Sukamon, Ogremon |
| Abyss of Grief | Goburimon, Ogremon |
| Goblin Fortress | Goburimon, Kokatorimon |
| Numenume River | Numemon + traps |
| Dome Base | Goburimon, Numemon, Sukamon, Ogremon |
| Doom Dome | Mummymon, MiniScorpiomon, Tyrannomon |
| Mummy Desert | Mummymon, MiniScorpiomon, Tyrannomon, Arukenimon |
| Sand Labyrinth | Mummymon, Minotauromon |
| Storm Train / Power Plant | MiniScorpiomon, Stingraymon, turrets |
| Grief Wasteland | Mummymon, MiniScorpiomon, Stingraymon, Minotauromon, Pharoahmon |
| Ancient Ruins | Pharoahmon, MiniScorpiomon, Minotauromon |
| Station X | MiniScorpiomon + many turret emplacements |
| Virus Lab | Pharoahmon, MiniScorpiomon, Minotauromon |
| GekoGeko Land / Geko Path | Otamamon, Gekomon |
| Mangrove Forest | Otamamon, Gekomon, "Rhinos" |
| Vine Tunnel | Otamamon, Gekomon, Rhinos; boss Mecha Rogue ×3 |
| Venom Swamp | MarineDevimon |
| Dread Note | MiniScorpiomon, Stingraymon, many defense turrets |
| Dread Bridge | MarineDevimon, Rhinos, Gekomon, Otamamon |

Dungeon archetypes worth looking for in code: **elevators/floors** with a
per-floor **map** pickup, floor **traps** (falling rocks), **switch** objects
that open doors elsewhere, **boss lair marker** (two blue circles + a heal
circle), end-of-dungeon **teleporter** back to the Home Server.

---

## 5. Asset / table indexes (for name→id mapping)

- **Weapon Units** — 6 skill lines × tiered names; tier order within each line
  is: starter, `<X> A` at tech 1, then 210, 810, 1080, 1400, 1680, 2020, 2200,
  2510, 2600. Lines: Blunt (Blunt Axe, Battle Hawk, Dbl Axe, Van Blade,
  Rage Hammer, Crusher, Hekatoncheir, Destroyer, Fang Smasher, Soul Burn,
  Meteor Force + Judgement/Orochi Slayer/Nightmare Lance), Slash (Slash Sword,
  Long Sword, Bone Blade, War Sword, Slasher, Victor Sword, Tri-Edge, Phantom,
  Dark Crimson, Onslaught, Doom Bringer + Light Bringer/Dark Shadow/Omega
  Blade), Bash (Bash Katana, Kamakiri Maru, Grand Blade, Kurogane Maru,
  Pain Scimitar, Denji Prince, Sword Break, Yasha Glass, Strider, Ankokuten,
  Infinity + Hyakki Yako/Plasma Blade), Stab (Stab Dagger, Dyno Tooth,
  Dbl Rapier, Red Moon, Light Blade, Rune Blade, Apocalypse, Light Ring,
  Flame Rose, Dragoon, Photon Edge + Data Destroyer/Stargazer/Invisible),
  Shot (Shot Pistol, Beam Magnum, Sword Cannon, Blaster Gun, Sphere Nova,
  Omega Raptor + Nosferatus/Executor/Dbl Pistron), Crush (Crush Arm,
  Mighty Talon, Hook Katar, D Slayer, Nova Blade, Drill Bunker +
  Kaiser Knuckles/Demon Arm).
- **Armor Cores** (Main Slot): Cipher, Brave, Element (lv 1/22/37),
  Spirit, Astral, Aegis (lv 61/78/93), Talis of Order.
- **Armor Boards** (Sub Slot): Achilles, Meteor, Armor, Beast, Fire, Ice, Dark,
  Lightning, Atlas, EXP, Rack, Resist, Mana, Bit, Talis of Chaos
  (lv 1 / 61 / …).
- **Disks**: HP Disk, MP Disk, Cure Disk (cure poison), Raise Disk, Gate Disk,
  Recovery (full HP+MP) — each in A/B/Y grades.
- **Ability Chips**: *Dual* — Speed Chip, Wisdom Chip, Spirit Chip;
  *Armor* — Defense ROM, Resist [fire/ice/darkness/lightning];
  *Weapon* — Assault RAM (crit), Drain RAM (HP on hit), Dread RAM (MP on hit),
  PWR Medal [element] (strength + element on attack).
- **Other items**: `???????????` (unidentified → Appraiser), `B. Pack` /
  Booster Pack (→ Card Keeper), `Key Chain` (trade 9 to Prince Maememon),
  `Digimon Data` = **X Data** (upgrades stats/chips).

**Known text bugs to expect in the string table** (walkthrough §12) — useful
because they confirm the *real* data when a tooltip disagrees:
Fang Smasher is listed as Bash but is Blunt; Dbl Axe and Rage Hammer are shown
as Bash but require Blunt; Prince Maememon says he gives an item but actually
gives Fang Smasher.

---

## 6. Page-1 known facts about the build

- Disc serial `SLUS-20836`, version `v1.01`, reported by PINE as
  `Digimon World 4 (SLUS-20836) v1.01`.
- PCSX2 sstate path uses `SLUS-20836 (B871C1D0).NN.p2s`.
- Boots fine on BIOS `scph39001.bin`; ~20 s of black screen while the BIOS and
  disc boot, then the "Annihilation" FMV; **Start or Cross skips the FMV**.
- The title screen appears after the FMV; `Game Start` is the first item.

## 7. Tooling notes

Install PDF tools on the host as needed. For Python dependencies, use a virtual environment
to avoid changing system Python packages:

```sh
python3 -m venv /tmp/pdfvenv          # temporary environment; re-create if /tmp is cleared
/tmp/pdfvenv/bin/pip install pypdf pillow
/tmp/pdfvenv/bin/python - <<'EOF'
from pypdf import PdfReader
r = PdfReader("US_PS2_Game_Manual.pdf")
for i, p in enumerate(r.pages):
    for j, im in enumerate(p.images):
        im.image.save(f"/tmp/pdfout/manual/p{i+1:02d}_{j}.png")
EOF
```

The manual has no text layer, so it must be read **visually** (the `read` tool
renders PNGs). Page mapping: PDF page 1 = covers; PDF page *k* (k ≥ 3) =
manual pages *2k−4* (left) and *2k−3* (right); PDF page 2 = warning + contents.
