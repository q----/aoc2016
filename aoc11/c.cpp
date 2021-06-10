#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>
#include <map>

using namespace std;

struct i{
  bool g = true;
  char e;
  i(){}
  i(bool x, string q){
    g = x;
    e = q[3];
  }
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

const bool operator<(const i& a, const i& b){
  if(a.e == b.e) return a.g;
  return a.e < b.e;
}

const bool operator==(const i&a, const i& b){
  return a.e == b.e && a.g == b.g;
}

const bool operator<(const pair<int,int>& a, const pair<int,int>& b){
  if(a.first == b.first) return a.second < b.second;
  return a.first < b.first;
}

const bool operator==(const pair<int,int>& a, const pair<int,int>& b){
  return (a.first == b.first) && (a.second == b.second);
}

const bool operator<(const vector<vector<i>>& a, const vector<vector<i>>& b){
  map<char,pair<int,int>> ah;
  map<char,pair<int,int>> bah;
  for(int q = 0; q < a.size(); q++){
    for(i h : a[q]){
      if(h.g) ah[h.e].second = q;
      if(!h.g) ah[h.e].first = q;
    }
  }
  for(int q = 0; q < b.size(); q++){
    for(i h : b[q]){
      if(h.g) bah[h.e].second = q;
      if(!h.g) bah[h.e].first = q;
    }
  }
  vector<pair<int,int>> aht;
  vector<pair<int,int>> baht;
  for(auto mah: ah) aht.push_back(mah.second);
  for(auto mah: bah) baht.push_back(mah.second);
  sort(aht.begin(), aht.end());
  sort(baht.begin(), baht.end());
  for(int z = 0; z < aht.size(); z++) if(aht[z] != baht[z]) return aht[z] < baht[z];
  return false;
}

const bool operator<(const pair<int,vector<vector<i>>>& a, const pair<int,vector<vector<i>>>& b){
  if(a.first != b.first) return a.first < b.first;
  return a.second < b.second;
}

i c(string l){
  for(int j = 0; j < l.size(); j++) if(l[j] == '-') l[j] = ' ';
  stringstream s(l);
  i o;
  string t;
  s >> t;
  o.e = t[3];
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

bool done(set<pair<int,vector<vector<i>>>> a){
  for(auto b : a) if(d(b.second)) return true;
  return false;
}

pair<int,vector<vector<i>>> move(pair<int,vector<vector<i>>> a, m b){
  vector<i> aa;
  for(int y = b.p.size() - 1; y >= 0; y--){
    aa.push_back(a.second[a.first][b.p[y]]);
    a.second[a.first].erase(a.second[a.first].begin() + b.p[y]);
  }
  a.first += b;
  if(a.first > 3) a.first = 3;
  if(a.first < 0) a.first = 0;
  for(i y : aa) a.second[a.first].push_back(y);
  return a;
}

set<pair<int,vector<vector<i>>>> step(set<pair<int,vector<vector<i>>>> a, set<pair<int,vector<vector<i>>>>& ooo){
  set<pair<int,vector<vector<i>>>> o;
  for(auto b : a){
    for(int j = 0; j < b.second[b.first].size(); j++){
      for(int z = 0; z < 2; z++){
        pair<int,vector<vector<i>>> q = move(b, m((z==1),{j}));
        if(!ooo.insert(q).second || ~q.second) continue;
        o.insert(q);
      }
    }
    for(int j = 0; j < b.second[b.first].size()-1; j++){
      for(int k = j+1; k < b.second[b.first].size(); k++){
        pair<int,vector<vector<i>>> q = move(b, m(true,{j,k}));
        if(!ooo.insert(q).second || ~q.second) continue;
        o.insert(q);
      }
    }
  }
  return o;
}

int go(set<pair<int,vector<vector<i>>>> oooo){
  set<pair<int,vector<vector<i>>>> ooo;
  int count = 0;
  while(!done(oooo) && oooo.size() > 0){
    oooo = step(oooo,ooo);
    count++;
  }
  return count;
}

int main(){
  ifstream f("input");
  string l;
  vector<vector<i>> g;
  while(getline(f,l)) g.push_back(p(l));
  
  set<pair<int,vector<vector<i>>>> oooo;
  oooo.insert(pair<int,vector<vector<i>>>(0,g));
  
  cout << go(oooo) << endl;

  g[0].push_back(i(true, "elerium"));
  g[0].push_back(i(false, "elerium"));
  g[0].push_back(i(true, "dilithium"));
  g[0].push_back(i(false, "dilithium"));
  set<pair<int,vector<vector<i>>>> ooooo;
  ooooo.insert(pair<int,vector<vector<i>>>(0,g));

  cout << go(ooooo) << endl;

  return 0;
}
