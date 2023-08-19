#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main() {
  int SIZE, upper_bound;
  cout << "Enter number of plant or market ";
  cin >> SIZE;
  cout << "Enter upper bound ";
  cin >> upper_bound;
  clock_t tStart = clock();
  int i, j, k, pos[SIZE], iter, iter_theta = 0;

  float p, c[SIZE][SIZE], Axkminusb[SIZE][SIZE], f[SIZE], lambda[SIZE][SIZE],
      d[SIZE], temp, dual = 0, sum = 0, next_lambda[SIZE][SIZE], g[SIZE],
                     lag_theta;
  float x[SIZE][SIZE], y[SIZE], lag_bound = 0, bound, bound1, bound2, u = 0,
                                theta = 0.75, step, Norm, Norm1[SIZE][SIZE],
                                dual_sol, lag_iter, temp_dual[SIZE];

  char *a;
  ifstream filin;
  ifstream filin1;
  ifstream filin2;
  ofstream filout7;
  filout7.open("data.txt", ios::out);
  filin.open("fix1_cost.csv", ios::in);
  filin1.open("demand1.csv", ios::in);
  filin2.open("trans1_cost.csv", ios::in);
  // reading data for fixed cost
  int n = 0;
  a = new char[3];
  for (int i = 0; i < SIZE; i++) {
    filin.seekg(n, ios_base::beg);
    filin.read(a, 3);
    f[i] = atof(a);
    // cout<< f[i]<<endl;
    n = n + 4;
  }
  // cout<<endl;
  filin.close();
  // reading data for market demand
  int m = 0;
  for (int k = 0; k < SIZE; k++) {
    filin1.seekg(m, ios_base::beg);
    filin1.read(a, 3);
    g[k] = atof(a);
    m = m + 4;
  }
  filin1.close();

  // converting market demand into fraction demand (demand of kth
  for (int k = 0; k < SIZE; k++)
    sum = sum + g[k];
  for (int k = 0; k < SIZE; k++)
    d[k] = g[k] / sum;
  /*cout<<d[k]<<endl;
  filout6<<k+1<<"\t"<<d[k]<<","<<endl;
  u=u+d[k];
  }
  //cout<<endl;
  //cout<<"frac_sum= "<<u<<endl;
  filout6.close();*/
  // reading data for transportation cost
  int l = 0;
  for (int i = 0; i < SIZE; i++) {
    for (int k = 0; k < SIZE; k++) {
      filin2.seekg(l, ios_base::beg);
      filin2.read(a, 3);
      l = l + 4;
      c[i][k] = atof(a);
      // cout<< c[i][k]<<" ";
    }
    // cout<<"\n";
    l = l + 2;
  }
  // cout<<endl;
  filin2.close();
  // initializing lambda equal to zero and start iteration
  for (int k = 0; k < SIZE; k++) {
    for (int i = 0; i < SIZE; i++)
      lambda[k][i] = 0;
  }
  // clock_t tStart = clock();
  for (iter = 0; iter < 100; iter++) {
    iter_theta = iter_theta + 1;
    if (iter_theta > 5) {
      theta = theta / 2;
      iter_theta = 0;
    }
    // cout<<"iteration no.= "<<iter<<endl;
    // cout<<"theta= "<<theta<<endl;
    /*Obtaining dual solution and location of plant to supply for particular
    market at least expense*/
    for (int k = 0; k < SIZE; k++) {
      for (int i = 0; i < SIZE; i++) {
        Norm1[k][i] = 0;
        Axkminusb[k][i] = 0;
      }
    }
    bound1 = 0;
    bound2 = 0;
    bound = 0;
    Norm = 0;
    temp = 0;
    dual = 0;
    for (int k = 0; k < SIZE; k++) {
      p = 100000;
      for (int i = 0; i < SIZE; i++) {
        temp = c[i][k] + f[i] + lambda[i][k] * (d[k] - 1);
        // cout<<"temp"<<k<<"="<<temp<<endl;
        if (p >= temp) {
          p = temp;
          pos[k] = i;
        }
      }
      // cout<<endl;
      temp_dual[k] = p * d[k];
      // cout<<"pos["<<k<<"]="<<pos[k]<<endl;
      // cout<<"p["<<k<<"]="<<p<<endl;
    }
    for (int k = 0; k < SIZE; k++) {
      dual += temp_dual[k];
    }
    // cout << "dual = "<<dual<<endl;
    // initializing value of x[i][k] and y[k]
    for (int k = 0; k < SIZE; k++) {
      y[k] = 0;
    }
    for (int k = 0; k < SIZE; k++) {
      for (int i = 0; i < SIZE; i++) {
        if (i == pos[k])
          x[i][k] = d[k];
        else
          x[i][k] = 0;
      }
    }

    for (int k = 0; k < SIZE; k++) {
      for (int i = 0; i < SIZE; i++) {
        y[k] += x[k][i];
      }
      // cout << "y["<<k<<"]=" << y[k]<<endl;
    }
    // find value of lagrangian bound
    for (int k = 0; k < SIZE; k++) {
      for (int i = 0; i < SIZE; i++) {
        bound1 +=
            ((c[k][i] - lambda[k][i]) * x[k][i]) + (lambda[k][i] * d[i] * y[k]);
      }
    }
    for (int i = 0; i < SIZE; i++)
      bound2 += f[i] * y[i];
    bound = bound1 + bound2;
    // cout <<"bound = " << bound <<endl;
    for (int k = 0; k < SIZE; k++) {
      for (int i = 0; i < SIZE; i++) {
        Axkminusb[k][i] = (d[i] * y[k] - x[k][i]);
        // cout<<"Axkminusb["<<k<<"]["<<i<<"]="<<Axkminusb[k][i]<<" ";
      }
      // cout<<endl;
    }
    for (int k = 0; k < SIZE; k++) {
      for (int i = 0; i < SIZE; i++) {
        Norm1[k][i] = (Axkminusb[k][i] * Axkminusb[k][i]);
        // cout << "Norm1["<<k<<"]["<<i<<"]="<<Norm1[k][i]<<" ";
      }
      // cout << endl;
    }
    for (int k = 0; k < SIZE; k++) {
      for (int i = 0; i < SIZE; i++) {
        Norm += Norm1[k][i];
      }
    }
    // cout<<"Norm= "<<Norm<<endl;
    step = theta * (upper_bound - bound) / Norm;
    // cout<<"step size= "<<step<<endl;

    for (int k = 0; k < SIZE; k++) {
      for (int i = 0; i < SIZE; i++) {
        next_lambda[k][i] = lambda[k][i] + step * Axkminusb[k][i];
      }
    }

    for (int k = 0; k < SIZE; k++) {
      for (int i = 0; i < SIZE; i++) {
        lambda[k][i] = next_lambda[k][i];
      }
    }

    for (int k = 0; k < SIZE; k++) {
      for (int i = 0; i < SIZE; i++) {
        if (d[i] * y[k] - x[k][i] >= 0)
          lambda[k][i] = 0;
        // cout<<"lambda["<<k<<"]["<<i<<"]="<<lambda[k][i]<<" ";
      }
      // cout<<endl;
    }
    // Solution data output in file
    /*filout7<<"iteration no.= "<<iter<<endl;
    filout7<<"theta= "<<theta<<endl;
    filout7<<"stepsize="<<step<<endl;
    filout7<<"dual="<<dual<<endl;
    filout7<<"bound="<<bound<<endl;

    for(int k = 0; k<SIZE ;k++){
      for(int i= 0; i<SIZE ;i++){
        filout7<<"lambda["<<k<<"]["<<i<<"]="<<lambda[k][i]<<" ";
      }
      cout << endl;
    }
    for(int k = 0; k<SIZE ;k++){
      for(int i= 0; i<SIZE ;i++){
        if(x[i][k]>0) filout7<<"x["<<i<<"]["<<k<<"]="<<x[i][k]<<" ";
      }
      cout << endl;
    }
    for(int i = 0; i<SIZE ;i++){
      filout7<<"y["<<i<<"]="<<y[i]<<endl;
    }*/
    //}
    if (lag_bound <= bound) {
      lag_bound = bound;
      lag_iter = iter;
      dual_sol = dual;
      lag_theta = theta;
    }
  }
  cout << endl;
  filout7 << "Time taken:" << (double)(clock() - tStart) / CLOCKS_PER_SEC
          << endl;
  filout7 << "iteration= " << lag_iter << endl;
  filout7 << "Lagrangian bound= " << lag_bound << endl;
  filout7 << "dual solution= " << dual_sol << endl;
  filout7 << "theta= " << lag_theta << endl;
  cout << "Time taken:" << (double)(clock() - tStart) / CLOCKS_PER_SEC << endl;
  cout << "iteration= " << lag_iter << endl;
  cout << "Lagrangian bound= " << lag_bound << endl;
  cout << "dual solution= " << dual_sol << endl;
  cout << "theta= " << lag_theta << endl;

  return 0;
}