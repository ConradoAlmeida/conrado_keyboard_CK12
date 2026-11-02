# Keymaps e VIA/Vial

[← Voltar ao README](../README.md) · [Firmware e build](FIRMWARE.md) · [Hardware](HARDWARE.md)

> Keymaps do firmware via, configuração ao vivo, alternativos e backup/restore.

---

## Keymaps do firmware `via` (padrões após flash limpo)

Valem até restaurar o backup `.vil`:

```
Layer 0:
┌──────────┬──────────┬──────────┬──────────┐
│ TD(0)    │ Ctrl+X   │ Ctrl+C   │ Ctrl+V   │
├──────────┼──────────┼──────────┼──────────┤
│ Backspace│ Enter    │ Tab      │ Esc      │
├──────────┼──────────┼──────────┼──────────┤
│ Mute     │ Vol-     │ Vol+     │ Play     │
└──────────┴──────────┴──────────┴──────────┘

Layer 1: TRNS, F14-F20, TRNS (tecla [0,0] = KC_TRNS, herda o Tap Dance)
Layer 2: TRNS, F21-F24, TRNS (tecla [0,0] = KC_TRNS, herda o Tap Dance)
```

## Configuração ao vivo (backup `firmware_backup/keyboards/ck12/bakcup01.vil`)

```
Layer 0: TD(0)/Cut/Copy/Paste, Bksp/Enter/Tab/M2, Mute/Vol-/Vol+/Play
Layer 1: TRNS/F14/F15/TD(1), NO/NO/NO/TD(2), Vol+/Vol-/Mute/BTN1
Layer 2: TRNS/F22/F23/F24, resto transparente (herda das layers de baixo)
Macros: M0 = hold W, M1 = hold 2, M2 = texto "opencode" + Enter, M3 = rajada 2x BTN1 (50ms)
Tap Dance: TD(0) = TO(0)/hold TO(2)/2-toques TO(1), TD(1) = tap M0/hold W,
           TD(2) = tap M1/hold 2, TD(3) = tap M3
```

> ⚠️ `M0` e `M1` estão como `down` sem o `up` correspondente (tecla fica "presa").
> Revisar no Vial: trocar por `Tap` ou adicionar o `Up`.

## Keymaps Alternativos

### Debug (mapeia cada tecla para 1-9, 0, A, B)

```sh
qmk compile -kb ck12 -km debug
```

Útil para verificar se o wiring está correto.

### Produtividade (antigo)

```sh
qmk compile -kb ck12 -km produtividade
```

### Gaming - Terraria (antigo)

```sh
qmk compile -kb ck12 -km gaming-terraria
```
