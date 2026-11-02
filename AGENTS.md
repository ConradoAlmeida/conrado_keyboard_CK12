# AGENTS.md

Guia para agentes de IA que trabalharem neste projeto.

## Visão geral

Macropad de 12 teclas (3x4) com firmware QMK + VIA, rodando em RP2040 via USB.
O teclado é chamado de **CK12** (Conrado Keyboard, 12 teclas) no QMK
(`keyboards/ck12/`). O case 3D já foi projetado e impresso.

## Contexto técnico (não alterar sem consultar o usuário)

- **Microcontrolador**: RP2040 (Pico ou clone, USB-C). Configurar como `rp2040`
  genérico no QMK — não importa se é placa original ou clone (2/4/8MB).
- **USB apenas** — sem Bluetooth. **Sem** usar ZMK.
- **Matrix**: 3 linhas x 4 colunas.
  - Colunas: GPIO 2, 3, 4, 5
  - Linhas: GPIO 6, 7, 8
- **Sem diodos** (uso de tecla única, sem combos — ghosting não é problema).
- **Firmware atual (v2)**: keymap `via` com 3 layers padrão, Tap Dance na tecla [0,0],
  macros, mousekey, autoclick toggle e Repeat Key. A config ao vivo (EEPROM) está
  salva em `firmware_backup/keyboards/ck12/*.vil` — tudo é configurável via Vial
  ao vivo (exceto tecla [0,0] e o custom keycode).
- **VIA/Vial**: `VIA_ENABLE = yes`, `VIAL_ENABLE = yes`, `DYNAMIC_KEYMAP_MACRO_ENABLE = yes`
  e `QMK_SETTINGS = yes` no `rules.mk` do teclado.
- **Vial**: compilar com o fork `vial-kb/vial-qmk` (branch `vial`), NÃO o QMK upstream.
  O `~/qmk_firmware` está no branch `vial` do fork.
- **Tap Dance**: `TAP_DANCE_ENABLE = yes` no `rules.mk` do keymap `via`. No Vial o Tap Dance
  é dinâmico (configurável via `vial.rocks`); o slot 0 é pré-programado no firmware para
  manter o comportamento de troca de layers.
- **Vial security**: UID em `keymaps/via/config.h` (`VIAL_KEYBOARD_UID`) e combo de
  desbloqueio `VIAL_UNLOCK_COMBO_ROWS/COLS` (tecla [0,0] + [2,3]).
  **Não alterar o UID**: os backups `.vil` só restauram se o UID for o mesmo.
- **Backup Vial**: `firmware_backup/keyboards/ck12/*.vil` (layers, macros, tap dance,
  combos, overrides, settings). Salvar antes de cada flash (flash apaga o EEPROM);
  restaurar depois com Unlock prévio.
- **Bootmagic**: configurado na tecla [0,0] para entrar em modo bootloader.
- **Mousekey**: habilitado (`mousekey: true` no `keyboard.json`).
- **Autoclick (duplo-click)**: 3 custom keycodes a partir de `SAFE_RANGE` no
  `keymaps/via/keymap.c`: `AUTO_CLICK_250MS` (User0), `AUTO_CLICK_500MS` (User1),
  `AUTO_CLICK_1000MS` (User2) = pausa ENTRE duplos-clicks; gap de ~40ms
  (`DOUBLE_CLICK_GAP_MS`, fixo) entre os 2 clicks do duplo. Mesma tecla =
  liga/desliga (com 1 click imediato de feedback); outra tecla = troca a pausa sem
  desligar (máquina de estados `dbl_step` em `matrix_scan_user` via `tap_code(KC_MS_BTN1)`).
  `process_record_user` aceita os códigos do Vial novo (`0x7E40+`) **e** do antigo
  (`QK_KB_0..2`, `0x7E00+`) — não remover o fallback sem confirmar a versão do app.
- **Repeat Key**: habilitado (`REPEAT_KEY_ENABLE = yes` no `keymaps/via/rules.mk`).
  Repete 1x por toque, não é loop — click contínuo é o autoclick acima.

## Convenções

- Português (pt-BR) nas comunicações e documentos.
- Firmware em C, seguindo convenções do QMK (`keymap.c`, `keyboard.json`, `rules.mk`).
- Não usar PlatformIO — build via QMK CLI (`qmk compile` / `qmk flash`).
- O teclado no QMK é o `ck12` — pasta `firmware/keyboards/ck12/`, copiada para
  `~/qmk_firmware/keyboards/ck12/`.
