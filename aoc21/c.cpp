#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

string rotate(string x, int q){
  string o = "";
  for(int i = 0; i < x.size(); i++){
    o += x[(i + q + x.size()) % x.size()];
  }
  return o;
}

string apply(string l, string input, bool rev = false){
  stringstream s(l);
  string t;
  s >> t;
  if(t == "swap"){
    s >> t;
    if(t == "position"){
      int x,y;
      s >> x >> t >> t >> y;
      char m = input[x];
      input[x] = input[y];
      input[y] = m;
    } else {
      char x,y;
      s >> x >> t >> t >> y;
      int a = input.find(x);
      int b = input.find(y);
      input[a] = y;
      input[b] = x;
    }      
  } else if(t == "reverse"){
    int x,y;
    s >> t >> x >> t >> y;
    string temp = "";
    for(int i = y; i >= x; i--) temp += input[i];
    input.replace(x, temp.size(), temp);
  } else if(t == "move"){
    int x,y;
    s >> t >> x >> t >> t >> y;
    if(rev){
      int z = x;
      x = y;
      y = z;
    }
    char m = input[x];
    input.erase(x, 1);
    input.insert(y, 1, m);
  } else if(t == "rotate"){
    s >> t;
    if(t != "based"){
      int x;
      s >> x;
      return rotate(input, (t=="left"^rev)?x:-x);
    }
    s >> t >> t >> t >> t >> t;
    int x = input.find(t);
    if(!rev){
      if(x >= 4) x++;
      x++;
      x = -x;
    } else {
      switch(x){
        case 0:
          x = 1;
          break;
        case 1:
          x = 1;
          break;
        case 2:
          x = -2;
          break;
        case 3:
          x = 2;
          break;
        case 4:
          x = -1;
          break;
        case 5:
          x = 3;
          break;
        case 6:
          x = 0;
          break;
        case 7:
          x = 4;
          break;
      }
    }
    return rotate(input, x);
  }
  return input;
}

int main(){
  string input = "abcdefgh";

  ifstream f("input");
  string l;
  vector<string> inst;

  while(getline(f,l)){
    input = apply(l, input);
    inst.push_back(l);
  }

  cout << input << endl;

  vector<string> res;
  res.push_back("fbgdceah");
  for(int i = inst.size() - 1; i >= 0; i--) res.push_back(apply(inst[i],res.back(),true));

  cout << res.back() << endl;

  for(int i = 0; i < res.size() - 1; i++) if(res[i] != apply(inst[inst.size()-i-1], res[i+1])) cout << inst[inst.size()-i-1] << '\t' << res[i+1] << " " << res[i] << " " << apply(inst[inst.size()-i-1], res[i+1]) << endl;

  return 0;
}
