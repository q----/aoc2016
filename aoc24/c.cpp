#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

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

const c operator+(const c& lhs, const c& rhs){
  return c(lhs.x + rhs.x, lhs.y + rhs.y);
}

const bool operator==(const c& lhs, const c& rhs){
  return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

const bool operator<(const c& lhs, const c& rhs){
  if(lhs.x == rhs.x) return lhs.y < rhs.y;
  return lhs.x < rhs.x;
}

set<c> step(set<c> i, vector<string> v){
  set<c> o;
  for(c b: i){
    for(c a: {c(0,1), c(0,-1), c(1,0), c(-1,0)}){
      c t = a+b;
      if(v[t.y][t.x] == '.') o.insert(t);
    }
  }
  return o;
}

bool in(c b, set<c> x){
  for(c a : x) if(a == b) return true;
  return false;
}

int dist(c a, c b, vector<string> v){
  set<c> i = {a};
  int count = 0;
  while(!in(b,i)){
    count++;
    i = step(i,v);
  }
  return count;
}

int main(){
  ifstream f("input");
  string l;

  vector<string> v;
  map<int,c> goals;

  while(getline(f,l)){
    for(int i = 0; i < l.size(); i++){
      if(l[i] != '#' && l[i] != '.'){
        goals.insert(pair<int,c>(l[i] - '0', c(i, v.size())));
        l[i] = '.';
      }
    }
    v.push_back(l);
  }

  map<c,int> d;

  for(int i = 0; i < goals.size() - 1; i++){
    for(int j = i+1; j < goals.size(); j++){
      int x = dist(goals[i], goals[j], v);
      d.insert(pair<c,int>(c(i, j), x));
      d.insert(pair<c,int>(c(j, i), x));
    }
  }

  vector<int> gn;
  for(auto a: goals) gn.push_back(a.first);

  sort(gn.begin(), gn.end());

  int sp = 100000;

  do{
    int t = 0;
    for(int i = 0; i < gn.size() - 1; i++) t += d[c(gn[i],gn[i+1])];
    if( t < sp) sp = t;
  } while(next_permutation(gn.begin()+1, gn.end()));

  cout << sp << endl;

  sp = 100000;

  do{
    int t = 0;
    for(int i = 0; i < gn.size(); i++) t += d[c(gn[i],gn[(i+1)%gn.size()])];
    if( t < sp) sp = t;
  } while(next_permutation(gn.begin()+1, gn.end()));

  cout << sp << endl;

  return 0;
}

      




