#include<vector>
#include<iostream>

using namespace std;

int main(){
  vector<int> a(10);
  for(int i=0;i<10;i++){
    a[i]=i;
  }

  for(auto v:a){
    cout << v << end;
  }
}