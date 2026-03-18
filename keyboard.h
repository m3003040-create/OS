#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "io.h"

// Скан-коды некоторых клавиш
#define KEY_ENTER 0x1C
#define KEY_BACKSPACE 0x0E

// Массив для перевода скан-кодов в символы (упрощенный)
unsigned char kbd_map[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '
};

// Функция чтения символа с клавиатуры (ожидание нажатия)
char get_char() {
    unsigned char scancode;
    while (!(inb(0x64) & 1)); // Ждем, пока в буфере появится данные
    scancode = inb(0x60);     // Читаем код клавиши
    
    // Если код больше 128, это значит клавиша отпущена — игнорируем
    if (scancode & 0x80) return 0;
    
    return kbd_map[scancode];
}

#endif
