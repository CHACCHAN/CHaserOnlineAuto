/************************************************/
/* */
/* CHaserOnlineClient2020 earthworm */
/* */
/* Date 2020.3.4 */
/* Programed by Masayuki Inada */
/* */
/* 簡易マッピング */
/* 場外に出たら切断する */
/* もしも右が土だったら右へ、 */
/* そうでなければ下へ */
/* */
/************************************************/
0 0
//起動パラメータの書式
// ./CHaserOnlineClient○○.o ターゲットurl [-x プロキシアドレス プロキシポート -u ユーザID -p パスワード -r ルーム 番号
// パラメータの順番、有無は任意でよい
int send_cmd(char *command, char *param, char *returnCode);
int returnCode2int(char *returnCode, int *returnNumber);
int Init(int argc, char **argv, char *ProxyAddress, int ProxyPort);
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/param.h>
#include <sys/uio.h>
#include <unistd.h>
#include "CHaserOnline2020.h"
#define BUF_LEN 512 /* バッファのサイズ */
#define MAX_KEYWORD 30 /*キーワードの最大数*/
struct sockaddr_in server; /* ソケットを扱うための構造体 */
char host[BUF_LEN] = "localhost"; /* 接続するホスト名 */
char path[BUF_LEN] = "/"; /* 要求するパス */
unsigned short port = 0; /* 接続するポート番号 */
int main(int argc, char *argv[]){
 int i;
 int Retsu, Gyou;
 int RoomNumber = -1;
 char command[20];
 char param[BUF_LEN];
 char buff[10];
 char ProxyAddress[256];
 int ProxyPort;
 char UserName[20];
 char PassWord[20];
 char ReturnCode[BUF_LEN];
 int returnNumber[10];
 int ActionReturnNumber[10];
 int HoseiReturnNumber[19][19];
 char *pivo;
 int count;
 int ActionCount;
 int mode=5;
 int GetReadyMode=5;
 int kyori_count;
 float kyori;
 int koudou[4]={7,3,1,5};
 int koudou_pivo=0;
 int wait_flag = 1;
 int wait_time = 0;
 int BreakLimitMax = 0;
 int BreakLimit = 0;
 int OutSide=1;
 int ViewMode=0;
 int MyNumber=-1;
 strcpy(ProxyAddress, ""); //初期化
 ActionReturnNumber[0]=-10000;
 //戻り値補正用配列の初期化
 for(Retsu = 0; Retsu < 19; Retsu++){
 for(Gyou = 0; Gyou < 19; Gyou++){
 //不明(-2)で初期化する
 HoseiReturnNumber[Retsu][Gyou] = -2;
 }
 }
 //補正用配列の自分の位置を初期化
 HoseiReturnNumber[9][9]=1000;
 /*-----------------------
 パラメータの読み込み
 * 2013.4.3
 ------------------------*/
 i = 2;
 while(argv[i] != NULL){
 if(argv[i][0] == '-'){ //パラメータ指定子だったら
 switch(argv[i][1]){
 case 'x' //プロキシアドレス プロキシポート
 i++;
 pivo = strchr(argv[i], ' '); //アドレスとポートを切り離す
 *pivo = '\0';
 strcpy(ProxyAddress, argv[i]);
 ProxyPort = atoi((char *)(++pivo));
 break;
 case 'u' //ユーザID
 i++;
 strcpy(UserName, argv[i]);
 break;
 case 'p' //パスワード
 i++;
 strcpy(PassWord, argv[i]);
 break;
 case 'r' //ルーム番号
 i++;
 RoomNumber = atoi(argv[i]);
 break;
 case 'w' //ウェイト時間
 i++;
 wait_time = atoi(argv[i]);
 break;
 case 'b' //自動終了制限回数
 i++;
 BreakLimitMax = atoi(argv[i]);
 break;
 case 'v' //マップ表示モード　0 更新モード、1 ログモード
 i++;
 ViewMode = atoi(argv[i]);
 break;
 default
 break;
 }
 }
 i++;
 }
 //補正用マップの表示
 MapView(HoseiReturnNumber, ViewMode);
 printf("\n\n");
 /*-----------------------
 ネットワーク接続
 -------------------------*/
 if(Init(argc, argv, ProxyAddress, ProxyPort)!=0){
 return -1;
 }
 /*-----------------------
 ユーザ名とパスワードをセットする
 -------------------------*/
 do{
 //printf("L158 User&PassWord\n"); //debug
 if(strcmp(UserName, "")==0){ //ユーザ名パラメータがなければ
 printf("UserName=");
 scanf("%s",UserName);
 }
 strcpy(param, "user=");
 strcat(param, UserName);
 if(strcmp(PassWord, "")==0){ //パスワードパラメータがなければ
 printf("PassWord=");
 scanf("%s",PassWord);
 }
 strcat(param, "&pass=");
 strcat(param, PassWord);
 //printf("L172\n");
 send_cmd("UserCheck", param, ReturnCode);
 //printf("UserCheck L176\n"); //debug
 if(strcmp(ReturnCode, "roomNumber=")==0){ //ユーザ名が受け付けられたら
 }
 else{
 //強制終了
 printf("User CheckNG\n");
 return -1;
 }
 }while(strcmp(ReturnCode, "roomNumber=")!=0); //ユーザ名が受け付けられるまでループ
 /*--------------------
 ルーム番号を指定する
 --------------------*/
 do{
 if(RoomNumber < 0){ //ルーム番号パラメータがなければ
 printf("RoomNumber=");
 scanf("%d",&RoomNumber);
 }
 printf("RoomNumber=%d\n", RoomNumber);
 strcpy(param, "roomNumber=");
 sprintf(buff, "%d", RoomNumber);
 strcat(param, buff);
 send_cmd("RoomNumberCheck", param, ReturnCode);
 //printf("L196 \n"); //debug
 if(strcmp(ReturnCode, "command1=")==0){ //ルーム番号が受け付けられたら
 }
 else{
 //強制終了
 printf("RoomCheckNG\n");
 return -1;
 }
 }while(strcmp(ReturnCode, "command1=")!=0); //ルーム番号が受け付けられるまでループ
 if(ViewMode != 1){
 printf("\x1b[5A");
 }
 while(OutSide>=0){
 BreakLimit = BreakLimitMax;
 //printf("L213 \n"); //debug
 /*-----------------------
 GetReadyを発行する
 -------------------------*/
 do{
 //printf("\n\n\ndeb191 GetReady\n"); //デバッグ用 この行を削除するとセグメントエラーになる
 strcpy(param, "command1=");
 //↓↓↓↓↓↓ GetReadyMoveの作戦を記入 ↓↓↓↓↓↓↓
 GetReadyMode = 4;
 //↑↑↑↑↑↑ GetReadyMoveの作戦を記入 ↑↑↑↑↑↑↑
 switch(GetReadyMode){
 case 4
 strcat(param, "gr");
 break;
 case 1
 strcat(param, "gru");
 break;
 case 3
 strcat(param, "grl");
 break;
 case 5
 strcat(param, "grr");
 break;
 case 7
 strcat(param, "grd");
 break;
 default
 strcat(param, "gr");
 }
 send_cmd("GetReadyCheck", param, ReturnCode);
 if(strchr(ReturnCode, ',')!=NULL){ //GetReadyが受け付けられたら
 wait_flag = 0; //ユーザ待ちをクリア
 }
 else{
 if(BreakLimitMax > 0){
 if(BreakLimit-- <= 0){ //制限回数を越えたら
 return -1; //異常終了
 }
 }
 if(strcmp(ReturnCode, "user=")==0){
 break;
 }
 if(wait_flag == 1){ //ユーザ接続待ちの場合
 sleep(wait_time); //待ち時間
 }
 }
 }while(strchr(ReturnCode, ',')==NULL); //GetReadyが受け付けられるまでループ
 count = returnCode2int(ReturnCode, returnNumber);
 //printf("L271 count=%d\n", count); //debug
 //Mynumberを設定
 if(MyNumber < 1000){
 if((returnNumber[4] >= 1000)&&(count >= 9)){
 MyNumber = returnNumber[4];
 }
 }
 //戻り値を補正する
 RemakeReturnNumber19x19(count, GetReadyMode, returnNumber, HoseiReturnNumber);
 if(ViewMode != 1){
 printf("\x1b[23A");
 }
 //補正用マップの表示
 MapView(HoseiReturnNumber, ViewMode);
 printf("GetReadyMode=%d", GetReadyMode);
 if(ViewMode != 1){
 printf("\x1b[K");
 }
 printf("\n");
 printf("ReturnNumber=");
 for(i = 0; i < count; i++){
 printf("%d, ", returnNumber[i]);
 }
 if(ViewMode != 1){
 printf("\x1b[K");
 }
 printf("\n");
 if(count <= 0){
 OutSide--;
 }
 /*-----------------------
 Actionを発行する
 -------------------------*/
 do{
 //printf("L314 Action\n"); //deb
 strcpy(param, "command2=");
 //↓↓↓↓↓↓ Actionの作戦を記入 ↓↓↓↓↓↓↓
 printf("deb194 kyori[%f],kyori_count[%d],koudou_pivo[%d],mode[%d]\n", kyori, kyori_count, koudou_pivo, mode); //debug
 //動きを確認
 //　距離の動き　1,1,2,2,3,3,4,4,5,5,6,6・・・
 // →1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 5.5, 6 ～
 // をint型にして切り捨てると期待値に変換できる
 // 向きの動き　5, 7, 3, 1
 // 距離をカウントしていき、折り返し距離になったら折り返す
 if(kyori_count >= (int)kyori){
 if(koudou_pivo >= 3){
 koudou_pivo = 0;
 }
 else{
 koudou_pivo++;
 }
 mode = koudou[koudou_pivo];
 kyori_count = 0;
 kyori += 0.5;
 }
 else{
 kyori_count++;
 }
 //場外チェック
 if(count == 6){
 //0C2
 //345
 if(returnNumber[1] == MyNumber){
 if(returnNumber[4] >=5){
 mode = 7;
 }
 else{
 mode = 36;
 }
 }
 //01
 //C3
 //45
 else if(returnNumber[2] == MyNumber){
 if(returnNumber[3] >=5){
 mode = 5;
 }
 else if(returnNumber[1] >=5){
 mode = 1;
 }
 else if(returnNumber[5] >=5){
 mode = 7;
 }
 else{
 mode = 5;
 }
 }
 //01
 //2C
 //45
 else if(returnNumber[3] == MyNumber){
 if(returnNumber[2] >=5){
 mode = 3;
 }
 else if(returnNumber[0] >=5){
 mode = 1;
 }
 else if(returnNumber[4] >=5){
 mode = 7;
 }
 else{
 mode = 3;
 }
 }
 //012
 //3C5
 else if(returnNumber[4] == MyNumber){
 if(returnNumber[1] >=5){
 mode = 1;
 }
 else{
 mode = 32;
 }
 }
 }
 else if(count == 4){
 //01
 //2C
 if(returnNumber[3] == MyNumber){
 mode = 30;
 }
 //01
 //C3
 else if(returnNumber[2] == MyNumber){
 mode = 32;
 }
 //C1
 //23
 else if(returnNumber[0] == MyNumber){
 mode = 38;
 }
 //0C
 //23
 else if(returnNumber[1] == MyNumber){
 mode = 36;
 }
 }
 //↑↑↑↑↑↑ Actionの作戦を記入 ↑↑↑↑↑↑↑
 switch(mode){
 case 1
 strcat(param, "wu");
 break;
 case 3
 strcat(param, "wl");
 break;
 case 5
 strcat(param, "wr");
 break;
 case 7
 strcat(param, "wd");
 break;
 case 11
 strcat(param, "pu2wd");
 break;
 case 13
 strcat(param, "pl2wr");
 break;
 case 15
 strcat(param, "pr2wl");
 break;
 case 17
 strcat(param, "pd2wu");
 break;
 case 10
 strcat(param, "plu2wrd");
 break;
 case 12
 strcat(param, "pru2wld");
 break;
 case 16
 strcat(param, "pld2wru");
 break;
 case 18
 strcat(param, "prd2wlu");
 break;
 case 20
 strcat(param, "prd0wlu");
 break;
 case 22
 strcat(param, "pld0wru");
 break;
 case 28
 strcat(param, "plu0wrd");
 break;
 case 26
 strcat(param, "pru0wld");
 break;
 case 30
 strcat(param, "keilu");
 break;
 case 32
 strcat(param, "keiru");
 break;
 case 36
 strcat(param, "keild");
 break;
 case 38
 strcat(param, "keird");
 break;
 default
 strcat(param, "wr");
 }
 send_cmd("CommandCheck", param, ReturnCode);
 if(strchr(ReturnCode, ',')!=NULL){ //Actionが受け付けられたら
 }
 else{
 if(BreakLimitMax > 0){
 if(BreakLimit-- <= 0){ //制限回数を越えたら
 return -1; //異常終了
 }
 }
 }
 }while(strchr(ReturnCode, ',')==NULL&&strcmp(ReturnCode, "user=")!=0); //Actionが受け付けられるまでループ
 ActionCount = returnCode2int(ReturnCode, ActionReturnNumber);
 //戻り値を補正する
 RemakeReturnNumber19x19(ActionCount, mode, ActionReturnNumber, HoseiReturnNumber);
 if(ViewMode != 1){
 printf("\x1b[23A");
 }
 //補正用マップの表示
 MapView(HoseiReturnNumber, ViewMode);
 printf("mode=%d", mode);
 if(ViewMode != 1){
 printf("\x1b[K");
 }
 printf("\n");
 printf("ReturnNumber=");
 for(i = 0; i < ActionCount; i++){
 printf("%d, ", ActionReturnNumber[i]);
 }
 if(ViewMode != 1){
 printf("\x1b[K");
 }
 printf("\n");
 /*-----------------------
 #を発行する
 -------------------------*/
 i = 0;
 do{
 send_cmd("EndCommandCheck", "command3=%23", ReturnCode);
 if(strcmp(ReturnCode, "command1=")==0){ //#が受け付けられたら
 }
 else if(strcmp(ReturnCode, "user=")==0
 ||i++>5){ //ゲーム終了だったら
 printf("\n\n\n\n\nGameSet\n");
 return 0; //ゲーム終了
 }
 else{
 }
 }while(strcmp(ReturnCode, "command1=")!=0&&strcmp(ReturnCode, "user=")!=0);
 }
 if(OutSide<0){
 printf("\n\n\n\n\nOutside\n");
 }
}
int send_cmd(char *command, char *param, char *returnCode){
 char buf[BUF_LEN]; //サーバ返答
 char WebBuf[BUF_LEN*40];
 int s; /* ソケットのためのファイルディスクリプタ */
 char send_buf[BUF_LEN]; /* サーバに送る HTTP プロトコル用バッファ */
 static char SessionID[100]; //セッションID
 char *SessionIDstart; //セッションID記入開始位置
 char *SessionIDend; //セッションID記入終了位置
 int SessionIDlength; //セッションIDの長さ
 char ReturnBuf[BUF_LEN];
 char *ReturnBufStart;
 char *ReturnBufEnd;
 int ReturnBufLength;
 char keyword[MAX_KEYWORD][30]=
 {
 "user=", "<input",
 "command1=", "<input",
 "GetReady ReturnCode=", "\n",
 "command2=", "<input",
 "Action ReturnCode=", "\n",
 "command3=", "<input",
 "roomNumber=", "<input"
 };
 int i;
 returnCode[0] = '\0';
 /* ソケット生成 */
 if ( ( s = socket(AF_INET, SOCK_STREAM, 0) ) < 0 ){
 fprintf(stderr, "そケットの生成に失敗しました。\n"); //カタカナの「そ」はワーニングが出る
 return 1;
 }
 //printf("L501 \n"); //debug
 /* サーバに接続 */
 if ( connect(s, (struct sockaddr *)&server, sizeof(server)) == -1 ){
 fprintf(stderr, "connect に失敗しました。\n");
 return 1;
 }
 /* HTTP プロトコル生成 & サーバに送信 */
 if(strcmp(SessionID, "")==0){
 sprintf(send_buf,
 "GET http//%s/CHaserOnline003/user/%s?%s HTTP/1.1\r\n",
 host, command, param);
 }
 else{
 sprintf(send_buf,
 "GET http//%s/CHaserOnline003/user/%s;jsessionid=%s?%s HTTP/1.1\r\n",
 host, command, SessionID, param);
 }
 write(s, send_buf, strlen(send_buf));
 sprintf(send_buf, "Host %s %d\r\n", host, port);
 write(s, send_buf, strlen(send_buf));
 sprintf(send_buf, "\r\n");
 write(s, send_buf, strlen(send_buf));
 /* あとは受信して、表示するだけ */
 int read_size;
 //printf("L531 \n"); //debug
 read_size = read(s, buf, BUF_LEN);
 buf[read_size] = '\0';
 //printf("L533 read_size=%d\n", read_size); //debug
 if ( read_size > 0 ){
 strcpy(WebBuf, buf);
 do{
 //printf("L539 read_size=%d\n", read_size); //debug
 read_size = read(s, buf, BUF_LEN);
 buf[read_size] = '\0';
 strcat(WebBuf, buf);
 }while(read_size >= BUF_LEN);
 if(SessionID[0] == '\0'){
 //サーバ返答からセッションＩＤを取り出す
 SessionIDstart = strstr(WebBuf, "JSESSIONID=");
 if(SessionIDstart != NULL){
 SessionIDend = strchr(SessionIDstart, ';');
 if(SessionIDend != NULL){
 SessionIDlength = SessionIDend - SessionIDstart - 11;
 strncpy(SessionID, SessionIDstart+11, SessionIDlength);
 SessionID[SessionIDlength] = '\0'; //文字列終端の補正
 }
 else{
 }
 }
 else{
 }
 }
 for(i = 0; i<=MAX_KEYWORD; i=i+2){
 if(keyword[i][0]=='\0'){
 break;
 }
 //サーバ返答からReturnCodeを取り出す
 ReturnBufStart = strstr(WebBuf, keyword[i]);
 if(ReturnBufStart != NULL){
 ReturnBufEnd = strstr(ReturnBufStart, keyword[i+1]);
 if(ReturnBufEnd != NULL){
 ReturnBufLength = ReturnBufEnd - ReturnBufStart - strlen(keyword[i]);
 if(ReturnBufLength == 0){
 strcpy(ReturnBuf, keyword[i]);
 }
 else{
 strncpy(ReturnBuf, ReturnBufStart+strlen(keyword[i]), ReturnBufLength);
 ReturnBuf[ReturnBufLength] = '\0'; //文字列終端の補正
 }
 if(strlen(ReturnBuf)==1){ //もしもリターンコードが1文字だったらカンマを追加する
 strcat(ReturnBuf, ",");
 }
 strcpy(returnCode, ReturnBuf);
 i = MAX_KEYWORD + 1;
 //printf("ReturnCode=%s\n", returnCode);
 close(s);
 return 0;
 }
 }
 }
 }
 /* 後始末 */
 close(s);
 return 0;
}
int returnCode2int(char *returnCode, int *returnNumber){
 int i=0;
 char *buf;
 int count = 0;
 buf = strtok(returnCode, ",");
 if(buf != NULL){
 count++;
 returnNumber[i] = atoi(buf);
 for(i=1; i<9; i++){
 buf = strtok(NULL, ",");
 if(buf != NULL){
 count++;
 returnNumber[i] = atoi(buf);
 }
 else{
 break;
 }
 }
 return count;
 }
 else{
 return -1;
 }
}
int Init(int argc, char **argv, char *ProxyAddress, int ProxyPort)
{
 struct hostent *servhost; /* ホスト名と IP アドレスを扱うための構造体 */
 struct servent *service; /* サービス (http など) を扱うための構造体 */
 if ( argc > 1 ){ /* URLが指定されていたら */
 char host_path[BUF_LEN];
 if ( strlen(argv[1]) > BUF_LEN-1 ){
 fprintf(stderr, "URL が長すぎます。\n");
 return 1;
 }
 /* http // から始まる文字列で */
 /* sscanf が成功して */
 /* http // の後に何か文字列が存在するなら */
 if ( strstr(argv[1], "http //") &&
 sscanf(argv[1], "http //%s", host_path) &&
 strcmp(argv[1], "http //" ) ){
 char *p;
 p = strchr(host_path, '/'); /* ホストとパスの区切り "/" を調べる */
 if ( p != NULL ){
 strcpy(path, p); /* "/"以降の文字列を path にコピー */
 *p = '\0';
 strcpy(host, host_path); /* "/"より前の文字列を host にコピー */
 } else { /* "/"がないなら＝http //host という引数なら */
 strcpy(host, host_path); /* 文字列全体を host にコピー */
 }
 p = strchr(host, ' '); /* ホスト名の部分に " が含まれていたら */
 if ( p != NULL ){
 port = atoi(p+1); /* ポート番号を取得 */
 if ( port <= 0 ){ /* 数字でない (atoi が失敗) か、0 だったら */
 port = 80; /* ポート番号は 80 に決め打ち */
 }
 *p = '\0';
 }
 } else {
 fprintf(stderr, "URL は http //host/path の形式で指定してください。\n");
 return 1;
 }
 }
 printf("http//%s%s を取得します。\n\n", host, path);
 /* ホストの情報(IPアドレスなど)を取得 */
 if(strcmp(ProxyAddress, "") == 0){
 servhost = gethostbyname(host);
 if ( servhost == NULL ){
 fprintf(stderr, "[%s] から IP アドレスへの変換に失敗しました。\n", host);
 return 0;
 }
 }
 else{
 servhost = gethostbyname(ProxyAddress); //プロキシの設定
 if ( servhost == NULL ){
 fprintf(stderr, "[%s] から IP アドレスへの変換に失敗しました。\n", ProxyAddress);
 return 0;
 }
 }
 bzero(&server, sizeof(server)); /* 構造体をゼロクリア */
 printf("[debug]bzero()\n"); //デバッグ用
 server.sin_family = AF_INET;
 /* IPアドレスを示す構造体をコピー */
 bcopy(servhost->h_addr, &server.sin_addr, servhost->h_length);
 if(strcmp(ProxyAddress, "") == 0){
 if ( port != 0 ){ /* 引数でポート番号が指定されていたら */
 server.sin_port = htons(port);
 } else { /* そうでないなら getservbyname でポート番号を取得 */
 service = getservbyname("http", "tcp");
 if ( service != NULL ){ /* 成功したらポート番号をコピー */
 server.sin_port = service->s_port;
 } else { /* 失敗したら 80 番に決め打ち */
 server.sin_port = htons(80);
 }
 }
 }
 else{
 server.sin_port = htons(ProxyPort); //プロキシのポートを設定する
 }
 return 0;
}