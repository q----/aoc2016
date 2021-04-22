#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int operator!(const string& i){
  stringstream s(i);
  int out;
  s >> out;
  return out;
}

void operator+=(pair<int,long long int>& a, const pair<int,long long int>& b){
  a.first += b.first;
  a.second += b.second;
}

pair<int,long long int> c(string l){
  int o = 0;
  long long int n = 0;
  for(int i = 0; i < l.size(); i++){
    if(l[i] == '('){
      string x = "";
      while(l[++i] != 'x') x += l[i];
      int g = !x;
      x = "";
      while(l[++i] != ')') x += l[i];
      int h = !x;
      o += g * h;
      n += h * c(l.substr(i+1, g)).second;
      i += g;
      continue;
    }
    o++;
    n++;
  }
  return pair<int,long long int>(o,n);
}

int main(){
  ifstream f("input");
  string l;

  pair<int,long long int> o (0,0);
  while(getline(f,l)) o+= c(l);
  cout << o.first << endl;
  cout << o.second << endl;

  return 0;
}

