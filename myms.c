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
void generateMap(struct Area **map, int tate, int yoko, int bomb);

void disp(Area **arr,int x, int y){
  // disp aroundBom
  for(int i=0)
}

int main(){
  srand((unsigned)time(NULL));

  int tate;
  int yoko;
  int bomb;
  struct Area** map;

  setStates(&tate, &yoko, &bomb);
  printf("%d %d %d\n",tate,yoko,bomb);

  generateMap(map,tate,yoko,bomb);
  disp(map,tate,yoko);

  return 0;
}


void setStates(int *tate, int *yoko, int *bomb){
  printf("Input Board Size and Number of Bomb.\n");
  printf("[tate] [yoko] [Number of Bomb] >> ");
  scanf("%d %d %d", tate, yoko, bomb);
}

void generateMap(struct Area **map, int tate, int yoko, int bomb){
  /*geneMap*/
  map=(struct Area**)malloc(sizeof(Area*)*(yoko+2));
  for(int i=0;i<yoko+2;i++){
    map[i]=(struct Area*)malloc(sizeof(Area)*(tate+2));
    for(int j=0;j<tate+2;j++){
        map[i][j].stat='.';
        map[i][j].setBom=false;
        map[i][j].aroundBom=0;
    }
  }

  if(bomb >= tate*yoko){
    bomb = tate*yoko-1;
  }

  /*Set Bomb in map*/
  while(bomb>0){
    int bomRow=rand()%tate+1;
    int bomCol=rand()%yoko+1;
    if(!map[bomRow][bomCol].setBom){
      map[bomRow][bomCol].setBom=true;
      bomb--;
    }
  }

  /*Calcurate Around Sum*/
  for(int i=1;i<=yoko;i++){
    for(int j=1;j<=tate;j++){
      for(int k=-1;k<=1;k++){
        for(int l=-1;l<=1;l++){
          map[i][j].aroundBom+=map[i+k][j+l].setBom;
        }
      }
    }
  }

}