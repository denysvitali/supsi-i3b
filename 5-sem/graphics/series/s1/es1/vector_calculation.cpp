#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void printVec(vector<float>* vec){
  for(int i=0; i < vec->size(); i++){
    cout << (*vec)[i] << endl;
  }
}

int main(){
  vector<float> a  = {1,0,-1};
  vector<float> b = {-0.5, 1.5, 0.5};

  vector<float> sum = {a[0] + b[0], a[1] + b[1], a[2] + b[2]};
  vector<float> sub = {a[0] - b[0], a[1] - b[1], a[2] - b[2]};
  float dotp = a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
  vector<float> crossp = {a[1] * b[2] - b[1] * a[2],
                          a[0] * b[2] - b[0] * a[2],
                          a[0] * b[1] - b[0] * a[1]};
                          
                          
    // xyzzy
    // a = b x c

  float intensity = sqrt(pow(a[0],2) + pow(a[1], 2) + pow(a[2],2));
  float intensity_b = sqrt(pow(b[0],2) + pow(b[1], 2) + pow(b[2],2));

  vector<float> normalized_b = {b[0]/intensity_b, b[1]/intensity_b,
                                  b[2]/intensity_b};

  cout << "SUM: " << endl;
  printVec(&sum);
  cout << endl;

  cout << "CrossP: " << endl;
  printVec(&crossp);
  cout << endl;

  cout << "Intensity: " << intensity << endl;

  cout << "\\hat{b} = ";
  printVec(&normalized_b);
  cout << endl;

}
