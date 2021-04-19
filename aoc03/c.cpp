#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct t{
  int a;
  int b;
  int c;
  t(){}
  t(int x, int y, int z){
    a = x;
    b = y;
    c = z;
  }
};

bool operator!(const t& a){
  return ((a.a + a.b > a.c) && (a.b + a.c > a.a) && (a.c + a.a > a.b));
}

t p(string l){
  t o;
  stringstream s(l);
  s >> o.a >> o.b >> o.c;
  return o;
}

int main(){
  ifstream f("input");
  string l;

  int x = 0;
  int y = 0;
  vector<t> a;
  while(getline(f,l)){
    if(!p(l)) x++;
    a.push_back(p(l));
    if(a.size() == 3){
      if(!t(a[0].a,a[1].a,a[2].a)) y++;
      if(!t(a[0].b,a[1].b,a[2].b)) y++;
      if(!t(a[0].c,a[1].c,a[2].c)) y++;
      a.clear();
    }
  }

  cout << x << endl;
  cout << y << endl;

  return 0;
}
