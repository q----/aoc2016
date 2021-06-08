#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

//0 then 1
int step(int a){
  if(a % 2 == 1) return -1;
  int o = a/2;
  if(o % 2 == 0) return -1;
  return o/2;
}

int main(){
  for(int a = 1; a < 100; a++){
    int x = a;
    while(x > 0){
      x = step(x);
    }
    if(x == 0) cout << a << endl;
  }

  return 0;
}
