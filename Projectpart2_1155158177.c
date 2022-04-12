/**
 * ENGG1110 Problem Solving by Programming
 *
 * Course Project
 *
 * I declare that the project here submitted is original
 * except for source material explicitly acknowledged,
 * and that the same or closely related material has not been
 * previously submitted for another course.
 * I also acknowledge that I am aware of University policy and
 * regulations on honesty in academic work, and of the disciplinary
 * guidelines and procedures applicable to breaches of such
 * policy and regulations, as contained in the website.
 *
 * University Guideline on Academic Honesty:
 * https://www.cuhk.edu.hk/policy/academichonesty/
 *
 * Student Name : Li Tsz Kin
 * Student ID : 1155158177
 * Class/Section : ENGG1110A
 * Date : 17/12/2020
 */


#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

#define pi acos(-1)

void nogd(){
    printf("Invaild input, please enter again.\n");
}

void delay(int ms){
    long pause;
    clock_t now,then;

    pause = ms*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while((now-then) < pause){
        now = clock();
    };
}

int checkmark(int gameboard[3][3],int mark){
    int i = (mark-1)/3;
    int j = mark-1-i*3;
    if(gameboard[i][j] == 0){
        return 1;
    };
    return 0;
}

void printboard(int gameboard[3][3]){
    printf("=========\n");
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(gameboard[i][j] == 0){
                printf("|%d|",(i*3+j+1));
            }else if(gameboard[i][j] == 1){
                printf("|%c|",'O');
            }else if(gameboard[i][j] == 2){
                printf("|%c|",'X');
            };
        };
        printf("\n");
    };
    printf("=========\n");
}

void printmark(int gameboard[3][3],int mark,int currentplayer){
    int i = (mark-1)/3;
    int j = mark -1 - i*3;
    gameboard[i][j] = currentplayer;
}

int checkwin(int gameboard[3][3],int mark){
    int count0,count1,count2,count3;
    count0 = count1 = count2 = count3 = 0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(gameboard[i][j] == mark){
                count0++;
            };
            if(gameboard[j][i] == mark){
                count1++;
            };
            if(count0 == 3 || count1 == 3){
                return 1;
            };
        };
        count0 = count1 = 0;
        if(gameboard[i][i] == mark){
            count2++;
        };
        if(gameboard[i][abs(2-i)] == mark){
            count3++;
        };
        if(count2 == 3 || count3 == 3){
            return 1;
        };
    };
    return 0;
}

int checkdraw(int gameboard[3][3]){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(gameboard[i][j] == 0){
                return i*3+j+1;
            };
        };
    };
    return -1;
}

int scanwin(int gameboard[3][3],int player){
    int count1,count2,count3,count4;
    count1=count2=count3=count4=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(gameboard[i][j] == player){
                count1++;
                if(count1 == 2){
                    for(int k=0;k<3;k++){
                        int mark=i*3+k+1;
                        if(checkmark(gameboard,mark)){
                            return mark;
                        };
                    };
                };
            };
            if(gameboard[j][i] == player){
                count2++;
                if(count2 == 2){
                    for(int k=0;k<3;k++){
                        int mark=k*3+i+1;
                        if(checkmark(gameboard,mark)){
                            return mark;
                        };
                    };
                };
            };
        };
        count1=count2=0;
        if(gameboard[i][i] == player){
            count3++;
            if(count3 == 2){
                for(int k=0;k<3;k++){
                    int mark=i*3+i+1;
                    if(checkmark(gameboard,mark)){
                        return mark;
                    };
                };
            };
        };
        if(gameboard[i][2-i] == player){
            count4++;
            if(count4 == 2){
                for(int k=0;k<3;k++){
                    int mark=i*3+2-i+1;
                    if(checkmark(gameboard,mark)){
                        return mark;
                    };
                };
            };
        };
    };
    return -1;
}

int ticailogic(int gameboard[3][3], int aiplayer){
    int log[5] = {5,1,3,7,9};
    int mark;
    // 1
    mark = scanwin(gameboard,aiplayer);
    if(mark > 0){
        return mark;
    }else{
        // 2
        mark = scanwin(gameboard,3-aiplayer);
        if(mark > 0){
            return mark;
        };
    };
    // 3
    for(int i=0;i<5;i++){
        if(checkmark(gameboard,log[i])){
            return log[i];
        };
    };
    // 4
    return checkdraw(gameboard);
}

int ailose(int gameboard[3][3]){
    srand(time(0));
    while(1){
        int mark = rand()%9+1;
        // printf("%d,",mark);
        if(checkmark(gameboard,mark)){
            return mark;
        };
    };
}

void cleanstin(){
    int tmp;
    while(1){
        tmp = getchar();
        if(tmp == EOF || tmp == '\n'){
            break;
        };
    };
}

int getinput(int low,int up){
    int mark,check;
    double tmp;
    while(1){
        check = scanf("%lf",&tmp);
        mark = (int)tmp;
        if(tmp == mark){
            if(check != 1){
                cleanstin();
            }else if(check == 1){
                if(mark >= low && mark <= up){
                    cleanstin();
                    return mark;
                };
            };
        };
        nogd();
        cleanstin();
    };
}

