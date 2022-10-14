using System;

class SimulatedAnnealingTrabalho
{
    static int d = 2;
    static double y;
    static double vmin = -5.12;
    static double vmax = 5.12;

      static double Funcao(double[] x){
        //Rastrigin
        int A = 10;
        for (int i = 0; i < d-1; i++){
          y = Math.Pow(x[i],2) - A*Math.Cos(2*Math.PI*x[i]);
        }
        return (A*d) + y;

        /*/Rosenbrock
        y = 0;
        for (int i = 0; i < d-1; i++)
        {
            y += 100 * Math.Pow(x[i + 1] - Math.Pow(x[i], 2), 2) + Math.Pow(x[i] - 1, 2);
        }
        return y;*/
    }


    static double[] Tweak(double[] v, double n)
    {
        //Valor aleatorio
        double ruido = 2;
        int nint = (int)ruido;
        int p = 1;
        for (int i = 0; i < ruido; i++)
        {
            System.Random random = new System.Random();
            if (p >= random.NextDouble())
            {
                while ((v[i] + n) < vmin || (v[i] + n) > vmax)
                {
                    n = (random.NextDouble() * (ruido - (-ruido)) + (-ruido));
                }
            }
            v[i] = v[i] + n;
        }
        return v;
    }

    static bool Quality(double[] possivelideal, double[] atual)
    {
        //Validar qualidade
        if (Funcao(possivelideal) < Funcao(atual))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    public static void Main(string[] args)
    {
        // Numero de perturbações desejadas
        double n = 10;
        System.Random random = new System.Random();
        double[] s = new double[d];// Atribuir com n valores aleatórios
        for (int i = 0; i < 2; i++)
        {
            s[i] = (random.NextDouble() * (vmax - vmin) + vmin);
        }

        double[] best = s;
        double[] r = new double[d];

        double t = 1000;
        double alpha = 0.8;

        int count = 0;
        int tweaks = 0;
        while (count < 1000 && t > 0)
        {
            Console.WriteLine("\nIteração = " + String.Join("", count));
            double[] saux = new double[d];
            for (int i = 0; i < d; i++) saux[i] = s[i];
            r = Tweak(saux, n);
            Console.WriteLine("S = " + String.Join("\t", s));
            bool qual = Quality(r, s);
            double tw = random.NextDouble();
            double rb = Math.Pow(Math.E, (Funcao(r) - Funcao(s)) / t);
            /*if (tw < rb)
            {
                Console.WriteLine(String.Format("Fez tweak por tw < rb: {0:C4}\t{1:C4}", tw, rb));
                Console.WriteLine(String.Format("vetor r: {0:C4}\t{1:C4}", r[0], r[1]));
                Console.WriteLine(String.Format("vetor s: {0:C4}\t{1:C4}\n", s[0], s[1]));
            }
            Console.WriteLine("RB = " + String.Join("\t", rb));
            Console.WriteLine("TW = " + String.Join("\t", tw));*/
            if (qual || tw < rb)
            {
                tweaks++;
                Console.WriteLine("R melhor que S");
                s = r;
            }
            Console.WriteLine("S = " + String.Join("\t", s));
            if (Quality(s, best))
            {
                Console.WriteLine("S melhor que Best");
                //Console.WriteLine("S = " + String.Join("\t", s));
                //Console.WriteLine("R = " + String.Join("\t", best));
                best = s;
            }
            count++;
            t = t * Math.Pow(alpha, 2);

            Console.WriteLine("Temperatura = " + String.Join("", t));
            Console.WriteLine("Best = " + String.Join("\t", best));
            Console.WriteLine("F(Best) = " + String.Join("\t", Funcao(best)));
            if (qual) Console.WriteLine("Fez tweak por qualidade do tweak");
            if (tw < rb)
            {
                Console.WriteLine(String.Format("Fez tweak por tw < rb: {0:C4}\t{1:C4}", tw, rb));
                //Console.WriteLine(String.Format("vetor r: {0:C4}\t{1:C4}", r[0], r[1]));
                //Console.WriteLine(String.Format("vetor s: {0:C4}\t{1:C4}\n", s[0], s[1]));
            }
            //String.Format("The current price is {0:C2} per ounce.",pricePerOunce);
        }//fecha o while
         //Console.WriteLine("S = " + String.Join("\t", s));
         //Console.WriteLine("R = " + String.Join("\t", r));
        Console.WriteLine("\nBest = " + String.Join("\t", best));
        Console.WriteLine("\nF(Best) = " + String.Join("\t", Funcao(best)));
        if (t != 0)
        {
            Console.WriteLine("Tempo Esgotado\t" + String.Join("", tweaks));
        }
    }//fecha a main
}//fecha a classe