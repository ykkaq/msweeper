//map[y][x] = map[tate][yoko]
/*
arr[2][3]={{1,2,3},
           {4,5,6}};
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>  
#include<stdbool.h>

typedef struct Area{
  char stat;  //表示されるゲーム画面
  bool setBom;  //マスに爆弾があるか．
  int aroundBom;  //周囲の爆弾数
}Area;

void setStates(int *tate, int *yoko, int *bomb);  //ステージの大きさと爆弾数を設定
void generateMap(Area **map, int tate, int yoko, int bomb);
void inputOpenPoint(int *inTate, int *inYoko, char *op, int tate, int yoko);
bool changeMap(Area **map, int inputX, int inputY, char op, int tate, int yoko);
bool checkClear(Area **map, int tate, int yoko, int bomb);
void autoMapOpen(Area **map,int changeX, int changeY, int tate, int yoko);

void disp_aroundBom(Area **map,int tate, int yoko);
void disp_Bom(Area **map,int tate, int yoko);
void disp_Gamemap(Area **map,int tate, int yoko);


int main(){
  srand((unsigned)time(NULL));

  struct Area** map;
  int tate, yoko, bomb;
  char op;  //Map操作
  bool finFlag;
  time_t startTime,endTime;

  setStates(&tate, &yoko, &bomb);
  printf("%d %d %d\n",tate,yoko,bomb);

  map = (struct Area**)malloc(sizeof(Area*)*(tate+2));

  generateMap(map,tate,yoko,bomb);
  printf("%d\n",map[0][0].aroundBom);

  finFlag = false;
  startTime = time(NULL);
  while(!finFlag){
    int changeX = 0, changeY = 0;
    disp_aroundBom(map,tate,yoko);
    disp_Bom(map,tate,yoko);
    disp_Gamemap(map,tate,yoko);
    inputOpenPoint(&changeX, &changeY, &op, tate, yoko);
    finFlag = changeMap(map,changeX,changeY,op,tate,yoko) + checkClear(map, tate, yoko, bomb);
  }
  endTime = time(NULL);

  disp_Gamemap(map,tate,yoko);
  printf("Time is %lds.\n",endTime - startTime);

  return 0;
}


void disp_aroundBom(Area **map,int tate, int yoko){
  // disp aroundBom
  puts(">aroundBom map");
  printf("y\\x|");
  for(int i=1;i<=yoko;i++) printf("%2d ",i-1);
  printf("\n---+");
  for(int i=1;i<=yoko;i++) printf("---");
  printf("\n");
  for(int i=1;i<=tate;i++){
    printf("%2d |",i-1);
    for(int j=1;j<=yoko;j++)  printf("%2d ",map[i][j].aroundBom);
    printf("\n");
  }
  printf("\n");
}

void disp_Bom(Area **map,int tate, int yoko){
  // disp Bom
  puts(">Bom map");
  printf("y\\x|");
  for(int i=1;i<=yoko;i++) printf("%2d ",i-1);
  printf("\n---+");
  for(int i=1;i<=yoko;i++) printf("---");
  printf("\n");
  for(int i=1;i<=tate;i++){
    printf("%2d |",i-1);
    for(int j=1;j<=yoko;j++){
      if(map[i][j].setBom){
        printf("M  ");
      }else{
        printf("   ");//printf("%2d ",0);
      }
    }
    printf("\n");
  }
  printf("\n");
}

void disp_Gamemap(Area **map,int tate, int yoko){
  // disp GameMap
  printf("y\\x|");
  for(int i=1;i<=yoko;i++) printf("%2d ",i-1);
  printf("\n---+");
  for(int i=1;i<=yoko;i++) printf("---");
  printf("\n");
  for(int i=1;i<=tate;i++){
    printf("%2d |",i-1);
    for(int j=1;j<=yoko;j++)  printf("%2c ",map[i][j].stat);
    printf("\n");
  }
  printf("\n");
}


void setStates(int *tate, int *yoko, int *bomb){
  while(1){
    printf("Input Board Size and Number of Bomb.\n");
    printf("[tate] [yoko] [Number of Bomb] >> ");
    scanf("%d %d %d", tate, yoko, bomb);
    if(*tate<=1 || *yoko<=1 || bomb<=0){
      puts("Input other num.");
    }else{
      return;
    }
  }
}

void generateMap(Area **map, int tate, int yoko, int bomb){ 
  puts("Generate map.");
  /*geneMap*/
  for(int i=0;i<tate+2;i++){
    map[i]=(struct Area*)malloc(sizeof(Area)*(yoko+2));
    for(int j=0;j<yoko+2;j++){
        map[i][j].stat='.';
        map[i][j].setBom=false;
        map[i][j].aroundBom=0;
    }
  }

  if(bomb >= tate*yoko){
    bomb = tate*yoko-1;
  }
  puts("Clear map array");

  /*Set Bomb in map*/
  while(bomb>0){
    int bomtate=rand()%tate +1;
    int bomyoko=rand()%yoko +1;
    if(!map[bomtate][bomyoko].setBom){
      map[bomtate][bomyoko].setBom=true;
      bomb--;
    }
  }
  puts("Complate set bomb.");

  /*Calcurate Around Sum*/
  for(int i=1;i<=tate;i++){
    for(int j=1;j<=yoko;j++){
      for(int k=-1;k<=1;k++){
        for(int l=-1;l<=1;l++){
          map[i][j].aroundBom+=map[i+k][j+l].setBom;
        }
      }
    }
  }
  puts("Complate Generated map.");
}

