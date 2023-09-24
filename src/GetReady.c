#include <stdio.h>
#include <string.h>

#define BUF_LEN 512

void GetReadyModePost(int GetReadyMode);

// extern宣言
extern int  returnNumber[10];
extern int  ActionReturnNumber[10];
extern int  mode;
extern int  GetReadyMode;
extern char param[BUF_LEN];
extern int  MoveX;
extern int  MoveY;

void GetReadyModePost(int GetReadyMode)
{
    // GetReadyコマンドの設定↓
    switch(GetReadyMode)
	{
			case 4:
				strcat(param, "gr");
				break;
					
			case 1:
				strcat(param, "gru");
				break;
					
			case 3:
				strcat(param, "grl");
				break;
					
			case 5:
				strcat(param, "grr");
				break;
					
			case 7:
				strcat(param, "grd");
				break;
				
			default:
				strcat(param, "gr");
		}
	// GetReadyコマンドの設定↑
}