/**********************************************
	CHaserOnlineClient2023public_001

	Date	2023.2.8
**********************************************/

//�N���p�����[�^�̏���
//	./CHaserOnlineClient����.o �^�[�Q�b�gurl [-x �v���L�V�A�h���X:�v���L�V�|�[�g -u ���[�UID -p �p�X���[�h -r ���[���ԍ�
//																							 -w �E�F�C�g���� -b �����I��������]
//	�p�����[�^�̏��ԁA�L���͔C�ӂł悢

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
#include "CHaserOnline2023.h"

#define BUF_LEN 512                      /* �o�b�t�@�̃T�C�Y */
#define MAX_KEYWORD	30					/*�L�[���[�h�̍ő吔*/

struct sockaddr_in server;           /* �\�P�b�g���������߂̍\���� */

char host[BUF_LEN] = "localhost";    /* �ڑ�����z�X�g�� */
char path[BUF_LEN] = "/";            /* �v������p�X */
unsigned short port = 0;             /* �ڑ�����|�[�g�ԍ� */


	


int main(int argc, char *argv[]){
	
	int  i;
	int  Retsu, Gyou;
	int  RoomNumber = -1;
	char command[20];
	char param[BUF_LEN];
	char buff[10];
	char ProxyAddress[256];
	int  ProxyPort;
	char UserName[20];
	char PassWord[20];
	char ReturnCode[BUF_LEN];
	int  returnNumber[10];
	int  ActionReturnNumber[10];
	int  HoseiReturnNumber[19][19];
	char *pivo;
	int  count;
	int  ActionCount;
	int  mode=5;
	int  GetReadyMode=5;
	int  check[4] = {1,5,7,3};
	int  naname_check[4] = {0, 2, 8, 6};
	int	 ItemRui[9] = {20, 3, 1, 9, 5, 6, 7, 8};
	int	 item;
	int  wait_flag = 1;
	int  wait_time = 1;
	int  BreakLimitMax = 480;
	int  BreakLimit = 0;
	int  OutSide=1;
	int  ViewMode=0;

	strcpy(ProxyAddress, "");	//������
	ActionReturnNumber[0]=-10000;

	//�߂�l�␳�p�z��̏�����
	for(Retsu = 0; Retsu < 19; Retsu++){
		for(Gyou = 0; Gyou < 19; Gyou++){
			//�s��(-2)�ŏ���������
			HoseiReturnNumber[Retsu][Gyou] = -2;
		}
	}
	
	//�␳�p�z��̎����̈ʒu��������
	HoseiReturnNumber[9][9]=1000;
	
	/*-----------------------
	 �p�����[�^�̓ǂݍ���
	 * 2013.4.3
	 ------------------------*/
	i = 2;
	while(argv[i] != NULL){
		if(argv[i][0] == '-'){	//�p�����[�^�w��q��������
			switch(argv[i][1]){
				case	'x':	//�v���L�V�A�h���X:�v���L�V�|�[�g
					i++;
					pivo = strchr(argv[i], ':');	//�A�h���X�ƃ|�[�g��؂藣��
					*pivo = '\0';
					strcpy(ProxyAddress, argv[i]);
					ProxyPort = atoi((char *)(++pivo));
					break;
					
				case	'u':	//���[�UID
					i++;
					strcpy(UserName, argv[i]);
					break;
					
				case	'p':	//�p�X���[�h
					i++;
					strcpy(PassWord, argv[i]);
					break;
					
				case	'r':	//���[���ԍ�
					i++;
					RoomNumber = atoi(argv[i]);
					break;
					
				case	'w':	//�E�F�C�g����
					i++;
					wait_time = atoi(argv[i]);
					break;
					
				case	'b':	//�����I��������
					i++;
					BreakLimitMax = atoi(argv[i]);
					break;
					
				case	'v':	//�}�b�v�\�����[�h�@0:�X�V���[�h�A1:���O���[�h
					i++;
					ViewMode = atoi(argv[i]);
					break;
					
				default:
					break;
			}
		}
		
		i++;
	}

	//�␳�p�}�b�v�̕\��
	MapView(HoseiReturnNumber, ViewMode);
	
	/*-----------------------
		�l�b�g���[�N�ڑ�
	-------------------------*/
	if(Init(argc, argv, ProxyAddress, ProxyPort)!=0){
		return -1;
	}

	/*-----------------------
	���[�U���ƃp�X���[�h���Z�b�g����
	-------------------------*/
	do{
		if(strcmp(UserName, "")==0){	//���[�U���p�����[�^���Ȃ����
			printf("UserName=");
			scanf("%s",UserName);
		}
		strcpy(param, "user=");
		strcat(param, UserName);
		if(strcmp(PassWord, "")==0){	//�p�X���[�h�p�����[�^���Ȃ����
			printf("PassWord=");
			scanf("%s",PassWord);
		}
		strcat(param, "&pass=");
		strcat(param, PassWord);
		send_cmd("UserCheck", param, ReturnCode);
		
		if(strcmp(ReturnCode, "roomNumber=")==0){		//���[�U�����󂯕t����ꂽ��
		}
		else{
			//�����I��
			printf("User CheckNG\n");
			return -1;
		}
	}while(strcmp(ReturnCode, "roomNumber=")!=0);		//���[�U�����󂯕t������܂Ń��[�v

	/*--------------------
	���[���ԍ����w�肷��
	--------------------*/
	do{
		if(RoomNumber < 0){	//���[���ԍ��p�����[�^���Ȃ����
			printf("RoomNumber=");
			scanf("%d",&RoomNumber);
		}
		printf("RoomNumber=%d\n", RoomNumber);
		strcpy(param, "roomNumber=");
		sprintf(buff, "%d", RoomNumber);
		strcat(param, buff);
		send_cmd("RoomNumberCheck", param, ReturnCode);

		if(strcmp(ReturnCode, "command1=")==0){		//���[���ԍ����󂯕t����ꂽ��
		}
		else{
			//�����I��
			printf("RoomCheckNG\n");
			return -1;
		}
	}while(strcmp(ReturnCode, "command1=")!=0);	//���[���ԍ����󂯕t������܂Ń��[�v

	while(OutSide>=0){
		BreakLimit = BreakLimitMax;
		
		/*-----------------------
		GetReady�𔭍s����
		-------------------------*/
		//printf("\n\n\ndeb191 GetReady\n");	//�f�o�b�O�p	���̍s���폜����ƃZ�O�����g�G���[�ɂȂ�

		strcpy(param, "command1=");

		//GetReadyMove�̍����L��
		GetReadyMode = 4;

		switch(GetReadyMode){
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
		do{
			send_cmd("GetReadyCheck", param, ReturnCode);

			if(strchr(ReturnCode, ',')!=NULL){		//GetReady���󂯕t����ꂽ��
				wait_flag = 0;	//���[�U�҂����N���A
			}
			else{
				if(BreakLimitMax > 0){
					if(BreakLimit-- <= 0){	//�����񐔂��z������
						return -1;	//�ُ�I��
					}
				}
				
				if(strcmp(ReturnCode, "user=")==0){
					return 0;	//�Q�[���I��
				}
				if(wait_flag == 1){	//���[�U�ڑ��҂��̏ꍇ
					sleep(wait_time);	//�҂�����
				}
			}
			
		}while(strchr(ReturnCode, ',')==NULL);	//GetReady���󂯕t������܂Ń��[�v
		count = returnCode2int(ReturnCode, returnNumber);

		//Mynumber��ݒ�
/*		if(MyNumber < 1000){
			if((returnNumber[4] >= 1000)&&(count >= 9)){
				MyNumber = returnNumber[4];
			}
		}
*/
		//�߂�l��␳����
		RemakeReturnNumber19x19(count, GetReadyMode, returnNumber, HoseiReturnNumber);

		//�␳�p�}�b�v�̕\��
		MapView(HoseiReturnNumber, ViewMode);

		if(count <= 0){
			OutSide--;
		}

		
		/*-----------------------
		Action�𔭍s����
		-------------------------*/
		strcpy(param, "command2=");
		//Action�̍����L������
		mode = 5;

		switch(mode){
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
					
			default:
				strcat(param, "wr");
		}
		do{
			send_cmd("CommandCheck", param, ReturnCode);

			if(strchr(ReturnCode, ',')!=NULL){		//Action���󂯕t����ꂽ��
			}
			else{
				return -1;	//�ُ�I��
			}
			
		}while(strchr(ReturnCode, ',')==NULL&&strcmp(ReturnCode, "user=")!=0);	//Action���󂯕t������܂Ń��[�v
		ActionCount = returnCode2int(ReturnCode, ActionReturnNumber);

		//�߂�l��␳����
		RemakeReturnNumber19x19(ActionCount, mode, ActionReturnNumber, HoseiReturnNumber);

		//�␳�p�}�b�v�̕\��
		MapView(HoseiReturnNumber, ViewMode);
		
		/*-----------------------
		#�𔭍s����
		-------------------------*/
		i = 0;
		do{			
			send_cmd("EndCommandCheck", "command3=%23", ReturnCode);
			if(strcmp(ReturnCode, "command1=")==0){		//#���󂯕t����ꂽ��
			}
			else if(strcmp(ReturnCode, "user=")==0
					||i++>5){		//�Q�[���I����������
				printf("GameSet\n");
			
				return 0;	//�Q�[���I��
			}
			else{
			}
		}while(strcmp(ReturnCode, "command1=")!=0&&strcmp(ReturnCode, "user=")!=0);
	}
	if(OutSide<0){
		printf("\n\nOutside\n");
	}
}



int send_cmd(char *command, char *param, char *returnCode){
    char buf[BUF_LEN];					//�T�[�o�ԓ�
    char WebBuf[BUF_LEN*40];
    int s;                               /* �\�P�b�g�̂��߂̃t�@�C���f�B�X�N���v�^ */
    char send_buf[BUF_LEN];              /* �T�[�o�ɑ��� HTTP �v���g�R���p�o�b�t�@ */

    static char SessionID[100];					//�Z�b�V����ID
    char *SessionIDstart;				//�Z�b�V����ID�L���J�n�ʒu
    char *SessionIDend;					//�Z�b�V����ID�L���I���ʒu
	int	 SessionIDlength;				//�Z�b�V����ID�̒���

	char ReturnBuf[BUF_LEN];
	char *ReturnBufStart;
	char *ReturnBufEnd;
	int  ReturnBufLength;

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
		
	
	int  i;
	int read_size;

	returnCode[0] = '\0';
	
	/* �\�P�b�g���� */
    if ( ( s = socket(AF_INET, SOCK_STREAM, 0) ) < 0 ){
		fprintf(stderr, "���P�b�g�̐����Ɏ��s���܂����B\n");	//�J�^�J�i�́u���v�̓��[�j���O���o��
        return 1;
    }
    
    /* �T�[�o�ɐڑ� */
    if ( connect(s, (struct sockaddr *)&server, sizeof(server)) == -1 ){
        fprintf(stderr, "connect �Ɏ��s���܂����B\n");
        return 1;
    }

    /* HTTP �v���g�R������ & �T�[�o�ɑ��M */
	if(strcmp(SessionID, "")==0){
		sprintf(send_buf, 
			"GET http://%s/CHaserOnline003/user/%s?%s HTTP/1.1\r\n",
			host, command, param);
	}
	else{
		sprintf(send_buf, 
			"GET http://%s/CHaserOnline003/user/%s;jsessionid=%s?%s HTTP/1.1\r\n",
			host, command, SessionID, param);
	}
	
	write(s, send_buf, strlen(send_buf));

	sprintf(send_buf, "Host: %s:%d\r\n", host, port);
	write(s, send_buf, strlen(send_buf));

	sprintf(send_buf, "Cookie: jsession=%s\r\n", SessionID);
	write(s, send_buf, strlen(send_buf));

	sprintf(send_buf, "User-Agent:CHaserOnlineClient/2022\r\n");
	write(s, send_buf, strlen(send_buf));

	sprintf(send_buf, "\r\n");
	write(s, send_buf, strlen(send_buf));

	/* ���Ƃ͎�M���āA�\�����邾�� */
        read_size = read(s, buf, BUF_LEN);
		buf[read_size] = '\0';

        if ( read_size > 0 ){
			strcpy(WebBuf, buf);

			do{
				read_size = read(s, buf, BUF_LEN);
				buf[read_size] = '\0';

				strcat(WebBuf, buf);
			}while(read_size >= BUF_LEN);

			if(SessionID[0] == '\0'){
				//�T�[�o�ԓ�����Z�b�V�����h�c�����o��
				SessionIDstart = strstr(WebBuf, "JSESSIONID=");
				if(SessionIDstart != NULL){
					SessionIDend = strchr(SessionIDstart, ';');
					if(SessionIDend != NULL){
						SessionIDlength = SessionIDend - SessionIDstart - 11; 
						strncpy(SessionID, SessionIDstart+11, SessionIDlength);
						SessionID[SessionIDlength] = '\0';	//������I�[�̕␳
					}
					else{
					}
				}
				else{
				}
			}

			if(strcmp(command, "UserCheck")==0){
				i = 12;
			}
			else if(strcmp(command, "RoomNumberCheck")==0){
				i = 2;
			}
			else if(strcmp(command, "GetReadyCheck")==0){
				i = 4;
			}
			else if(strcmp(command, "CommandCheck")==0){
				i = 8;
			}
			else if(strcmp(command, "EndCommandCheck")==0){
				i = 2;
			}

			//�T�[�o�ԓ�����ReturnCode�����o��
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
						ReturnBuf[ReturnBufLength] = '\0';	//������I�[�̕␳
					}
					if(strlen(ReturnBuf)==1){	//���������^�[���R�[�h��1������������J���}��ǉ�����
						strcat(ReturnBuf, ",");
					}
						
					strcpy(returnCode, ReturnBuf);
					i = MAX_KEYWORD + 1;
						
					close(s);
					return 0;
				}
			}
		}
	/* ��n�� */
    close(s);
	return 0;
}


    
int returnCode2int(char *returnCode, int *returnNumber){
	int	 i=0;
	char *buf;
	int  count = 0;
	
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
    struct hostent *servhost;            /* �z�X�g���� IP �A�h���X���������߂̍\���� */
    struct servent *service;             /* �T�[�r�X (http �Ȃ�) ���������߂̍\���� */

	if ( argc > 1 ){                     /* URL���w�肳��Ă����� */
		char host_path[BUF_LEN];

		if ( strlen(argv[1]) > BUF_LEN-1 ){
            fprintf(stderr, "URL ���������܂��B\n");
            return 1;
        }
                                         /* http:// ����n�܂镶����� */
                                         /* sscanf ���������� */
                                         /* http:// �̌�ɉ��������񂪑��݂���Ȃ� */
        if ( strstr(argv[1], "http://") &&
             sscanf(argv[1], "http://%s", host_path) &&
             strcmp(argv[1], "http://" ) ){

            char *p;
            p = strchr(host_path, '/');  /* �z�X�g�ƃp�X�̋�؂� "/" �𒲂ׂ� */
            if ( p != NULL ){
                strcpy(path, p);        /* "/"�ȍ~�̕������ path �ɃR�s�[ */
                *p = '\0';
                strcpy(host, host_path); /* "/"���O�̕������ host �ɃR�s�[ */
            } else {                     /* "/"���Ȃ��Ȃ灁http://host �Ƃ��������Ȃ� */
                strcpy(host, host_path); /* ������S�̂� host �ɃR�s�[ */
            }

            p = strchr(host, ':');       /* �z�X�g���̕����� ":" ���܂܂�Ă����� */
            if ( p != NULL ){
                port = atoi(p+1);        /* �|�[�g�ԍ����擾 */
                if ( port <= 0 ){        /* �����łȂ� (atoi �����s) ���A0 �������� */
                    port = 80;         /* �|�[�g�ԍ��� 80 �Ɍ��ߑł� */
                }
                *p = '\0';
            }
        } else {
            fprintf(stderr, "URL �� http://host/path �̌`���Ŏw�肵�Ă��������B\n");
            return 1;
        }
    }

    printf("http://%s%s ���擾���܂��B\n\n", host, path);

	/* �z�X�g�̏��(IP�A�h���X�Ȃ�)���擾 */
	if(strcmp(ProxyAddress, "") == 0){
		servhost = gethostbyname(host);
		if ( servhost == NULL ){
			fprintf(stderr, "[%s] ���� IP �A�h���X�ւ̕ϊ��Ɏ��s���܂����B\n", host);
			return 0;
		}
	}
	else{
		servhost = gethostbyname(ProxyAddress);	//�v���L�V�̐ݒ�
		if ( servhost == NULL ){
			fprintf(stderr, "[%s] ���� IP �A�h���X�ւ̕ϊ��Ɏ��s���܂����B\n", ProxyAddress);
			return 0;
		}
	}

    bzero(&server, sizeof(server));            /* �\���̂��[���N���A */
	printf("[debug]bzero()\n");	//�f�o�b�O�p
	
    server.sin_family = AF_INET;

                                               /* IP�A�h���X�������\���̂��R�s�[ */
    bcopy(servhost->h_addr, &server.sin_addr, servhost->h_length);

	if(strcmp(ProxyAddress, "") == 0){
		if ( port != 0 ){                          /* �����Ń|�[�g�ԍ����w�肳��Ă����� */
			server.sin_port = htons(port);
		} else {                                   /* �����łȂ��Ȃ� getservbyname �Ń|�[�g�ԍ����擾 */
			service = getservbyname("http", "tcp");
			if ( service != NULL ){                /* ����������|�[�g�ԍ����R�s�[ */
				server.sin_port = service->s_port;
			} else {                               /* ���s������ 80 �ԂɌ��ߑł� */
				server.sin_port = htons(80);
			}
		}
	}
	else{
		server.sin_port = htons(ProxyPort);		//�v���L�V�̃|�[�g��ݒ肷��
	}
	
	return 0;
}

