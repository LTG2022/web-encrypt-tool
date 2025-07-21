#include <stdio.h>
#include <stdint.h>
#include <string.h>

const uint8_t key[6] = {7, 2, 9, 4, 6, 3};

void encrypt_code(const char *input_code, char *output_code)
{
    uint8_t temp[6];
    uint8_t reversed[6];
    uint8_t encrypted[6];
    int i;

    for(i = 0; i < 6; i++) {
        uint8_t digit = input_code[i] - '0';
        temp[i] = (digit + (i + 1)) % 10;
    }
    for(i = 0; i < 6; i++) {
        reversed[i] = temp[5 - i];
    }
    for(i = 0; i < 6; i++) {
        encrypted[i] = (reversed[i] ^ key[i]) % 10; // 保证是0~9
    }
    for(i = 0; i < 6; i++) {
        output_code[i] = encrypted[i] + '0';
    }
    output_code[6] = '\0';
}

int main()
{
    char input_code[32];
    char output_code[7];

    while(1) {
        printf("Please enter a 6-digit number (or type 'exit' to quit): ");
        if (fgets(input_code, sizeof(input_code), stdin) == NULL) {
            printf("Input error!\n");
            continue;
        }

        // 去除换行符
        size_t len = strlen(input_code);
        if (len > 0 && input_code[len - 1] == '\n') {
            input_code[len - 1] = '\0';
        }

        // 允许输入exit退出
        if(strcmp(input_code, "exit") == 0) {
            printf("Program exited.\n");
            break;
        }

        if(strlen(input_code) != 6) {
            printf("Input must be 6 digits!\n\n");
            continue;
        }
        int valid = 1;
        for(int i=0; i<6; i++) {
            if(input_code[i] < '0' || input_code[i] > '9') {
                valid = 0;
                break;
            }
        }
        if(!valid) {
            printf("Input must be 6 digits!\n\n");
            continue;
        }

        encrypt_code(input_code, output_code);
        printf("Encrypted 6-digit number: %s\n\n", output_code);
    }
    return 0;
}