#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

#define NO_SECTION 1
#define SECTION 0
#define EPS 0.01

int flag = 1;

double function_beg (double x) {
  return x * x;
}

double function_end (double x) {
  return cos(x) - x;
}

void table(double *x, double *y, int *n, double begin, double end, int kol, double (*function)(double )) {
  double step = (end - begin) / (kol - 1);
  int j = 0;
  for (double i = begin; i < (end + step - EPS); i += step) {
    x[j] = i;
    y[j] = function(i);
    j++;
  }
  (*n) = j;

  /*cout << "Исходная таблица" << endl;
  for (int i = 0; i < (*n); i++) {
    cout << setw(8) << x[i] << " " << setw(8) << y[i] << endl;
  }*/
}

void approximation(double *x, double *y, int e_num, int b_num, int kol, double x0) {
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

  if (flag)
    cout << endl << "Полученный полином" << endl;
  for (int i = 0; i < m_matrix - 1; i++) {
    if (flag) {
      if (i > 0) {
        if (matrix[0 + i][1 + i] < 0)
          cout << "- " << fabs(matrix[0 + i][1 + i]);
        else
          cout << "+ " << fabs(matrix[0 + i][1 + i]);
      } else {
        cout << matrix[0 + i][1 + i] << " ";
      }
    }

    for (int j = 0, k = 0; k < str; j += 2, k++) {
      kf *= (x0 - matrix[j][0]);
      if (flag) {
        if (matrix[j][0] < 0)
          cout << "(x + " << fabs(matrix[j][0]) << ")";
        else
          cout << "(x - " << fabs(matrix[j][0]) << ")";
      }
    }
    y0 += kf * matrix[0 + i][1 + i];
    kf = 1;
    str++;
  }

  if (flag) {
    cout << endl << endl << "Полученное значение f(x) = " << y0 << endl;
    cout << "Погрешность " << fabs(y0 -  function_beg(x0)) / function_beg(x0) << endl;
  } else {
    cout << endl << "Корень функции " << y0 << endl;
  }
}

int table_near(double *x, double *y, int n, double x0, int kol) {
  int num = -1;
  for (int i = 0; i < n - 1; i++) {
    if ((x0 < x[i + 1]) && (x0 >= x[i])) {
      num = i;
    }
  }
  if (x0 == x[n-1]) {
    num = n - 1;
  }
  if (num < 0) {
    cout << endl << "Идет экстраполяция " << endl << endl;
    if (x0 < x[0])
      num = 0;
    if (x0 > x[n - 1])
      num = n - 1;
  }

  int b_num = num, e_num = num;

  if (b_num - 1 >= 0 && e_num + 1 < n && fabs(x[b_num - 1] - x[b_num]) < fabs(x[b_num + 1] - x[b_num])) {
    while (e_num - b_num < kol) {
      if ((b_num - 1) >= 0) {
        b_num--;
        if (e_num - b_num == kol)
          break;
      }
      if ((e_num + 1) < n) {
        e_num++;
      }
      if (b_num == 0 && e_num == n - 1) {
        break;
      }
    }
  } else {
    while (e_num - b_num < kol) {
      if ((e_num + 1) < n) {
        e_num++;
        if (e_num - b_num == kol)
          break;
      }
      if ((b_num - 1) >= 0) {
        b_num--;
      }
      if (b_num == 0 && e_num == n - 1) {
        break;
      }
    }
  }

  if (e_num - b_num < kol) {
    cout << "Недостаточно данных " << endl;
    return NO_SECTION;
  }

  if (flag) {
    cout << "Таблица" << endl;
    for (int i = b_num; i <= e_num; i++) {
      cout << setw(8) << x[i] << " " << setw(8) << y[i] << endl;
    }
  }

  approximation(x, y, e_num, b_num, kol, x0);

  return SECTION;
}

int main() {
  int n = 0;
  int degree;
  int kol;
  double x0, x_begin, x_end;

  cout << "Введите начальный Х\n";
  cin >> x_begin;
  cout << "Введите конечный Х\n";
  cin >> x_end;
  cout << "Введите количество точек\n";
  cin >> kol;
  cout << endl << "Исходная таблица" << endl;
  double x[kol], y[kol];
  table(x, y, &n, x_begin, x_end, kol, function_beg);
  for (int i = 0; i < n; i++) {
    cout << setw(8) << x[i] << " " << setw(8) << y[i] << endl;
  }

  cout << "Введите степень полинома\n";
  cin >> degree;
  cout << "Введите Х\n";
  cin >> x0;
  table_near(x, y, n, x0, degree);

  cout << endl << "Найдем корень функции " << endl;
  cout << "Введите левое значение промежутка\n";
  cin >> x_begin;
  cout << "Введите правое значение промежутка\n";
  cin >> x_end;
  cout << "Введите количество точек\n";
  cin >> kol;
  cout << "Введите степень полинома\n";
  cin >> degree;
  double new_x[kol], new_y[kol];
  int new_n = 0;
  flag = 0;

  table(new_x, new_y, &new_n, x_begin, x_end, kol, function_end);
  if (new_y[0] > new_y[kol - 1]) {
    std::reverse(new_y, new_y + kol);
    std::reverse(new_x, new_x + kol);
  }
  table_near(new_y, new_x, new_n, 0, degree);

  return 0;
}
