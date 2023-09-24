#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 0
#define MAX_LENGTH 100

// CHaserOnlineAutoのバージョン
const char version[] = "CHaserOnlineAuto-v2.1";

// 設定情報
char ProxyAddress[MAX_LENGTH];
char ServerAddress[MAX_LENGTH];
char fname[] = "Config/userconfig.txt";
char fname2[] = "Config/addressconfig.txt";
char Checkflag[] = "src/Cash/UserCheckFlag.txt";

// プロトタイプ宣言
void NormalRun(char*, char*, char*);
void LoopRun(char*, char*, char*);

int main()
{
    int  i = 0;
    int  j = 0;
    int  line_count = 0;
    char SelectStr[MAX_LENGTH];
    int  SelectNumber;
    char line[MAX_LENGTH];
    char username[6][MAX_LENGTH];
    char password[6][MAX_LENGTH];
    int  length;
    FILE *file;

    reset:
    // バージョン表示
    printf("> %s\n",version);

    // ファイルを読み込みモードで開く
    file = fopen(fname, "r");
    if (file == NULL) {
        printf("Can not open the [%s]\n",fname);
        return 1;
    }
    
    j = 0;
    // ユーザー情報を読み込む
    while(j < 5)
    {
        for(i = 1; i <= 20; i++)
        {
            if(i == 2 || i == 6 || i == 10 || i == 14 || i == 18)
            {
                fgets(line, sizeof(line), file);
                sscanf(line,"\"%[^\"]\"",username[j]);
            }
            else if(i == 4 || i == 8 || i == 12 || i == 16 || i == 20)
            {
                fgets(line, sizeof(line), file);
                sscanf(line,"\"%[^\"]\"",password[j]);
                j++;
            }
            else
            {
                fgets(line, sizeof(line), file);
            }
        }
    }
    fclose(file);

    // ファイルを読み込みモードで開く
    file = fopen(fname2, "r");
    if (file == NULL) {
        printf("Can not open the [%s]\n",fname2);
        return 1;
    }

    // アクセス情報を読み込む
    while (fgets(line, MAX_LENGTH, file) != NULL)
    {
        line_count++;
        length = strlen(line);
        if (line_count == 2)
        {
            for (i = 0, j = 0; i < length; i++)
            {
                if (line[i] != '"')
                {
                    ServerAddress[j++] = line[i];
                }
            }

            if (ServerAddress[j - 1] == '\n')
            {
                ServerAddress[j - 1] = '\0';
            }
        }
        else if (line_count == 4)
        {
            length = strlen(line);
            for (i = 0, j = 0; i < length; i++)
            {
                if (line[i] != '"')
                {
                    ProxyAddress[j++] = line[i];
                }
            }

            if (ProxyAddress[j - 1] == '\n')
            {
                ProxyAddress[j - 1] = '\0';
            }
        }
    }
    fclose(file);

    // 登録済みアカウントの一覧を表示する
    printf("\n> 登録済みアカウント\n");
    for (i = 0; i < 5; i++)
    {
        printf("[%d]ACCOUNT : %s\n", i+1 , username[i]);
    }

    // アカウントの選択
    j = 0;
    while(j < 1)
    {
        printf("\n> 使用するアカウントを番号で選択してください\n=");
        fgets(SelectStr,MAX_LENGTH,stdin);
        switch(atoi(SelectStr))
        {
            case 1:
                SelectNumber = 0;
                j++;
                break;
            case 2:
                SelectNumber = 1;
                j++;
                break;
            case 3:
                SelectNumber = 2;
                j++;
                break;
            case 4:
                SelectNumber = 3;
                j++;
                break;
            case 5:
                SelectNumber = 4;
                j++;
                break;
            default:
                printf("\n> エラー\n> 1～5から選んでください\n");
        }
    }
    
    // 処理パターン選択
    while(TRUE)
    {
        printf("\n> 実行方法を選択してください\n> 通常(T) 連続(L)\n=");
        fgets(SelectStr,MAX_LENGTH,stdin);
        strtok(SelectStr,"\n");
        if(strcmp(SelectStr,"T") == 0 || strcmp(SelectStr,"t") == 0) // 通常処理動作
        {
            // チェックフラグファイルを初期化する
            file = fopen(Checkflag,"w");
            fprintf(file,"Unchecked");
            fclose(file);
            // 通常実行をする関数を呼び出す
            NormalRun(username[SelectNumber],password[SelectNumber],Checkflag);
            while(TRUE)
            {
                printf("\n> 終了しますか？(Y or N)\n=");
                fgets(SelectStr,MAX_LENGTH,stdin);
                strtok(SelectStr,"\n");
                if(strcmp(SelectStr,"Y") == 0 || strcmp(SelectStr,"y") == 0)
                {  
                    return 0;
                }
                else if(strcmp(SelectStr,"N") == 0 || strcmp(SelectStr,"n") == 0)
                {
                    goto reset;
                }
                else
                {
                    printf("\n> エラー\n> 入力に誤字があります\n");
                }
            }
            
        }
        else if(strcmp(SelectStr,"L") == 0 || strcmp(SelectStr,"l") == 0) // 連続処理動作
        {
            // チェックフラグファイルを初期化する
            file = fopen(Checkflag,"w");
            fprintf(file,"Unchecked");
            fclose(file);
            // 連続実行をする関数を呼び出す
            LoopRun(username[SelectNumber],password[SelectNumber],Checkflag);
            while(TRUE)
            {
                printf("\n> 終了しますか？(Y or N)\n=");
                fgets(SelectStr,MAX_LENGTH,stdin);
                strtok(SelectStr,"\n");
                if(strcmp(SelectStr,"Y") == 0 || strcmp(SelectStr,"y") == 0)
                {  
                    return 0;
                }
                else if(strcmp(SelectStr,"N") == 0 || strcmp(SelectStr,"n") == 0)
                {
                    goto reset;
                }
                else
                {
                    printf("\n> エラー\n> 入力に誤字があります\n");
                }
            }
        }
        else
        {
            printf("\n> エラー\n> 入力に誤字があります\n");
        }
    }
    
    return 0;
}

