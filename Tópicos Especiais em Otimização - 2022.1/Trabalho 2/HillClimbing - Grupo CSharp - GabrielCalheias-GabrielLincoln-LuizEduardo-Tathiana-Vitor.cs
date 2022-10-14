using System;

namespace Trabalho{
  class HillClimbingTrabalho {
    static double y;
    static double vmin = -5;
    static double vmax = 10;
  
    
    static double Rosenbrock(double [] x){
      int d = 2;
      for(int i=0;i<d-1;i++){
        y = 100*Math.Pow(x[i+1]-Math.Pow(x[i],2),2) + Math.Pow(x[i]-1,2);
      }
      return y;
    }
    
    static double[] Tweak(double[] v,double n){
      //Valor aleatorio
      double ruido = 2;
      int nint = (int)ruido; 
      int p = 1; 
      for (int i = 0; i<ruido; i++){
        System.Random random = new System.Random();
        if (p >= random.NextDouble()){
         while ((v[i] + n) < vmin || (v[i] + n) > vmax){
           n = (random.NextDouble() * (ruido - (-ruido)) + (-ruido)); 
         } 
        }
        v[i] = v[i] + n; 
      }
      return v;
    }
  
    static bool Quality(double[] possivelideal, double[] atual){
      //Validar qualidade
      if(Rosenbrock(possivelideal) > Rosenbrock(atual)){
        return true;
      }
      return false;
    }

    public static void Main(string[] args) {
      // Numero de perturbações desejadas
      double n = 10;
      System.Random random = new System.Random();
      double [] s = new double[2];// Atribuir com n valores aleatórios
      for(int i=0;i<2;i++){
        s[i] = (random.NextDouble() * (vmax - vmin) + vmin);
      }
      double[] best = s;
      double [] r = new double[2];
    
      int count = 0;
      while(count <= 1000){
        double[] saux = s;
        r = Tweak(saux,n);
        if(Quality(r,s) == true){
            s = r;
        }
        count++;
      }//fecha o while
      if(Quality(s,best) == true){
        best = s;
      }
      Console.WriteLine ($" s é: {s}");
      Console.WriteLine ($" r é: {r}");
      Console.WriteLine ($"O melhor ponto é: {best}");
    }//fecha a main
  }//fecha a classe
}//fecha o programa