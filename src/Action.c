#include <stdio.h>
#include <string.h>

#define BUF_LEN 512

void modePost(int mode);

// extern宣言
extern int  returnNumber[10];
extern int  ActionReturnNumber[10];
extern int  mode;
extern int  GetReadyMode;
extern char param[BUF_LEN];
extern int  MoveX;
extern int  MoveY;

void modePost(int mode)
{
    // Actionコマンドの設定↓
    switch(mode)
	{
			case 1:
				strcat(param, "wu");
				break;
				
			case 3:
				strcat(param, "wl");
				break;
					
			case 5:
				strcat(param, "wr");
				break;
					
			case 7:
				strcat(param, "wd");
				break;
					
			case 11:
				strcat(param, "pu2wd");
				break;
					
			case 13:
				strcat(param, "pl2wr");
				break;
					
			case 15:
				strcat(param, "pr2wl");
				break;
					
			case 17:
				strcat(param, "pd2wu");
				break;
					
			case 10:
				strcat(param, "plu2wrd");
				break;
					
			case 12:
				strcat(param, "pru2wld");
				break;
					
			case 16:
				strcat(param, "pld2wru");
				break;
					
			case 18:
				strcat(param, "prd2wlu");
				break;
					
			case 20:
				strcat(param, "prd0wlu");
				break;
					
			case 22:
				strcat(param, "pld0wru");
				break;
					
			case 28:
				strcat(param, "plu0wrd");
				break;
					
			case 26:
				strcat(param, "pru0wld");
				break;
					
			case 30:
				strcat(param, "keilu");
				break;

			case 32:
				strcat(param, "keiru");
				break;

			case 36:
				strcat(param, "keild");
				break;
					
			case 38:
				strcat(param, "keird");
				break;
					
			case 41:
				strcat(param, "du");
				break;
					
			case 43:
				strcat(param, "dl");
				break;
					
			case 45:
				strcat(param, "dr");
				break;
					
			case 47:
				strcat(param, "dd");
				break;
					
			case 71:
				strcat(param, "w3u");
				break;
					
			case 73:
				strcat(param, "w3l");
				break;
					
			case 75:
				strcat(param, "w3r");
				break;
					
			case 77:
				strcat(param, "w3d");
				break;
			
			case 105:
				strcat(param, "pr0");
				break;

			case 103:
				strcat(param, "pl0");
				break;

			case 101:
				strcat(param, "pu0");
				break;

			case 107:
				strcat(param, "pd0");
				break;
				
			case 207:
				strcat(param, "pu2wd");
				break;
					
			case 205:
				strcat(param, "pl2wr");
				break;
					
			case 203:
				strcat(param, "pr2wl");
				break;
					
			case 201:
				strcat(param, "pd2wu");
				break;
					
			case 303:
				strcat(param, "plu2wrd");
				break;
					
			case 305:
				strcat(param, "pru2wld");
				break;
					
			case 703:
				strcat(param, "pld2wru");
				break;
					
			case 705:
				strcat(param, "prd2wlu");
				break;

			case 503:
				strcat(param, "pl3sl");
				break;
					
			case 505:
				strcat(param, "pr3sr");
				break;
					
			case 501:
				strcat(param, "pu3su");
				break;
					
			case 507:
				strcat(param, "pd3sd");
				break;
					
			default:
				strcat(param, "wr");
		}
	// Actionコマンドの設定↑
}