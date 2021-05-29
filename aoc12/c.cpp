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

void a(c& d, i& j){
  if(j.o == "inc"){
    d.r[j.a]++;
    d.p++;
  } else if(j.o == "dec"){
    d.r[j.a]--;
    d.p++;
  } else if(j.o == "cpy"){
    d.r[j.b] = d.r[j.a];
    d.p++;
  } else if(j.o == "jnz"){
    if(d.r[j.a]) d.p += d.r[j.b];
    else d.p++;
  }
}

int main(){
  ifstream f("input");
  string l;
  vector<i> inst;
  while(getline(f,l)) inst.push_back(p(l));

  c comp;
  for(int i = -10; i < 30; i++) comp.r.insert(pair<string,int>(to_string(i),i));

  while(comp.p < inst.size()) a(comp, inst[comp.p]);

  cout << comp.r["a"] << endl;

  c comp2;
  for(int i = -10; i < 30; i++) comp2.r.insert(pair<string,int>(to_string(i),i));
  comp2.r.insert(pair<string,int>("c",1));

  while(comp2.p < inst.size()) a(comp2, inst[comp2.p]);

  cout << comp2.r["a"] << endl;

  return 0;
}
