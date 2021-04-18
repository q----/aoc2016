#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

struct key{
  int x = 1;
  int y = 1;
};

string operator!(const key& a){
  return to_string(1 + 3 * a.x + a.y);
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

string p(key& a, string l){
  for(char c : l) a += c;
  return !a;
}

int main(){
  ifstream f("input");
  string l;
  string o;

  key a;
  while(getline(f,l)) o += p(a,l);

  cout << o << endl;

  return 0;
}
