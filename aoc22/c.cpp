#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>

using namespace std;

struct c{
  int x;
  int y;
  c(){}
  c(int a, int b){
    x = a;
    y = b;
  }
};

struct d{
  int size;
  int used;
  int avail;
  bool goal = false;
};

const bool operator<(const d& l, const d& r){
  return (l.used != 0) && (l.used <= r.avail);
}

c& operator++(c& l, int){
  l.y++;
  if(l.y > 24){
    l.y = 0;
    l.x++;
  }
  return l;
}

const c operator+(const c& l, const c& r){
  c o;
  o.x = l.x + r.x;
  o.y = l.y + r.y;
  return o;
}

const bool operator<(const c& l, const c& r){
  if(l.x == r.x) return l.y < r.y;
  return l.x < r.x;
}

const bool operator==(const c& l, const c& r){
  return l.x == r.x && l.y == r.y;
}

const bool operator!=(const c& l, const c& r){
  return !(l == r);
}

const bool operator<=(const c& l, const c& r){
  return l < r || l == r;
}

const bool operator<(const vector<vector<d>>& a, const vector<vector<d>>& b){
  for(c i = c(0,0); i <= c(38,24); i++) if(a[i.x][i.y].used != b[i.x][i.y].used) return a[i.x][i.y].used < b[i.x][i.y].used;
  return false;
}

const bool operator!(const set<vector<vector<d>>>& a){
  for(auto x : a) if(x[0][0].goal) return false;
  return true;
}

pair<c,d> p(string l){
  for(int i = 0; i < l.size(); i++) if(l[i] == '-' || l[i] == 'x' || l[i] == 'y' || l[i] == 'T' || l[i] == '%') l[i] = ' ';
  d o;
  c a;
  string t;
  stringstream s(l);
  s >> t >> a.x >> a.y >> o.size >> o.used >> o.avail;
  return pair<c,d>(a,o);
}

int totell(vector<vector<d>> in){
  int o = 0;
  for(c i = c(0,0); i <= c(38,24); i++) for(c j = c(0,0); j <= c(38,24); j++) if(i != j && in[i.x][i.y] < in[j.x][j.y]) o++;
  return o;
}

vector<pair<c,c>> ell(vector<vector<d>> in){
  vector<pair<c,c>> o;
  for(c i = c(0,0); i <= c(38,24); i++){
    for(c j : {c(0,1), c(0,-1), c(1,0), c(-1,0)}){
      c t = i+j;
      if(t.x < 0 || t.x > 38 || t.y < 0 || t.y > 24) continue;
      if(in[i.x][i.y] < in[t.x][t.y]) o.push_back( pair<c,c>(i,t));
    }
  }
  return o;
}

vector<vector<d>> move(vector<vector<d>> in, pair<c,c> m){
  in[m.second.x][m.second.y].used += in[m.first.x][m.first.y].used;
  in[m.second.x][m.second.y].avail = in[m.second.x][m.second.y].size - in[m.second.x][m.second.y].used;
  in[m.first.x][m.first.y].used = 0;
  in[m.first.x][m.first.y].avail = in[m.first.x][m.first.y].size;
  in[m.second.x][m.second.y].goal = in[m.first.x][m.first.y].goal;
  in[m.first.x][m.first.y].goal = false;
  return in;
}

set<vector<vector<d>>> step(set<vector<vector<d>>> in){
  set<vector<vector<d>>> o;
  for(auto a : in){
    vector<pair<c,c>> x = ell(a);
    for(auto b : x){
      o.insert(move(a,b));
    }
  }
  return o;
}

int count(vector<vector<d>> nodes){
  set<vector<vector<d>>> nods;
  nods.insert(nodes);
  int o = 0;
  while(!nods){
    nods = step(nods);
    o++;
    cout << o << endl;
  }
  return o;
}

int main(){
  ifstream f("input");
  string l;
  vector<vector<d>> nodes;
  getline(f,l);
  getline(f,l);
  vector<d> line;
  while(getline(f,l)){
    pair<c,d> t = p(l);
    line.push_back(t.second);
    if(t.first.y == 24){
      nodes.push_back(line);
      line.clear();
    }
  }
  nodes[38][0].goal = true;

  cout << totell(nodes) << endl;

  cout << count(nodes) << endl;

  return 0;
}
