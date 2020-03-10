  [ORG 0000h]
  [BITS 16]

entry:
  mov ax, bx
  mov al, bl
  mov bx, 9999
  cli
  hlt
  mov al, dl
  mov ax, [1]
  push ax
  pop ax
