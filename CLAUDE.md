# Digimon World 4 decompilation

Rules for AI coding agents in this repository: the strict form of [CONTRIBUTING.md](CONTRIBUTING.md), which
you read first. The goal is to recover the PS2 release of **Digimon World 4** (USA, `SLUS-20836`) as
readable, evidence-named source that rebuilds to a byte-identical retail ELF.

## Hard rules

- **Privacy.** Nothing that identifies a developer's machine or account goes into the repository,
  generated files or commit messages: no absolute home/container paths, hardware models, driver/kernel
  versions, device nodes, user/host names, e-mail addresses, credentials, or emulator-driving facts (socket
  paths, display numbers). State requirements, not "this host" facts
  ([host details policy](docs/host-details-policy.md)). Install the hooks once per clone
  (`scripts/install_git_hooks.sh`), run `make hygiene` before every commit or push, never `--no-verify`, and
  fix a reported line rather than allow-list it unless it is a deliberate fixture.
- **Assets.** No game binaries or extracted assets in the repository (disc images, executables, IRX,
  BIOS, memory cards, savestates, screenshots, small extracts), and no retail code as assembly in any
  wrapper (see [No asm bodies](#decompilation)); the generated `asm/` tree is gitignored. Recovered
  metadata is fine. The retail executable is reached through the gitignored `orig/<GAMEID>/`. Never
  force-add, and never modify a disc image: work on a copy.
- **Only the owner approves assembly, inline `asm` and `volatile`.** A hand-written `.S` source needs a row in
  `config/assembly-sources.tsv` ([assembly sources](docs/engine/assembly-sources.md)); inline `asm`, `volatile`
  or an MWCC `asm` function in C and C++ needs a row in `config/source-approvals.tsv`
  ([source approvals](docs/engine/source-approvals.md)). The owner adds a row after reviewing the evidence
  that the original source used it. An agent writes one when the owner has explicitly told it to add that
  specific routine or function, or when one of the owner's standing rules below covers it; never otherwise, and
  never as part of a broader request ("match everything", "clear the queue"). A row written under a standing
  rule names its evidence at the anchor and is listed for the owner's review, who may withdraw it.
  - **Hardware and shared state:** a `volatile` on a hardware register, or on state an interrupt handler or
    another thread also writes, with that writer or the register named in the evidence.
  - **Instructions C cannot spell:** an `asm` statement for COP0, COP2/VU0 macro instructions
    (`lqc2`/`sqc2`/`qmtc2`/`qmfc2`, `v*`, `cfc2`/`ctc2`), `qfsrv`/`mtsab`, `di`, writes to `sp`, `syscall`,
    `plzcw` and trapping `add`/`sub`/`addi`, with every operand and the logic around it in C. Instructions
    C has a spelling for (`lq`, `sq`, `lwc1`, `swc1`, …) are not covered.
  - **Volatile VU0 or hardware blocks:** an `asm volatile` qualifier on an asm block that drives VU0 or
    hardware state, when no plain `asm { }` spelling matches (the tries recorded with the function) and the
    function still matches with every one of its asm blocks written `asm volatile`. The function then writes
    all its blocks that way, the usual form of PS2 inline VU0 code.
- **Scope.** The repository holds the decompilation and what it needs: source, build tables, tools,
  evidence and reference documentation. Agent handoffs, session logs, per-wave work reports, changelogs and
  accounts of how the repository was reorganised, player-facing guides and catalogues, and tools that
  drive or read a running emulator (with their captures) go to the workspace's archive outside Git. Write
  what a wave learned into the topic's document, not a dated log.
- **One build at a time.** At most one full build (`make check`, `make link`, `make objdiff`) runs on a
  host at once. The integrating session and sub-agents working in their own worktree outside the repository
  both run builds under the shared lock: `flock <shared lock file> make check`; `tools/apply_names.py --check`
  takes the file `DW4_BUILD_LOCK` names for its own builds. Gate stamps are kept per tree in the clone's git
  common directory, so a branch whose final tree passed the four gates in its own worktree lands without
  running them again; a merge of several branches is a new tree and runs them.
- **Sub-agents write only to a scratch directory outside the repository**, never `src/`, `config/`, `asm/`,
  `docs/` or the repository root. The integrator promotes work ([Delegated work](#delegated-work)).
- **Commits.** Sync with `git fetch && git merge origin/main` (never rebase shared history).

## Every task

- **Done means the four completion lines** ([Completion and regression](#completion-and-regression)),
  quoted from runs on the final tree.
- **Every landing includes the readability pass** on what it touches ([Readable](#matched-and-readable)).
- **Sub-agent models are set by the kind of work** ([Delegated work](#delegated-work)): byte matching and
  mechanical work start on Sonnet 5.5, and the integrator (which runs on Opus 5.5) reviews every Sonnet result
  and fixes what it could not match or explain (and does the readability pass). The integrator does no bulk
  mechanical work itself, and names each sub-agent's model to the owner.
- **Owner decisions are presented one at a time, as a question** the owner answers (the options with a
  recommendation, and the evidence), and an approval row is written only on the owner's instruction for it or
  under one of the standing rules in [Hard rules](#hard-rules).
- **Everything a Sonnet sub-agent hands back as needing the owner's approval gets an Opus 5.5 check first.**
  That covers an `asm`, a `volatile`, a hand-written assembly source, an owner-counted pragma, or any other
  approval row. The integrator starts the check as soon as the item comes back, without being asked, and
  never puts Sonnet's evidence to the owner directly. The Opus check looks for plain C first, strips each
  keyword or statement to show which change the bytes, looks at the GameCube and Xbox builds and other
  decompilations where they exist, and judges what remains against the approval standard. The owner sees only
  what survives, with the Opus recommendation.
- **Names.** A proposed name with high or medium confidence that says what the thing is or does, and reads
  like a name a person on the original team would have written, is applied without asking and listed in the
  report, with its evidence (medium ones with the alternative considered). Low-confidence guesses stay out
  until there is more evidence.

## Layout

Paths are repository-relative, and commands run from the repository root.

- `src/` recovered source (`src/third_party/` is stock zlib, libpng and Lua, never edited;
  [README](src/third_party/README.md)); `asm/` the retail split, generated from your executable and never
  committed (`make asm`; `make check` writes it when it is missing or stale); `include/dw4/<library>/` shared headers,
  one folder per library mirroring `src/` (`core/`, `game/`, `game/ndmw/`, `p2/`, `movie/`, `cri/`, `sony/`, ...; a header lives in the
  folder of the library whose unit defines its subject, and `support/` holds the project-wide utilities no single library owns;
  `support/reflected.h` is generated); `tools/` build and matching tools ([README](tools/README.md)); `scripts/`
  analysis; `data/` recovered data; `lua/` the game's Lua scripts decompiled and filed by stage
  (`scripts/lua_tree.py` resolves a pack entry and chunk to its file); `docs/` the documentation
  ([index](docs/README.md), whose Conventions cover how documents are written).
- The build follows the [dtk-template](https://github.com/encounter/dtk-template) layout
  ([build system](docs/build-system.md)): each version's address-bearing tables live in `config/<GAMEID>/`
  (`config.yml`, `symbols.txt`, `units.tsv` as the splits, `regions.tsv`, `data-owners.tsv`, `unit-*`,
  `exceptions.txt`, `names/`, `build.sha1`); project-wide policy files stay in `config/`
  (`debt-baseline.json`, `typed-*`). `make` extracts the executable from a disc image in `orig/<GAMEID>/`,
  and `python3 tools/download_tools.py` fetches the pinned compilers into `local/`.
- Documentation states the current state, never tallies of matched functions, and a method document names
  no function ([conventions](docs/README.md#conventions); `make hygiene` enforces the function names).
  Preserve unrelated changes.

## Decompilation

Read [naming](docs/engine/naming.md), [asm-body matches](docs/engine/asm-body-matches.md) and
[matched and readable](#matched-and-readable) before module work. A draft may be rough while it is in
scratch; what lands is both matched and readable.

- **Source compiles as whole files, never as functions.** The original build compiled each source file
  whole, and so does this one: a function lands inside its whole-file unit (`src/<module>/<file>.c|.cpp`,
  one `config/<GAMEID>/units.tsv` row and one `unit-objects.json` row with `whole_file`, measured by
  `tools/whole_file_rows.py`, never typed), in retail address order, and the whole unit must verify. A
  function in a range not yet folded is never banked as a new one-function file: fold the range into its
  file first (the file's extent from its strings, data and same-file calls, `scripts/same_file_calls.py`;
  `tools/merge_units.py` for the one-function files already there), then join the function. Compiling
  whole decides code under both compilers, so a candidate that matches alone can differ inside its file and
  one that misses alone can match there ([whole-file units](docs/engine/emitted-functions.md#whole-file-units)):
  `tools/check.py --function` on a one-function candidate is a drafting aid, and the verdict is the
  file's. The one-function files left in `src/unmatched/` and the per-function rows of `units.tsv` are
  legacy, each removed when its range is folded.
- **Every landing includes the readability pass on what it touches.** Folding functions into a whole-file
  unit, or joining held-out functions to one, makes the touched code readable in the same change: the unit
  is the scope, with one header and one set of types.
- **A function that resists matching is understood before it is searched.** When the obvious spellings
  fail, read the function and its unit first: real types from `include/dw4/support/reflected.h`, what each value
  is for, names from evidence, the same virtual slot in sibling classes, and the GameCube and Xbox builds.
  Only then run a permuter or a variant search. A spelling whose only reason is the bytes (a temporary
  that holds a stack slot, a one-element array that holds a register, a directive that ends a scheduling
  block, a class shaped to dodge the inliner) needs a reason in the code's own terms before it is proposed.
  [Understanding a resisting shape](docs/engine/understanding-shapes.md) gives the procedure, the instruments
  (the compiler's IR dump, gdb tracing, the register-allocator tracer, other builds, SDK archives) and the
  causes found so far.
- **One translation unit, one profile.** Every method of a class, and every function of a folded unit,
  verifies under the same compiler and flags. A per-function row that disagrees with its siblings is
  provisional: note it in the topic's open questions, re-attempt under the sibling profile, and count it
  separately until resolved. Never pin a profile to make one function pass while its unit says otherwise.
- **Exception metadata is part of the match.** C++ cleanup scopes are RAII holder classes whose destructor
  copies `config/<GAMEID>/unit-objects.json` names (`emitted`, `duplicates`, `externals`, `exceptions`, and
  `stripped` for an out-of-line destructor copy the retail linker dead-stripped);
  [emitted functions](docs/engine/emitted-functions.md).
- **Progress is fully matched source** (`functions.fully_matched` in `docs/progress.json`; what counts is
  in the [conventions](docs/README.md#conventions)). No partial score for a near miss, and no figure summed
  with asm bodies.
- **No asm bodies.** A function without C has no file in `src/`: it links from the retail image and reads
  from the generated `asm/`. Its retail instructions wrapped in an `asm` function recover nothing and are
  not committed; `make check` files any that appear as `asm-body`, counted in no figure. The exception is a
  function the original source wrote as an MWCC `asm` function, with an owner's `asm-function` row
  ([asm-body matches](docs/engine/asm-body-matches.md)). The work queue is every symbol without a
  definition in `src/`: `python3 tools/m2c_batch.py` drafts them (gcc target for Sony EE GCC units), and a
  draft lands only by joining its whole file. When a compiler is added, re-attempt the functions in its
  blocks first. Blocks built by a compiler build the project does not have stay without source.
- **No unapproved inline `asm` or `volatile`.** Either passes the byte check whether or not C could produce
  the same bytes, so it can hide a spelling nobody found: find the C. A function using one without its row
  is `unapproved`: it links, but it is not matched. Only `sync` and `ei` need no row, as C cannot spell
  them. A `volatile` that only pins when a load is scheduled, where retail reads once, is never approved; the
  one exception is an `asm volatile` block under the standing rule for VU0 and hardware blocks.
  `python3 tools/sourceapprovals.py --list` is the queue, `tools/inline_asm.py --test <source>` shows which
  `asm` statements can go, and `tools/progress.py --debt-check` fails on any rise in `inline_asm.other`.
- **Names** follow [Readable](#matched-and-readable) item 2. Apply overlays with `tools/apply_names.py`
  (dry run, then `--apply --check`).

### Matched and readable

**Matched** is one condition: the function verifies byte-identical as a member of its whole-file unit,
compiled under that **translation unit's profile** in `config/SLUS-20836/units.tsv` (compiler, flags,
exception mode; [build profiles](docs/engine/build-profiles.md)), including the C++ exception metadata. A
function that matches only under a per-function override in `config/SLUS-20836/unit-flags.tsv` /
`unit-compilers.tsv` is `foreign-profile` debt, not a match, and one using inline `asm` or `volatile` without
an owner approval is `unapproved` debt.

**Readable** is the second condition, measured by the README's Readable column, and every landing meets it.
A function is readable when all of these hold:

1. It sits in its module translation unit (`src/<module>/<Class or topic>.c|.cpp`), in retail address order.
2. Every identifier is a recovered name: from RTTI, strings or callers where they exist, otherwise a best
   guess from what the thing does. What it does should make the name obvious, so source never justifies a
   name: doubt about one goes in the topic document's open questions. A name holding an address is not
   recovered: it says where a thing is, not what it is. That goes for functions, variables, structs and
   classes alike; a type also needs a real name, not a placeholder such as `S`, `Obj` or `Info176`.
   Strings are named by their text, with no prefix.
3. No m2c idioms (`temp_*`, `var_*`, `argN`, stack-offset locals such as `sp5C`) and no raw offset casts where
   `include/dw4/support/reflected.h` names the field; real structs, enums and control flow; offset members are
   decimal `fNN` and temporary, with one shared definition per class under `include/dw4/<library>/<Module>.h`. A comment appears
   only when it is necessary, for what the code cannot say, and it stands alone: no pointer to another
   document or tool, and no account of how the code was recovered.
4. A shape found by a permuter, flag sweep or random walk carries
   `/* matching construct: <tool> — <what moved> */` at the affected line.
5. What it calls and reads is declared once, in a header, with its real type
   ([rules](docs/engine/debt-ratchet.md#declarations)): no local `extern` of another unit's symbol, no `(...)`
   or C `()` prototype in place of real parameters, no declaration whose type differs from the definition.

An owner-approved assembly source counts as readable once it has a recovered name. When two spellings match
the same bytes, keep the more readable one.

### Completion and regression

A task is complete only when the report quotes these four lines verbatim from runs on the final tree
(the pre-push hook refuses a commit without them; the [oracle runner](docs/engine/oracle-runner.md) repeats
them from a clean checkout when started by hand):

1. `make check`: the `cover :` summary, `0 mismatch` in its `(N not matched: M mismatch, D debt)` line when
   that line appears, and the `match` count at or above `functions.fully_verified` in the parent commit's
   `docs/progress.json`.
2. `make link`: `linkcheck: BYTE-IDENTICAL — the relinked section matches retail exactly`.
3. `make typed-check`: `typed coverage: N recovered accesses, baseline matches` (or the re-recorded baseline
   with the reason).
4. `make hygiene`: `check_host_details: clean`.

Each passing run stamps the tree it ran on, and the pre-push hook refuses a commit whose tree lacks a stamp
from all four, so commit exactly the tree the four ran on; `DW4_PUSH_DOCS_ONLY=1` lets a commit that changes
only `docs/` and `*.md` files through ([the local stamp](docs/engine/oracle-runner.md#the-local-stamp)).

Run `make check-fresh` and `make link-fresh` (cache ignored) before any commit that changes
`config/<GAMEID>/units.tsv`, `unit-*`, `extent-overrides.tsv`, `jumptables.txt`, `compiler-runtime-symbols.tsv`
or `tools/`, and before a milestone. A commit that changes only the recorded baselines
(`config/typed-coverage.json`, `config/debt-baseline.json`) and/or tools test files (`tools/test_*.py`) may use
the cached `make check` and `make link`; any other change under `tools/` or `config/` still needs the fresh
variants. A drop in the `match` count is a regression, including a function moving to `unapproved` (such as
through a new `volatile`): find the cause, never explain it away. A debt
counter that rises (`tools/progress.py --debt-check`) is re-recorded only with a reason
(`--debt-baseline --allow-increase "<reason>"`; [debt ratchet](docs/engine/debt-ratchet.md)).

### Extents, splits and regenerated artifacts

Changes to `config/<GAMEID>/extent-overrides.tsv` or `data/function-extents.json`, symbol splits/merges and
a regenerated `config/<GAMEID>/symbols.txt` are reviewed in the commit message with before/after counts
(functions, laid-out bytes, truncated units) and how the denominator changed. Regenerate, never hand-edit:
`config/<GAMEID>/{symbols,layout,jumptables,syscalls}.txt`, `data/`, `lua/`, flag tables and progress blocks
(`scripts/sync_data.sh`, `make progress`). Update topic documents, generated views and prose in the same
commit.

### Tools and limits

- One Ghidra process at a time; reuse an analysed project with `--no-analysis`. Check function shape with
  `mipsel-linux-gnu-objdump`; decompiler output alone is not proof.
- `python3 tools/m2c_batch.py --jobs 8 …`; never invoke imported `m2c.main` concurrently. `make check`/`make link`
  already run in parallel.
- `make objdiff` is a diff aid ([build system](docs/build-system.md)); `tools/check.py` and
  `tools/linkcheck.py` are the oracle.
- Callers and callees of retail functions: grep `asm/` and `src/` for the symbol, or the Ghidra xref scripts
  (`scripts/dump_xrefs.py`, `scripts/xrefs_multi.py`).

## Delegated work

Sub-agents draft; the integrator verifies and promotes. A sub-agent report lists, per function: address,
symbol, candidate path (in its scratch directory), the exact `tools/check.py --function` (or `tools/verify.py`)
command with flags, compiler path and SHA-256, the candidate source's SHA-256, the verifier's last line, and
any `config/<GAMEID>/unit-*` rows the match needs. The integrator re-runs that command before promoting
anything and treats an unreproduced claim as unmatched. Brief sub-agents with what matched and readable mean;
they never run full builds and never write into the repository. An agent briefed on a resisting shape is
pointed at [understanding a resisting shape](docs/engine/understanding-shapes.md), with the earlier agent's
report.

A matching agent works each function the same way:

- **Read what is already written first.** `python3 tools/notes_for.py <symbol or 0xVA>` prints its status,
  profile, unit-objects row, source comments and every document line naming it; read each earlier refutation
  and open note it shows, and do not retry a refuted spelling without a new reason. Then look the difference up:
  `python3 tools/levers.py --symptom "<the difference in machine terms>"` lists the known causes sharing it.
- **Working one function:** read its context pack (`python3 tools/pack.py --function <name>`) rather than whole unity
  files; for functions of 1 KB or more, record drafts on the region board (`python3 tools/region_board.py --unit-va <va>
  --function <name> --cand <unit file> --record <label>`) and start from it. Verification is always the whole-unit
  `tools/check.py`.
- **Fix the difference in order:** control flow and call order, then load and store order, then instruction
  selection, then registers, then the frame. A later kind often moves when an earlier one is fixed.
- **Stop on a budget.** About 30 attempts or 45 minutes on one function without the differing-word count
  falling ends the attempt. The function is handed on with a note in the report: the best C, the remaining
  diff, and the spellings tried with their results.

The sub-agent's model is set by the kind of work. This is a requirement, not a preference:

- **Mechanical work** (renames, applying names or data names, regenerating or rewriting tables and config
  rows, landing agents' files, collecting data): Sonnet 5.5.
- **Byte matching, first pass** (drafting functions, folding a range into whole files, matching them under the
  unit profile): Sonnet 5.5. Its report lists what matched and, separately, what it could not match or explain.
- **Review and fix:** the integrator, which runs on Opus 5.5, reviews every Sonnet 5.5 matching result before it
  lands: real types and names, no byte-only spellings or stray `asm`/`volatile`, extents and rows right, the
  readability pass done. It fixes what Sonnet left unmatched or unexplained. Opus 5.5 sub-agents take the review,
  one per slice, when it is too large for the integrator alone or when several Sonnet results are waiting at once,
  so the reviews run in parallel. Understanding work with no Sonnet pass (a resisting shape, a tool change) starts
  at Opus 5.5, and the hardest cases stay on Opus 5.5. Fable 5.2 runs only when the owner asks for it.

How it is enforced:

- **Every start names its model.** No sub-agent runs on a default model by omission. Before starting
  sub-agents, the integrator gives the owner the list of sub-agent and model. A slice that mixes kinds is
  split, or runs on the model of its hardest part.
- **The integrator does no bulk mechanical work itself.** It plans, briefs, re-verifies, promotes and fixes
  what verification finds. A mechanical pass over many files or rows goes to a Sonnet 5.5 sub-agent, with the
  exact mapping or table to apply and the check that proves it was applied.
- **Every leftover is handed on, in order.** A leftover is a function that still differs, a shape whose
  mechanism is unexplained, an extent or boundary nothing proves, or an approval item. Sonnet 5.5's go to the
  integrator's Opus 5.5 review, and every approval item goes through an Opus 5.5 check before it reaches the
  owner. Work does not count as done before that. What Opus 5.5 still cannot land goes under the topic's open
  questions with the reports.
- **Reports carry the model.** A sub-agent's report states its model in its first line. A progress or
  final report that credits a sub-agent's result names the model that produced it.

## Retail-game work

Read [testing tools](testing/tools.md), the [game reference](docs/reference/game-reference.md),
[stage selection](docs/systems/dev-stage-debug-menu.md) and the documentation for the build under test.
Live-memory claims need a running-game or offline savestate read; a savestate carries the loaded world, so
test a disc change by booting the disc and loading the stage afterwards. Menus accept stick and D-pad; in the
world only the stick moves the player. Emulator-driving tools and their notes stay outside the repository.