int natailogic(int gameboard[3][3], int lastmark){
    int bad[10] = {0};
    // 1
    if(checkmark(gameboard,5)){
        return 5;
    };
    // 2
    if(lastmark%2 == 0){
        for(int i=1;i<5;i++){
            bad[2*i]++;
        };
    };
    // 3
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(i*3+j+1 == lastmark){
                for(int k=0;k<3;k++){
                    bad[i*3+k+1]++;
                    bad[k*3+j+1]++;
                };
            };
            // 4
            if(gameboard[i][j] != 0){
                bad[abs(10-(i*3+j+1))]++;
                bad[i*3+j+1]++;
            };
        };
    };
    // 5
    for(int i=1;i<10;i++){
        if(bad[i] == 0){
            return i;
        };
    };
    // 6
    return ailose(gameboard);
}

int getmark(int gameboard[3][3], int numofplayer, int round, int aiplayer,int win,int mode){
    int mark;
    int currentplayer = 2-round%2;
    if(numofplayer == 1){
        if(currentplayer == aiplayer){
            // win = 1;
            // win = 0;
            if(win){
                if(mode == -1){
                    mark = ticailogic(gameboard,aiplayer);
                }else if(mode >= 0){
                    // printf("1");
                    mark = natailogic(gameboard,mode);
                };
            }else if(!win){
                mark = ailose(gameboard);
            };
            printf("Computer placed the mark: %d.\n",mark);
        }else if(2-round%2 != aiplayer){
            printf("Player %d, please place your mark.\n",currentplayer);
            while(1){
                mark = getinput(1,9);
                if(checkmark(gameboard,mark)){
                    break;
                }else{
                    nogd();
                };
            };
        };
    }else if(numofplayer == 2){
        printf("Player %d, please place your mark.\n",currentplayer);
        while(1){
            int tmp = getinput(1,9);
            if(checkmark(gameboard,tmp)){
                mark = tmp;
                break;
            }else{
                nogd();
            };
        };
    };
    return mark;
}

void gametic(){
    int numofplayer = 2;
    int gameboard[3][3] = {0};
    int aiplayer = -1;
    int round = 1;
    int win;
    int undoc[2] = {1,1};
    int lastmark = 0;
    srand(time(0));
    win = rand()%2;
    // printf("%d win\n",win);
    printf("How many people are playing?(1 or 2)\n");
    numofplayer = getinput(1,2);
    if(numofplayer == 1){
        printf("Which Player will the computer be?(Player 1 or Player 2)\n");
        aiplayer = getinput(1,2);
    };
    printf("Starting...\n");
    delay(500);
    printboard(gameboard);
    delay(500);
    while(1){
        // printf("%d\n",round);
        int mark = getmark(gameboard,numofplayer,round,aiplayer,win,-1);
        lastmark = mark;
        printmark(gameboard,mark,(2-round%2));
        printboard(gameboard);
        delay(600);
        if(checkwin(gameboard,(2-round%2)) == 1){
            if(numofplayer == 2){
                printf("Player %d wins!\n",(2-round%2));
                break;
            }else if(2-round%2 == aiplayer){
                printf("Computer wins!\n");
                break;
            };
        };
        if(checkdraw(gameboard) == -1){
            printf("Draw game!\n");
            break;
        };
        round++;
    };
};


void gamenat(){
    int numofplayer = 2;
    int gameboard[3][3] = {0};
    int lastmark = 0;
    int aiplayer = 1;
    int round = 1;
    int win;
    srand(time(0));
    win = rand()%2;
    // printf("%d win",win);
    printf("How many people are playing? (1 or 2)\n");
    numofplayer = getinput(1,2);
    if(numofplayer == 1){
        printf("Which player will the computer be? (1 or 2)\n");
        aiplayer = getinput(1,2);
    };
    printf("Starting...\n");
    delay(500);
    printboard(gameboard);
    delay(500);
    while(1){
        int mark = getmark(gameboard,numofplayer,round,aiplayer,win,lastmark);
        lastmark = mark;
        printmark(gameboard,mark,2);
        printboard(gameboard);
        delay(500);
        if(checkwin(gameboard,2) == 1){
            int x = pow(sin(round*pi/2),2) + 1;
            if(numofplayer == 2 || 2-round%2 == aiplayer){
                printf("Player %d wins!\n",x);
                break;
            }else if(x == aiplayer){
                printf("Computer wins!\n");
                break;
            };
        };
        round++;
    }
}

int main(){
    int gamemode = 1;
    int again = 0;
    while(1){
        printf("Please select gamemode (1:tic-tac-toe  2:notakto)\n");
        gamemode = getinput(1,2);
        if(gamemode == 1){
            gametic();
        }else if(gamemode == 2){
            gamenat();
        };
        printf("Again?(1:Yes, 0:No)\n");
        again = getinput(0,1);
        again = 1;
        if(again == 0){
            break;
        };
    };
}
