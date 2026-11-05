#!/usr/bin/env python3
"""Ordered diagnostic raster for the aligned ring-f008/f022 GS dumps.

Retains GIF PRE primitive boundaries, per-vertex state, XYZF depth/fog, actual
texture alpha, GREATER alpha test, GEQUAL depth, ordinary/additive blend and fog.
This is a scoped model, not a GS emulator: nearest sampling, approximate float
interpolation/edge rounding, a zero initial depth surface and no GS memory aliasing.
The selected section must contain the observed context-0 triangle pipeline only.
Images are evidence for draw ordering, not a pixel-exact PCSX2 replacement.
Requires Pillow and the GS dump readers gsread, gsregs and gsdraws, which are not in the repository.
"""
import os, struct, sys, argparse, json
from pathlib import Path
from PIL import Image
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / '../local/tools/gs'))
from gsread import load, parse_header
import gsregs
from gsdraws import eff_addr

W, H = 640, 448


def collect(path):
    d = load(path); info = parse_header(d); off = info['off']
    state = {}; restart = 0; prim = 0; tex0 = 0; rgba = (0, 0, 0, 0)
    s = t = q = 0.0; ofx = ofy = 0.0
    frames = []; cur_f = None

    def frame():
        nonlocal cur_f
        if cur_f is None:
            cur_f = {'runs': []}; frames.append(cur_f)
        return cur_f

    def do(addr, lo, hi, ad):
        nonlocal prim, tex0, rgba, s, t, q, ofx, ofy, cur_f
        if addr not in (1,2,4,5,12,13): state[addr] = lo
        if addr in (0x4c, 0x4d):
            cur_f = None; return
        if addr == 0x00: prim = lo & 0x7ff
        elif addr == 0x01: rgba = gsregs.ad_rgba(lo) if ad else gsregs.packed_rgba(lo, hi)
        elif addr == 0x02:
            s = struct.unpack_from('<f', struct.pack('<I', lo & 0xffffffff))[0]
            t = struct.unpack_from('<f', struct.pack('<I', (lo >> 32) & 0xffffffff))[0]
            q = struct.unpack_from('<f', struct.pack('<I', (hi or 0) & 0xffffffff))[0]
        elif addr in (0x06, 0x07): tex0 = lo
        elif addr in (0x18, 0x19): ofx, ofy = gsregs.xyoff_px(lo)
        elif addr in (0x04, 0x05, 0x0c, 0x0d):
            x, y, z, _f = gsregs.decode_vertex(lo, hi, ad=ad, addr=addr)
            f = frame()
            if not f['runs'] or f['runs'][-1]['prim'] != prim or f['runs'][-1]['tex0'] != tex0:
                f['runs'].append({'prim': prim, 'tex0': tex0, 'verts': []})
            f['runs'][-1]['verts'].append((x - ofx, y - ofy, z, rgba, s, t, q, _f, dict(state), restart))

    while off < len(d):
        pid = d[off]; off += 1
        if pid == 0:
            ln = struct.unpack_from('<I', d, off + 1)[0]
            body = d[off + 5:off + 5 + ln]; off += 5 + ln
            o = 0; N = len(body)
            while o + 16 <= N:
                lo, hi = struct.unpack_from('<QQ', body, o)
                nloop = lo & 0x7fff; pre = (lo >> 46) & 1; gprim = (lo >> 47) & 0x7ff
                flg = (lo >> 58) & 3; nreg = (lo >> 60) & 0xf or 16
                o += 16
                if pre and flg == 0:
                    restart += 1
                if flg == 0:
                    if o + nloop * nreg * 16 > N: break
                    for i in range(nloop * nreg):
                        rc = (hi >> ((i % nreg) * 4)) & 0xf
                        l2, h2 = struct.unpack_from('<QQ', body, o); o += 16
                        if pre and i == 0: prim = gprim & 0x7ff
                        a = eff_addr(rc, h2)
                        if a is not None: do(a, l2, h2, rc == 0x0e)
                elif flg == 1:
                    if o + nloop * nreg * 8 > N: break
                    for i in range(nloop * nreg):
                        rc = (hi >> ((i % nreg) * 4)) & 0xf
                        l2 = struct.unpack_from('<Q', body, o)[0]; o += 8
                        if pre and i == 0: prim = gprim & 0x7ff
                        a = eff_addr(rc, 0)
                        if a is not None: do(a, l2, 0, rc == 0x0e)
                else:
                    if o + nloop * 16 > N: break
                    o += nloop * 16
        elif pid == 1: off += 1
        elif pid == 2:
            ln = struct.unpack_from('<I', d, off)[0]; off += 4 + ln
        elif pid == 3: off += 8192
        else: raise SystemExit('unknown packet %d' % pid)
    return info, frames


