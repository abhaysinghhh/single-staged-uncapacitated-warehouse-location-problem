#include <fstream>
#include <iostream>
#include <stdlib.h>
using namespace std;

int main() {
  int i, j, k, *f, a, b, q;
  float *g, **c;
  float *d;
  float sum = 0, u = 0;

  ofstream filout, filout1, filout2, filout3, filout4, filout5, filout6;
  // file for GAMS
  filout.open("fix_cost.txt", ios::out);
  filout1.open("demand.txt", ios::out);
  filout2.open("trans_cost.csv", ios::out);
  filout6.open("fraction demand.txt", ios::out);
  // csv file for taking C++
  filout3.open("fix1_cost.csv", ios::out);
  filout4.open("demand1.csv", ios::out);
  filout5.open("trans1_cost.csv", ios::out);
  // define number of plant and market
  cout << "enter the no. of location For Plant SET up" << endl;
  cin >> i;
  cout << "enter the no. of market" << endl;
  cin >> k;
  f = new int[i];
  g = new float[k];
  d = new float[k];
  c = new float *[i];

  for (j = 0; j < i; j++)
    c[j] = new float[k];

  // define the limits of plant setup cost and generate files
  cout << "Enter lower limit for plant setup" << endl;
  cin >> a;
  cout << "Enter the upper limit for plant setup" << endl;
  cin >> b;
  srand((unsigned)time(0));
  //-----------------
  for (int p = 0; p < i; p++) {
    f[p] = (rand() % (b - a) + a);
    filout << p + 1 << "\t" << f[p] << "," << endl;
    // filout3<<f[p]<<","<<endl;
    filout3 << f[p] << ",";
    cout << f[p] << " ";
  }
  filout.close();
  filout3.close();
  cout << endl;
  //------------------
  // define the limits of demand and generate file

  cout << "Enter lower limit for demand of the market" << endl;
  cin >> a;
  cout << "Enter the upper limit for demand of the market" << endl;
  cin >> b;
  srand((unsigned)time(0));
  //----------------------
  for (int q = 0; q < k; q++) {
    g[q] = (rand() % (b - a) + a);
    cout << g[q] << " ";
    filout1 << q + 1 << "\t" << g[q] << "," << endl;
    filout4 << g[q] << ",";
  }
  filout1.close();
  filout4.close();
  cout << endl;
  // converting market demand into fraction demand (demand of kth
  for (int q = 0; q < k; q++)
    sum += g[q];
  for (int q = 0; q < k; q++) {
    d[q] = g[q] / sum;
    filout6 << q + 1 << "\t" << d[q] << "," << endl;
    u = u + d[q];
  }
  cout << "frac_sum= " << u << endl;
  filout6.close();
  //--------------------
  // define the limits of transportation cost and generate files
  cout << "Enter lower limit for transportation cost" << endl;
  cin >> a;
  cout << "Enter the upper limit for transportation cost" << endl;
  cin >> b;
  srand((unsigned)time(0));

  //---------------
  for (int p = 0; p < i; p++)
    filout2 << "," << p + 1;
  filout2 << endl;
  for (int p = 0; p < i; p++) {
    filout2 << p + 1;
    for (q = 0; q < k; q++) {
      c[p][q] = (rand() % (b - a) + a);
      cout << c[p][q] << " ";
      // filout<<q+1<<'\t'<<c[p][q]<<endl;
      filout2 << "," << c[p][q];
      filout5 << c[p][q] << ",";
      // filout2<<endl;
      // filout2<<c[p][q]<<" ";
    }
    filout5 << endl;
    filout2 << endl;
    cout << endl;
  }
  filout2.close();
  filout5.close();
  cout << endl;
  //-------------------
  return 1;

  return 0;
}