# CK12

Macropad 3x4 (12 teclas), RP2040, QMK + VIA.

## Configuração

Pasta: `keyboards/ck12/` dentro do QMK firmware.

- Colunas: GPIO 2, 3, 4, 5
- Linhas: GPIO 6, 7, 8
- Sem diodos (matrix com ghosting aceito, `"ghost": true`)

## Compilar e gravar

```sh
qmk compile -kb ck12 -km via
qmk flash  -kb ck12 -km via
```

Segurar BOOTSEL no Pico ao conectar para entrar no modo de gravação.

## Tap Dance (tecla [0,0])

A tecla superior-esquerda [0,0] usa Tap Dance para troca de layers:

- **1 tap** → Layer 0 (atalhos normais)
- **2 taps** → Layer 1 (F13-F20)
- **3+ taps** → Layer 2 (F21-F24)

O tempo entre taps é ~200ms (`TAPPING_TERM`).

**IMPORTANTE**: Não altere a tecla [0,0] no VIA. O Tap Dance é implementado
no firmware. Nas Layers 1 e 2, a tecla [0,0] deve ser `KC_TRNS`.

## Adicionar novas funcionalidades

1. Edite os arquivos em `keymaps/via/`
2. Adicione a feature no `rules.mk` do keymap (ex: `TAP_DANCE_ENABLE = yes`)
3. Compile: `qmk compile -kb ck12 -km via`
4. Flashe: `qmk flash -kb ck12 -km via`
5. Desconecte e reconecte o teclado

Use `qmk clean` antes de compilar para evitar cache antigo.
