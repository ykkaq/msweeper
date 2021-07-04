#include<stdio.h>
#include<stdlib.h>

void disp(int **map){
  for(int i=0;i<3;i++){
    for(int j=0;j<4;j++){
      printf("%d\n",map[i][j]);
    }
  }
}

int main(){
  puts("Start");
  int **map=(int **)malloc(sizeof(int *)*3);

  puts("Gene");
  for(int i=0;i<3;i++){
    map[i]=(int *)malloc(sizeof(int)*4);
    for(int j=0;j<4;j++){
      map[i][j]=i+j;
    }
  }

  puts("Disp");
  disp(map);
}