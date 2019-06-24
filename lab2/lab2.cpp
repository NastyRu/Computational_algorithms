#include <iostream>
#include <iomanip>
#include <math.h>
#include <stdio.h>
using namespace std;

#define SUCCESS 0
#define FILENAME "file.txt"

double *x, *y, *h, *f, *a, *b, *c, *d, *xi, *eta;
int n;
double x0;

void read_from_file() {
  FILE *file = fopen(FILENAME, "r");
  fscanf(file, "%d ", &n);

  x = new double[n];
  y = new double[n];
  h = new double[n];
  f = new double[n];
  a = new double[n];
  b = new double[n];
  c = new double[n];
  d = new double[n];
  xi = new double[n];
  eta = new double[n];

  for (int i = 0; i < n; i++) {
    fscanf(file, "%lf %lf\n", x + i, y + i);
  }

  cout << "Таблица" << endl;
  for (int i = 0; i < n; i++) {
    cout << setw(8) << x[i] << " " << setw(8) << y[i] << endl;
  }

  fclose(file);
}

void interpolation() {
  for (int i = 1; i < n; i++) {
    h[i] = x[i] - x[i - 1];
  }
  for (int i = 2; i < n; i++) {
    f[i] = -3 * ((y[i] - y[i - 1]) / h[i] - (y[i - 1] - y[i - 2]) / h[i - 1]);
  }
  for (int i = 1; i < n; i++) {
    a[i] = h[i - 1];
    b[i] = -2 * (h[i - 1] + h[i]);
    d[i] = h[i];
  }
  xi[2] = 0;
  eta[2] = 0;
  for (int i = 2; i < n; i++) {
    xi[i + 1] = d[i] / (b[i] - a[i] * xi[i]);
    eta[i + 1] = (a[i] * eta[i] + f[i]) / (b[i] - a[i] * xi[i]);

    cout << xi[i] << " " << eta[i] << endl;
  }

  c[0] = 0;
  c[n] = 0;
  for (int i = n - 1; i > 0; i--) {
    c[i] = xi[i + 1] * c[i + 1] + eta[i + 1];
  }

  for (int i = 1; i < n; i++) {
    a[i] = y[i - 1];
    d[i] = (c[i + 1] - c[i]) / 3 / h[i];
    b[i] = (y[i] - y[i - 1]) / h[i] - h[i] * (c[i + 1] + 2 * c[i]) / 3;

    cout<< setw(8) << a[i] << " "<< setw(8) << b[i] << " "<< setw(8) << c[i] << " "<< setw(8) << d[i] << endl;
  }

  for (int i = 1; i < n; i++) {
    if (x0 < x[0]) {
      double ans = a[1] + b[1] * (x0 - x[0]) + c[1] * pow(x0 - x[0], 2) + d[1] * pow(x0 - x[0], 3);
      cout << endl << "экстраполяция " << endl << endl;
      //cout << "f(x) = " << ans << endl;
      //cout << "Погрешность " << fabs(ans - x0 * x0) / x0 / x0 << endl;
      return;
    }
    if (x0 >= x[i - 1] && x0 <= x[i]) {
      cout << a[i] << " " << b[i] << " " << d[i] << " " << i << endl;
      double ans = a[i] + b[i] * (x0 - x[i - 1]) + c[i] * pow(x0 - x[i -1], 2) + d[i] * pow(x0 - x[i - 1], 3);
      cout << "f(x) = " << ans << endl;
      cout << "Погрешность " << fabs(ans - x0 * x0) / x0 / x0 << endl;
      return;
    }
    if (x0 > x[n - 1]) {
      cout << endl << "экстраполяция " << endl << endl;
      double ans = a[n - 1] + b[n - 1] * (x0 - x[n - 1]) + c[n - 1] * pow(x0 - x[n - 1], 2) + d[1] * pow(x0 - x[n - 1], 3);
      //cout << "f(x) = " << ans << endl;
      //cout << "Погрешность " << fabs(ans - x0 * x0) / x0 / x0 << endl;
      return;
    }
  }
}

void free() {
  delete [] x;
  delete [] y;
  delete [] h;
  delete [] f;
  delete [] a;
  delete [] b;
  delete [] c;
  delete [] d;
  delete [] xi;
  delete [] eta;
}

int main() {
  read_from_file();
  cout << "Введите х" << endl;
  cin >> x0;
  interpolation();
  free();

  return 0;
}
