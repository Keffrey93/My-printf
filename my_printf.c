#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>

int my_printf(const char *var2, ...);

int main() {
    // Appels à my_printf() avec différents types de formats
    my_printf("Hello, world!\n");
    my_printf("The value of pi is approximately %.2f\n", 3.14159);
    my_printf("The number %d in octal is %o\n", 25, 25);
    my_printf("The number %d in hexadecimal is %x\n", 255, 255);
    my_printf("A character: %c\n", 'A');
    my_printf("A string: %s\n", "Hello from my_printf!");

    return 0;
}

int my_printf(const char *var2, ...){
    va_list my_lord;
    va_start(my_lord, var2);

    int bios = 0;

    while(*var2){
        if(*var2 == '%'){
            var2++;
            switch(*var2){
                case 'd': {
                    int bios_arg = va_arg(my_lord, int);
                    if (bios_arg < 0) {
                        bios += write(1, "-", 1);
                        bios_arg = -bios_arg;
                    } else if (bios_arg == 0) {
                        bios += write(1, "0", 1);
                        break;
                    }
                    char buffer[32];
                    char *hilmah = buffer + 31;
                    *hilmah = '\0';
                    while (bios_arg > 0) {
                        *--hilmah = bios_arg % 10 + '0';
                        bios_arg /= 10;
                    }
                    bios += write(1, hilmah, strlen(hilmah));
                    break;
                }
                case 'o': {
                    unsigned int keff = va_arg(my_lord, unsigned int);
                    char buffer[32];
                    char *hilmah = buffer + 31;
                    *hilmah = '\0';
                    while(keff > 0){
                        *--hilmah = keff % 8 + '0';
                        keff /= 8;
                    }
                    bios += write(1, hilmah, strlen(hilmah));
                    break;
                }
                case 'u': {
                    unsigned int value = va_arg(my_lord, unsigned int);
                    char buffer[32];
                    char *hilmah = buffer + 31;
                    *hilmah = '\0';
                    while (value > 0) {
                        *--hilmah = value % 10 + '0';
                        value /= 10;
                    }
                    bios += write(1, hilmah, strlen(hilmah));
                    break;
                }
                case 'x': {
                    unsigned int input = va_arg(my_lord, unsigned int);
                    char buffer[32];
                    char *hilmah = buffer + 31;
                    *hilmah = '\0';
                    while (input > 0) {
                        char c = input % 16;
                        if (c < 10) {
                            *--hilmah = c + '0';
                        } else {
                            *--hilmah = c - 10 + 'A';
                        }
                        input /= 16;
                    }
                    bios += write(1, hilmah, strlen(hilmah));
                    break;
                }
                case 'c': {
                    char value = va_arg(my_lord, int);
                    bios += write(1, &value, 1);
                    break;
                }
                case 's': {
                    const char *value = va_arg(my_lord, void*);
                    if (value == NULL){
                        bios += write(1, "(null)", 6);
                    } else {
                        size_t len = 0;
                        while (value[len] != '\0') {
                            len++;
                        }
                        bios += write(1, value, len);
                    }
                    break;
                }
                case 'p': {
                    void *value_brian = va_arg(my_lord, void*);
                    unsigned long long arr = (unsigned long long)value_brian;
                    char buffer[32];
                    char *hilmah = buffer + 31;
                    *hilmah = '\0';
                    while (arr > 0) {
                        char c = arr % 16;
                        if (c < 10) {
                            *--hilmah = c + '0';
                        } else {
                        *--hilmah = c - 10 + 'a';
                        }
                        arr /= 16;
                    }
                    bios += write(1, "0x", 2);
                    bios += write(1, hilmah, strlen(hilmah));
                    break;
                }
            }
        }else{
            bios += write(1, var2, 1);
        }
        var2++;
    }

    va_end(my_lord);
    return bios;
}