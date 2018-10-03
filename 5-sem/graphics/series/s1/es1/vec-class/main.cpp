#include <iostream>
#include "vector.h"

using namespace std;

int main(){
  Vector v1 = Vector{1, 2, 3};
  Vector v2 = Vector{1.0, 2.0, 3.0};

  Vector v3 = v1 + v2;
  Vector v4 = v1 - v2;

  v3.print();
  v4.print();

  cout << "V1 Normalized: " << endl;
  v1.normalize().print();

  cout << "V1: " << endl;
  v1.print();
  cout << "V2: " << endl;
  v2.print();
  cout << endl;
  cout << "v1 dot v2 = " << v1.dot(v2) << endl;
  cout << "v1 cross v2 = ";
  v1.cross(v2).print();
  cout << endl;
}
