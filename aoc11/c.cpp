#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct i{
  bool g = true;
  string e;
};

struct m{
  bool u;
  vector<int> p;
  m(bool a, vector<int> b){
    u = a;
    p = b;
  }
};

const bool operator~(const vector<i>& a){
  bool isg = false;
  bool uns = false;
  for(i b: a){
    if(!b.g){
      bool dan = true;
      for(i c: a){
        if(c.e == b.e && c.g != b.g){
          dan = false;
          break;
        }
      }
      uns = dan | uns;
    } else {
      isg = true;
    }
  }
  return isg & uns;
}

const bool operator~(const vector<vector<i>>& a){
  for(auto b : a) if(~b) return true;
  return false;
}

const void operator+=(int& lhs, const m& rhs){
  lhs += rhs.u?1:-1;
}

i c(string l){
  for(int j = 0; j < l.size(); j++) if(l[j] == '-') l[j] = ' ';
  stringstream s(l);
  i o;
  s >> o.e;
  string t;
  if(s>>t) o.g = false;
  return o;
}

vector<i> p(string l){
  stringstream s(l);
  string t;
  vector<i> o;
  while(s >> t){
    while(t != "a" && s >> t);
    if(s >> t) o.push_back(c(t));
  }
  return o;
}

bool d(vector<vector<i>> a){
  return a[0].size() == 0 && a[1].size() == 0 && a[2].size() == 0;
}

int step(vector<vector<i>> g, int o, int x, int& q);

int move(vector<vector<i>> g, int o, m a, int x, int& q){
  vector<i> aa;
  for(int y = a.p.size()-1; y >= 0; y--){
    aa.push_back(g[x][a.p[y]]);
    g[x].erase(g[x].begin() + a.p[y]);
  }
  x += a;
  if(x > 3 || x < 0) return 10000;
  for(i y : aa) g[x].push_back(y);

  if(~g) return 10000;

  if(d(g)){
    q = o;
    cout << q << endl;
    return o;
  }

  return step(g, o, x, q);
}

int step(vector<vector<i>> g, int o, int x, int& q){
  if(o > q) return 10000;
  vector<int> l;
  for(int j = 0; j < g[x].size(); j++) for(int z = 0; z < 2; z++) l.push_back(move(g, o+1, m((z==1),{j}),x,q));
  for(int j = 0; j < g[x].size() - 1; j++){
    for(int k = j + 1; k < g[x].size(); k++){
      l.push_back(move(g, o+1, m(true,{j,k}), x, q));
    }
  }
  int min = 10000;
  for(int a : l) if(a < min) min = a;
  return min;
}

int main(){
  ifstream f("input");
  string l;
  vector<vector<i>> g;
  while(getline(f,l)) g.push_back(p(l));
  
  int q = 10;

  cout << step(g, 0, 0, q) << endl;

  return 0;
}


