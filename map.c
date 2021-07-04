/*
進捗(5/26)
open関数の再帰によるsegmentation faultを直そう！
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>  
#include<stdbool.h>

typedef struct Area{
  char stat;
  int bom;
  int aro;
}Area;

void disp(Area **arr,int x, int y){

  printf("y\\x|");
  for(int i=1;i<=y;i++){
    printf("%2d ",i-1);
  }
  printf("\n");
  printf("---+");
  for(int i=1;i<=y;i++){
    printf("---",i-1);
  }
  printf("\n");

  for(int i=1;i<=x;i++){
    printf("%2d |",i-1);
    for(int j=1;j<=y;j++){
      printf("%2d ",arr[i][j].aro);
    }
    printf("\n");
  }
  printf("\n");


  printf("x\\y|");
  for(int i=1;i<=y;i++){
    printf("%2d ",i-1);
  }
  printf("\n");
  printf("---+");
  for(int i=1;i<=y;i++){
    printf("---",i-1);
  }

  printf("\n");
  for(int i=1;i<=x;i++){
    printf("%2d |",i-1);
    for(int j=1;j<=y;j++){
      printf("%2d ",arr[i][j].bom);
    }
    printf("\n");
  }
  printf("\n");


  printf("x\\y|");
  for(int i=1;i<=y;i++){
    printf("%2d ",i-1);
  }
  printf("\n");
  printf("---+");
  for(int i=1;i<=y;i++){
    printf("---",i-1);
  }
  printf("\n");
  for(int i=1;i<=x;i++){
    printf("%d  |",i-1);
    for(int j=1;j<=y;j++){
      printf("%2c ",arr[i][j].stat);
    }
    printf("\n");
  }
  printf("\n");

}

void open(Area **map,int beginX, int beginY){
  for(int i=-1;i<=1;i++){
    for(int j=-1;j<=1;j++){
      if(map[beginX+i][beginY+j].bom==0){
        map[beginX+i][beginY+j].stat='0'+map[beginX+i][beginY+j].aro;
      }
      if(map[beginX+i][beginY+j].aro==0 && map[beginX+i][beginY+j].stat!=' '){
        map[beginX+i][beginY+j].stat=' ';

        if(i!=0 || j!=0){
          open(map,beginX+i,beginY+j);
        }
      }
    }
  }
}


int main(){
  srand((unsigned)time(NULL));
 
  int row=-1;  //行yoko
  int col=-1;  //列tate
  int bom=-1;

  do{
  printf("Board no ookisa wo \"tate yoko NumberOfBom\" de suchi wo nyuryoku shitene.\n");
  scanf("%d %d %d",&col,&row,&bom);
  }while(row<1 || col<1 || bom >= row*col);

  /*Generate map*/
  //aroをとるために余分に配列を確保する．
  struct Area** map=(struct Area**)malloc(sizeof(Area*)*(row+2));
  for(int i=0;i<row+2;i++){
    map[i]=(Area*)malloc(sizeof(Area)*(col+2));
    for(int j=0;j<col+2;j++){
      map[i][j].stat='.';
      map[i][j].bom=0;
      map[i][j].aro=0;
    }
  }

  while(bom>0){
    int bomRow=rand()%row+1;
    int bomCol=rand()%col+1;
    if(map[bomRow][bomCol].bom==0){
      map[bomRow][bomCol].bom=1;
      bom--;
    }
  }

  /*Calcurate Around Sum*/
  for(int i=1;i<=row;i++){
    for(int j=1;j<=col;j++){
      for(int k=-1;k<=1;k++){
        for(int l=-1;l<=1;l++){
          map[i][j].aro+=map[i+k][j+l].bom;
        }
      }
    }
  }


  /*Open the box!*/
  bool finish=false;

  while(!finish){
    char buffer[64];

    disp(map,row,col);

    int inX,inY;
    char com,dum;
    printf("[x] [y] [o:open, f:flag] >> ");
    scanf("%d %d %c%c",&inX,&inY,&com,&dum);
    //fgets()
    
    
    while(inX<0 || inX>=row || inY<0 || inY>=col){
      puts("pls input continue.");
      printf("[x] [y] [o:open, f:flag] >> ");
      scanf("%d %d %c%c",&inX,&inY,&com,&dum);
      printf("\n"); 
    }
    inX++;inY++;

    if(com=='o'){
      //openなら
      if(map[inX][inY].bom==0 && map[inX][inY].stat=='.'){
        //爆弾でないとき
        map[inX][inY].stat='0'+map[inX][inY].aro;
        //open(map,inX,inY);

      }else if(map[inX][inY].bom==1 && map[inX][inY].stat=='.'){
        //爆弾かつ開かれていないとき
        puts("\nGame Over...");
        finish=true;
      }
    }else if(com=='f'){
      //flagなら
      if(map[inX][inY].stat=='.'){
        //フラグが置かれていないとき
        map[inX][inY].stat='f';
      }else if(map[inX][inY].stat=='f'){
        //フラグが置かれているとき
        map[inX][inY].stat='.';
      }
    }
    //finish=true;
  }
}