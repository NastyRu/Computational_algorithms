#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

#define NO_SECTION 1
#define SECTION 0
#define EPS 0.01

int flag = 1;

double function0 (double x, double y) {
  return x * x + y * y;
}

void table(int kol, double *x, double *y, double **z, int *n, double beginx, double endx, double beginy, double endy, double (*func)(double , double)) {
  double stepx = (endx - beginx) / (kol - 1);
  double stepy = (endy - beginy) / (kol - 1);
  for (int i = 0; i < kol; i++) {
    x[i] = beginx + i * stepx;
    y[i] = beginy + i * stepy;
  }
  for (int i = 0; i < kol; i++) {
    for (int j = 0; j < kol; j++) {
        z[i][j] = func(x[i], y[j]);
    }
  }
  (*n) = kol;
}

double approximation(double *x, double *y, int e_num, int b_num, int kol, double x0) {
  int n_matrix = (kol + 1) * 2;
  int m_matrix = kol + 2;
  double matrix[n_matrix][m_matrix];

  for (int i = 0; i < n_matrix; i++)
    for (int j = 0; j < m_matrix; j++)
      matrix[i][j] = 0;

  for (int i = 0, j = b_num; i < n_matrix && j <= e_num; i += 2, j++) {
      matrix[i][0] = x[j];
      matrix[i][1] = y[j];
  }

  int shift = 1;
  for (int j = 2; j < m_matrix; j++) {
    for (int i = shift; i < n_matrix - shift; i+=2) {
      matrix[i][j] = (matrix[i + 1][j - 1] - matrix[i - 1][j - 1]) / (matrix[i + shift][0] - matrix[i - shift][0]);
    }
    shift++;
  }

  /*cout << "Матрица" << endl;
  for (int i = 0; i < n_matrix; i++) {
    for (int j = 0; j < m_matrix; j++) {
      cout << setw(15) << matrix[i][j] << " ";
    }
    cout << endl;
  }*/

  double y0 = 0, kf = 1;
  int str = 0;

  for (int i = 0; i < m_matrix - 1; i++) {
    for (int j = 0, k = 0; k < str; j += 2, k++) {
      kf *= (x0 - matrix[j][0]);
    }
    y0 += kf * matrix[0 + i][1 + i];
    kf = 1;
    str++;
  }
  return y0;
}

