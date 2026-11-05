# Open questions / TODO (index)

What is **not yet known**, gathered in one place. Each row points at the document that owns the
detail — this page is a checklist and an index, not a duplicate. Status: **open** (unanswered),
**unconfirmed** (answered tentatively, needs a live test), **blocked** (needs an asset/state we do
not have), **decision** (a choice for the operator, not a fact to discover).

_Questions that have an answer are not kept in the tables — see [Answered](#answered)._

## Engine & formats

| Question | Status | Detail in |
|---|---|---|
| Object-graph serialization + locating `beBaseInfoData` / `beNDMWStatusInfo` | open for data other than the enemy stats — the enemy stats are the 649-row `AREA.AFS` table ([#195](../findings/findings-0001-0250.md#f195)/#205), not igBinary objects | [`../engine/igbinary-format.md`](../engine/igbinary-format.md), [`enemy-data.md`](enemy-data.md) |
| Property system: what the `0x38d860`/`0x38e060` and `0x38e6b0`/`0x38e8f0` pairs do, and the meaning of the property template's third word | open | [`../engine/property-system.md`](../engine/property-system.md) "Not yet resolved" |
| CodeWarrior build fingerprinting (compile + diff against the archived compiler) | open | [`../engine/toolchain.md`](../engine/toolchain.md) |
| `OUTER.DAT` (204 MB), IOP modules | unexplored | no doc yet |

## Enemy, spawn & drop data

| Question | Status | Detail in |
|---|---|---|
| Do enemies **terrain-snap** Y like the player? | open for enemies ([#413](../findings/findings-0251-0500.md#f413)) | [`enemy-spawn-system.md`](enemy-spawn-system.md) §7. The player **does** snap up (measured); the enemy's three found copies are *derived*, so writing them measures the refresh schedule, not the entity. The clean experiment is named: author a spawn Y **below** the floor in `_genePosList` |
| Decode the per-stage generator igb tables (positions/rows for every stage, not just the two sampled) | open — a sweep of the 143 generator-bearing packs; the instance encoding is solved ([#417](../findings/findings-0251-0500.md#f417)–[#420](../findings/findings-0251-0500.md#f420)) | same §7. Enumerating `beGenerater*` by vtable ([#415](../findings/findings-0251-0500.md#f415)/#416) reads a loaded stage's generator rows directly — 73 generators in stag0102 with enemy id, start/fill mode strings and timings — so the decode has a live cross-check |
| Any `_genePosIsGlobal=0` (stage-local) spawn entries anywhere | open | same §7 |
| Drop-list `rank` field meaning; `abChip` ids; weapon ids 256–265 model order | open | [`drop-tables.md`](drop-tables.md), `drops/WOODENCASE-DROPS.md` (outside the repository: `extras/reference/drop-reports/WOODENCASE-DROPS.md`) |
| ~16 variant models with no row of their own (`f_devl*`, `e_mecha2st0203`, `e_mecha4dn`, …) | unconfirmed | same §7.4 |
| Every boss row except `e_mecha4` row 60 — unmeasured (they scale by construction) | unconfirmed | same §7.4 |
| Destructibles: confirm the generator-row vs MODELCTRL-default split on a scratch disc; is the 20/34 damage fixed or a fraction of max? | open | same §7.10 / §5 |
| Boss enemy-drop amounts: two rows pay out different amounts — which is authoritative | open | `drops/GOBLIN-FORTRESS-ENEMY-DROPS.md` (outside the repository: `extras/reference/drop-reports/GOBLIN-FORTRESS-ENEMY-DROPS.md`) |

## Items, techniques & content

| Question | Status | Detail in |
|---|---|---|
| Technique damage: does a maxed technique level boost damage; effective vs displayed cap | open | [`techniques.md`](techniques.md) "Open questions" |
| Item **stat** database (id → base stats + model) in `NDMW.AFS` | open | [`items.md`](items.md) "Still open" |
| message-id → entry-9 string resolution (the text system step) | open | same |
| Item `0x8000` bit 11 meaning | open | same |
| Digivolution: byte → Lua encoding; Susanomon (form 15) has no `SETSHINKA` site; per-quest flag map; `*(gp-32428)`; the `entry_0603` grant-all loop | open | [`digivolution-and-sidequests.md`](digivolution-and-sidequests.md) §7 |

## Gameplay facts still unverified

| Question | Status | Detail in |
|---|---|---|
| RNG: call frequency of the lobby `funcRandom` `SYSgetRandom(1)` no-op draws | open | [`rng.md`](rng.md) §8 |
| RNG: are the `M==1` draws a disabled debug branch or deliberate | open | [`rng.md`](rng.md) §8 |
| RNG: exact crown-roll group count (2 vs 3) per crown-capable stage | open | [`rng.md`](rng.md) §8 |
| RNG: is a desirable roll (pink crown / rare layout) reachable cheaply from fresh-boot seed 5150 | open | [`rng.md`](rng.md) §8 |
| Whether an end-game card can enter a world at all (gate offers no destination on `endgame.ps2`) | open | observed live once, never re-checked |
| Which flag/folder combination opens that gate | open | same |
| Attack held while moving in a world (needs a good save) | open | same |

## Answered

Detail lives in the linked doc, not repeated here:
the save-field byte map and level formula ([`save-format.md`](save-format.md)); MP/EXP/LEVEL
storage ([`../engine/property-system.md`](../engine/property-system.md)); the Lua decompiler
([`../engine/lua-decompilation.md`](../engine/lua-decompilation.md)); the igBinary header +
string table (partial — [`../engine/igbinary-format.md`](../engine/igbinary-format.md)); the enemy stat-table
location and the crown rank→colour mapping (findings [#172](../findings/findings-0001-0250.md#f172), [#255](../findings/findings-0251-0500.md#f255)); the drop-table weighted roll
([`drop-tables.md`](drop-tables.md)); and the warp-gate `(name,pos)` question (finding [#246](../findings/findings-0001-0250.md#f246)).
The **class reflection records** (MetaObject field tables) are decoded — per-class field
names/offsets/types, the class-name association and
the MetaObject registrar ([`../engine/reflection-metadata.md`](../engine/reflection-metadata.md),
`data/reflection.json`, findings [#284](../findings/findings-0251-0500.md#f284)/#286/#287). What remains open there is the 28 shared vfuncs whose owner class has no MetaObject (19 more were named by descendant-set
match — finding [#410](../findings/findings-0251-0500.md#f410); they are method data, not field data).

Answers that stop a repeated search:

- **igBinary field-descriptor semantics** — 6-byte `{type_id, ordinal, size}` (finding [#289](../findings/findings-0251-0500.md#f289));
  `ordinal` → byte offset and the omitted fields are explained (findings [#290](../findings/findings-0251-0500.md#f290)/#292).
  [`../engine/igbinary-format.md`](../engine/igbinary-format.md) "Next steps";
  [`../engine/reflection-metadata.md`](../engine/reflection-metadata.md) §6.
- **Property system: runtime value of `*(registry+8)`** (record name offset) — it is `8`, read
  from EE RAM ([#295](../findings/findings-0251-0500.md#f295)). [`../engine/property-system.md`](../engine/property-system.md) "Registry object".
- **Property system: the 4 `sd` internal ids (29–32)** — two operations × optional-5th-arg, not
  four operations ([#296](../findings/findings-0251-0500.md#f296)). [`../engine/property-system.md`](../engine/property-system.md)
  "`sd` — the four internal ids".
- **Enemy model swap** — works for models whose geometry is resident in the stage and spawns
  nothing for the rest, confirmed with an instance count ([#427](../findings/findings-0251-0500.md#f427)/#428).
  [`enemy-spawn-system.md`](enemy-spawn-system.md) §6b/§7. `beGeneraterInfoWork._enemyRamList` (+20)
  is a live per-work pointer ([#416](../findings/findings-0251-0500.md#f416)).
- **Timer-mode semantics** (`_startData` units, `GENE_TIMER`) and how `add` interacts with
  `_geneMaxCount` ([#412](../findings/findings-0251-0500.md#f412)) — `_startData`/`_fillData` are **frames at 60 fps**; keys
  `BOOT_TIMER`/`GENE_TIMER`; `_geneMaxCount` is the alive-at-once cap.
  [`enemy-spawn-system.md`](enemy-spawn-system.md) §7.
- **Drop tables: the pack-internal id/`X` encoding** — element arrays read with no live reference
  ([#419](../findings/findings-0251-0500.md#f419)/#460); a stage's three difficulty-tier packs carry the same drop table ([#462](../findings/findings-0251-0500.md#f462)).
  [`drop-tables.md`](drop-tables.md) §6.
- **A flat ~88-record `beNDMWStatusInfo` definition table indexed by `RecNo`** does not exist
  ([#301](../findings/findings-0251-0500.md#f301), refuted): the stat table is **649 rows of plain data in `AREA.AFS`/ISO** (HPMAX i32
  col-major @0x78D64C5 + 12 i16 row-major @0x78DACB9 + 3 u8 row-major @0x78DA51D, 665 copies),
  decoded as findings **[#195](../findings/findings-0001-0250.md#f195)/#205**; "×667" is a miscount and "×88" an instance count. The
  live read path is [#182](../findings/findings-0001-0250.md#f182), corroborated by [#298](../findings/findings-0251-0500.md#f298)/#299.
  [`enemy-data.md`](enemy-data.md) §"The enemy stat table".
