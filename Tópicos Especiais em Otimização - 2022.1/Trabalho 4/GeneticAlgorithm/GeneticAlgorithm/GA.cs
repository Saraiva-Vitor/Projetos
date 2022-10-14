using System;

class GeneticAlgorithm
{
    static int d = 2;

    static double griekwank(double[] x)
    { //Minimo global = 0 em (0, …, 0)
        double sum = 0;
        double prod = 1;
        for (int i = 0; i < x.length; x++) sum += Math.pow(x[i], 2);
        for (int i = 0; i < x.length; x++) prod *= Math.cos(x[i] / Math.sqrt(i));
        return 1 + sum / 4000 - prod;
    }

    static double schaffer(double[] x)
    { //Minimo global = 0 em (0, 0)
        double x02 = Math.pow(x[0], 2);
        double x12 = Math.pow(x[1], 2);
        double ret = 0.5;
        ret += (Math.pow(Math.sin(x02 - x12), 2) - 0.5) / Math.pow((1 + 0.001 * (x02 + x12)), 2);
        return ret;
    }

    static bool[] geracao_aleatoria()
    {
        bool[] v = new bool[d];
        System.Random random = new System.Random();
        for (int i = 0; i < d - 1; i++)
        {
            if (0.5 > random.NextDouble())
            {
                v[i] = true;
            }
            else
            {
                v[i] = false;
            }
        }
        return v;
    }

    static bool[] mutacao(bool[] v)
    {
        p = 0.5  //probabilidade    
        System.Random random = new System.Random();
        for (int i = 0; i < d - 1; i++)
        {
            if (p >= random.NextDouble())
            {
                v[i] = !v[i];
            }
        }
        return v;
    }


    static bool[], bool[] crossover1Point(bool[] v, bool[] w)
    {
        c = random(random.NextDouble() * (d - 1) + 1);
        if (c != 1)
        {
            for (int i = c; i < d; i++)
            {
                Swap(v[i], w[i]);
            }
        }

        return v, w;
    }

    static bool[], bool[] crossover2Point(bool[] v, bool[]w)
    {

        c = random(random.NextDouble() * (d - 1) + 1);
        d = random(random.NextDouble() * (d - 1) + 1);

        if (c > d)
        {
            Swap(c, d);
        }

        if (c != d)
        {
            for (int i = c; i < d; i++)
            {
                Swap(v[i], w[i]);
            }
        }

        return v, w;
    }

    static bool[] selecao()
    {

    }


    public static void Main(string[] args)
    {
        int popsize = 10;
        bool[] p = new bool[popsize];
        double best= 0;

        bool[] v = geracao_aleatoria();
        bool[] w = geracao_aleatoria();

        for (int i = 0; i < popsize; i++)
        {
            p[i] = p[random(random.NextDouble() * (popsize - 0) + 0)];
        }
        best = p[0];

        while (count < 1000)
        {
            for (int i = 0; i < popsize; i++)
            {
                Fitness(p[i]);
                if (Fitness(p[i]) < Fitness(best))
                {
                    best = p[i];
                }
            }
            bool[] q = new bool[popsize];
            for (int i = 0; i < popsize/2; i++)
            {
                Pa = SelecionaREPOSICAO(p);
                Pb = SelecionaREPOSICAO(p);
                Pa_aux = Pa;
                Pb_aux = Pb;
                Ca, Cb = cross1Point(Pa_aux, Pb_aux);
                q = q + (mutacao(Ca),mutacao(Cb));
            }
            p = q;
            count++;
        }
    }//fecha a main
}//fecha a classe