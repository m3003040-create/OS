; syntax: nasm
; boot.asm - Улучшенный загрузчик для нашей ОС
bits 32                         ; Работаем в 32-битном режиме x86

section .multiboot              ; Специальная секция для Multiboot-заголовка
    align 4
    dd 0x1BADB002               ; Магическое число (заголовок Multiboot)
    dd 0x03                     ; Флаги: выравнивание страниц + информация о памяти
    dd -(0x1BADB002 + 0x03)    ; Контрольная сумма (Magic + Flags + Checksum = 0)

section .bss
align 16
stack_bottom:
    resb 16384                  ; Резервируем 16 Килобайт для стека
stack_top:

section .text
global _start
extern kernel_main              ; Ссылка на вашу функцию в main.cpp

_start:
    ; 1. Устанавливаем указатель стека (stack pointer)
    ; Это нужно, чтобы C++ мог вызывать функции и использовать переменные
    mov esp, stack_top

    ; 2. Передаем управление в ваш C++ код
    call kernel_main

    ; 3. Если ядро каким-то образом завершится, останавливаем процессор
    cli                         ; Отключаем прерывания
.hang:
    hlt                         ; Останавливаем ядро (бесконечное ожидание)
    jmp .hang
