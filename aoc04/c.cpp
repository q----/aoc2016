#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

struct r{
  vector<string> n;
  int i;
  string c;
};

r p(string l){
  for(int i = 0; i < l.size(); i++) if(l[i] == '-' || l[i] == '[' || l[i] == ']') l[i] = ' ';
  r o;
  {
    stringstream s(l);
    while(s >> o.c) o.n.push_back(o.c);
  }
  stringstream s(o.n[o.n.size() - 2]);
  s >> o.i;
  o.n.resize(o.n.size()-2);
  return o;
}

string q(string l, int x){
  x %= 26;
  for(int i = 0; i < l.size(); i++){
    l[i] += x;
    if(l[i] > 'z') l[i] -= 26;
  }
  return l;
}

bool operator!(r i){
  map<char, int> x;
  for(string s : i.n) for(char c : s) x[c]++;
  int max = 0;
  for(auto f : x) if(f.second > max) max = f.second;
  string c = "";
  while(c.size() < 5){
    for(char f = 'a'; f <= 'z'; f++) if(x[f] == max) c += f;
    max--;
  }
  return (i.c == c.substr(0,5));
}

int main(){
  ifstream f("input");
  string l;

  int o = 0;
  int g = 0;
  while(getline(f,l)){
    r t = p(l);
    if(!t){
      o+= t.i;
      if(q(t.n[0],t.i) == "northpole"){
	g = t.i;
      }
    }
  }

  cout << o << endl;
  cout << g << endl;

  return 0;
}
