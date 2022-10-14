using System;
using System.IO;

namespace SimulatedAnnealing
{
	/// <summary>
	/// Summary description for TspDataReader.
	/// </summary>
	public class TspDataReader
	{
		
			private static string file="tsp.txt";
			private static int dim=15;
			private static double[,]data;

		public static double computeDistance(int[] t)
		{
			int dist=0;
			for(int i=0;i<dim-1;i++)
				dist +=Convert.ToInt32(data[t[i],t[i+1]]);
			dist+=Convert.ToInt32(data[t[dim-1],t[0]]);
			return dist;
		}

		public TspDataReader()
		{

			//
			// TODO: Add constructor logic here
			//
		}
		public static double[,] getData()
		{
			return data;
		}
    
		public static void computeData()
		{
			String line;
			data=new double[dim,dim];
        
			try
			{
			 StreamReader str = new StreamReader(System.Windows.Forms.Application.StartupPath+"\\tsp.txt");
				for(int i=0;i<dim;i++)
				{
					line=str.ReadLine();
				string[]	st=line.Split(' ');
					for(int j=0;j<dim;j++)
						data[i,j]= Double.Parse(st[j]);
				}
				str.Close();
			}
			catch(FileNotFoundException e)
			{
				Console.WriteLine(e.ToString());
			}
			catch(IOException e)
			{
				Console.WriteLine(e.ToString());
			}
        
		}
	}
}
