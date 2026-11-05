#!/usr/bin/env python3
"""localize_slots.py IN.cpp OUT.cpp [--min HEX] [--max HEX] [--names a,b,...]

Retail lays out named locals by lexical declaration order (first declared = highest address).  The m2c draft declares
every address-taken scalar `spNNN` at function level, which places them all above the block-scoped objects with
destructors.  This moves each selected scalar declaration to its first use (or to the start of the smallest enclosing
block that contains all uses), so declaration order follows code order."""
import re, sys, argparse
ap = argparse.ArgumentParser(); ap.add_argument('src'); ap.add_argument('dst')
ap.add_argument('--min', default='0'); ap.add_argument('--max', default='ffff'); ap.add_argument('--names', default='')
a = ap.parse_args()
lo, hi = int(a.min, 16), int(a.max, 16)
names = set(x for x in a.names.split(',') if x)
L = open(a.src).read().split('\n')
start = next(i for i, l in enumerate(L) if l.startswith('int Gap__Bec__beNDMWGameRam__vfunc_34(beNDMWGameRam *arg0, int arg1, void *arg2) {'))
decl = re.compile(r'^    (unsigned int|int) (sp([0-9A-F]+));$')
cands = {}
for i in range(start + 1, len(L)):
    m = decl.match(L[i])
    if m:
        off = int(m.group(3), 16)
        if (names and m.group(2) in names) or (not names and lo <= off <= hi):
            cands[m.group(2)] = (i, m.group(1))
    elif L[i].strip() and not L[i].startswith('    ') : break
first_code = min(i for i in range(start + 1, len(L)) if L[i].startswith('    temp_ret = '))
# brace stack per line (stack of opening line indices that are open at the START of the line)
stacks = []; st = []
for i, l in enumerate(L):
    stacks.append(list(st))
    code = re.sub(r'/\*.*?\*/', '', l)
    for ch in code:
        if ch == '{': st.append(i)
        elif ch == '}': st.pop() if st else None
moves = []
for name, (di, ty) in cands.items():
    uses = [i for i in range(first_code, len(L)) if re.search(r'\b%s\b' % name, L[i])]
    if not uses: continue
    common = stacks[uses[0]]
    for u in uses[1:]:
        k = 0
        while k < len(common) and k < len(stacks[u]) and common[k] == stacks[u][k]: k += 1
        common = common[:k]
    f = uses[0]
    # insert at first use if its block is the common block; otherwise at the start of the common block
    if stacks[f] == common: pos = f
    else: pos = common[-1] + 1
    # avoid a label line: insert before label would still be fine; keep
    moves.append((pos, name, ty, di))
for pos, name, ty, di in sorted(moves, key=lambda m: (-m[0], m[1])):
    ind = re.match(r'\s*', L[pos]).group(0) if L[pos].strip() else '    '
    L.insert(pos, '%s%s %s;' % (ind, ty, name))
for pos, name, ty, di in moves:
    pass
dels = sorted([di for _, _, _, di in moves], reverse=True)
# deletions are above all insertions (declarations precede code), so indices of insertions shifted by len(moves) only below
for d in dels: del L[d]
open(a.dst, 'w').write('\n'.join(L))
print('moved', len(moves), 'declarations')
