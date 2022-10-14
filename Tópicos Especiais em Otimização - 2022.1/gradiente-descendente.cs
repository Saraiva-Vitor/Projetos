using System;

namespace ConsoleApp3
{
    class Program
    {
        private const double EPSILON = 0.001;
        //funçao x^3 - x^2  + 2
        static double func(double x)
        {
            return x * x * x - x * x + 2;
        }

        // derivada 3*x^x - 2*x
        static double derivFunc(double x)
        {
            return 3 * x * x - 2 * x;
        }
        static void newtonRaphson(double x)
        {
            int iteraçao = 0;
            double h = func(x) / derivFunc(x);
            while (Math.Abs(h) >= EPSILON)
            {
                h = func(x) / derivFunc(x);

                // x(i+1) = x(i) - f(x) / f'(x)  
                x = x - h;
                iteraçao++;
                Console.WriteLine("Iteraçao = {0} - raiz = {1}", iteraçao, x);
            }

            Console.WriteLine("A raiz é {0} em {1} iteraçoes", x, iteraçao);
        }


        static void Main(string[] args)
        {
            Console.WriteLine("Método de Newton-Raphson");
            double x0 = -20; // valor inicial
            newtonRaphson(x0);
            Console.ReadKey();
        }
    }
}