- O keymap principal é `via` (não `default`), que tem suporte completo ao VIA.
- O arquivo `firmware/conrado_keyboard_ck12.layout.json` é a definição para o VIA reconhecer o teclado.
- O `firmware/keyboards/ck12/keymaps/via/vial.json` é a definição para o Vial.
- **Tap Dance**: no Vial é dinâmico — `keymap.c` só mapeia `TD(0)` na tecla [0,0] e o
  comportamento é configurado na GUI (`vial.rocks`). O slot 0 é pré-carregado no firmware
  (via `dynamic_keymap_set_tap_dance`) para manter a troca de layers original.

## Keymaps disponíveis

- `via` - Keymap principal com suporte completo ao VIA, macros e Tap Dance
  (padrões do firmware — a config ao vivo está no `.vil`, ver README)
  - Layer 0: Tap Dance [0,0], Ctrl+X/C/V, Backspace, Enter, Tab, Esc, Mute, Vol-, Vol+, Play
  - Layer 1: F14-F20 (tecla [0,0] = `KC_TRNS` para herdar Tap Dance)
  - Layer 2: F21-F24 (tecla [0,0] = `KC_TRNS` para herdar Tap Dance)
- `default` - Keymap básico (Ctrl+Z, Ctrl+X, Ctrl+C, Ctrl+V, etc.)
- `debug` - Mapeia cada tecla para 1-9, 0, A, B (para testar wiring)
- `produtividade` - Keymap de produtividade (antigo)
- `gaming-terraria` - Keymap para Terraria (antigo)

## Compilar e gravar firmware

O QMK precisa estar instalado (`pip3 install qmk`). O código fonte do teclado fica em
`firmware/keyboards/ck12/` e deve ser copiado para `~/qmk_firmware/keyboards/ck12/`.

### Comandos

```sh
# Firmware principal (VIA + macros + Tap Dance)
qmk compile -kb ck12 -km via
qmk flash -kb ck12 -km via

# Firmware de debug (testar wiring)
qmk compile -kb ck12 -km debug
qmk flash -kb ck12 -km debug

# Keymaps alternativos
qmk compile -kb ck12 -km produtividade
qmk compile -kb ck12 -km gaming-terraria
```

### Fluxo de trabalho para adicionar funcionalidades

1. Pedir/salvar backup `.vil` atual em `firmware_backup/` (flash apaga o EEPROM)
2. Editar arquivos em `firmware/keyboards/ck12/keymaps/via/`
3. Copiar para `~/qmk_firmware/keyboards/ck12/keymaps/via/` (e `keyboard.json` se alterado)
4. Limpar build cache: `qmk clean`
5. Compilar: `qmk compile -kb ck12 -km via`
6. Flashar: bootloader (`[0,0]` + conectar, vira `RPI-RP2`) → `qmk flash` ou copiar o `.uf2`
7. Pedir ao usuário: Unlock no Vial → restaurar o `.vil` → remapear novidades → salvar novo `.vil`

### Notas importantes

- No RP2040, `qmk flash` pede para segurar BOOTSEL e conectar via USB.
- Ou use bootmagic: segure tecla [0,0] + conecte USB.
- Para IntelliSense: `qmk compile -kb <keyboard> -km <keymap> --compiledb`.
- **Sempre** copie os arquivos editados para `~/qmk_firmware/` antes de compilar.
- **Sempre** use `qmk clean` antes de compilar para evitar cache antigo.
- Para adicionar novas features (Tap Dance, Combo, etc.), adicione `FEATURE_ENABLE = yes`
  no `rules.mk` do keymap (não no `rules.mk` do teclado).

## Tap Dance

A tecla [0,0] usa Tap Dance para trocar de layer (`TD(0)` = `TO(0)` / hold `TO(2)` / 2 taps `TO(1)`):
- **1 tap** → Layer 0 (atalhos normais)
- **2 taps** → Layer 1 (F14-F20)
- **segurar** → Layer 2 (F21-F24)

**IMPORTANTE**: A tecla [0,0] **não deve ser alterada no VIA**. O Tap Dance é
implementado no firmware e sobrescreve o mapeamento do VIA. Nas Layers 1 e 2,
a tecla [0,0] deve ser `KC_TRNS` (transparent) para herdar o Tap Dance da Layer 0.

## Estado do projeto

- [x] Hardware/pinagem definidos
- [x] Design 3D impresso
- [x] Firmware QMK+VIA criado
- [x] Gravação no RP2040
- [x] Validação de remap no VIA
- [x] Suporte a macros habilitado
- [x] Tap Dance na tecla [0,0] (3 layers)
- [x] Mousekey habilitado (`mousekey: true`)
- [x] Autoclick toggle (`AUTO_CLICK`/`User0`, dual keycode Vial novo/antigo)
- [x] Repeat Key habilitado
- [x] Backup `.vil` + fluxo backup → flash → restore documentado
- [x] Troubleshooting documentado
