# Findings register

A finding is one of three things:

- **confirmed**: a fact about the game, the build or the port, with evidence a reader can open;
- **unconfirmed**: a hypothesis that is not yet proven (a guessed name, a field's meaning, a reading
  of some code);
- **refuted**: an idea that was tried and is wrong, kept so nobody repeats it.

Documents and source comments cite a finding as `#N`. In a document the citation is a link; in a
source comment it is plain text.

## Finding an entry

Finding `#N` is in the file for its block of 250, in id order: `#2747` is in
[`findings-2501-2750.md`](findings-2501-2750.md), at the anchor `#f2747`. From a terminal:

```sh
python3 scripts/findings.py show 2747
grep -rn "RARITY" docs/findings/          # search the register by word
```

## What an entry looks like

```markdown
<a id="f2747"></a>
### #2747 · confirmed

**Where:** 0x0039a9e0 — beNodeAnim clock update

The statement, in the present tense.

**Notes:** detail that supports or limits the statement.

**Evidence:** src/game/beNodeAnimClock.cpp; docs/engine/stage-loading.md; another finding's id
```

`**Where:**` and `**Notes:**` are optional. A confirmed finding must have `**Evidence:**`, and the
evidence is repository-relative: a file, a command, another finding.

## Adding or changing one

- `python3 scripts/findings.py next` prints the next free id and the file it goes in. Add the entry
  at the end of that file, anchor line first.
- A fact that is already described in its topic document does not need a finding as well. Use the
  register for what a document cannot hold: a hypothesis that code or a name depends on, or a dead
  end.
- When a finding turns out to be wrong, change its status to `refuted` and rewrite the statement to
  say what is wrong and what is true instead. Do not append a dated correction: an entry states
  where things stand, like every other document.
- The register holds findings about the decompilation and the native port only.
- `make hygiene` runs `python3 scripts/findings.py check`: ids are unique and in order, statuses are
  valid, confirmed entries have evidence, no entry carries a date, and every `#N` cited anywhere in
  the documents or the source exists.
