// main.cpp - Ядро нашей операционной системы (TUI эскиз)

// На голой системе мы не можем использовать include <iostream> или time.h.
// Все функции для работы с железом мы должны написать сами.

// Указываем компилятору, что эта функция будет вызываться из Ассемблера.
extern "C" void kernel_main();

// Указатель на начало видеопамяти VGA в текстовом режиме (80x25 символов).
// Каждый символ занимает 2 байта: [Символ] [АтрибутЦвета].
// АтрибутЦвета: фон (высокие 4 бита) | передний план (низкие 4 бита).
unsigned short* const VIDEO_MEMORY = (unsigned short*)0xB8000;

// Размеры экрана
const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

// Цвета атрибута (фон | передний план)
const char COLOR_BLACK_ON_WHITE = 0x0F; // Белый текст на черном фоне (по умолчанию)
const char COLOR_BLACK_ON_GRAY  = 0x07; // Серый текст на черном фоне
const char COLOR_WHITE_ON_BLACK = 0xF0; // Черный текст на белом фоне (для аватарки)

// Функция для очистки экрана (заполняем пробелами).
void clear_screen(char attribute = COLOR_BLACK_ON_WHITE) {
    for (int y = 0; y < SCREEN_HEIGHT; ++y) {
        for (int x = 0; x < SCREEN_WIDTH; ++x) {
            const int index = y * SCREEN_WIDTH + x;
            VIDEO_MEMORY[index] = (' ' | (attribute << 8)); // Пробел с цветом
        }
    }
}

// Функция для печати строки в заданную координату.
void print_string(const char* str, char attribute, int x, int y) {
    int index = y * SCREEN_WIDTH + x;
    int i = 0;
    while (str[i] != '\0' && index < SCREEN_WIDTH * SCREEN_HEIGHT) {
        VIDEO_MEMORY[index] = (str[i] | (attribute << 8));
        ++i;
        ++index;
    }
}

// Главная функция ядра.
void kernel_main() {
    // 1. Сначала очистим экран, чтобы сделать его черным.
    clear_screen(COLOR_BLACK_ON_WHITE);

    // 2. Имитируем верхнюю панель: время, дата, день недели (захардкодено).
    // Мы не можем получить реальное время без драйвера RTC, который пишется отдельно.
    print_string("Mon, Jan 01 00:00:00", COLOR_BLACK_ON_WHITE, 55, 0); // В правом верхнем углу

    // 3. Имитируем "Аватарку EGov". На этом этапе это будет просто ASCII-арт.
    // [EGov] в центре.
    print_string("      [EGov]     ", COLOR_WHITE_ON_BLACK, 31, 10);

    // 4. Имитируем Аккаунт человека.
    print_string("       Admin     ", COLOR_BLACK_ON_WHITE, 31, 11);

    // 5. Имитируем надпись "Введите пароль".
    print_string("  Введите пароль: ", COLOR_BLACK_ON_WHITE, 31, 13);
    // Нарисуем "поле ввода" символами (неактивное, пока мы не напишем драйвер клавиатуры).
    print_string("-----------------", COLOR_BLACK_ON_WHITE, 31, 14);

    // 6. Имитируем надпись "Создать аккаунт" (маленькими буковками ниже).
    // В TUI нет маленьких букв, мы просто сделаем текст серым.
    print_string("Создать аккаунт", COLOR_BLACK_ON_GRAY, 33, 16);

    // 7. Основной цикл ядра. Мы должны зациклить процессор,
    // иначе он выполнит этот код и выключится.
    while (true) {
        // Ничего не делаем, просто ждем.
        // Здесь мы будем обрабатывать прерывания клавиатуры в будущем.
    }
}
