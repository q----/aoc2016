#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct d{
  int x;
  int y;
  int size;
  int used;
  int avail;
  int usep;
};

const bool operator==(const d& a, const d& b){
  return (a.x == b.x) && (a.y == b.y);
}

d p(string l){
  for(int i = 0; i < l.size(); i++) if(l[i] == '-' || l[i] == 'x' || l[i] == 'y' || l[i] == 'T' || l[i] == '%') l[i] = ' ';
  d o;
  string t;
  stringstream s(l);
  s >> t >> o.x >> o.y >> o.size >> o.used >> o.avail >> o.usep;
  return o;
}

int main(){
  ifstream f("input");
  string l;
  vector<d> nodes;

  getline(f,l);
  getline(f,l);
  while(getline(f,l))nodes.push_back(p(l));

  int o = 0;

  for(auto a: nodes){
    for(auto b: nodes){
      if(a==b || a.used == 0) continue;
      if(a.used <= b.avail) o++;
    }
  }

  cout << o << endl;

  return 0;
}

      
