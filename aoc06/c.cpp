#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

char max(map<char,int>& m){
  int a = 0;
  char b;
  for(auto f: m) if(a < f.second) {
    a = f.second;
    b = f.first;
  }
  return b;
}

char min(map<char,int>& m){
  int a = 1000;
  char b;
  for(auto f: m) if(a > f.second) {
    a = f.second;
    b = f.first;
  }
  return b;
}



int main(){
  ifstream f("input");
  string l;

  vector<map<char,int>> v;
  for(int i = 0; i < 8; i++){
    map<char,int> m;
    v.push_back(m);
  }

  while(getline(f,l)) for(int i = 0; i < 8; i++) v[i][l[i]]++;

  for(int i = 0; i < 8; i++) cout << max(v[i]);
  cout << endl;

  for(int i = 0; i < 8; i++) cout << min(v[i]);
  cout << endl;

  return 0;
}