void inputOpenPoint(int *inputX, int *inputY, char *op, int tate, int yoko){
  char dum;
  do{
    printf("[x] [y] [o:open, f:flag, ?:Dont know] >> ");
    scanf("%d %d %c%c",inputX,inputY,op,&dum);
  }while(*inputX < 0 || yoko < *inputX || *inputY < 0 || tate < *inputY);
  *inputX=*inputX+1;
  *inputY=*inputY+1;
}

bool changeMap(Area **map, int inputX, int inputY, char op, int tate, int yoko){
  switch(op){
    //openのとき
    case 'o':
      //爆弾なら 
      if(map[inputY][inputX].setBom && map[inputY][inputX].stat != '?'){
        puts("\nGame Over...");
        return true;
      }else if(!map[inputY][inputX].setBom && map[inputY][inputX].stat != '?'){
        //爆弾でないとき
        //map[inputY][inputX].stat = ' ';
        autoMapOpen(map, inputX, inputY, tate, yoko);
      }
      break;
    case 'f':
      if(map[inputY][inputX].stat == '.'){
        map[inputY][inputX].stat = 'F';
      }else if(map[inputY][inputX].stat == 'F'){
        map[inputY][inputX].stat = '.';
      }
      break;
    case '?':
      if(map[inputY][inputX].stat == '.'){
        map[inputY][inputX].stat = '?';
      }else if(map[inputY][inputX].stat == '?'){
        map[inputY][inputX].stat = '.';
      }
  }
  return false;
}

bool checkClear(Area **map, int tate, int yoko, int bomb){
  int dotCount=0;
  for(int i=1;i<=tate;i++){
    for(int j=1;j<=yoko;j++){
      if(map[i][j].stat == '.'){
        dotCount++;
      }
    }
  }

  if(dotCount == bomb){
    puts("Game Clear!");
    return true;
  }else{
    return false;
  }
}

void autoMapOpen(Area **map,int changeX, int changeY, int tate, int yoko){
  //マップの外or爆弾なら，関数を終了させる．
  if(changeX<=0 || changeX>tate || changeY<0 || changeY>yoko || map[changeY][changeX].setBom || map[changeY][changeX].stat!='.'){
    return;
  }

  if(map[changeY][changeX].aroundBom == 0){
    map[changeY][changeX].stat=' ';
  }else{
    map[changeY][changeX].stat = '0' + map[changeY][changeX].aroundBom;
  }

  for(int i=changeX-1;i<=changeX+1;i++){
    for(int j=changeY-1;j<=changeY+1;j++){
      if(map[changeY][changeX].aroundBom==0){
        autoMapOpen(map, i, j, tate, yoko);
      }
    }
  }
}

    
