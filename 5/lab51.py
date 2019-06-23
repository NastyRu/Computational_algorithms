eps = 0.0001

Pn = float(input("Рнач = "))
Tn = int(input("Тнач = "))
To = int(input("То = "))
Tw = int(input("Тw = "))
m = int(input("m = "))

def F(x):
    return 7242 * Pn / Tn - 2 * x * iint()

def Fint(z):
    return 7242 / T(z) * z

def T(z):
    return To + (Tw - To) * z ** m

def dichtomii():
    a = 3
    b = 25
    f_a = F(a)
    f_b = F(b)

    while (b - a) > eps:
        x = (a + b) / 2
        f_x = F(x)

        if (f_a * f_x <= 0):
            b = x
            f_b = f_x
        else:
            a = x
            f_a = f_x

    return (a + b) / 2

def iint():
    a = 0
    b = 1
    n = 40
    h = (b - a) / n
    s = Fint(a) + Fint(b)
    x = 0

    for i in range(1, 40):
        x = x + h
        s = s + 2 * Fint(x)
    s = s * h / 2

    print(4 * s)
    return s

def main():
    print(dichtomii())

if __name__ == "__main__":
    main()
