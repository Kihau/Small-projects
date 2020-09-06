using System;

namespace Algorytmy
{
    public static class Matma
    {
        public const double PI = 3.41592653589793238462643383279502884197169399375;

        public static double WyliczPI(int n)
        {
            /*                      XDDDDDDDDD
                                        |
                                        |
                                        V  
             */
            double Pi = Math.Sin(2 * Matma.PI / Matma.FastPow(2, (uint)n)) * Matma.FastPow(2, (uint)n);
            return Pi;
        }

        public static double Potęga(double x, double y)
        {
            double y_base = y;
            y = Matma.Abs(y);

            // Rozdzielenie x na iloczyn potęg (ex. x^-3.21 = (x^3 * x^0.21)^-1 = 1/(x^3 * x^0.21))
            ulong y_N = (ulong)y;
            double x1 = FastPow(x, y_N);
            double x2 = RootPow(x, (double)((decimal)y - y_N));

            x = x1 * x2;
            if (y_base < 0) x = 1 / x;

            return x;
        }

        private static double RootPow(double x, double y)
        {
            // Konwersja liczby rzeczywistej na ułamek liczb naturalnych
            ulong root = 1;
            decimal p = (decimal)y;
            while (p % 1 != 0)
            {
                p *= 10;
                root *= 10;
            }

            // Uproszczenie
            ulong nwd = Matma.NWD((ulong)p, root);
            // Zmniejszyć dokładność dla p > 100000 (ex. 127841 - 12784)
            p /= nwd;
            root /= nwd;

            // x^(y/root) = root√(x^y)
            x = Matma.FastPow(x, (ulong)p);
            return Pierwiastek(x, root);
        }

        public static double Pierwiastek(double x, ulong y)
        {
            if (x >= 0 || y % 2 != 0)
            {
                // Algorytm pierwiastkowania 
                // https://pl.wikipedia.org/wiki/Algorytm_obliczania_pierwiastka_n-tego_stopnia
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