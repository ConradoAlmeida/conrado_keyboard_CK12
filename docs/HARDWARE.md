# Hardware

[← Voltar ao README](../README.md) · [Firmware e build](FIRMWARE.md) · [Keymaps](KEYMAPS.md)

> Placa RP2040, matrix 3x4, pinagem e diagrama de ligação.

---

## Placa e matrix

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
