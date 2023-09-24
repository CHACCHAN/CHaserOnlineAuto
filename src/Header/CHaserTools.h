#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define MAX_ARGS 10

int SelectID(int,int,int);
int SelectID_some(int,int,...);
char* RemoveSubString(const char* input, const char* substring);

// ID自動選択処理
int SelectID(int data, int start, int end)
{
	int temp;
	if(start > end)
	{
		temp = start;
		start = end;
		end = temp;
	}
	while(start <= end)
	{
		if(data == start)
		{
			return start;
		}
		else
		{
			start++;
		}
	}
}

// ID指定選択処理
int SelectID_some(int data,int select, ... )
{
	va_list  ap; // 可変引数変数宣言
	va_start (ap,select); // 可変引数の個数
	int i = 0;
	int number;
	int ID[MAX_ARGS];

	for(i = 0; (i < select) && (i < MAX_ARGS); i++)
	{
		ID[i] = va_arg(ap,int);
	}
	va_end(ap);

	for(i = 0; (i < select) && (i < MAX_ARGS); i++)
	{
		if(data == ID[i])
		{
			number = ID[i];
			return number;
		}
	}
}

// 特定の文字列を除去する
char* RemoveSubString(const char* input, const char* substring) {
    size_t input_length = strlen(input);
    size_t substring_length = strlen(substring);

    char* result = (char*)malloc(input_length + 1);
    if (!result) {
        printf("\n> メモリ割り当てエラー\n");
        return NULL;
    }

    size_t j = 0;
	size_t i = 0;

    for (i = 0; i < input_length; i++) {
        if (i <= input_length - substring_length && strncmp(input + i, substring, substring_length) == 0) {
            i += substring_length - 1;
        } else {
            result[j++] = input[i];
        }
    }

    result[j] = '\0';
    return result;
}