// 通常実行
void NormalRun(char *username, char *password, char *Checkflag)
{
    FILE *file = NULL;
    char fmessage[10];
    int  i;
    int  flag = FALSE;
    char RoomNumber[MAX_LENGTH];
    char RunCommand[MAX_LENGTH];
    char Proxy[MAX_LENGTH];
    char x[MAX_LENGTH];

    // ルーム番号入力
    printf("\n> ルーム番号を指定してください\n=");
    fgets(RoomNumber,MAX_LENGTH,stdin);
    strtok(RoomNumber,"\n");

    // プロキシサーバー
    while(TRUE)
    {
        printf("\n> プロキシサーバーを利用しますか？(Y or N)\n=");
        fgets(Proxy,MAX_LENGTH,stdin);
        strtok(Proxy,"\n");
        if(strcmp(Proxy,"Y") == 0 || strcmp(Proxy,"y") == 0)
        {
            strcpy(x,ProxyAddress);
            break;
        }
        else if(strcmp(Proxy,"N") == 0 || strcmp(Proxy,"n") == 0)
        {
            strcmp(x,"");
            break;
        }
        else
        {
            printf("\n> エラー\n> 入力に誤字があります\n");
        }
    }
    
    // 処理実行
    while(flag == FALSE)
    {
        system("cd src;rm a.out");
        system("cd src;gcc Base.c Command.c GetReady.c Action.c");
        if(strcmp(Proxy,"Y") == 0 || strcmp(Proxy,"y") == 0)
        {
            sprintf(RunCommand,"cd src;./a.out %s -u %s -p %s -r %d -x %s",ServerAddress,username,password,atoi(RoomNumber),x);
            system(RunCommand);
        }
        else if(strcmp(Proxy,"N") == 0 || strcmp(Proxy,"n") == 0)
        {
            sprintf(RunCommand,"cd src;./a.out %s -u %s -p %s -r %d",ServerAddress,username,password,atoi(RoomNumber));
            system(RunCommand);
        }

        // User CheckNGの再試行
        file = fopen(Checkflag,"r");
        fscanf(file,"%s",&fmessage);
        fclose(file);  

        if(strcmp(fmessage,"CheckComplete") == 0)
        {
            flag = TRUE;
        }
        else if(strcmp(fmessage,"Unchecked") == 0)
        {
            printf("\n\n> コンパイルエラーが発生しました\n> 詳しい内容はErrorHelp.txtでエラーコードを参照してください\n> エラーコード[ME001]\n");
            exit(1);
        }
        else
        {
            printf("\n\n> エラー\n> User CheckNGなので、再試行します。\n");
        }

        // 待機
        printf("\n");
        for(i = 10; (i >= 1 && flag == FALSE); i--)
        {
            printf("> [待機中] しばらくお待ちください...あと%d秒..\n",i);
            sleep(1);
        }
        printf("\n");
    }
    
    
    printf("\n\n> 処理が終了しました\n");
}

