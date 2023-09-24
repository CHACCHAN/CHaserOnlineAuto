#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MAP 500

// プロトタイプ宣言
char* CheckMapEvent(int MoveCommand, char* param, char* type);

// コマンドによる座標補正を行う
char* CheckMapEvent(int MoveCommand, char* param, char* type)
{
    int* number = NULL;
    char GetReady[] = "GetReady";
    char Action[] = "Action";
    number = (int*)malloc(sizeof(int) * 50); // メモリを動的に確保してコピー用の数値を作成
    if (number == NULL)
    {
        printf("\n> メモリ割り当てエラー\n");
        exit(1);
    }

	if(strcmp(type,"GetReadyMode") == 0) // GetReady
    {
        if(strcmp(param,"command1=gr") == 0)
        {
            number[0] = 0;
            number[1] = 0;
        }
        else if(strcmp(param,"command1=gru") == 0)
        {
            number[0] = 0;
            number[1] = 1;
        }
        else if(strcmp(param,"command1=grl") == 0)
        {
            number[0] = -1;
            number[1] = 0;
        }
        else if(strcmp(param,"command1=grr") == 0)
        {
            number[0] = 1;
            number[1] = 0;
        }
        else if(strcmp(param,"command1=grd") == 0)
        {
            number[0] = 0;
            number[1] = -1;
        }
        else
        {
            printf("\n> 想定外のGetReadyコマンドを検出しました\n> 詳しい内容はErrorHelp.txtでエラーコードを参照してください\n> エラーコード[ME101]\n> 検出コマンド[%s]\n\n",param);
            free(number);
            exit(1);
        }
        return number;
    }
    else if(strcmp(type,"mode") == 0) // Action
    {
        if(strcmp(param,"command2=wu") == 0)
        {
            number[0] = 0;
            number[1] = 1;
        }
        else if(strcmp(param,"command2=wl") == 0)
        {            
            number[0] = -1;
            number[1] = 0;
        }
        else if(strcmp(param,"command2=wr") == 0)
        {           
            number[0] = 1;
            number[1] = 0;
        }
        else if(strcmp(param,"command2=wd") == 0)
        {           
            number[0] = 0;
            number[1] = -1;
        }
        else if(strcmp(param,"command2=pu2wd") == 0)
        {
            number[0] = 0;
            number[1] = -1;
        }
        else if(strcmp(param,"command2=pl2wr") == 0)
        {
            number[0] = 1;
            number[1] = 0;
        }
        else if(strcmp(param,"command2=pr2wl") == 0)
        {
            number[0] = -1;
            number[1] = 0;
        }
        else if(strcmp(param,"command2=pd2wu") == 0)
        {
            number[0] = 0;
            number[1] = 1;
        }
        else if(strcmp(param,"command2=plu2wrd") == 0)
        {
            number[0] = 1;
            number[1] = -1;
        }
        else if(strcmp(param,"command2=pru2wld") == 0)
        {
            number[0] = -1;
            number[1] = -1;
        }
        else if(strcmp(param,"command2=pld2wru") == 0)
        {
            number[0] = 1;
            number[1] = 1;
        }
        else if(strcmp(param,"command2=prd2wlu") == 0)
        {
            number[0] = -1;
            number[1] = 1;
        }
        else if(strcmp(param,"command2=prd0wlu") == 0)
        {
            number[0] = -1;
            number[1] = 1;
        }
        else if(strcmp(param,"command2=pld0wru") == 0)
        {
            number[0] = 1;
            number[1] = 1;
        }
        else if(strcmp(param,"command2=plu0wrd") == 0)
        {
            number[0] = 1;
            number[1] = -1;
        }
        else if(strcmp(param,"command2=pru0wld") == 0)
        {
            number[0] = -1;
            number[1] = -1;
        }
        else if(strcmp(param,"command2=keilu") == 0)
        {
            number[0] = -1;
            number[1] = 2;
        }
        else if(strcmp(param,"command2=keiru") == 0)
        {
            number[0] = 1;
            number[1] = 2;
        }
        else if(strcmp(param,"command2=keild") == 0)
        {
            number[0] = -1;
            number[1] = -2;
        }
        else if(strcmp(param,"command2=keird") == 0)
        {
            number[0] = 1;
            number[1] = -2;
        }
        else if(strcmp(param,"command2=du") == 0)
        {
            number[0] = 0;
            number[1] = 1;
        }
        else if(strcmp(param,"command2=dl") == 0)
        {
            number[0] = -1;
            number[1] = 0;
        }
        else if(strcmp(param,"command2=dr") == 0)
        {
            number[0] = 1;
            number[1] = 0;
        }
        else if(strcmp(param,"command2=dd") == 0)
        {
            number[0] = 0;
            number[1] = -1;
        }
        else if(strcmp(param,"command2=dru") == 0)
        {
            number[0] = 1;
            number[1] = 1;
        }
        else if(strcmp(param,"command2=drd") == 0)
        {
            number[0] = 1;
            number[1] = -1;
        }
        else if(strcmp(param,"command2=dlu") == 0)
        {
            number[0] = -1;
            number[1] = 1;
        }
        else if(strcmp(param,"command2=dld") == 0)
        {
            number[0] = -1;
            number[1] = -1;
        }
        else if(strcmp(param,"command2=w3u") == 0)
        {
            number[0] = 0;
            number[1] = 3;
        }
        else if(strcmp(param,"command2=w3l") == 0)
        {
            number[0] = -3;
            number[1] = 0;
        }
        else if(strcmp(param,"command2=w3r") == 0)
        {
            number[0] = 3;
            number[1] = 0;
        }
        else if(strcmp(param,"command2=w3d") == 0)
        {
            number[0] = 0;
            number[1] = -3;
        }
        else if(strcmp(param,"command2=pr0") == 0)
        {
            number[0] = 0;
            number[1] = 0;
        }
        else if(strcmp(param,"command2=pl0") == 0)
        {
            number[0] = 0;
            number[1] = 0;
        }
        else if(strcmp(param,"command2=pu0") == 0)
        {
            number[0] = 0;
            number[1] = 0;
        }
        else if(strcmp(param,"command2=pd0") == 0)
        {
            number[0] = 0;
            number[1] = 0;
        }
        else if(strcmp(param,"command2=pl3sl") == 0)
        {
            number[0] = 0;
            number[1] = 0;
        }
        else if(strcmp(param,"command2=pr3sr") == 0)
        {
            number[0] = 0;
            number[1] = 0;
        }
        else if(strcmp(param,"command2=pu3su") == 0)
        {
            number[0] = 0;
            number[1] = 0;
        }
        else if(strcmp(param,"command2=pd3sd") == 0)
        {
            number[0] = 0;
            number[1] = 0;
        }
        else if(strcmp(param,"command2=pu3lu") == 0)
        {
            number[0] = 0;
            number[1] = 0;
        }
        else if(strcmp(param,"command2=pd3ld") == 0)
        {
            number[0] = 0;
            number[1] = 0;
        }
        else if(strcmp(param,"command2=pl3ll") == 0)
        {
            number[0] = 0;
            number[1] = 0;
        }
        else if(strcmp(param,"command2=pr3lr") == 0)
        {
            number[0] = 0;
            number[1] = 0;
        }
        else
        {
            printf("\n> 想定外のGetReadyコマンドを検出しました\n> 詳しい内容はErrorHelp.txtでエラーコードを参照してください\n> エラーコード[ME102]\n> 検出コマンド[%s]\n\n",param);
            free(number);
            exit(1);
        }
        return number;
    }
}