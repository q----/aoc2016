#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

struct b{
  vector<int> o;
  vector<int> v;
};

bool operator!(const b& x){
  return (x.o.size() == 2 && x.v.size() == 2);
}

bool operator==(const vector<int>& a, const vector<int>& b){
  return (a[0] == b[0] && a[1] == b[1]) || (a[0] == b[1] && a[1] == b[0]);
} 

int m(string x, int a){
  return (x=="bot")?a:-1-a;
}

int p(string l, map<int,b>& g){
  stringstream s(l);
  string t;
  s >> t;
  int a,b;
  if(t == "value"){
    s >> b >> t >> t >> t >> a;
    g[a].v.push_back(b);
  } else {
    int c;
    string x, y;
    s >> a >> t >> t >> t >> x >> b >> t >> t >> t >> y >> c;
    g[a].o.push_back(m(x,b));
    g[a].o.push_back(m(y,c));
  }
  return !g[a]? a:-1;
}

void s(vector<int>& a, map<int,b>& g){
  int x = a.back();
  a.pop_back();

  vector<int> vals;
  if(g[x].v[0] < g[x].v[1]){
    vals = g[x].v;
  } else {
    vals.push_back(g[x].v[1]);
    vals.push_back(g[x].v[0]);
  }

  for(int i = 0; i <= 1; i++){
    int j = g[x].o[i];
    g[j].v.push_back(vals[i]);
    if(!g[j]){
      a.push_back(j);
    }
  }
}

int main(){
  ifstream f("input");
  string l;

  map<int,b> g;

  while(getline(f,l)){
    int x = p(l,g);
    if(x != -1){
      vector<int> a;
      a.push_back(x);
      while(a.size() != 0) s(a,g);
    }
  }

  vector<int> x;
  x.push_back(61);
  x.push_back(17);

  for(auto a: g){
    if(a.second.v == x){
      cout << a.first << endl;
      break;
    }
  }

  int o = 1;
  for(int i = -1; i >= -3; i--) o *= g[i].v[0];

  cout << o << endl;

  return 0;
}



