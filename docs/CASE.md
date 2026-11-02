# Case 3D — SolidWorks

O case do CK12 é a **fonte da verdade** e fica no NAS, no share `documentos`.
O firmware e a documentação elétrica ficam neste repositório; os binários do
CAD **não são versionados aqui**.

## Fonte

```text
\\192.168.0.150\documentos\Projetos_3D\conrado_keyboard_ck12
```

No Linux (montagem gvfs):

```text
/run/user/1000/gvfs/smb-share:server=homelab.local,share=documentos/Projetos_3D/conrado_keyboard_ck12
```

## Arquivos

| Arquivo | Tipo | Papel |
|---|---|---|
| `case.SLDPRT` | SolidWorks | **Fonte principal** (~2,1 MB) |
| `case.STEP` | STEP | Export de intercâmbio/impressão (~1,0 MB) |

Total: ~3,0 MB.

## Como usar

- **Editar:** abra `case.SLDPRT` no SolidWorks (VM Windows) e salve de volta no
  NAS.
- **Imprimir/visualizar:** importe `case.STEP` no slicer (OrcaSlicer,
  PrusaSlicer) ou no FreeCAD. O STEP é export; o `.SLDPRT` é a fonte.
- **Conferir o hardware:** matrix, pinagem e teclas estão em
  [HARDWARE.md](HARDWARE.md); keymaps em [KEYMAPS.md](KEYMAPS.md).

## Versionamento

Os arquivos `.SLDPRT`/`.STEP` **não entram no Git**. Se for publicar uma versão
do case, prefira anexar o STEP a um release do GitHub em vez de commitar o
binário.
