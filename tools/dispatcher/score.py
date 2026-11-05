#!/usr/bin/env python3
"""score.py SOURCE.cpp [--flags FLAGS] [--json OUT] : per-region diff of a dispatcher draft against retail.
Run from a repository root (uses tools/verify.py).  Regions: pre-FIGHTCALC parent code, the 22 FIGHTCALC commands, post."""
import sys, re, json, difflib, argparse
sys.path.insert(0, 'tools')
import verify, m2c_loop
BASE = 0x3fca10
CMDS = [(0,'E2PISHITCHECK',0x401b80),(1,'P2EISHITCHECK',0x3fdeb8),(2,'P2EISCRITICAL',0x3fe130),(3,'E2PDAMAGE',0x401e68),
 (4,'E2PDAMAGERANK',0x402ec0),(5,'P2EDAMAGE',0x3fe550),(6,'P2EEXPUP',0x3ff748),(7,'E2PSTUNTIME',0x4031e8),(8,'E2PPOISONTIME',0x403570),
 (9,'E2PSLEEPTIME',0x403990),(10,'E2PBINDTIME',0x403ca8),(11,'E2PATKDWNTIME',0x404198),(12,'E2PPOWDWNTIME',0x4049b0),
 (13,'P2ESKILLUP',0x3ff200),(14,'P2ESTUNTIME',0x3ffd20),(15,'P2EPOISONTIME',0x3ffef0),(16,'P2ESLEEPTIME',0x4003b0),
 (17,'P2EBINDTIME',0x400738),(18,'P2EATKDWNTIME',0x400ac0),(19,'P2EPOWDWNTIME',0x401330),(20,'P2PKOUKAMAGIC',0x4051c8),(21,'GETPATKZOKUSEI',0x3ff030)]
PRE_END, FC_START, FC_END = 0x3fde30, 0x3fde30, 0x406ad0
def regions():
    pts = sorted(CMDS, key=lambda c: c[2])
    out = [('pre-FIGHTCALC (parent switch, GETCOMMON/GETPLAYER/CTRLITEM..)', BASE, pts[0][2])]
    for i, (n, name, a) in enumerate(pts):
        end = pts[i+1][2] if i+1 < len(pts) else FC_END
        out.append(('%02d %s' % (n, name), a, end))
    out.append(('post-FIGHTCALC (tail, CTRLPLAYER..)', FC_END, BASE + 41864))
    return out
MEM_OPS = {0x0f, 0x09, 0x23, 0x2b, 0x20, 0x24, 0x28, 0x21, 0x25, 0x29, 0x31, 0x39, 0x1e, 0x1f, 0x37, 0x3f, 0x0d, 0x08}
def masked_equal(r, o):
    if r == o: return True
    opr, opo = r >> 26, o >> 26
    if opr != opo: return False
    if opr in (2, 3): return True                      # j / jal: target is relocated
    if opr in MEM_OPS and (o & 0xffff) == 0 and (r >> 16) == (o >> 16): return True   # relocated immediate
    return False
def norm(m, o):
    if re.match(r'^(b|j|bal)', m) : o = re.sub(r'0x[0-9a-f]+', 'T', o)
    o = re.sub(r'\b(?:[sv][0-8]|a[0-3]|t[0-9]|at)\b', 'R', o)
    o = re.sub(r'-?\d+\(sp\)', 'SLOT(sp)', o)
    o = re.sub(r'\bsp,sp,-?\d+', 'sp,sp,N', o)
    return m + ' ' + o
def main():
    ap = argparse.ArgumentParser(); ap.add_argument('source'); ap.add_argument('--flags', default='-O3,p -Iinclude')
    ap.add_argument('--symbols', default=None); ap.add_argument('--json'); a = ap.parse_args()
    if a.symbols is None:
        import tempfile, os
        tf = tempfile.NamedTemporaryFile('w', suffix='.txt', delete=False)
        tf.write(open('config/SLUS-20836/symbols.txt').read().rstrip('\n') + '\n0033e9c0 000080 __dt__17RecoveryCopiedRefFv\n'); tf.close(); a.symbols = tf.name
    ok, report = verify.verify_one(BASE, a.source, symbols=a.symbols, mwcc='local/mwcps2/combat/mwccps2.exe', flags=a.flags, verbose=True)
    ours, retail = m2c_loop.parse_verbose(report)
    head = [l for l in report.splitlines() if not m2c_loop.VERBOSE_WORD_RE.match(l)][:6]
    print('verify:', 'MATCH' if ok else 'no match'); [print('  ' + l) for l in head]
    if not ours:
        print('no aligned words parsed'); return 1
    wo = [ours[i] for i in sorted(ours)]; wr = [retail[i] for i in sorted(retail)]
    do = m2c_loop.disasm_words(wo, BASE); dr = m2c_loop.disasm_words(wr, BASE)
    ko, kr = sorted(do), sorted(dr)
    no = [norm(*do[k]) for k in ko]; nr = [norm(*dr[k]) for k in kr]
    sm = difflib.SequenceMatcher(None, nr, no, autojunk=False)
    # per retail word: matched in shape? raw equal?
    shape = [False]*len(nr); raw = [False]*len(nr); extra = {}
    for tag, l, h, x, y in sm.get_opcodes():
        if tag in ('replace', 'insert') and (y - x) > (h - l):
            ri = min(l, len(kr) - 1); extra[kr[ri]] = extra.get(kr[ri], 0) + (y - x) - (h - l)
        if tag == 'equal':
            for k in range(h-l):
                shape[l+k] = True; raw[l+k] = masked_equal(wr[l+k], wo[x+k])
    regs = regions(); rows = []
    for name, lo, hi in regs:
        idx = [i for i, k in enumerate(kr) if lo <= k < hi]
        n = len(idx); s = sum(shape[i] for i in idx); r = sum(raw[i] for i in idx)
        rows.append((name, lo, hi, n, n - s, n - r, sum(v for k, v in extra.items() if lo <= k < hi)))
    print('ours words %d, retail words %d' % (len(wo), len(wr)))
    print('%-58s %8s %6s %10s %10s %6s' % ('region', 'start', 'words', 'shape-diff', 'exact-diff', 'extra'))
    for name, lo, hi, n, sd, rd, ex in rows:
        print('%-58s %08x %6d %10d %10d %6d' % (name, lo, n, sd, rd, ex))
    tot = (sum(r[3] for r in rows), sum(r[4] for r in rows), sum(r[5] for r in rows))
    print('%-58s %8s %6d %10d %10d %6d' % ('TOTAL', '', *tot, sum(r[6] for r in rows)))
    if a.json:
        json.dump({'ok': ok, 'ours_words': len(wo), 'retail_words': len(wr), 'rows': rows}, open(a.json, 'w'), indent=1)
main()
