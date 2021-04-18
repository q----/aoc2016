#include <iostream>
#include <fstream>
#include <sstream>
#include <set>

using namespace std;

struct c{
  int x = 0;
  int y = 0;
};

struct w{
  c x;
  int d = 0;
};

struct i{
  char t;
  int d;
};

const bool operator<(const c& lhs, const c& rhs){
  if(lhs.x != rhs.x) return lhs.x < rhs.x;
  return lhs.y < rhs.y;
}

int ab(int x){
  if(x < 0) return -x;
  return x;
}

int apply (w& a, i b, set<c>& v){
  a.d += (b.t == 'R')?1:3;
  a.d %= 4;
  int out = -1;
  if(a.d % 2){
    if(a.d == 1){
      for(int i = 0; i < b.d; i++){
      	a.x.x++;
	if(out == -1 && !v.insert(a.x).second){
         out = ab(a.x.x) + ab(a.x.y);
	}
      }
    } else {
      for(int i = 0; i < b.d; i++){
        a.x.x--;
	if(out == -1 && !v.insert(a.x).second){
          out = ab(a.x.x) + ab(a.x.y);
	}
      }
    }
  } else {
    if(a.d){
      for(int i = 0; i < b.d; i++){
        a.x.y++;
	if(out == -1 && !v.insert(a.x).second){
          out = ab(a.x.x) + ab(a.x.y);
	}
      }
    } else {
      for(int i = 0; i < b.d; i++){
        a.x.y--;
	if(out == -1 && !v.insert(a.x).second){
          out = ab(a.x.x) + ab(a.x.y);
	}
      }
    }
  }
  return out;
}

i p (string l){
  i out;
  out.t = l[0];
  int off = (l[l.size()-1] == ',')?2:1;
  stringstream s(l.substr(1,l.size()-off));
  s >> out.d;
  return out;
}

int main(){
  string l;
  ifstream f("input");
  getline(f,l);
  stringstream s(l);

  set<c> v;
  w g;
  v.insert(g.x);
  string t;
  bool flag = true;
  int p2;
  int x = 0;
  while(s>>t){
    int m = apply(g, p(t), v);
    if(flag && m != -1){
      p2 = m;
      flag = false;
    }
  }

  cout << ab(g.x.x) + ab(g.x.y) << endl;
  cout << p2 << endl;

  return 0;
}