def tri_indices(n, prim):
    t = prim & 7
    if t == 4:
        for k in range(n - 2): yield (k, k + 1, k + 2)
    elif t == 5:
        for k in range(1, n - 1): yield (0, k, k + 1)
    elif t == 3:
        for k in range(0, n - 2, 3): yield (k, k + 1, k + 2)


def raster(run, tex, aref=None, texalpha=None, buf=None, zbuf=None):
    if buf is None:
        buf = [[0, 0, 0] for _ in range(W * H)]
    if zbuf is None:
        zbuf = [[0] * W for _ in range(H)]
    ntri = 0
    ta = 255
    segments = []
    start = 0
    vs_all = run['verts']
    for end in range(1,len(vs_all)+1):
        if end == len(vs_all) or vs_all[end][9] != vs_all[start][9]:
            segments.extend(tuple(start+k for k in tri) for tri in tri_indices(end-start,run['prim']))
            start=end
    for (i0, i1, i2) in segments:
        vs = [run['verts'][i0], run['verts'][i1], run['verts'][i2]]
        xs = [v[0] for v in vs]; ys = [v[1] for v in vs]
        x0 = max(0, int(min(xs))); x1 = min(W - 1, int(max(xs)))
        y0 = max(0, int(min(ys))); y1 = min(H - 1, int(max(ys)))
        if x1 < x0 or y1 < y0: continue
        ax, ay = xs[0], ys[0]; bx, by = xs[1], ys[1]; cx, cy = xs[2], ys[2]
        den = (by - cy) * (ax - cx) + (cx - bx) * (ay - cy)
        if den == 0: continue
        ntri += 1
        for py in range(y0, y1 + 1):
            for px in range(x0, x1 + 1):
                la = ((by - cy) * (px - cx) + (cx - bx) * (py - cy)) / den
                lb = ((cy - ay) * (px - cx) + (ax - cx) * (py - cy)) / den
                lc = 1.0 - la - lb
                if la < 0 or lb < 0 or lc < 0: continue
                z = la * vs[0][2] + lb * vs[1][2] + lc * vs[2][2]
                if not (z >= zbuf[py][px]): continue
                s = la * vs[0][4] + lb * vs[1][4] + lc * vs[2][4]
                t = la * vs[0][5] + lb * vs[1][5] + lc * vs[2][5]
                q = la * vs[0][6] + lb * vs[1][6] + lc * vs[2][6]
                if tex is not None and q:
                    u = (s / q) % 1.0; vv = (t / q) % 1.0
                    tw, th = tex.size
                    tx = min(tw - 1, max(0, int(u * tw))); ty = min(th - 1, max(0, int(vv * th)))
                    tr, tg, tb = tex.load()[tx, ty]
                    if isinstance(texalpha, int):
                        ta = texalpha
                    else:
                        ta = texalpha[tx, ty] if texalpha is not None else 255
                else:
                    tr = tg = tb = 255; ta = 255
                vr = int(la * vs[0][3][0] + lb * vs[1][3][0] + lc * vs[2][3][0])
                vg = int(la * vs[0][3][1] + lb * vs[1][3][1] + lc * vs[2][3][1])
                vb = int(la * vs[0][3][2] + lb * vs[1][3][2] + lc * vs[2][3][2])
                va = int(la * vs[0][3][3] + lb * vs[1][3][3] + lc * vs[2][3][3])
                # TFX=MODULATE uses the GS's 0x80 == 1.0 domain: (T*V)>>7, clamped
                # to 8 bits.  Dividing by 255 here falsely turned 128*128 into 64 and
                # produced the refuted task-4D alpha-test explanation.
                cr = gsregs.tfx_modulate_channel(tr, vr)
                cg = gsregs.tfx_modulate_channel(tg, vg)
                cb = gsregs.tfx_modulate_channel(tb, vb)
                frag_a = gsregs.tfx_modulate_channel(ta, va)
                state = vs[2][8]
                threshold = (state.get(0x47,0) >> 4) & 255
                if (state.get(0x47,0)&1) and not (frag_a > threshold):
                    continue                # ATE=1 ATST=GREATER: drop
                zbuf[py][px] = z
                ca = min(1.0, frag_a / 128.0)  # GS ALPHA uses 0x80 as blend factor 1.0
                d = buf[py * W + px]
                if state.get(0x1b,0) & 32:
                    fog = (la*vs[0][7]+lb*vs[1][7]+lc*vs[2][7])/255
                    fc = state.get(0x3d,0)
                    cr = cr*fog+(fc&255)*(1-fog)
                    cg = cg*fog+((fc>>8)&255)*(1-fog)
                    cb = cb*fog+((fc>>16)&255)*(1-fog)
                dest = 1-ca if state.get(0x42,0)==0x44 else 1
                d[0] = min(255, int(d[0]*dest + cr * ca))
                d[1] = min(255, int(d[1]*dest + cg * ca))
                d[2] = min(255, int(d[2]*dest + cb * ca))
    return buf, ntri


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('dump')
    ap.add_argument('texture', help='PCSX2 dumped RGBA texture, with GS-domain alpha')
    ap.add_argument('outdir')
    ap.add_argument('--frame', type=int, default=8, help='FRAME-section index, not displayed frame')
    ap.add_argument('--all-additive', action='store_true', help='controlled ALPHA=0x48 ablation')
    args = ap.parse_args()
    out = Path(args.outdir); out.mkdir(parents=True, exist_ok=True)
    info, frames = collect(args.dump)
    tex = Image.open(args.texture).convert('RGBA')
    rgb, alpha = tex.convert('RGB'), tex.getchannel('A').load()
    buf = [[0, 0, 0] for _ in range(W*H)]; depth = [[0]*W for _ in range(H)]
    rows = []
    # Split state changes for intermediate images; all observed changes coincide with PRE.
    for ri, run in enumerate(frames[args.frame]['runs']):
        verts = run['verts']; begin = 0; part = 0
        for end in range(1, len(verts)+1):
            if end != len(verts) and verts[end][8] == verts[begin][8]:
                continue
            if end != len(verts):
                assert verts[end][9] != verts[end-1][9], 'state change inside a primitive batch'
            sub = dict(run, verts=verts[begin:end])
            state = sub['verts'][0][8]
            assert (run['prim'] & 7) in (3,4,5)
            assert state[0x1b] in (0x78,0x58)
            assert state[0x42] in (0x44,0x48)
            assert state[0x47] in (0x504cd,0x500cd)
            row = dict(run=ri, part=part, vertices=end-begin,
                       state={gsregs.REG.get(k,hex(k)):hex(v) for k,v in state.items()})
            if args.all_additive:
                for v in sub['verts']: v[8][0x42] = 0x48
            buf, ntri = raster(sub, rgb, texalpha=alpha, buf=buf, zbuf=depth)
            im = Image.new('RGB',(W,H)); im.putdata([tuple(p) for p in buf])
            name = 'run%d-part%d.png' % (ri,part); im.save(out/name)
            row.update(triangles=ntri, mean=sum(map(sum,buf))/(W*H*3), image=name)
            rows.append(row)
            print(json.dumps({k:v for k,v in row.items() if k!='state'}), flush=True)
            begin=end; part+=1
    im.save(out/'final.png')
    (out/'metrics.json').write_text(json.dumps(rows,indent=2)+'\n')


if __name__ == '__main__':
    main()
