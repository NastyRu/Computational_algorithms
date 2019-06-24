from tabulate import tabulate
a0, a1, a2 = 1, 2, 3

def f(x):
    return a0 * x / (a1 + a2 * x)

def p(x):
    return (a0 * (a1 + a2 * x) - a2 * a0 * x) / (a1 + a2 * x) ** 2

def arg(a, b, h):
    x = []
    for i in range (a, b + h, h):
        x.append(i)
    return x

def pprint(s, x):
    print(s, end = '\t')
    for el in x:
        if (el != None):
            print("%.4f" % el, end = '\t')
        else:
            print(el, end = '\t')
    print()

def function(x):
    y = []
    for el in x:
        y.append(f(el))
    return y

def derivate(x):
    d = []
    for el in x:
        d.append(p(el))
    return d

def left_div(y, h):
    d = []
    d.append(None)
    for i in range(1, len(y)):
        d.append((y[i] - y[i - 1]) / h)
    return d

def centr_div(y, h):
    d = []
    d.append(None)
    for i in range (1, len(y) - 1):
        d.append((y[i + 1] - y[i - 1]) / 2 / h)
    d.append(None)
    return d

def runge(left, centr):
    r = 2
    p = 1
    rn = []
    rn.append(None)
    rn.append(None)
    for i in range (2, len(left)):
        rn.append(left[i] + (left[i] - centr[i - 1]) / (r ** p - 1))
    return rn

def alline(y, x):
    p = []
    for i in range (len(x)):
        if (0 == x[i]):
            p.append(None)
            continue
        p.append(y[i] * a1 / x[i] / (a1 + a2 * x[i]))
    return p

def gran(y, h):
    p = []
    p.append((-3 * y[0] + 4 * y[1] - y[2]) / 2 / h)
    for i in range (len(y) - 2):
        p.append(None)
    p.append((3 * y[len(y) - 1] - 4 * y[len(y) - 2] + y[len(y) - 3]) / 2 / h)
    return p

def main():
    a = int(input("Нижняя граница "))
    b = int(input("Верхняя граница "))
    h = int(input("Шаг "))

    x = arg(a, b, h)
    y = function(x)
    d = derivate(x)
    ld = left_div(y, h)
    cd = centr_div(y, h)
    al = alline(y, x)
    pprint("x                              ", x)
    pprint("y                              ", y)
    pprint("y'                             ", d)
    pprint("Левосторонняя разность         ", ld)
    pprint("В крайних узлах                ", gran(y, h))
    pprint("Центральная разность           ", cd)
    pprint("Рунге с левосторонней разностью", runge(ld, cd))
    pprint("Выравнивающие                  ", al)

if __name__ == "__main__":
    main()
