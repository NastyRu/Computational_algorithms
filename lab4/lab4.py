#!/usr/bin/env python
# -*- coding: utf-8 -*-
from math import sin, pi, factorial, cos, exp, log
import numpy as np
import matplotlib.pyplot as plt
from collections import namedtuple

Table = namedtuple('Table', ['x','y', 'w']) # w = вес функции

eps_const = 0.00001
eps_otn = 0.0001
def fi(x, k):
    return x ** k

# Загрузка таблицы
def get_table(filename):
    infile = open(filename, 'r')
    data = []
    for line in infile:
        if line:
            a, b, c = map(float, line.split())
            data.append(Table(a, b, c))
        print(data[-1].x, data[-1].y, data[-1].w)
    infile.close()
    return data

# Вывод графика
def print_result(table, A, n):
    dx = 10
    if len(table) > 1:
        dx = (table[1].x - table[0].x)
 
    x = np.linspace(table[0].x - dx, table[-1].x + dx, 100)
    y = []
    for i in x:
        tmp = 0;
        for j in range(0, n + 1):
            tmp += fi(i, j) * A[j]
        y.append(tmp)
    plt.plot(x, y)

    x1 = [a.x for a in table]
    y1 = [a.y for a in table]
    plt.plot(x1, y1, 'ro', color = 'red')

    plt.grid(True)
    plt.show()
    return 

def get_slau_matrix(table, n):
    N = len(table)
    matrix = [[0 for i in range(0, n + 1)] for j in range (0, n + 1)]
    col = [0 for i in range(0, n + 1)]

    for m in range(0, n + 1):
        for i in range(0, N):
            for k in range(0, n + 1):
                matrix[m][k] += fi(table[i].x, k) * table[i].w * fi(table[i].x, m)
            col[m] += table[i].w * fi(table[i].x, m) * table[i].y
    return matrix, col

def mult(col, matr):
    n = len(col)
    otv = [0 for j in range(0, n)]
    for j in range(0, n):
        for k in range(0, n):
            otv[j] += col[k] * matr[j][k]
    return otv

def replace(mat_a, x):
    size = len(mat_a)
    row = max(range(x, size), key=lambda i: abs(mat_a[i][x]))
    if x != row:
        mat_a[x], mat_a[row] = mat_a[row], mat_a[x]
    return mat_a

def invert(mat_a):
    n = len(mat_a)
    
    for i in range(n):
        mat_a[i] += [int(i == j) for j in range(n)]
    
    for x in range(n):
        mat_a = replace(mat_a, x)
        for i in range(x + 1, n):
            coef = mat_a[i][x] / mat_a[x][x]
            for j in range(x, n * 2):
                mat_a[i][j] -= coef * mat_a[x][j]

    for x in reversed(range(n)):
        for i in reversed(range(x)):
            coef = mat_a[i][x] / mat_a[x][x]
            for j in reversed(range(n * 2)):
                mat_a[i][j] -= coef * mat_a[x][j]

    for i in range(n):
        den = mat_a[i][i]
        for j in range(n * 2):
            mat_a[i][j] /= den

    for i in range(n):
        mat_a[i] = mat_a[i][n:]
    
    return mat_a

def get_coef(table, n):
    koef, svch = get_slau_matrix(table, n)
    inv = invert(koef)
    otv = mult(svch, inv)
    return otv

table = get_table("file.txt")
n = int(input("Введите степень полинома n = "))
A = get_coef(table, n)
print_result(table, A, n)
