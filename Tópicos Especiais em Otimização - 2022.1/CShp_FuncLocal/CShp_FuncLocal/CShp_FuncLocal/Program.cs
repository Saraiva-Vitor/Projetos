using System;
using static System.Console;

public static class RandomExtensionMethods
{
    public static double NextDoubleRange(this System.Random random, double minNumber, double maxNumber)
    {
        return random.NextDouble() * (maxNumber - minNumber) + minNumber;
    }
}

namespace CShp_FuncLocal
{
    class Program
    {
        static void Main(string[] args)
        {

            float x1 = random.NextDoubleRange(-10.0, 5.0); ;
            float x2 = random.NextDoubleRange(-6.0, 6.0); ;
            long resultado1 = Calculo.Calcular(x1);
            long resultado2 = Calculo.Calcular(x2);
            ReadKey();
        }
    }
}