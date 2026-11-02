# Troubleshooting

[← Voltar ao README](../README.md) · [Firmware e build](FIRMWARE.md) · [Keymaps](KEYMAPS.md)

> Sintomas e correções de wiring, VIA/Vial, macros, flash e bootloader.

---

## Teclas não funcionam ou fazem coisas estranhas

1. Use o keymap `debug` para verificar o wiring
2. Verifique se não há curto-circuito entre linhas/colunas
3. Confira se os pinos estão conectados corretamente (pule os pinos GND do Pico)

## VIA/Vial não reconhece o teclado

1. Importe o arquivo `firmware/conrado_keyboard_ck12.layout.json` manualmente no VIA
2. No Vial, verifique se o firmware foi compilado com o fork `vial-kb/vial-qmk` (branch `vial`)
3. Use Chrome ou Edge (Firefox tem problemas com WebHID)
4. Se usar Chrome Flatpak, pode ter problemas de permissão - use Chrome RPM

## VIA diz que não suporta macros

1. Verifique se `DYNAMIC_KEYMAP_MACRO_ENABLE = yes` está no `rules.mk`
2. Recompile e grave o firmware novamente

## Flash apagou minha configuração (layers, macros)

Normal no RP2040: o flash limpa o EEPROM. Restaure o backup `.vil`
(Unlock em `Security` antes de carregar). Da próxima vez, salve o `.vil`
em `firmware_backup/` **antes** de flashar.

## Tecla `User0` (autoclick) não faz nada

1. Confirme que o firmware gravado é o v2+ (com `AUTO_CLICK` no `keymap.c`)
2. Dê Unlock no Vial **antes** de mapear (sem unlock não grava)
3. Use `User0` (o primeiro da aba `User`) na layer certa e aperte a tecla física
4. O firmware v2+ aceita o `User0` tanto do Vial novo (`0x7E40`) quanto do antigo (`0x7E00`)

## Precisa entrar em modo bootloader

1. Desconecte o USB
2. Segure a tecla [0,0] (canto superior esquerdo)
3. Conecte o USB mantendo pressionada
4. Ou use o botão BOOTSEL físico no Pico
