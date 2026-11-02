# Conrado Keyboard (CK12)

Macropad de produtividade com 12 teclas (CK12 = Conrado Keyboard, 12 teclas),
firmware QMK + VIA, rodando em um microcontrolador RP2040 (Raspberry Pi Pico ou
clone), conectado via USB.

## Início rápido

```sh
# copiar o teclado para o QMK e gravar
cp -r firmware/keyboards/ck12 ~/qmk_firmware/keyboards/
cd ~/qmk_firmware
qmk compile -kb ck12 -km via
qmk flash  -kb ck12 -km via
```

Setup completo do QMK/Vial, keymaps e troubleshooting estão nos docs.

## Documentação

| Documento | Conteúdo |
|---|---|
| [Hardware](docs/HARDWARE.md) | RP2040, matrix 3x4, pinagem e diagrama |
| [Firmware e build](docs/FIRMWARE.md) | QMK + VIA/Vial, bootloader, features, build e ambiente |
| [Keymaps e VIA/Vial](docs/KEYMAPS.md) | Keymap `via`, configuração ao vivo, alternativos e backup |
| [Troubleshooting](docs/TROUBLESHOOTING.md) | Wiring, VIA/Vial, macros, flash e bootloader |
| [Regras para agentes](AGENTS.md) | Contexto técnico, convenções e fluxo de firmware |

## Status

**Projeto concluído e funcionando!** ✅

O CK12 está pronto para uso com todas as funcionalidades básicas implementadas.

## Roadmap Futuro (opcional)

- [x] Mousekey + autoclick toggle (`User0`) + Repeat Key
- [x] Tap-dance (tecla [0,0], dinâmico no Vial)
- [ ] Criar mais keymaps pré-configurados
- [ ] Adicionar suporte a encoder rotativo (se adicionar hardware)
