#!/usr/bin/env python3
"""table_diff.py DRAFT.cpp : per-entry report on the dispatcher's non-code regions.

Compiles the draft exactly as full_verify.py does and compares, entry by entry, with retail:

  * both switch tables (0x519310, 0x519370): every entry that differs, with the retail and
    our case-label offset inside the function, the byte shift between them, and the
    FIGHTCALC region (tools/dispatcher/score.py numbering) each label falls in;
  * the exception index record (0x553b80): function, code size, table address;
  * the exception table (0x544fd4, 416 bytes): header, then every protected return-PC range
    (retail vs ours: absolute start/end, byte shift, cleanup chain) and cleanup action.

Nothing is relaxed: any difference is printed, and the exit status is 1 unless all three
regions are byte-identical (the exception table's 0-3 trailing zero pad bytes excepted, as in
tools/verify.py). Code is NOT judged here (score.py / full_verify.py do that), so a draft whose
size differs from retail still gets a meaningful table report: case labels past the first
extra/missing word are expected to shift until the code matches.

Run from the repository root:  python3 tools/dispatcher/table_diff.py tools/dispatcher/draft.cpp
Also called by `full_verify.py --diagnose`."""
import bisect, difflib, os, re, struct, subprocess, sys, tempfile

sys.path.insert(0, 'tools'); sys.path.insert(0, 'scripts')
import verify, unitobjects, combat_unwind_inventory as unwind

VA = 0x3fca10
COMPILER, FLAGS = 'local/mwcps2/combat/mwccps2.exe', '-O3,p -Iinclude'
OVERLAY = 'tools/dispatcher/unit-objects.json'


def region_table():
    """[(start, label)] for the dispatcher's regions, taken from score.py without running it."""
    src = open('tools/dispatcher/score.py').read().rsplit('\nmain()', 1)[0]
    ns = {'__name__': 'score_regions'}
    exec(compile(src, 'score.py', 'exec'), ns)
    rows = ns['regions']()
    return [(lo, name) for name, lo, hi in rows]


def label_of(regions, addr):
    keys = [lo for lo, _ in regions]
    i = bisect.bisect_right(keys, addr) - 1
    return regions[i][1] if 0 <= i else '?'


def compile_draft(draft):
    obj = os.path.join(tempfile.gettempdir(), 'ownership-td-%d.o' % os.getpid())
    if os.path.exists(obj):
        os.remove(obj)
    env = dict(os.environ, MWCIncludes=os.path.dirname(os.path.abspath(draft)))
    subprocess.run([verify.WIBO_DEFAULT, COMPILER, '-c', *FLAGS.split(), draft, '-o', obj],
                   capture_output=True, text=True, env=env)
    if not os.path.exists(obj):
        raise SystemExit('table_diff: compile failed')
    return obj


def analyse(draft, overlay=OVERLAY, symbols='config/SLUS-20836/symbols.txt', out=print):
    """Print the report; return True when all three regions are exact."""
    obj = compile_draft(draft)
    try:
        return _analyse(obj, overlay, symbols, out)
    finally:
        os.remove(obj)


