using System;
using System.Security.Cryptography.X509Certificates;

namespace Algorytmy
{
    public static class Matma
    {
        public const double PI = 3.41592653589793238462643383279502884197169399375;

        public static double Potęga(double x, double y, bool recurring = false, ulong skipped_decimals = 0)
        {
            double y_base = y;
            y = Matma.Abs(y);

            // Rozdzielenie x na iloczyn potęg (ex. x^-3.21 = (x^3 * x^0.21)^-1 = 1/(x^3 * x^0.21))
            ulong y_N = (ulong)y;
            double x1 = FastPow(x, y_N);
            double x2 = RootDecimal(x, (double)((decimal)y - y_N), recurring, skipped_decimals);

            x = x1 * x2; ;
            if (y_base < 0) x = 1 / x;

            return x;
        }

        private static double RootDecimal(double x, double y, bool rec, ulong skip)
        {
            ulong[] set = ZamieńNaUłamek(y, rec, skip);

            // ZBYT DUŻE LICZBY DLA:
            // x^(y/root) = root√(x^y) => set[1]√(x^set[0])
            /* x = Matma.FastPow(x, set[0]);
            return Pierwiastek(x, set[1); */

            // x^(y/root) = (root√x)^y => (set[1]√x)^set[0]
            x = Pierwiastek(x, set[1]);
            return Matma.FastPow(x, set[0]);
        }

        public static ulong[] ZamieńNaUłamek(double y, bool recurring = false, ulong skipped_decimals = 0)
        {
            // Konwersja liczby rzeczywistej na ułamek liczb naturalnych
            ulong root = 1;
            decimal p = (decimal)y;
            while (p % 1.0m != 0)
            {
                p *= 10.0m;
                root *= 10;
            }
            y = (double)p;

            // Suma szeregu geometrycznego dla ułamka okresowego
            if (recurring && root != 1)
            {
                ulong root1 = (ulong)FastPow(10, skipped_decimals);
                if (root1 < root)
                {
                    // (ex. y = 0.213, skip = 2 => root1 = 100, root2 = 1000, y1 = 21, y2 = 3 => (y1/root1 + y2/root2) = szukany ułamek)
                    ulong root2 = root;

                    ulong y1 = (ulong)(y / (root2 / root1));
                    ulong y2 = (ulong)(y - (y1 * (root2 / root1)));

                    // Po wykonaniu dużej ilości przekształceń wzoru (S = a1/1-q) mianownik sumy szeregu wynosi: 
                    root2 = root2 - root1;

                    // Wspólny ułamek
                    y1 *= root2 / Matma.NWD(root1, root2);

                    y = y1 + y2;
                    root = root2;
                }
                // Szereg: a1/(1 - q) => (p / root)/(1 - 1/root) => p/(root - 1)
                else --root;
            }

            // Uproszczenie
            ulong nwd = Matma.NWD((ulong)y, root);
            y /= nwd;
            root /= nwd;

            return new ulong[] { (ulong)y, root };
        }

        public static double Pierwiastek(double x, ulong y)
        {
            // Algorytm pierwiastkowania 
            // https://pl.wikipedia.org/wiki/Algorytm_obliczania_pierwiastka_n-tego_stopnia
            if (x >= 0 || y % 2 != 0)
            {
                double x_base = x, x_new = x;
                do
                {
                    x = x_new;
                    x_new = (1.0 / y * (((y - 1.0) * x) + (x_base / FastPow(x, y - 1))));
                } while (Abs(x - x_new) > 1e-10);
                return x_new;
            }
            else return double.NaN;
        }

        public static double FastPow(double x, ulong y)
        {
            // Algorytm szybkiego potęgowania dla y będącą liczbą naturalną
            if (y == 0) return 1;
            if (y % 2 == 0)
            {
                x = FastPow(x, y / 2);
                return x * x;
            }
            else return x * FastPow(x, y - 1);
        }

        public static double Abs(double x)
        {
            if (x >= 0) return x;
            else return -x;
        }

        public static ulong NWD(ulong a, ulong b)
        {
            ulong c;
            while (b != 0)
            {
                c = a % b;
                a = b;
                b = c;
            }
            return a;
        }

        public static ulong NWW(ulong a, ulong b)
        {
            return a * (b / NWD(a, b));
        }

        // Useless
        private static double IterPow(ulong x, ulong y)
        {
            ulong result = 1, counter = 1;
            while (y > 0)
            {
                if (y % 2 == 0)
                {
                    y = y / 2;
                    x = x * x;
                }
                else
                {
                    y = y - 1;
                    result = x * result;
                }

                y = y / 2;
                x = x * x;

                counter++;
            }

            Console.WriteLine(counter);
            return result;
        }
    }
}

/*
Matma: 1,9493592617830977
Math: 1,9493592617830977
1,0123123123123123123131231231
Matma: 2,82842712474619
Math: 2,8284271247461903
NaN
-3
2
1,9999986137061194
---------------------
16
75

D:\Virtual Stuff\Repos\CsharpProject\RandomProj\bin\Debug\netcoreapp3.1\TestProj.exe (process 16100) exited with code 0.
Press any key to close this window . . . 

 */