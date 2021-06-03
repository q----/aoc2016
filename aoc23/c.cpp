#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

struct i{
  string o;
  string a;
  string b;
};

struct c{
  map<string, int> r;
  int p = 0;
};

i p(string l){
  stringstream s(l);
  i o;
  s >> o.o >> o.a >> o.b;
  return o;
}

void a(c& d, vector<i>& inst){
  i j = inst[d.p];
  if(j.o == "inc"){
    if(j.a[0] > '9') d.r[j.a]++;
    d.p++;
  } else if(j.o == "dec"){
    if(j.a[0] > '9') d.r[j.a]--;
    d.p++;
  } else if(j.o == "cpy"){
    if(j.b[0] > '9') d.r[j.b] = d.r[j.a];
    d.p++;
  } else if(j.o == "jnz"){
    if(d.r[j.a]) d.p += d.r[j.b];
    else d.p++;
  } else if(j.o == "tgl"){
    int x = d.p + d.r[j.a];
    if(x < 0 || x >= inst.size()){
    } else if(inst[x].o == "inc"){
      inst[x].o = "dec";
    } else if(inst[x].o == "dec" || inst[x].o == "tgl"){
      inst[x].o = "inc";
    } else if(inst[x].o == "jnz"){
      inst[x].o = "cpy";
    } else {
      inst[x].o = "jnz";
    }
    d.p++;
  }
}

int main(){
  ifstream f("input");
  string l;
  vector<i> inst;
  while(getline(f,l)) inst.push_back(p(l));

  c comp;
  for(int i = -1000; i < 1000; i++) comp.r.insert(pair<string,int>(to_string(i),i));
  comp.r.insert(pair<string,int>("a", 7));
  while(comp.p < inst.size()) a(comp, inst);
  cout << comp.r["a"] << endl;

  long int o = 1;
  for(int i = 12; i > 0; i--) o *= i;
  cout << o + 89*90 << endl;

  return 0;
}
