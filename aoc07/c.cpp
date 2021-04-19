#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void operator+=(vector<string>& lhs, const vector<string>& rhs){
  for(string a : rhs) lhs.push_back(a);
}

string operator!(const string& a){
  return a[1] + a.substr(0,2);
}

bool operator==(const vector<string>& lhs, const vector<string>& rhs){
  for(string a: lhs) for(string b: rhs) if(a == !b) return true;
  return false;
}

bool abba(string l){
  if(l.size() < 4) return false;
  for(int i = 0; i < l.size() - 3; i++) if(l[i] == l[i+3] && l[i+1] == l[i+2] && l[i] != l[i+1]) return true;
  return false;
}

vector<string> aba(string l){
  vector<string> out;
  if(l.size() < 3) return out;
  for(int i = 0; i < l.size() - 2; i++) if(l[i] == l[i+2] && l[i] != l[i+1]) out.push_back(l.substr(i,3));
  return out;
}

bool v(string l){
  for(int i = 0; i < l.size(); i++) if(l[i] < 'a') l[i] = ' ';
  stringstream s(l);
  bool f = true;
  bool out = false;
  string t;
  while(s>>t){
    if(f) if(abba(t)) out = true;
    if(!f) if(abba(t)) return false;
    f = !f;
  }
  return out;
}

bool v2(string l){
  for(int i = 0; i < l.size(); i++) if(l[i] < 'a') l[i] = ' ';
  stringstream s(l);
  bool f = true;
  string t;
  vector<string> ab;
  vector<string> bab;
  while(s >> t){
    if(f) ab += aba(t);
    if(!f) bab += aba(t);
    f = !f;
  }
  return ab == bab;
}
  
int main(){
  ifstream f("input");
  string l;

  int o = 0;
  int o2 = 0;
  while(getline(f,l)){
    if(v(l)) o++;
    if(v2(l)) o2++;
  }

  cout << o << endl;
  cout << o2 << endl;

  return 0;
}
