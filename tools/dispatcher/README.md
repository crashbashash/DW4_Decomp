# `tools/dispatcher/`: register-allocation and shape tools

Written while matching the GAMERAM combat dispatcher ([result](../../docs/systems/combat-dispatcher.md)); the tools work on any
function. Background: [register allocation](../../docs/engine/register-allocation.md).

## Register allocation tools

    python3 tools/dispatcher/regalloc_trace.py src/game/beNDMWGameRam.cpp [--only-case N] [--tail N] [--adj DIR --ctx FILE] [--ids a,b,c]
    python3 tools/dispatcher/regalloc_sim.py DIR/adj1.json FILE

`regalloc_trace.py` traces the pinned compiler's graph colouring (last big pass) and reports the receiver colour and the last
pushed nodes; with `--adj/--ctx` it also dumps the interference graph, which `regalloc_sim.py` replays exactly for what-if
experiments.  `ALLOCATION.md` explains the rules and how the receiver was brought to `s4`.
## Small functions

    python3 tools/dispatcher/regalloc.py FUNCTION_OR_VA CANDIDATE.c[pp] [--as MEMBER] [--flags "..."] [--compiler EXE] [--max-pool N]
        [--show-all] [--no-suggest] [--no-edits] [--edit-pool N] [--edit-show N] [--edit-depth 1|2]

Run from the repository root.  `FUNCTION_OR_VA` is a symbol of `config/SLUS-20836/symbols.txt`, a VA (`0x1c5870`), or a member
`config/SLUS-20836/compiler-names.tsv` binds (its compiler name, or `Class::method` read through `tools/demangle.py`).  The tool
takes the compiler and flags the build uses for that function (its `config/SLUS-20836/units.tsv` profile, or a provisional row
of `unit-compilers.tsv`/`unit-flags.tsv`, as `tools/verify.py` compiles it), and has `tools/verify.py` compare the function on
its own, outside its unit's `unit-objects.json` row: the candidate is the whole file or a test file with just the function,
which it defines under the name the build binds, or as a member the build does not bind yet, named with `--as` (a compiler
name, or `Class::method` matched against the compiled candidate's functions).  It prints the verdict and instruction diff
(classified: register-only, same registers with the operands swapped, other), traces the compiler's last general-register
colouring of the candidate and reports, for every node whose register differs from retail, its id, cost, degree, push
position, neighbours and what it is.  It then replays simplify/select on the dumped graph (checked against the compiler's own
pushes and colours) and searches the permutations of the node ids of the involved nodes and their most related neighbours
(up to `--max-pool`; a neighbour whose id comes below an involved node's lowers its degree when simplify scans it) for an
order that gives retail's colours; the orders that leave the parameters' ids in place come first, printed with the
instruction that defines each node.  Last it searches single graph edits around the involved nodes (renumber, including a
neighbour of an involved node and the same neighbour move at each of a set of alike involved nodes at once, merge, delete,
add an interference, add neighbours, un-coalesce; pairs when no single edit is enough), replays each and prints the ones that
give retail's colours with the guessed source name of every node and the nodes the coalescer merged into it
([graph edits](../../docs/engine/register-allocation.md#b52-coalescing-and-the-graph-edit-search)).  The instruction diff is
aligned (difflib), so one missing `nop` does not turn the rest into differences; in a whole-file candidate the colouring
pass that fits the function is chosen.  Exit status 0 = match, 1 = still different, 2 = tool error.

Typical loop: `python3 tools/m2c_batch.py --only NAME --keep-all --max-size 4096` writes the draft to `build/m2c/NAME.c`;
copy it, make the instruction sequence match first (anything marked "not a register difference"), then run the tool and apply
the suggested id order by moving declarations (the id rules are in the tool's docstring and in
`docs/engine/register-allocation.md`); repeat.

The tool is built on the modules above: `regalloc_trace.py` (`trace()`: profiles for the two compilers the tree uses, selected
by the SHA-256 of the executable), `regalloc_sim.py` (replay) and the IR dump added to the trace helper.

What it cannot do:

* It only runs for a compiler build it has a patch profile for (`local/mwcps2/3.0b52-030722`, `local/mwcps2/3.0-011126` and
  the pinned combat build; coalescing is recorded for b52 and combat); for any
  other build it stops with "no trace profile".  gdb, GNU `as`/`ld` with 32-bit x86 support, `local/wibo`,
  `mipsel-linux-gnu-objdump` and permission to ptrace the loader are required.
* It explains *register choice only*.  A different instruction sequence (size, order, extra moves, a `t9` virtual call,
  operand order of a commutative operation) is reported but not explained.
* The alignment between the compiler's IR and the emitted instructions is a register-set heuristic; heavy scheduling or large
  address-materialising sequences leave some nodes without an instruction ("IR op ..."), and a node tied to conflicting retail
  registers is excluded from the search.
* The levers it searches are the id order and single graph edits (or pairs).  An edit is a graph change; turning it into
  source is up to you (the printed names are a declaration-order guess), and an un-coalesce edit takes the split node's cost
  from its survivor.
* Spills: it follows the last pass, but a function that spills in retail but not in the candidate (or the reverse) is
  structural.
* Pools of more than 8 nodes are searched by random swaps, not exhaustively.
* One translation unit may contain several functions; the pass is chosen by how well it fits the emitted code of the
  requested function, so keep helper functions out of the candidate when possible.
