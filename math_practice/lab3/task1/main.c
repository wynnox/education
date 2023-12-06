#include <stdio.h>

// Функция для перевода числа из десятичной системы в систему с основанием 2^r
void decimalToBaseR(int decimal, int r) {
    int result = 0;
    int baseR = 1;

    // Маска для извлечения младшего бита
    int mask = 1;

    while (decimal) {
        // Получаем младший бит числа
        int current_bit = decimal & mask;

        // Умножаем текущий бит на текущую степень основания r
        int weighted_bit = current_bit << (r - 1);

        // Добавляем в результат
        result |= weighted_bit;

        // Сдвигаем число вправо на 1 (деление на 2)
        decimal >>= 1;

        // Увеличиваем текущую степень основания r
        baseR <<= r;
    }

    // Результат хранится в переменной result
    // Теперь вы можете использовать result или напечатать его
    printf("Результат в системе с основанием %d: %d\n", 1 << r, result);
}

int main() {
    int decimalNumber = 11; // Замените это на ваше десятичное число

    // Продемонстрируем работу функции для разных значений r
    for (int r = 1; r <= 5; ++r) {
        decimalToBaseR(decimalNumber, r);
    }

    return 0;
}
