#include <stdio.h>
#include <string.h>
#include "Header/CHaserTools.h"

#define N 64

int command_code(char*);

//extern宣言
extern int returnNumber[10];
extern int ActionReturnNumber[10];
extern int mode;
extern int GetReadyMode;
extern int MapData[19][19];
extern int MoveX,MoveY;
extern int MapX,MapY;

int command_code(char* param)
{
	if(strcmp(param,"command1=") == 0)
	{
		// GetReadyの作戦はここから↓
		if(ActionReturnNumber[1] == SelectID(ActionReturnNumber[1],70,79))
		/*
		ActionReturnNumber[1] ➡ クライアント(自分)を基準として座標[1]を指す。	
								 [4]は自分の座標(クライアント)となる。
								 _______
								 |0 1 2|
								 |3 4 5|
								 |6 7 8|
								 ￣￣￣￣
		*/
		{
			GetReadyMode = 1;
		/*
		GetReadyMode = 1 ➡ コマンド[1]を実行する。
							コマンドの値はこの場合、GetReady.cに記録されている。
							初期値では、コマンド[1]は"上に進んで1～8までのアイテムIDを記録する"と定義されている。
							コマンドの詳細は http://www.zenjouken.com/?page_id=621 から確認できる。
							[X]を自分とすると以下のようになる。
								 _______	 _______
								 |0 1 2|	 |0 X 2|
								 |3 X 5|  ➡ |3 4 5|
								 |6 7 8|	 |6 7 8|
								 ￣￣￣￣	  ￣￣￣￣

		*/
		}
		else if(ActionReturnNumber[3] == SelectID(ActionReturnNumber[3],70,79))
		/*
		ActionReturnNumber[3] ➡ クライアント(自分)を基準として座標[3]を指す。	
								 [4]は自分の座標(クライアント)となる。
								 _______
								 |0 1 2|
								 |3 4 5|
								 |6 7 8|
								 ￣￣￣￣
		*/
		{
			GetReadyMode = 3;
		/*
		GetReadyMode = 3 ➡ コマンド[3]を実行する。
							コマンドの値はこの場合、GetReady.cに記録されている。
							初期値では、コマンド[3]は"左に進んで1～8までのアイテムIDを記録する"と定義されている。
							コマンドの詳細は http://www.zenjouken.com/?page_id=621 から確認できる。
							[X]を自分とすると以下のようになる。
								 _______	 _______
								 |0 1 2|	 |0 1 2|
								 |3 X 5|  ➡ |X 4 5|
								 |6 7 8|	 |6 7 8|
								 ￣￣￣￣	  ￣￣￣￣

		*/
		}
		else if(ActionReturnNumber[5] == SelectID(ActionReturnNumber[5],70,79))
		/*
		ActionReturnNumber[5] ➡ クライアント(自分)を基準として座標[5]を指す。	
								 [4]は自分の座標(クライアント)となる。
								 _______
								 |0 1 2|
								 |3 4 5|
								 |6 7 8|
								 ￣￣￣￣
		*/
		{
			GetReadyMode = 5;
		/*
		GetReadyMode = 5 ➡ コマンド[5]を実行する。
							コマンドの値はこの場合、GetReady.cに記録されている。
							初期値では、コマンド[5]は"右に進んで1～8までのアイテムIDを記録する"と定義されている。
							コマンドの詳細は http://www.zenjouken.com/?page_id=621 から確認できる。
							[X]を自分とすると以下のようになる。
								 _______	 _______
								 |0 1 2|	 |0 1 2|
								 |3 X 5|  ➡ |3 4 X|
								 |6 7 8|	 |6 7 8|
								 ￣￣￣￣	  ￣￣￣￣

		*/
		}
		else if(ActionReturnNumber[7] == SelectID(ActionReturnNumber[7],70,79))
		/*
		ActionReturnNumber[7] ➡ クライアント(自分)を基準として座標[7]を指す。	
								 [4]は自分の座標(クライアント)となる。
								 _______
								 |0 1 2|
								 |3 4 5|
								 |6 7 8|
								 ￣￣￣￣
		*/
		{
			GetReadyMode = 7;
		/*
		GetReadyMode = 7 ➡ コマンド[7]を実行する。
							コマンドの値はこの場合、GetReady.cに記録されている。
							初期値では、コマンド[7]は"下に進んで1～8までのアイテムIDを記録する"と定義されている。
							コマンドの詳細は http://www.zenjouken.com/?page_id=621 から確認できる。
							[X]を自分とすると以下のようになる。
								 _______	 _______
								 |0 1 2|	 |0 1 2|
								 |3 X 5|  ➡ |3 4 5|
								 |6 7 8|	 |6 X 8|
								 ￣￣￣￣	  ￣￣￣￣

		*/
		}
		else
		/*
		elseは例外処理になる。
		if ~ else ifまでの条件外になった場合のみ、ここが適用される。
		*/
		{
			GetReadyMode = 4;
		/*
		GetReadyMode = 4 ➡ コマンド[4]を実行する。
							コマンドの値はこの場合、GetReady.cに記録されている。
							初期値では、コマンド[4]は"動かないで1～8までのアイテムIDを記録する"と定義されている。
							コマンドの詳細は http://www.zenjouken.com/?page_id=621 から確認できる。
							[X]を自分とすると以下のようになる。
								 _______	 _______
								 |0 1 2|	 |0 1 2|
								 |3 X 5|  ➡ |3 X 5|
								 |6 7 8|	 |6 7 8|
								 ￣￣￣￣	  ￣￣￣￣

		*/
		}
		// GetReadyの作戦はここから↑
		return GetReadyMode;
	}
	else if(strcmp(param,"command2=") == 0)
	{
		// Actionの作戦はここから↓
		if(returnNumber[1] == SelectID(returnNumber[1],70,79))
		/*
		returnNumber[1] ➡  クライアント(自分)を基準として座標[1]を指す。
							[4]は自分の座標(クライアント)となる。
							よってif文の条件は、次のように表現できる。	
							「もし、座標[1]番にアイテムID70 ～ 79があったら」
							_______
							|0 1 2|
							|3 4 5|
							|6 7 8|
							￣￣￣￣
		*/
		{
			mode = 1;
		/*
		mode = 1 ➡ コマンド[1]を実行する。
					コマンドの値はこの場合、Action.cに記録されている。
					初期値では、コマンド[1]は"上に進む"と定義されている。
					コマンドの詳細は http://www.zenjouken.com/?page_id=621 から確認できる。
					[X]を自分とすると以下のようになる。
						_______	 	_______
						|0 1 2|	 	|0 1 2|
						|3 X 5|  ➡ |3 4 5|
						|6 7 8|	 	|6 X 8|
						￣￣￣￣	 ￣￣￣￣

		*/
		}
		else if(returnNumber[3] == SelectID(returnNumber[3],70,79))
		/*
		returnNumber[3] ➡  クライアント(自分)を基準として座標[3]を指す。
							[4]は自分の座標(クライアント)となる。
							よってif文の条件は、次のように表現できる。	
							「もし、座標[3]番にアイテムID70 ～ 79があったら」
							_______
							|0 1 2|
							|3 4 5|
							|6 7 8|
							￣￣￣￣
		*/
		{
			mode = 3;
		/*
		mode = 3 ➡ コマンド[3]を実行する。
					コマンドの値はこの場合、Action.cに記録されている。
					初期値では、コマンド[3]は"左に進む"と定義されている。
					コマンドの詳細は http://www.zenjouken.com/?page_id=621 から確認できる。
					[X]を自分とすると以下のようになる。
						_______	 	_______
						|0 1 2|	 	|0 1 2|
						|3 X 5|  ➡ |X 4 5|
						|6 7 8|	 	|6 7 8|
						￣￣￣￣	 ￣￣￣￣

		*/
		}
		else if(returnNumber[5] == SelectID(returnNumber[5],70,79))
		/*
		returnNumber[5] ➡  クライアント(自分)を基準として座標[5]を指す。
							[4]は自分の座標(クライアント)となる。
							よってif文の条件は、次のように表現できる。	
							「もし、座標[5]番にアイテムID70 ～ 79があったら」
							_______
							|0 1 2|
							|3 4 5|
							|6 7 8|
							￣￣￣￣
		*/
		{
			mode = 5;
		/*
		mode = 5 ➡ コマンド[5]を実行する。
					コマンドの値はこの場合、Action.cに記録されている。
					初期値では、コマンド[5]は"右に進む"と定義されている。
					コマンドの詳細は http://www.zenjouken.com/?page_id=621 から確認できる。
					[X]を自分とすると以下のようになる。
						_______	 	_______
						|0 1 2|	 	|0 1 2|
						|3 X 5|  ➡ |3 4 X|
						|6 7 8|	 	|6 7 8|
						￣￣￣￣	 ￣￣￣￣

		*/
		}
		else if(returnNumber[7] == SelectID(returnNumber[7],70,79))
		/*
		returnNumber[7] ➡  クライアント(自分)を基準として座標[7]を指す。
							[4]は自分の座標(クライアント)となる。
							よってif文の条件は、次のように表現できる。	
							「もし、座標[7]番にアイテムID70 ～ 79があったら」
							_______
							|0 1 2|
							|3 4 5|
							|6 7 8|
							￣￣￣￣
		*/
		{
			mode = 7;
		/*
		mode = 7 ➡ コマンド[7]を実行する。
					コマンドの値はこの場合、Action.cに記録されている。
					初期値では、コマンド[7]は"下に進む"と定義されている。
					コマンドの詳細は http://www.zenjouken.com/?page_id=621 から確認できる。
					[X]を自分とすると以下のようになる。
						_______	 	_______
						|0 1 2|	 	|0 1 2|
						|3 X 5|  ➡ |3 4 5|
						|6 7 8|	 	|6 X 8|
						￣￣￣￣	 ￣￣￣￣

		*/
		}
		else
		{
			mode = 5;
		}
		// Actionの作戦はここから↑
		return mode;
	}
}