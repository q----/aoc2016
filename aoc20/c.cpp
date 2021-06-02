#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct r{
  unsigned long int b;
  unsigned long int e;
  r(unsigned long int x, unsigned long int y){
    b = x;
    e = y;
  }
};

const bool operator<(const r& lhs, const r& rhs){
  if(lhs.b == rhs.b) return lhs.e < rhs.e;
  return lhs.b < rhs.b;
}

const bool operator&(const r& lhs, const r& rhs){
  if(lhs.b > rhs.b) return rhs & lhs;
  return rhs.b - 1 <= lhs.e;
}

r c(r a, r b){
  return r((a.b<b.b)?a.b:b.b, (a.e>b.e)?a.e:b.e);
}

r p(string l){
  for(int i = 0; i < l.size(); i++) if(l[i] == '-') l[i] = ' ';
  stringstream s(l);
  unsigned long int x;
  unsigned long int y;
  s >> x >> y;
  return r(x,y);
}

int main(){
  ifstream f("input");
  string l;
  vector<r> g;

  while(getline(f,l)) g.push_back(p(l));

  sort(g.begin(), g.end());

  auto it = g.begin();
  while(it != g.end()-1){
    if(*it & *(it+1)){
      r t = c(*it, *(it+1));
      it = g.insert(g.erase(g.erase(it)), t);
    } else {
      it++;
    }
  }

  cout << g[0].e + 1 << endl;

  long int t = 0;

  for(int i = 0; i < g.size()-1; i++) t += g[i+1].b - g[i].e - 1;

  t += 4294967295 - g.back().e;

  cout << t << endl;

  return 0;
}
