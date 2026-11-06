# Contributing

The decompilation is a work in progress and there's plenty left to do, so you're more than welcome
to help! You don't need to know the whole project. Making one small function read well is a real
contribution.

There are a few ways to help:

1. Decompile a function that has no C yet. `tools/m2c_batch.py` drafts a starting point
   ([how that works](docs/engine/m2c-bulk.md)).
2. Tidy up code that already matches. Renaming a mystery function or giving a struct real fields
   helps everyone who reads it next. [PROGRESS.md](PROGRESS.md) shows what's left.
3. Open an issue if you've found something wrong or worked out how part of the game behaves.

## Before you start

Follow the [README](README.md#installation) to get a build working, then check nobody has beaten you
to it. Check the [documentation](docs/README.md) for the topic you're working on, including its notes
on what didn't work. If you're planning something big, open an issue first so two people don't
end up on the same module.

## Writing code

The code has to match the original byte for byte, and a person has to be able to read it. Both count.

- Name things for what they are, based on something you can point to, like a string or how it's
  called. If you're only guessing, leave the name and note the guess in the topic's document. Addresses
  aren't names.
- Clean up after the decompiler: rename `temp_s0` and `sp5C`, and use real structs instead of pointer
  maths.
- Only comment what the code can't tell the reader, and keep it to the point.
- If you wrote something odd just to match, mark it: `/* matching construct: <what and why> */`.
- If you can't get a function into C yet, leave it out. Please don't wrap its instructions in `asm`.

## Checking your work

To try one function:

```sh
python3 tools/check.py --function 0xVA --cand src/unmatched/FUN_XXXXXXXX.c
```

Read everything it prints, because the first line isn't always the real problem. For a side-by-side
view, run `python3 configure.py && ninja objdiff` and open the folder in
[objdiff](https://github.com/encounter/objdiff).

Before opening a pull request, run all four of these:

```sh
make check        # everything still matches, and no matches were lost
make link         # the rebuilt game is identical to the original
make typed-check  # struct field coverage didn't slip
make hygiene      # nothing private is about to be published
```

If you changed `tools/` or the tables in `config/`, use `make check-fresh` and `make link-fresh`.

## Making a pull request

1. Fork the repo and run `scripts/install_git_hooks.sh` once in your clone.
2. Make your changes. If you learned something useful, add it to the document for that topic.
3. Run the four checks above.
4. Open a pull request with a clear title, like "Name the shop menu's page functions", and include the
   results of the checks.
5. Done!

## Opening an issue

1. Go to the [issues page](https://github.com/crashbashash/DW4_Decomp/issues) and click "New issue".
2. Add a clear title, like "Save screen hangs after loading slot 2 in the port".
3. Say what you saw or found, and how to see it yourself.

## Please keep these out

- **Anything from the game:** disc images, executables, BIOS files, saves, extracted assets,
  screenshots, or the game's code as assembly. Names and notes we've worked out are fine.
- **Hand edits to generated files:** `PROGRESS.md`, most of `data/` and the symbol tables in `config/`.
  Change what they're built from and run `make progress`.

## Licence

Your own work here is dedicated to the public domain under CC0 1.0, as described in
[LICENSE](LICENSE). Game-derived material stays as described there.
