# Inline textures — the destructible props' material

Most stage geometry samples a **texture pack** (see [`texture-packs.md`](texture-packs.md)); the
destructible props do not. The Goblin Pass crate and barrel (`M_BK19a0_boxShape`,
`M_BK17v1_barrelsShape`) are textured by a material that lives **inside the stage pack itself**, as
an `igAttrSet` in the pack's own content pool:

    igAttrSet._attributes -> igAttrList -> igTextureBindAttr._texture
        -> igTextureAttr._image -> igImage._pImage / _pClut

`igImage` names the pool blocks directly (`_pImage`, `_pClut`, `_px`, `_py`, `_bytesPerRow`,
`_imageSize`), so the image is a plain indexed bitmap plus a 256-entry palette, and no texture pack
or live object graph is involved. That is why the texture-pack walk and the live texture walk both
come back empty for these two shapes.

## The format

* **Palette order is `R G B A`** — colour in bytes 0..2. (The texture packs use `A R G B`; the two
  are not interchangeable.)
* The image is a `_px × _py` grid of indices, `_bytesPerRow` bytes per row (row-major), indexing the
  palette. In the Goblin Pass fixture both props' atlases are **32×32**.
* The atlas is a *shared* layout, not one texture per shape: `g_bbarrelsz01` holds the barrel's wood
  staves, its metal hoops and a top-corner block, and the shapes' UVs select the pieces.

## Orientation

**The stored image is top-down**: row 0 of `_pImage` is the row the GS samples at `v = 0`. A GS dump
confirms it — the per-vertex `ST/Q` the VU1 emitted equals the mesh's own `(u, v)` exactly (an affine
fit is the identity, residual `0.000000`), and the texture the GS samples out of VRAM is this image,
RGB-for-RGB.

That matters because PS2-era samplers commonly index their texture array with `1 - v` (the GS's `v`
increasing downward against a bottom-up array), and a renderer that does so must **flip the rows when
it decodes the image**. The port does exactly this: `src/texpack.c` reads the texture-pack grids as
`grid + (h - 1 - y) * w`, and `src/dw4asset.c`'s inline-texture loader mirrors that with
`rgba_flip_rows`. Writing the decoded image out **pre-flipped** instead sampled the mirrored texel,
which is what made the barrel's metal trim read pale (see
[`vertex-shading.md`](vertex-shading.md) for the shading side): the trim sampled a bright part of the
atlas instead of the dark hoop band.

One more property of the same aliasing: the palette's alpha is what the GS sees. The Goblin Pass
barrel's inline palette carries **alpha `128`** on every entry (the GS's texture alpha), while the
same RGB written with alpha `255` is a decode difference, not a colour one — the barrel is drawn
`ABE 0`, so alpha only feeds the `TEST` cutout (`ATE 1 ATST 6 AREF 0xc`, i.e. discard `A ≤ 12`).

## Where the decoded data is consumed

`scripts/pack_inline_tex.py` decodes a material set by name to a PNG (the natural top-down image)
or to a `<u32 w><u32 h><RGBA>` blob for a renderer's `--texdir`. It writes the **pack's own
top-down order**; the renderer owns the flip, so the blob stays a faithful dump of the pack.