int table_near(double *x, double *y, double **z, int n, double x0, double y0, int kolx, int koly) {
  int numx = -1;
  for (int i = 0; i < n - 1; i++) {
    if ((x0 < x[i + 1]) && (x0 >= x[i])) {
      numx = i;
    }
  }
  if (x0 == x[n-1]) {
    numx = n - 1;
  }
  if (numx < 0) {
    cout << endl << "Идет экстраполяция " << endl << endl;
    if (x0 < x[0])
      numx = 0;
    if (x0 > x[n - 1])
      numx = n - 1;
  }

  int b_numx = numx, e_numx = numx;

  if (b_numx - 1 >= 0 && e_numx + 1 < n && fabs(x[b_numx - 1] - x[b_numx]) < fabs(x[b_numx + 1] - x[b_numx])) {
    while (e_numx - b_numx < kolx) {
      if ((b_numx - 1) >= 0) {
        b_numx--;
        if (e_numx - b_numx == kolx)
          break;
      }
      if ((e_numx + 1) < n) {
        e_numx++;
      }
      if (b_numx == 0 && e_numx == n - 1) {
        break;
      }
    }
  } else {
    while (e_numx - b_numx < kolx) {
      if ((e_numx + 1) < n) {
        e_numx++;
        if (e_numx - b_numx == kolx)
          break;
      }
      if ((b_numx - 1) >= 0) {
        b_numx--;
      }
      if (b_numx == 0 && e_numx == n - 1) {
        break;
      }
    }
  }

  if (e_numx - b_numx < kolx) {
    cout << "Недостаточно данных " << endl;
    return NO_SECTION;
  }

  int numy = -1;
  for (int i = 0; i < n - 1; i++) {
    if ((y0 < y[i + 1]) && (y0 >= y[i])) {
      numy = i;
    }
  }
  if (y0 == y[n-1]) {
    numy = n - 1;
  }
  if (numy < 0) {
    cout << endl << "Идет экстраполяция " << endl << endl;
    if (y0 < y[0])
      numy = 0;
    if (y0 > y[n - 1])
      numy = n - 1;
  }

  int b_numy = numy, e_numy = numy;

  if (b_numy - 1 >= 0 && e_numy + 1 < n && fabs(y[b_numy - 1] - y[b_numy]) < fabs(y[b_numy + 1] - y[b_numy])) {
    while (e_numy - b_numy < koly) {
      if ((b_numy - 1) >= 0) {
        b_numy--;
        if (e_numy - b_numy == koly)
          break;
      }
      if ((e_numy + 1) < n) {
        e_numy++;
      }
      if (b_numy == 0 && e_numy == n - 1) {
        break;
      }
    }
  } else {
    while (e_numy - b_numy < koly) {
      if ((e_numy + 1) < n) {
        e_numy++;
        if (e_numy - b_numy == koly)
          break;
      }
      if ((b_numy - 1) >= 0) {
        b_numy--;
      }
      if (b_numy == 0 && e_numy == n - 1) {
        break;
      }
    }
  }

  if (e_numy - b_numy < koly) {
    cout << "Недостаточно данных " << endl;
    return NO_SECTION;
  }

  cout << setw(9) << "x\\y";
  for (int i = b_numy; i <= e_numy; i++) {
    cout << setw(8) << y[i] << " ";
  }
  cout << endl;
  for (int i = b_numx; i <= e_numx; i++) {
    cout << setw(8) << x[i] << " ";
    for (int j = b_numy; j <= e_numy; j++) {
      cout << setw(8) << z[i][j] << " ";
    }
    cout << endl;
  }

  double *new_y = new double[n];

  for (int i = b_numx; i <= e_numx; i++) {
    new_y[i] = approximation(y, z[i], e_numy, b_numy, koly, y0);
  }

  double z0 = approximation(x, new_y, e_numx, b_numx, kolx, x0);
  cout << endl << "Полученное значение F(x) = " << z0 << endl;
  cout << "Реальное значение F(x) = " << function0(x0, y0) << endl;
  cout << "Погрешность " << fabs(z0 - function0(x0, y0)) / function0(x0, y0) << endl;
  return SECTION;
}

int main() {
  int n = 0;
  int degreex, degreey;
  int kol;
  double x0, y0, x_begin, x_end, y_begin, y_end;

  cout << "Введите начальный Х\n";
  cin >> x_begin;
  cout << "Введите конечный Х\n";
  cin >> x_end;
  cout << "Введите начальный Y\n";
  cin >> y_begin;
  cout << "Введите конечный Y\n";
  cin >> y_end;
  cout << "Введите количество точек\n";
  cin >> kol;
  cout << endl << "Исходная таблица" << endl;
  double x[kol], y[kol];
  double **z = new double*[kol];
  for (int i = 0; i < kol; i++) {
    z[i] = new double[kol];
  }
  table(kol, x, y, z, &n, x_begin, x_end, y_begin, y_end, function0);
  cout << setw(9) << "x\\y";
  for (int i = 0; i < n; i++) {
    cout << setw(8) << y[i] << " ";
  }
  cout << endl;
  for (int i = 0; i < n; i++) {
    cout << setw(8) << x[i] << " ";
    for (int j = 0; j < n; j++) {
      cout << setw(8) << z[i][j] << " ";
    }
    cout << endl;
  }

  cout << "Введите степень полинома X\n";
  cin >> degreex;
  cout << "Введите Х\n";
  cin >> x0;
  cout << "Введите степень полинома Y\n";
  cin >> degreey;
  cout << "Введите Y\n";
  cin >> y0;
  table_near(x, y, z, n, x0, y0, degreex, degreey);

  delete []z;
  return 0;
}
