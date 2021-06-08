#include <iostream>

using namespace std;

int next(int a){
  return 4 * a + 2;
}

int main(){
  int a = 2;
  while(a <= 7 * 362) a = next(a);

  cout << a - (7 * 362) << endl;

  return 0;
}
