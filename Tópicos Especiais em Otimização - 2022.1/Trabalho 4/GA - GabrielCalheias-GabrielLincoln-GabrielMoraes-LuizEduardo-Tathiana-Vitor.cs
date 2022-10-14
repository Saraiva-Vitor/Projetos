using System;
using System.Diagnostics.Metrics;
using System.Text;

class GeneticAlgorithm
{
    static int length = 2;
    static int popsize = 10;
    static Random r = new Random();
    static int fitcall = 0;
    static int fitzero = 0;


    static double griekwank(bool[] x)
    { //Minimo global = 0 em (0, …, 0)
        fitcall++;
        if (!x[0] && !x[1]) fitzero++;
        double sum = 0;
        double prod = 1;
        for (int i = 0; i < length; i++) sum += Math.Pow(x[i] ? 1.0 : 0.0, 2);
        for (int i = 0; i < length; i++) prod *= Math.Cos((x[i] ? 1.0 : 0.0) / (Math.Sqrt(i+1)));
        return 1 + sum / 4000 - prod;
    }

    static double schaffer(bool[] x)
    { //Minimo global = 0 em (0, 0)
        fitcall++;
        if (!x[0] && !x[1]) fitzero++;
        double x02 = Math.Pow(x[0] ? 1.0 : 0.0, 2);
        double x12 = Math.Pow(x[1] ? 1.0 : 0.0, 2);
        double ret = 0.5;
        ret += (Math.Pow(Math.Sin(x02 - x12), 2) - 0.5) / Math.Pow((1 + 0.001 * (x02 + x12)), 2);
        return ret;
    }

    static bool[] geracao_aleatoria()
    {
        bool[] v = new bool[length];
        for (int i = 0; i < length; i++)
        {
            if (0.5 > r.NextDouble()) v[i] = true;
            else v[i] = false;
        }
        return v;
    }

    static bool[] mutacao(bool[] v)
    {
        double p = 0.5;  //probabilidade    
        for (int i = 0; i < length; i++)
        {
            if (p >= r.NextDouble()) v[i] = !v[i];
        }
        return v;
    }

    static double individuo2ToDouble(bool[] p)
    {
        double d = 0.0;
        if (p[0]) d += 1.0;
        if (p[1]) d += 2.0;
        return d;
    }

    static void Swap(bool[] a, bool[] b, int v)
    {
        bool x = a[v];
        a[v] = b[v];
        b[v] = x;
    }

    static (bool[], bool[]) crossover1Point(bool[] v, bool[] w)
{
        int c = r.Next(0, length);
        if (c != 1)
        {
            for (int i = c; i < length; i++) Swap(v, w, i);
        }

        return (v , w);
    }

    static (bool[], bool[]) crossover2Point(bool[] v, bool[] w)
    {
        int c = r.Next(0, length);
        int d = r.Next(0, length);

        if (c > d)
        {
            int aux = c;
            d = c;
            c = aux;
        }

        if (c != d)
        {
            for (int i = c; i < d; i++) Swap(v, w, i);
        }

        return (v, w);
    }

    static int selecao(bool[][] pop, int popsize)
    {
        double[] fitness = new double[popsize];
        double sum = 0;
        for (int i = 0; i < popsize; i++)
        {
            double aux = griekwank(pop[i]);
            sum += aux;
            fitness[i] = aux;
            //Console.WriteLine(fitness[i]);
        }

        double S = r.NextDouble() * sum;
        for (int i = 0; i < popsize; i++)
        {
            S -= fitness[i];
            if (S < 0.0) return i;
        }
        return length-1;
    }

    static void printadora(bool[] individuo)
    {
        Console.WriteLine(String.Format("Individuo: {0}\t{1}\t{2:C4}", individuo[0], individuo[1], griekwank(individuo)));
    }


    public static void Main(string[] args)
    {
        bool[][] p = new bool[popsize][];
        bool[] best = new bool[length];
        double fbest = 1.0/0.0;

        for (int i = 0; i < popsize; i++) p[i] = new bool[length];

        bool[] v = geracao_aleatoria();
        bool[] w = geracao_aleatoria();

        for (int i = 0; i < popsize; i++)
        {
            bool[] paleatorio = geracao_aleatoria();
            for (int j = 0; j < length; j++)
            {
                p[i][j] = paleatorio[j];
            }
        }

        for (int j = 0; j < length; j++)
        {
            best[j] = p[0][j];
        }

        fbest = griekwank(best);

        int count = 0;
        int bestcount = 0;
        while (count < 1000)
        {
            Console.WriteLine("\nIteração: " + count);
            for (int i = 0; i < popsize; i++)
            {
                //griekwank(p[i]);
                //Console.WriteLine("Fitness: " + griekwank(p[i]));
                if (griekwank(p[i]) < griekwank(best))
                {
                    best = p[i];
                    fbest = griekwank(best);
                }
            }

            Console.WriteLine("Best: " + best[0] + " " + best[1]);

            bool[][] q = new bool[popsize][];
            for (int i = 0; i < popsize; i++) q[i] = new bool[length];

            for (int i = 0; i < popsize / 2; i++)
            {
                bool[] Pa = p[selecao(p,popsize)];
                bool[] Pb = p[selecao(p, popsize)];
                bool[] Pa_aux = Pa;
                bool[] Pb_aux = Pb;
                //(bool[] Ca, bool[] Cb) = crossover1Point(Pa_aux, Pb_aux);
                (bool[] Ca, bool[] Cb) = crossover2Point(Pa_aux, Pb_aux);
                Console.WriteLine("Ca: " + Ca[0] + " " + Ca[1]);
                Console.WriteLine("Cb: " + Cb[0] + " " + Cb[1]);
                q[i] = mutacao(Ca);
            }
            p = q;
            for (int i = 0; i < popsize; i++) if (!p[i][0] && !p[i][1]) bestcount++;
            count++;
        }/*
        for(int i=0; i < popsize; i++)
        {
            printadora(p[i]);
        }*/
        Console.WriteLine("\nVezes no Zero: " + bestcount);
        Console.WriteLine("Vezes que (0 0) Entrou na Fitness: " + fitzero);
        Console.WriteLine("Vezes que Entrou na Fitness: " + fitcall);
        Console.WriteLine("Esforço relativo à Iteração: " + ((bestcount*1.0)/10000)*100 + " %");
        Console.WriteLine("Esforço relativo à Fitness: " + ((fitzero*1.0)/(fitcall*1.0)*100) + " %");
        
        /*
        Console.WriteLine("\n");
        bool[] tmp = {false ,false};
        bool[] tmp1 = { false, true };
        bool[] tmp2 = { true, false };
        bool[] tmp3 = { true, true };
        Console.WriteLine("0 0 :" + griekwank(tmp));
        Console.WriteLine("0 1 :" + griekwank(tmp1));
        Console.WriteLine("1 0 :" + griekwank(tmp2));
        Console.WriteLine("1 1 :" + griekwank(tmp3));*/
    }//fecha a main
}//fecha a classe


