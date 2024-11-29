#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define H 21
#define W 79
#define SFKC 25
#define STC 40
#define OC 10
#define SS 1
/*
                   *
                  ***
                 *****/
                typedef
              struct {int
            x,y;} Snowflake;
          typedef struct {int 
       x,y;} Star;typedef struct
             {int x,y;int
            c;} Ornament;//
         Snowflake sfks[SFKC];
       Star strs[STC]; Ornament
      orns[OC];/***********/char 
    wbuf[H][W][1];int wcbuf[H][W];
  int scbuf[H][W]; char sbuf[H][W][1];
             void init() {
         srand(time(0));for
        (size_t y = 0; y < H;
       y++) {for (size_t x = 0;
       x < W; x++) {wbuf[y][x][0]=
    ' ';}}for (int i = 0; i < SFKC;
   ++i) {sfks[i].x=rand()%W;sfks[i].y
  =rand() % H;}for (int i = 0; i < STC;
++i){strs[i].x=rand()%W;strs[i].y=rand()
             %H;}for (int
             i = 0; i< OC;
             ++i){orns[i].x
           = 35 + rand() % 9;
          orns[i].y = (H - 11)
+rand()%8;orns[i].c=196+rand()%6;}}void rorn(){for (int i=0;i<OC;++i) {if (21<
wcbuf[orns[i].y][orns[i].x]&&wcbuf[orns[i].y][orns[i].x]<118) {wbuf[orns[i].y]
[orns[i].x][0] = 'O';wcbuf[orns[i].y][orns[i].x]=orns[i].c;}}}void rscr() {for
(size_t y = 0; y < H; y++) {for(size_t x=0; x < W; x++){printf("\x1b[38;5;%dm"
"%c" "\x1b[0m",scbuf[y][x],sbuf[y][x][0]);}printf("\n\r");}/*****************/
printf("Merry Christmas!\n\r");}int rax() {return (rand() % (80));}void rsn()
{for (int i = 0; i < SFKC; ++i) {sfks[i].y += SS;if (sfks[i].y > H) {sfks[i].y
/****************************************************************************/
= 0;sfks[i].x = rax();}wbuf[sfks[i].y][sfks[i].x][0]= '.';wcbuf[sfks[i].y]/**/
[sfks[i].x] = 231;}}void rst() {for (int i = 0; i < STC; ++i) {wbuf[strs[i].y]
[strs[i].x][0] = '*';wcbuf[strs[i].y][strs[i].x]=55;}}void rtr() {char lidx[7]
= "@&%*=-.";char lcidx[7] = {46, 118, 76, 40, 34, 28, 22};int w =13;int l=H-14;
          for (size_t t = 2; t
           <5;t++){for(size_t
           i=t-1;i<(2*t);i++)
           {int lSz = (2*i)-1
           ;for(size_t j=40-(
(lSz+1)/2);j<39+((lSz+1)/2);j++){wbuf[l]
  [j][0]=lidx[i-1];wcbuf[l][j] = lcidx
   [i-1];}l++;}}for (size_t i = H-2;i 
    < H; i++) {for (size_t j = 38; j 
     < 41; j++) {wbuf[i][j][0] = '#'
      ;wcbuf[i][j]=52;}}}void rsk() 
       {char lidx[3] = "=-.";char 
        lcidx[3] = {19, 18, 17};
         int cL = 0;for (size_t
  y = 0; y < H; y++){for (size_t x=0;
    x < W; x++) {wbuf[y][x][0]=lidx
     [cL];wcbuf[y][x]=lcidx[cL];}
      cL=y/(H/3);}}void scbufs()
       {for (size_t y=0; y < H; 
         y++){for (size_t x=0; 
           x < W; x++) {sbuf
        [y][x][0]=wbuf[y][x][0];
          scbuf[y][x]=wcbuf[y]
           [x];}}}int main()
             {init();while
                (1==1){
                /*****
                  ***
                   *
                 
                 
*/rsk();rsn();rst();rtr();rorn();scbufs();/****/
/***********************************************
*               Merry Christmas!               *
***********************************************/
printf("\e[1;1H\e[2J");rscr();usleep(1000000);}}