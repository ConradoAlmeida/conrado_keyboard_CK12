# Conrado Keyboard (CK12)

Macropad de produtividade com 12 teclas (CK12 = Conrado Keyboard, 12 teclas),
firmware QMK + VIA, rodando em um microcontrolador RP2040 (Raspberry Pi Pico ou
clone), conectado via USB.

## Hardware

- **Placa**: RP2040 (Pico ou clone), USB-C (conveniência do cabo)
- **Matrix físico**: 3 linhas x 4 colunas (12 teclas)
- **Diodos**: opcionais (não usaremos — uso é de tecla única, sem combos)

### Pinagem (definida)

| Função | GPIOs |
|---|---|
| Colunas | 2, 3, 4, 5 |
| Linhas | 6, 7, 8 |

### Diagrama de Conexão

**Matrix 3x4** (cada switch conecta uma linha a uma coluna):

| Tecla | Posição | Linha | Coluna |
|-------|---------|-------|--------|
| K00   | [0,0]   | GP6   | GP2    |
| K01   | [0,1]   | GP6   | GP3    |
| K02   | [0,2]   | GP6   | GP4    |
| K03   | [0,3]   | GP6   | GP5    |
| K10   | [1,0]   | GP7   | GP2    |
| K11   | [1,1]   | GP7   | GP3    |
| K12   | [1,2]   | GP7   | GP4    |
| K13   | [1,3]   | GP7   | GP5    |
| K20   | [2,0]   | GP8   | GP2    |
| K21   | [2,1]   | GP8   | GP3    |
| K22   | [2,2]   | GP8   | GP4    |
| K23   | [2,3]   | GP8   | GP5    |

**Pinout do RP2040 Pico:**

| Pino RP2040 | GPIO | Função no CK12 |
|-------------|------|----------------|
| 4           | GP2  | Coluna 0       |
| 5           | GP3  | Coluna 1       |
| 6           | GP4  | Coluna 2       |
| 7           | GP5  | Coluna 3       |
| 9           | GP6  | Linha 0        |
| 10          | GP7  | Linha 1        |
| 11          | GP8  | Linha 2        |

**Como montar:** Cada switch tem 2 pinos. Um pino vai para a **linha** (GP6/7/8), o outro para a **coluna** (GP2/3/4/5). Quando pressionado, o switch fecha o circuito entre linha e coluna.

## Firmware

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

## Estrutura do Repositório

```
conrado_keyboard/
├── README.md              # Este arquivo
├── AGENTS.md              # Guia para agentes de IA
├── pyproject.toml         # Configuração uv
├── 3d/                    # Arquivos de impressão 3D do case
├── firmware_backup/       # Backups .vil do Vial + cópia de referência do fonte
│   └── keyboards/ck12/    # Ex: bakcup01.vil (layers, macros, tap dance, settings)
└── firmware/
    ├── conrado_keyboard_ck12.layout.json  # Arquivo de definição para o VIA
    └── keyboards/
    ├── conrado_keyboard_ck12.layout.json  # Arquivo de definição para o VIA
    └── keyboards/
        └── ck12/
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

## Troubleshooting

### Teclas não funcionam ou fazem coisas estranhas

1. Use o keymap `debug` para verificar o wiring
2. Verifique se não há curto-circuito entre linhas/colunas
3. Confira se os pinos estão conectados corretamente (pule os pinos GND do Pico)

### VIA/Vial não reconhece o teclado

1. Importe o arquivo `firmware/conrado_keyboard_ck12.layout.json` manualmente no VIA
2. No Vial, verifique se o firmware foi compilado com o fork `vial-kb/vial-qmk` (branch `vial`)
3. Use Chrome ou Edge (Firefox tem problemas com WebHID)
4. Se usar Chrome Flatpak, pode ter problemas de permissão - use Chrome RPM

### VIA diz que não suporta macros

1. Verifique se `DYNAMIC_KEYMAP_MACRO_ENABLE = yes` está no `rules.mk`
2. Recompile e grave o firmware novamente

### Flash apagou minha configuração (layers, macros)

Normal no RP2040: o flash limpa o EEPROM. Restaure o backup `.vil`
(Unlock em `Security` antes de carregar). Da próxima vez, salve o `.vil`
em `firmware_backup/` **antes** de flashar.

### Tecla `User0` (autoclick) não faz nada

1. Confirme que o firmware gravado é o v2+ (com `AUTO_CLICK` no `keymap.c`)
2. Dê Unlock no Vial **antes** de mapear (sem unlock não grava)
3. Use `User0` (o primeiro da aba `User`) na layer certa e aperte a tecla física
4. O firmware v2+ aceita o `User0` tanto do Vial novo (`0x7E40`) quanto do antigo (`0x7E00`)

### Precisa entrar em modo bootloader

1. Desconecte o USB
2. Segure a tecla [0,0] (canto superior esquerdo)
3. Conecte o USB mantendo pressionada
4. Ou use o botão BOOTSEL físico no Pico

## Status

**Projeto concluído e funcionando!** ✅

O CK12 está pronto para uso com todas as funcionalidades básicas implementadas.

## Roadmap Futuro (opcional)

- [x] Mousekey + autoclick toggle (`User0`) + Repeat Key
- [x] Tap-dance (tecla [0,0], dinâmico no Vial)
- [ ] Criar mais keymaps pré-configurados
- [ ] Adicionar suporte a encoder rotativo (se adicionar hardware)