def _analyse(obj, overlay, symbols, out):
    by_name, by_va = verify.load_symbols(symbols)
    group = unitobjects.group_for(VA, overlay)
    if group is None:
        raise SystemExit('table_diff: overlay %s has no entry for 0x%x' % (overlay, VA))
    img = verify.read_elf(verify.ELF_DEFAULT)
    headers = verify.elf_section_headers(obj)
    syms, _ = verify.object_syms(obj)
    members = [(by_va[group.owner][0], group.owner)] + list(group.emitted) + list(group.duplicates)
    records = {}
    for name, address in members:
        if name in syms and isinstance(syms[name][0], int):
            records[name] = (address, syms[name][0], syms[name][2])
    owner_name = by_va[group.owner][0]
    if owner_name not in records:
        raise SystemExit('table_diff: object defines no %s' % owner_name)
    owner_size = records[owner_name][2]
    aliases = dict(group.externals)
    jumptables = verify.load_jumptables(verify.jumptables_path(symbols))
    tables = verify.jump_table_sections(obj, sorted(jumptables.get(group.owner, [])))
    table_addr = {index: address for index, address, _ in tables}
    ex_index = ex_table = None
    for i, (n, h) in enumerate(headers):
        if n == '.exceptix' and h[5] == 12:
            rel = verify.object_relocs(obj, target_section=i)
            if any(r[3] == owner_name for r in rel if r[1] == 0):
                ex_index = i
        elif n == '.exception' and h[5]:
            ex_table = i
    index_at, table_at, table_size = group.exceptions
    gp = verify.reginfo_gp(verify.ELF_DEFAULT)

    def resolver(name):
        if name in records:
            return records[name][0]
        if name in aliases:
            return aliases[name]
        if name in syms and isinstance(syms[name][0], int):
            sec, value, _ = syms[name]
            if sec == records[owner_name][1]:
                return group.owner + value
            if sec == ex_table:
                return table_at + value
            if sec in table_addr:
                return table_addr[sec] + value
            return None
        return verify.sym_address(name, by_name)

    def relocated(section, kind):
        raw = verify.object_section(obj, kind, section)
        patched, _, unresolved = verify.apply_relocs(
            raw, verify.object_relocs(obj, target_section=section), resolver, gp)
        return patched, unresolved

    regions = region_table()
    exact = True
    out('table_diff: owner body %d bytes (retail %d, %+d)' % (owner_size, by_va[group.owner][1],
                                                              owner_size - by_va[group.owner][1]))

    # ---- switch tables ------------------------------------------------------
    for section, address, size in tables:
        got, unresolved = relocated(section, '.rodata')
        want = verify.va_bytes(img, address, size)
        for off, nm in unresolved:
            out('  jump table 0x%x: unresolved relocation %r at +0x%x' % (address, nm, off)); exact = False
        bad = [i for i in range(0, size, 4) if got is None or got[i:i + 4] != want[i:i + 4]]
        if not bad and not unresolved and got is not None and len(got) == size:
            out('MATCH jump table 0x%x: %d entries identical' % (address, size // 4)); continue
        exact = False
        out('DIFFER jump table 0x%x: %d of %d entries differ' % (address, len(bad), size // 4))
        for i in bad:
            r = struct.unpack_from('<I', want, i)[0]
            o = struct.unpack_from('<I', got, i)[0] if got else 0
            out('   entry %2d  retail 0x%06x (+0x%05x, %s)  ours 0x%06x  shift %+d bytes (%+d words)'
                % (i // 4, r, r - group.owner, label_of(regions, r), o, o - r, (o - r) // 4))

    # ---- exception index record --------------------------------------------
    got, unresolved = relocated(ex_index, '.exceptix')
    want = verify.va_bytes(img, index_at, 12)
    fields = ('function', 'code size', 'table')
    names = [struct.unpack_from('<I', want, 4 * k)[0] for k in range(3)]
    ours = [struct.unpack_from('<I', got, 4 * k)[0] for k in range(3)]
    if got == want and not unresolved:
        out('MATCH exception index 0x%x: (0x%x, 0x%x, 0x%x)' % ((index_at,) + tuple(names)))
    else:
        exact = False
        out('DIFFER exception index 0x%x' % index_at)
        for f, r, o in zip(fields, names, ours):
            if r != o:
                out('   %-9s retail 0x%x ours 0x%x (%+d)' % (f, r, o, o - r))

    # ---- exception table ----------------------------------------------------
    got, unresolved = relocated(ex_table, '.exception')
    pad = table_size - len(got)
    want_all = verify.va_bytes(img, table_at, table_size)
    want = want_all[:len(got)]
    same = got == want and not unresolved and 0 <= pad <= 3 and not any(want_all[len(got):])
    if same:
        out('MATCH exception table 0x%x: %d bytes (+%d pad)' % (table_at, len(got), pad)); return exact
    exact = False
    out('DIFFER exception table 0x%x: ours %d bytes (+%d pad to retail %d)' % (table_at, len(got), pad, table_size))
    for off, nm in unresolved:
        out('   unresolved cleanup pointer %r at +0x%x' % (nm, off))
    try:
        r_inv = unwind.decode(want_all, group.owner, by_va[group.owner][1], table_at)
        o_inv = unwind.decode(bytes(got), group.owner, owner_size, table_at)
    except unwind.DecodeError as error:
        out('   cannot decode (%s); raw byte differences:' % error)
        for i in range(min(len(got), len(want))):
            if got[i] != want[i]:
                out('   +0x%03x retail %02x ours %02x' % (i, want[i], got[i]))
        return exact
    for key in ('header', 'frame', 'save_area_base', 'saved_gprs', 'saved_fprs', 'return_save_offset'):
        if r_inv[key] != o_inv[key]:
            out('   header %s retail %s ours %s' % (key, r_inv[key], o_inv[key]))

    def dname(a):
        return by_va.get(a, ('0x%x' % a,))[0]

    def sig(row):
        return (row['end_inclusive'] - row['start'], tuple((c['stack_offset'], c['destructor'], c['final'])
                                                           for c in row['cleanup_chain']))

    def chain(row):
        return ' -> '.join('%s@+0x%x' % (dname(c['destructor']).split('__')[0] or dname(c['destructor']), c['stack_offset'])
                           for c in row['cleanup_chain'])

    rr, orr = r_inv['ranges'], o_inv['ranges']
    out('   ranges: retail %d, ours %d' % (len(rr), len(orr)))
    sm = difflib.SequenceMatcher(None, [sig(r) for r in rr], [sig(r) for r in orr], autojunk=False)
    run = None  # (first_retail_index, last, shift) of consecutive same-shift matched ranges
    shifts = []

    def flush():
        nonlocal run
        if run:
            a, b, s = run
            out('   ranges %d..%d: same action and length, start %+d bytes (%+d words) from retail'
                % (a, b, s, s // 4) if s else '   ranges %d..%d identical' % (a, b))
        run = None

    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag == 'equal':
            for k in range(i2 - i1):
                s = orr[j1 + k]['start'] - rr[i1 + k]['start']
                if run and run[2] == s and run[1] == i1 + k - 1:
                    run = (run[0], i1 + k, s)
                else:
                    flush(); run = (i1 + k, i1 + k, s)
            continue
        flush()
        for r in rr[i1:i2]:
            out('   retail-only range %d: 0x%06x..0x%06x (%s) chain %s' % (rr.index(r), r['start'], r['end_inclusive'],
                                                                         label_of(regions, r['start']), chain(r)))
        for o in orr[j1:j2]:
            out('   ours-only   range %d: 0x%06x..0x%06x (%s) chain %s' % (orr.index(o), o['start'], o['end_inclusive'],
                                                                         label_of(regions, o['start']), chain(o)))
    flush()
    ra, oa = r_inv['actions'], o_inv['actions']
    rk = [(a['tag'], a['stack_offset'], a['destructor']) for a in ra]
    ok_ = [(a['tag'], a['stack_offset'], a['destructor']) for a in oa]
    if rk == ok_:
        out('   actions: %d, identical (order, frame offsets, destructors)' % len(ra))
    else:
        out('   actions: retail %d, ours %d' % (len(ra), len(oa)))
        for tag, i1, i2, j1, j2 in difflib.SequenceMatcher(None, rk, ok_, autojunk=False).get_opcodes():
            if tag == 'equal':
                continue
            for a in ra[i1:i2]:
                out('   retail action @+0x%03x: tag 0x%02x frame +0x%x -> %s' % (a['offset'], a['tag'], a['stack_offset'], dname(a['destructor'])))
            for a in oa[j1:j2]:
                out('   ours   action @+0x%03x: tag 0x%02x frame +0x%x -> %s' % (a['offset'], a['tag'], a['stack_offset'], dname(a['destructor'])))
    return exact


if __name__ == '__main__':
    if len(sys.argv) != 2 or not os.path.isfile('tools/verify.py'):
        raise SystemExit(__doc__.split('\n')[0] + '\nrun from the repository root with one draft path')
    sys.exit(0 if analyse(sys.argv[1]) else 1)
