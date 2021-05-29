#include <iostream>
#include <map>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

struct c{
  int x, y;
  c(){
    x = 1;
    y = 1;
  }

  c(int a, int b){
    x = a;
    y = b;
  }
};

bool operator<(const c& a, const c& b){
  if(a.x != b.x) return a.x < b.x;
  return a.y < b.y;
}

c operator+(const c& a, const c& b){
  c o;
  o.x = a.x + b.x;
  o.y = a.y + b.y;
  return o;
}

bool f(c t, int n){
  int x = t.x * t.x + 3 * t.x + 2 * t.x * t.y + t.y + t.y * t.y + n;
  string s = bitset<16>(x).to_string();
  return (count(s.begin(), s.end(), '1') + 1) % 2;
}

void m(vector<c>& p, map<c,int>& l, int& n){
  c t = p[0];
  p.erase(p.begin());
  for(auto a : {c(0,1), c(0,-1), c(1,0), c(-1,0)}){
    if((t+a).x < 0 | (t+a).y < 0 | !f(t+a,n)){
      l[t+a] = 10000;
    } else {
      if(!l.count(t+a)){
        l[t+a] = l[t] + 1;
        p.push_back(t+a);
      }
    }
  }
}

int main(){
  int n = 1352;
  vector<c> p = {c()};
  map<c,int> l;
  l.insert(pair<c,int>(c(),0));

  c g = c(31,39);

  while(!l.count(g)) m(p,l,n);

  cout << l[g] << endl;

  int count = 0;
  for(auto a : l) if(a.second <= 50) count++;

  cout << count << endl;

  return 0;
}



