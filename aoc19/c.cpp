#include<iostream>
#include<queue>
#include<list>

using namespace std;

int main(){
  unsigned int i = 3012210;
  queue<unsigned int> c;

  for(unsigned int j = 1; j <= i; j++) c.push(j);

  while(c.size() > 1){
    c.push(c.front());
    c.pop();
    c.pop();
  }

  cout << c.front() << endl;

  list<unsigned int> x;
  for(unsigned int j = 1; j <= i; j++) x.push_back(j);
  auto it = x.begin();
  advance(it, i/2);
  while(x.size() > 1){
    it = x.erase(it);
    if(it == x.end()) it = x.begin();
    if(x.size() % 2 == 0) advance(it, 1);
    if(it == x.end()) it = x.begin();
  }

  cout << x.front() << endl;

  return 0;
}
