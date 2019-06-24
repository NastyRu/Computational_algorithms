from math import *

ttable = []
for i in range (1, 14):
    ttable.append(i * 2000)

q1table = [1, 1, 1, 1.0001, 1.0025, 1.0198, 1.0895, 1.2827, 1.6973, 2.4616, 3.6552, 5.3749, 7.6838]
q2table = [4, 4, 4.1598, 4.3006, 4.4392, 4.5661, 4.6817, 4.7923, 4.9099, 5.0511, 5.2354, 5.4841, 5.8181]
q3table = [5.5, 5.5, 5.5116, 5.9790, 6.4749, 6.9590, 7.4145, 7.8370, 8.2289, 8.5970, 8.9509, 9.3018, 9.6621]
q4table = []
q5table = []
for i in range(13):
    q4table.append(11)
    q5table.append(15)

gm = 0
v = -5
x = [-5, 3, -2, -15, -40, -70]
eps = 0.0001
e = [12.13, 20.98, 31, 45]
zin = [0, 0, 1, 2, 3, 4]

Pn = float(input("Рнач = "))
Tn = int(input("Тнач = "))
To = int(input("То = "))
Tw = int(input("Тw = "))
m = int(input("m = "))

def F(x, z):
    otv = 7242 * Pn / Tn - 2 * iint(x)
    return otv

def T(z):
    return To + (Tw - To) * z ** m

def dichtomii(a, b, z, Func):
    f_a = Func(a, z)
    f_b = Func(b, z)
    xp = (a + b) / 2
    while abs((b - a) / xp) > eps:
        xp = (a + b) / 2
        f_x = Func(xp, z)

        if (f_a * f_x <= 0):
            b = xp
            f_b = f_x
        else:
            a = xp
            f_a = f_x

    return (a + b) / 2

def iint(x):
    a = 0
    b = 1
    n = 40
    h = (b - a) / n
    xt = 0
    s = Fint(x, a) + Fint(x, b)

    for i in range(1, 40):
        xt = xt + h
        s = s + 2 * Fint(x, xt)
    s = s * h / 2

    return s

def system():
    w = []
    w.append([1, -1, 1, 0, 0, 0])
    w.append([1, 0, -1, 1, 0, 0])
    w.append([1, 0, 0, -1, 1, 0])
    w.append([1, 0, 0, 0, -1, 1])
    w.append([exp(x[0]), 0, -exp(x[2]), -2 * exp(x[3]), -3 * exp(x[4]), -4 * exp(x[5])])
    w.append([-exp(x[0]), -exp(x[1]), -exp(x[2]), -exp(x[3]), -exp(x[4]), -exp(x[5])])
    return w

def replace(w, x):
    size = len(w)
    row = max(range(x, size), key=lambda i: abs(w[i][x]))
    if x != row:
        w[x], w[row] = w[row], w[x]
    return w

def invert(w):
    n = len(w)
    for i in range(n):
        w[i] += [int(i == j) for j in range(n)]
    for x in range(n):
        w = replace(w, x)
        for i in range(x + 1, n):
            coef = w[i][x] / w[x][x]
            for j in range(x, n * 2):
                w[i][j] -= coef * w[x][j]
    for x in reversed(range(n)):
        for i in reversed(range(x)):
            coef = w[i][x] / w[x][x]
            for j in reversed(range(n * 2)):
                w[i][j] -= coef * w[x][j]
    for i in range(n):
        den = w[i][i]
        for j in range(n * 2):
            w[i][j] /= den
    for i in range(n):
        w[i] = w[i][n:]
    return w

def approximation(x, y):
    n_matrix = (len(y) + 1) * 2
    m_matrix = len(y) + 2
    matrix = [[0] * m_matrix for i in range(n_matrix)]

    j = 0
    for i in range(len(ttable)):
        matrix[j][0] = ttable[i]
        matrix[j][1] = y[i]
        j += 2

    shift = 1
    for j in range(2, m_matrix):
        for i in range(shift, n_matrix - shift, 2):
            matrix[i][j] = (matrix[i + 1][j - 1] - matrix[i - 1][j - 1]) / (matrix[i + shift][0] - matrix[i - shift][0])
        shift += 1

    y0 = 0
    kf = 1
    str = 0

    for i in range(m_matrix - 1):
        j = 0
        for k in range(str):
            kf *= (x - matrix[j][0])
            j += 2
        y0 += kf * matrix[0 + i][1 + i]
        kf = 1
        str += 1

    return y0

def k_mas(z):
    k = []
    t = T(z)
    Q = qmas(t)
    delt = deltae(z)
    for i in range(4):
        k.append(2 * 2.415 * 0.001 * Q[i + 1] / Q[i] * (t ** (1.5)) * exp(-(e[i] - delt[i]) * 11603 / t))

    return k

def qmas(t):
    q = []
    q.append(approximation(t, q1table))
    q.append(approximation(t, q2table))
    q.append(approximation(t, q3table))
    q.append(approximation(t, q4table))
    q.append(approximation(t, q5table))
    return q

def function(p, z):
    k = k_mas(z)
    func = []
    func.append(x[0] + x[2] - x[1] - log(k[0]))
    func.append(x[0] + x[3] - x[2] - log(k[1]))
    func.append(x[0] + x[4] - x[3] - log(k[2]))
    func.append(x[0] + x[5] - x[4] - log(k[3]))
    func.append(exp(x[0]) - (exp(x[2]) + 2 * exp(x[3]) + 3 * exp(x[4]) + 4 * exp(x[5])))
    func.append(p * 7242 / T(z) - exp(x[0]) - (exp(x[1]) + exp(x[2]) + exp(x[3]) + exp(x[4]) + exp(x[5])) + alpha(z))

    return func

def Fint(p, h):
    while(True):
        w = system()
        w = invert(w)
        f = function(p, h)
        t = multiply(w, f)
        vb = x[0]
        for i in range(len(x)):
            x[i] = x[i] - t[i]
        if (fabs(vb - x[0]) < eps):
            break

    summ = 0
    for i in range(1, len(x)):
        summ += exp(x[i])
    return summ * h

def multiply(m, s):
    res = []
    for i in range(len(s)):
        res.append(0)
        for j in range(len(s)):
            res[i] += m[i][j] * s[j]
    return res

def G(p, z):
    summ = 0
    for i in range(2, 6):
        summ += exp(x[i]) * (zin[i] ** 2) / (1 + (zin[i] ** 2) * p / 2)
    otv = p * p - 5.87 * (10 ** 10) / (T(z) ** 3) * (exp(x[0]) / (1 + p / 2) + summ)
    '''if (0 == z):
        print('g ', otv)'''
    return otv

def gamma(z):
    gam = dichtomii(0, 2, z, G)

    global gm
    gm = gam
    return gam

def deltae(z):
    delt = []
    gam = gamma(z)
    for i in range(4):
        delt.append(8.61 * (10 ** (-5)) * T(z) * log((1 + (zin[i + 1] ** 2) * gam / 2) * (1 + gam / 2) / (1 + (zin[i] ** 2) * gam / 2)))
    return delt

def alpha(z):
    return 0.285 * (10 ** (-11)) * ((T(z) * gamma(z)) ** 3)

def main():
    print(dichtomii(3, 25, 0, F))
    print()
    global x
    for el in x:
        print(exp(el))
    print('g ', exp(gm))

if __name__ == "__main__":
    main()
