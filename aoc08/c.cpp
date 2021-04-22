#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

vector<bool> operator*(const vector<bool> lhs, const int rhs){
  vector<bool> out;
  for(int i = 0; i < lhs.size(); i++) out.push_back(lhs[(lhs.size()+i-rhs)%lhs.size()]);
  return out;
}

void rect(int x, int y, vector<vector<bool>>& z){
  for(int i = 0; i < y; i++){
    for(int j = 0; j < x; j++){
      z[i][j] = true;
    }
  }
}

void r(int y, int o, vector<vector<bool>>& z){
  z[y] = z[y] * o;
}

void c(int x, int o, vector<vector<bool>>& z){
  vector<bool> rot;
  for(int i = 0; i < z.size(); i++) rot.push_back(z[i][x]);
  rot = rot * o;
  for(int i = 0; i < z.size(); i++) z[i][x] = rot[i];
}
  
void p(string l, vector<vector<bool>>& z){
  for(int i = 0; i < l.size(); i++) if(l[i] == '=' || (l[i] == 'x' && l[i+1] != '=')) l[i] = ' ';
  stringstream s(l);
  string t;
  s >> t;
  if(t == "rect"){
    int x, y;
    s >> x >> y;
    rect(x,y,z);
    return;
  }
  s >> t;
  if(t == "column"){
    int x, o;
    s >> t >> x >> t >> o;
    c(x,o,z);
    return;
  } else {
    int y, o;
    s >> t >> y >> t >> o;
    r(y,o,z);
    return;
  }
}

int count(vector<vector<bool>> z){
  int out = 0;
  for(auto x: z) for(auto y: x) if(y) out++;
  return out;
}

int main(){
  ifstream f("input");
  string l;
  vector<vector<bool>> z;
  int w = 50;
  int h = 6;

  vector<bool> t;
  for(int i = 0; i < w; i++) t.push_back(false);
  for(int i = 0; i < h; i++) z.push_back(t);

  while(getline(f,l)){
    p(l,z);
  }

  cout << count(z) << endl;

  for(int j = 0; j < h; j++){
    for(int i = 0; i < w; i++) cout << ((z[j][i])?'#':'.');
    cout << endl;
  }

  return 0;
}
