/* send android keyboard event via usb
 * 2010/1/5 by chihying
 *
 * release not:
 * 	v1.0 2010/1/5
 * 		first version, no '<' and '>'
 *
 *
 * */


#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>

#include "main.h"
#include "cmd.h"

static int S;

void set_tty(){
        struct termios old = {0};

        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");

        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;

        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
}

char getch(void) {
        char buf = 0;

        if (read(0, &buf, 1) < 0)
                perror ("read()");

        return (buf);
}

void send_cmd(int n){
	char command[100];
	for(int i=0; i<cmd[n].event_len; i++){
		sprintf(command, "adb shell input keyevent %d", cmd[n].event[i]);
		system(command);
	}
}

void unknow(char key){
	printf("error: unknow key %d\n", key);
	S=1;
}

void print_cmd(int n){
	for(int i=0;i<cmd[n].event_len; i++){
		printf("%d ", cmd[n].event[i]);
	}
	printf("\n");
}

int main() {
        char key;
	int cmd_num=0, cmd_max_length=0, flag;
	
	cmd_num=sizeof(cmd)/sizeof(CMD);
	for(int i=0; i<cmd_num; i++){
		if(cmd[1].input_len>cmd_max_length)
			cmd_max_length=cmd[1].input_len;
	}
//	printf("cmd_num=%d, cmd_max_length=%d\n", cmd_num, cmd_max_length);

	set_tty();

	S=0;
        while((key=getch()) /*&& (key != 27)*//*ESC*/){
//                printf ("you pressed %d, state=%d\n", key, S);

		//unknow state
		if( S<0 || S>=cmd_max_length ){
			printf("error: unknow state\n");
			S=0;
			continue;
		}

		//reset choice
		if(S==0){
			for(int i=0; i<cmd_num; i++){
				cmd[i].choice=1;
			}
		}
		
		flag=0;
		for(int i=0; i<cmd_num; i++){
			if(cmd[i].choice && cmd[i].input_len>S && cmd[i].input[S]==key){
//				printf("choice event: ");print_cmd(i);
	
				flag=1;
				if(cmd[i].input_len==S+1){
//					printf("found keyevent: ");print_cmd(i);

					flag=2;
					send_cmd(i);
					break;
				}
			}else{
				cmd[i].choice=0;
			}
		}
		
		
		if(flag==0){
			printf("error: no match event\n");

			S=0;
			continue;
		}	
		
		if(flag==1){
			S++;
			continue;
		}

		if(flag==2){
			S=0;
			continue;
		}
	}
	
        return(0);
}
