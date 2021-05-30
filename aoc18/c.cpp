#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

string n(string l){
  string o;
  o += (l[1] == '.')?'.':'^';
  for(int i = 1; i < l.size() - 1; i++) o += (l[i-1] == l[i+1])?'.':'^';
  o += (l[l.size()-2] == '.')?'.':'^';
  return o;
}

int c(vector<string> a){
  int o = 0;
  for(string x : a) o += count(x.begin(), x.end(), '.');
  return o;
}

int main(){
  ifstream f("input");
  string l;
  vector<string> r;

  getline(f,l);

  r.push_back(l);
  for(int i = 1; i < 40; i++) r.push_back(n(r.back()));

  cout << c(r) << endl;

  for(int i = 40; i < 400000; i++) r.push_back(n(r.back()));

  cout << c(r) << endl;

  return 0;
}

  
