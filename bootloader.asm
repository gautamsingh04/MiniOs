[BITS 16]
[ORG 0x7C00]

start:
    ; Clear screen
    mov ah, 0x0E
    mov al, 'B'
    int 0x10
    mov al, 'L'
    int 0x10
    mov al, '!'
    int 0x10

    ; Load shell 
    mov bx, 0x0000
    mov es, bx
    mov bx, 0x0000     ; Destination offset
    mov ah, 0x02
    mov al, 3          ; Number of sectors
    mov ch, 0
    mov cl, 2          ; Start at sector 2
    mov dh, 0
    mov dl, 0x80
    int 0x13
    jc error

    ; Jump to shell at 0x1000:0000
    jmp 0x1000:0000

error:
    mov ah, 0x0E
    mov al, 'E'
    int 0x10
    jmp $
times 510 - ($ - $$) db 0
dw 0xAA55
