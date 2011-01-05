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

#define MAX_LENGTH 10

int S;

typedef struct _cmd{
	int event[MAX_LENGTH];
	int event_len;
	int input_len;
	int input[MAX_LENGTH];
	int choice;
}CMD;

CMD cmd[]={

//	{{0}	,1	,	,{}},
//	{{1}	,1	,	,{}},
//	{{2}	,1	,	,{}},
	{{3}	,1	,5	,{27,91,49,53,126}},//KEYCODE_HOME
	{{4}	,1	,5	,{27,91,49,56,126}},//KEYCODE_BACK
//	{{5}	,1	,	,{}},//KEYCODE_CALL
//	{{6}	,1	,	,{}},//KEYCODE_ENDCALL

	{{7}	,1	,1	,{'0'}},
	{{8}	,1	,1	,{'1'}},
	{{9}	,1	,1	,{'2'}},
	{{10}	,1	,1	,{'3'}},
	{{11}	,1	,1	,{'4'}},
	{{12}	,1	,1	,{'5'}},
	{{13}	,1	,1	,{'6'}},
	{{14}	,1	,1	,{'7'}},
	{{15}	,1	,1	,{'8'}},
	{{16}	,1	,1	,{'9'}},
	{{59,7}	,2	,1	,{')'}},
	{{59,8}	,2	,1	,{'!'}},
	{{59,11},2	,1	,{'$'}},
	{{59,12},2	,1	,{'%'}},
	{{59,13},2	,1	,{'^'}},
	{{59,14},2	,1	,{'&'}},
	{{59,16},2	,1	,{'('}},

	{{17}	,1	,1	,{'*'}},
	{{18}	,1	,1	,{'#'}},
	{{19}	,1	,3	,{27,91,65}},//KEYCODE_DPAD_UP
	{{20}	,1	,3	,{27,91,66}},//KEYCODE_DPAD_DOWN
	{{21}	,1	,3	,{27,91,68}},//KEYCODE_DPAD_LEFT
	{{22}	,1	,3	,{27,91,67}},//KEYCODE_DPAD_RIGHT
//	{{23}	,1	,	,{}},//KEYCODE_DPAD_CENTER
	{{24}	,1	,4	,{27,91,53,126}},//KEYCODE_VOLUME_UP
	{{25}	,1	,4	,{27,91,54,126}},//KEYCODE_VOLUME_DOWN
//	{{26}	,1	,	,{}},//KEYCODE_POWER
//	{{27}	,1	,	,{}},//KEYCODE_CAMERA
//	{{28}	,1	,	,{}},//KEYCODE_CLEAR

	{{29}	,1	,1	,{'a'}},
	{{30}	,1	,1	,{'b'}},
	{{31}	,1	,1	,{'c'}},
	{{32}	,1	,1	,{'d'}},
	{{33}	,1	,1	,{'e'}},
	{{34}	,1	,1	,{'f'}},
	{{35}	,1	,1	,{'g'}},
	{{36}	,1	,1	,{'h'}},
	{{37}	,1	,1	,{'i'}},
	{{38}	,1	,1	,{'j'}},
	{{39}	,1	,1	,{'k'}},
	{{40}	,1	,1	,{'l'}},
	{{41}	,1	,1	,{'m'}},
	{{42}	,1	,1	,{'n'}},
	{{43}	,1	,1	,{'o'}},
	{{44}	,1	,1	,{'p'}},
	{{45}	,1	,1	,{'q'}},
	{{46}	,1	,1	,{'r'}},
	{{47}	,1	,1	,{'s'}},
	{{48}	,1	,1	,{'t'}},
	{{49}	,1	,1	,{'u'}},
	{{50}	,1	,1	,{'v'}},
	{{51}	,1	,1	,{'w'}},
	{{52}	,1	,1	,{'x'}},
	{{53}	,1	,1	,{'y'}},
	{{54}	,1	,1	,{'z'}},

	{{59,29},2	,1	,{'A'}},
	{{59,30},2	,1	,{'B'}},
	{{59,31},2	,1	,{'C'}},
	{{59,32},2	,1	,{'D'}},
	{{59,33},2	,1	,{'E'}},
	{{59,34},2	,1	,{'F'}},
	{{59,35},2	,1	,{'G'}},
	{{59,36},2	,1	,{'H'}},
	{{59,37},2	,1	,{'I'}},
	{{59,38},2	,1	,{'J'}},
	{{59,39},2	,1	,{'K'}},
	{{59,40},2	,1	,{'L'}},
	{{59,41},2	,1	,{'M'}},
	{{59,42},2	,1	,{'N'}},
	{{59,43},2	,1	,{'O'}},
	{{59,44},2	,1	,{'P'}},
	{{59,45},2	,1	,{'Q'}},
	{{59,46},2	,1	,{'R'}},
	{{59,47},2	,1	,{'S'}},
	{{59,48},2	,1	,{'T'}},
	{{59,49},2	,1	,{'U'}},
	{{59,50},2	,1	,{'V'}},
	{{59,51},2	,1	,{'W'}},
	{{59,52},2	,1	,{'X'}},
	{{59,53},2	,1	,{'Y'}},
	{{59,54},2	,1	,{'Z'}},

	{{55}	,1	,1	,{','}},
	{{56}	,1	,1	,{'.'}},
//	{{59,55},2	,1	,{'<'}},
//	{{59,56},2	,1	,{'>'}},

//	{{57}	,1	,	,{}},//KEYCODE_ALT_LEFT
//	{{58}	,1	,	,{}},//KEYCODE_ALT_RIGHT
//	{{59}	,1	,	,{}},//KEYCODE_SHIFT_LEFT
//	{{60}	,1	,	,{}},//KEYCODE_SHIFT_RIGHT

	{{61}	,1	,1	,{9}},//KEYCODE_TAB
	{{62}	,1	,1	,{32}},//KEYCODE_SPACE
//	{{63}	,1	,	,{}},//KEYCODE_SYM
//	{{64}	,1	,	,{}},//KEYCODE_EXPLORER
//	{{65}	,1	,	,{}},//KEYCODE_ENVELOPE
	{{66}	,1	,1	,{10}},//KEYCODE_ENTER
	{{67}	,1	,1	,{127}},//KEYCODE_DEL

	{{68}	,1	,1	,{'`'}},
	{{69}	,1	,1	,{'-'}},
	{{70}	,1	,1	,{'='}},
	{{71}	,1	,1	,{'['}},
	{{72}	,1	,1	,{']'}},
	{{73}	,1	,1	,{92}},
	{{74}	,1	,1	,{';'}},
	{{75}	,1	,1	,{39}},
	{{76}	,1	,1	,{'/'}},
	{{77}	,1	,1	,{'@'}},
	{{59,68},2	,1	,{'~'}},
	{{59,69},2	,1	,{'_'}},
	{{59,71},2	,1	,{'{'}},
	{{59,72},2	,1	,{'}'}},
	{{59,73},2	,1	,{'|'}},
	{{59,74},2	,1	,{':'}},
	{{59,75},2	,1	,{'"'}},
	{{59,76},2	,1	,{'?'}},

//	{{78}	,1	,	,{}},//KEYCODE_NUM
//	{{79}	,1	,	,{}},//KEYCODE_HEADSETHOOK
//	{{80}	,1	,	,{}},//KEYCODE_FOCUS

	{{81}	,1	,1	,{'+'}},

	{{82}	,1	,5	,{27,91,49,55,126}},//KEYCODE_MENU
//	{{83}	,1	,	,{}},//KEYCODE_NOTIFICATION
	{{84}	,1	,5	,{27,91,49,57,126}},//KEYCODE_SEARCH
//	{{85}	,1	,	,{}},//TAG_LAST_KEYCODE


};

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
