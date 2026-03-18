# Makefile для сборки нашей ОС

# Инструменты (на MacBook мы будем использовать кросс-компиляторы)
CC = i686-elf-gcc
AS = nasm
LD = i686-elf-ld

# Параметры сборки
CFLAGS = -m32 -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
LDFLAGS = -T linker.ld

# Список файлов
OBJ = boot.o main.o

# Главная цель: создание файла ядра
all: myos.bin

# Собираем загрузчик из ассемблера
boot.o: boot.asm
	$(AS) -f elf32 boot.asm -o boot.o

# Компилируем C++ код ядра
main.o: main.cpp
	$(CC) -c main.cpp -o main.o $(CFLAGS)

# Склеиваем всё вместе в один бинарный файл
myos.bin: $(OBJ)
	$(LD) $(LDFLAGS) -o myos.bin $(OBJ)

# Очистка проекта
clean:
	rm -rf *.o myos.bin
