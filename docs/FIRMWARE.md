# Firmware e build

[← Voltar ao README](../README.md) · [Hardware](HARDWARE.md) · [Keymaps](KEYMAPS.md) · [Troubleshooting](TROUBLESHOOTING.md)

> QMK + VIA/Vial, bootloader, features, estrutura, compilação e ambiente.

---

## Firmware QMK

- **QMK (fork Vial)** com **VIA/Vial habilitado** (`VIA_ENABLE = yes`, `VIAL_ENABLE = yes`)
  para remapear ao vivo via usevia.app ou vial.rocks, sem recompilar.
- Compilado/gravado via QMK CLI (`qmk compile` / `qmk flash`). O `~/qmk_firmware` usa o
  fork `vial-kb/vial-qmk` (branch `vial`).
- **Bootmagic** configurado na tecla [0,0] (canto superior esquerdo) para entrar em modo bootloader.

### Entrar em modo bootloader

Para gravar firmware, o Pico precisa entrar em modo bootloader:

1. Desconecte o USB
2. Segure a tecla **[0,0]** (primeira tecla, canto superior esquerdo)
3. Conecte o USB mantendo a tecla pressionada
4. O Pico aparece como pendrive `RPI-RP2`
5. Grave o firmware arrastando o arquivo `.uf2` ou usando `qmk flash`

## Funcionalidades

### Firmware Atual (v2)

- **Keymap padrão** com 3 layers (0, 1, 2) + 8 layers dinâmicos no Vial
- **VIA/Vial habilitado** para remapear tudo ao vivo
- **Suporte a macros** habilitado
- **Mousekey habilitado** (`mousekey: true` no `keyboard.json`): click e movimento de mouse via teclado (ex: `Mouse 1`)
- **Autoclick de duplo-click em 3 pausas** no keymap `via` (aba `User` no Vial):
  `User0` = duplo-click a cada 250ms, `User1` = a cada 500ms, `User2` = a cada 1s
  (gap de ~40ms entre os 2 clicks do duplo, fixo).
  Aperta 1x liga (com 1 click imediato de feedback), mesma tecla de novo desliga,
  outra tecla de pausa troca sem desligar. Compatível com Vial novo e antigo
- **Repeat Key habilitado** (`REPEAT_KEY_ENABLE = yes`): `QK_REP` / `QK_AREP` (aba Quantum / Alt Repeat Key no Vial). Nota: Repeat repete 1x por toque, não entra em loop — para click contínuo use o autoclick (`User0`)
- **Tap Dance** na tecla [0,0] (dinâmico no Vial): 1 toque → Layer 0, 2 toques → Layer 1, segurar → Layer 2

### Fluxo de uso

1. **Backup da config atual**: no Vial, Unlock (`[0,0]` + `[2,3]`) → menu `File` → salvar `.vil` em `firmware_backup/` (**o flash apaga o EEPROM**)
2. **Compilar firmware**: `qmk compile -kb ck12 -km via`
3. **Gravar no Pico**: entrar em bootloader (`[0,0]` + conectar) → `qmk flash` ou arrastar o `.uf2` para o pendrive `RPI-RP2`
4. **Restaurar backup**: Unlock → `File` → carregar o `.vil` salvo
5. **Configurar no dia a dia**: abrir https://usevia.app (VIA) ou https://vial.rocks (Vial) e remapear tudo

### O que dá pra fazer via VIA/Vial

- Mudar qualquer tecla
- Criar macros (suporte habilitado)
- Adicionar layers
- Configurar modificadores
- No **Vial**: configurar Tap Dance, Combos, Key Overrides e QMK Settings visualmente
- Tudo ao vivo, sem recompilar

### Arquivo de Definição VIA/Vial

Para usar o VIA, importe o arquivo de definição:
```
firmware/conrado_keyboard_ck12.layout.json
```

Este arquivo contém o layout do teclado para o VIA reconhecer. O Vial usa a definição
`firmware/keyboards/ck12/keymaps/via/vial.json` (carregada automaticamente pelo firmware).

### Backup e restore da configuração (Vial)

Toda a configuração ao vivo (layers, macros, tap dance, combos, overrides, QMK Settings)
fica no EEPROM e é **apagada a cada flash**. Os backups `.vil` ficam em:
```
firmware_backup/keyboards/ck12/
```

- **Salvar**: teclado conectado → aba `Security` → Unlock (segurar `[0,0]` + `[2,3]`) → menu `File` → salvar `.vil`
- **Restaurar**: mesmo Unlock → menu `File` → carregar o `.vil`

⚠️ Não altere o `VIAL_KEYBOARD_UID` no `keymaps/via/config.h` sem necessidade: o backup só restaura se o UID for o mesmo do firmware gravado.

## Estrutura do Repositório

```
conrado_keyboard/
├── README.md              # Índice e visão geral
├── AGENTS.md              # Guia para agentes de IA
├── pyproject.toml         # Configuração uv
├── 3d/                    # Arquivos de impressão 3D do case
├── firmware_backup/       # Backups .vil do Vial + cópia de referência do fonte
│   └── keyboards/ck12/    # Ex.: bakcup01.vil (layers, macros, tap dance, settings)
└── firmware/
    ├── conrado_keyboard_ck12.layout.json  # Definição para o VIA
    └── keyboards/ck12/
        ├── keyboard.json    # Configuração do hardware
        ├── rules.mk         # Features habilitadas
        ├── readme.md        # Documentação do firmware
        └── keymaps/
            ├── default/     # Keymap padrão (Ctrl+Z, etc.)
            ├── via/         # Keymap com VIA + Vial (inclui vial.json, config.h)
            ├── debug/       # Keymap para testar wiring (1-9, 0, A, B)
            ├── produtividade/  # Keymap de produtividade
            └── gaming-terraria/ # Keymap para Terraria
```

## Compilar e Gravar

### Firmware Principal (VIA + Macros)

```sh
qmk compile -kb ck12 -km via
qmk flash  -kb ck12 -km via
```

### Firmware de Debug (testar wiring)

```sh
qmk compile -kb ck12 -km debug
qmk flash  -kb ck12 -km debug
```

### Keymaps Alternativos

```sh
qmk compile -kb ck12 -km produtividade
qmk compile -kb ck12 -km gaming-terraria
```

## Ambiente de Desenvolvimento

- **OS**: Linux (Fedora)
- **Editor**: VSCode + clangd para edição
- **Build**: QMK CLI via uv (não PlatformIO)
- **Compilador ARM**: `arm-none-eabi-gcc-cs` + `arm-none-eabi-newlib`

### Instalação

```sh
# Instalar dependências do sistema
sudo dnf install arm-none-eabi-gcc-cs arm-none-eabi-newlib

# Instalar QMK CLI via uv
uv init
uv add qmk

# Configurar QMK (usar o fork do Vial, branch `vial`)
uv run qmk setup -b vial -H ~/qmk_firmware 2>/dev/null || true
cd ~/qmk_firmware && git remote add vial https://github.com/vial-kb/vial-qmk.git
cd ~/qmk_firmware && git fetch vial vial && git checkout -b vial vial/vial
cd ~/qmk_firmware && git submodule update --init --recursive

# Copiar firmware para qmk_firmware
cp -r firmware/keyboards/ck12 ~/qmk_firmware/keyboards/

# Compilar
cd ~/qmk_firmware
uv run qmk compile -kb ck12 -km via
```
