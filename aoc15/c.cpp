#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct d{
  int p;
  int l;
  int n;
  d(int c){
    n = c;
  }
};

const bool operator&(const d& i, const int& r){
  return (i.l + r) % i.p == i.p - i.n;
}

d p(string l, int n){
  stringstream s(l);
  string t;
  d o = d(n);
  s >> t >> t >> t >> o.p >> t >> t >> t >> t >> t >> t >> t >> o.l;
  return o;
}

bool q(vector<d>& i, int t){
  for(d a: i) if(!(a&t)) return false;
  return true;
}

int g(vector<d> s){
  int t = -1;
  while(!q(s,++t));
  return t;
}


int main(){
  ifstream f("input");
  string l;
  int i = 0;
  vector<d> s;
 
  while(getline(f,l)) s.push_back(p(l, ++i));

  cout << g(s) << endl;

  d t(++i);
  t.p = 11;
  t.l = 0;
  s.push_back(t);

  cout << g(s) << endl;

  return 0;
}

    
