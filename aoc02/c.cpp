#include<iostream>
#include<fstream>

using namespace std;

struct key{
  int x = 1;
  int y = 1;
};

struct key2{
  int x = -2;
  int y = 0;
};

int f(int x){
  if(x < 0) return -x;
  return x;
}

int operator-(const key2& a){
  return f(a.x) + f(a.y);
}

string operator!(const key& a){
  return to_string(1 + 3 * a.x + a.y);
}

string operator!(const key2& a){
  string d = "0123456789ABCD";
  int x;
  if(f(a.y) == 2){
    x = (a.y > 0)?13:1;
  } else if (f(a.y) == 1){
    x = a.x + ((a.y > 0)?11:3);
  } else {
    x = a.x + 7;
  }
  return d.substr(x,1);
}

void operator+=(key& a, const char& b){
  if(b == 'U'){
    a.x = (a.x > 0)? a.x - 1: 0;
  } else if (b == 'D'){
    a.x = (a.x < 2)? a.x + 1: 2;
  } else if (b == 'L'){
    a.y = (a.y > 0)? a.y - 1: 0;
  } else {
    a.y = (a.y < 2)? a.y + 1: 2;
  }
}

void operator+=(key2& a, const char& b){
  if(b == 'U'){
    a.y--;
    if(-a > 2) a.y++;
  } else if (b == 'D'){
    a.y++;
    if(-a > 2) a.y--;
  } else if (b == 'L'){
    a.x--;
    if(-a > 2) a.x++;
  } else {
    a.x++;
    if(-a > 2) a.x--;
  }
}

template <class T>
string p(T& a, string l){
  for(char c : l) a += c;
  return !a;
}

int main(){
  ifstream f("input");
  string l;
  string o;
  string o2;

  key a;
  key2 b;
  while(getline(f,l)){
    o += p(a,l);
    o2 += p(b,l);
  }

  cout << o << endl;
  cout << o2 << endl;

  return 0;
}
