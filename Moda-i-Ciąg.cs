using System;
using System.Collections.Generic;
using System.Linq;

namespace ConsoleApp1
{
    class Program
    {
        static void Main(string[] args)
        {
            List<int> list = new List<int>()
            {
                2, 4, 4, 4, 2, 7, 9, 9, 9, 9, 5, 1, 0, 5, 5, 4, 2, 4
            };

            foreach (var x in ZnajdźModę(list))
                Console.Write(x + " ");
            Console.WriteLine();

            Console.WriteLine(NajdłuższyCiąg(list));      
        }

        static List<int> ZnajdźModę(List<Int32> liczby)
        {
            List<Int32> uni = new List<int>();
            List<Int32> ilość = new List<int>();

            for (int i = 0; i < liczby.Count; i++)
            {
                if (uni.Contains(liczby[i]))
                    ilość[uni.IndexOf(liczby[i])]++;
                else
                {
                    uni.Add(liczby[i]);
                    ilość.Add(0);
                }
            }
            return ilość.Select((x, i) => x == ilość.Max() ? i : -1).
                Where(i => i != -1).ToList().Select(x => uni[x]).ToList();
        }

        static int NajdłuższyCiąg(List<Int32> liczby)
        {
            int max = 0;
            for (int i = 1, ciąg = 0; i < liczby.Count; i++)
            {
                if (liczby[i] != liczby[i - 1])
                {
                    if (max < ciąg) max = ciąg;
                    ciąg = 0;
                }
                else ciąg++;
            }
            return max + 1;
        }
    }
}