//連続実行
void LoopRun(char* username, char* password,char* Checkflag)
{
    FILE *file = NULL;
    char fmessage[10];
    int  i;
    int  temp;
    int  StartRoomNumber;
    int  EndRoomNumber;
    char StartRoomNumberCash[MAX_LENGTH];
    char EndRoomNumberCash[MAX_LENGTH];
    int  flag = FALSE;
    char RunCommand[MAX_LENGTH];
    char Proxy[MAX_LENGTH];
    char x[MAX_LENGTH];

    // ルーム番号選択
    printf("\n> [X]番 ～ [Y]番まで実行");
    printf("\n> [X] = ");
    fgets(StartRoomNumberCash,MAX_LENGTH,stdin);
    strtok(StartRoomNumberCash,"\n");

    printf("\n [%s]番 ～ [Y]番まで実行",StartRoomNumberCash);
    printf("\n> [Y] = ");
    fgets(EndRoomNumberCash,MAX_LENGTH,stdin);
    strtok(EndRoomNumberCash,"\n");

    StartRoomNumber = atoi(StartRoomNumberCash);
    EndRoomNumber = atoi(EndRoomNumberCash);

    if(StartRoomNumber > EndRoomNumber)
    {
        temp = EndRoomNumber;
        EndRoomNumber = StartRoomNumber;
        StartRoomNumber = temp;
    }


    // プロキシサーバー
    while(TRUE)
    {
        printf("\n> プロキシサーバーを利用しますか？(Y or N)\n=");
        fgets(Proxy,MAX_LENGTH,stdin);
        strtok(Proxy,"\n");
        if(strcmp(Proxy,"Y") == 0 || strcmp(Proxy,"y") == 0)
        {
            strcpy(x,ProxyAddress);
            break;
        }
        else if(strcmp(Proxy,"N") == 0 || strcmp(Proxy,"n") == 0)
        {
            strcmp(x,"");
            break;
        }
        else
        {
            printf("\n> エラー\n> 入力に誤字があります\n");
        }
    }
    
    // 処理実行
    system("cd src;rm a.out");
    system("cd src;gcc Base.c Command.c GetReady.c Action.c");
    while(flag == FALSE)
    {
        if(strcmp(Proxy,"Y") == 0 || strcmp(Proxy,"y") == 0)
        {
            sprintf(RunCommand,"cd src;./a.out %s -u %s -p %s -r %d -x %s",ServerAddress,username,password,StartRoomNumber,x);
            system(RunCommand);
            StartRoomNumber++;
        }
        else if(strcmp(Proxy,"N") == 0 || strcmp(Proxy,"n") == 0)
        {
            sprintf(RunCommand,"cd src;./a.out %s -u %s -p %s -r %d",ServerAddress,username,password,StartRoomNumber);
            system(RunCommand);
            StartRoomNumber++;
        }
        
        // User CheckNGの再試行
        file = fopen(Checkflag,"r");
        fscanf(file,"%s",&fmessage);
        fclose(file);

        // 演算
        if(StartRoomNumber <= EndRoomNumber && strcmp(fmessage,"CheckComplete") == 0)
        {
            printf("\n\n> [%d]番のルームを実行します\n",StartRoomNumber);
        }
        else if(strcmp(fmessage,"CheckNG") == 0)
        {
            printf("\n\n> エラー\n> User CheckNGなので、再試行します。\n");
            StartRoomNumber--;
        }
        else if(strcmp(fmessage,"Unchecked") == 0)
        {
            printf("\n\n> コンパイルエラーが発生しました\n> 詳しい内容はErrorHelp.txtでエラーコードを参照してください\n> エラーコード[ME001]\n");
            exit(1);
        }
        else
        {
            flag = TRUE;
        }

        // 待機
        printf("\n");
        for(i = 10; (i >= 1 && flag == FALSE); i--)
        {
            printf("> [待機中] しばらくお待ちください...あと%d秒..\n",i);
            sleep(1);
        }
        printf("\n");
    }
    printf("\n\n> 処理が終了しました\n");
}