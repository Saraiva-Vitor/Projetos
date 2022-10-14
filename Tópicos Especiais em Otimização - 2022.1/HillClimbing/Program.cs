using System;
using System.Diagnostics;

using CenterSpace.NMath.Core;
using CenterSpace.NMath.Analysis;
using CenterSpace.NMath.Matrix;

namespace CenterSpace.NMath.Analysis.Examples.CSharp
{
  /// <summary>
  /// A .NET example in C# showing how to use the stochastic hill 
  /// climbing solver <c>StochasticHillClimbingSolver</c> to solve a
  /// nonlinear programming problem.
  /// W. Hock, K. Schittkowski, Test Examples for Nonlinear Programming Codes.
  /// This is problem number 86.
  /// </summary>
  public class StochasticHillClimbingExample
  {
    public static void Main( string[] args )
    {
      // Create the objective function a an instance of a class derived from
      // DoubleFunctional.
      var f = new ObjectiveFunction();

      // Construct the nonlinear programming problem. There are
      // five constraints and each variable is required to be >= 0.
      var problem = new NonlinearProgrammingProblem( f );
      int numVars = 5;
      int numConstraints = 10;
      for ( int i = 0; i < numConstraints; i++ )
      {
        // Value of the ith constraint function must be >= 0.
        problem.AddLowerBoundConstraint( new ConstraintFunctions( i ), 0.0 );
      }
      for ( int i = 0; i < numVars; i++ )
      {
        // Each variable must be >= 0.
        problem.AddLowerBound( i, 0.0 );
      }

      // Create the solver object.
      var solver = new StochasticHillClimbingSolver();
      // The solver is stochastic. Setting a random seed before
      // the solver will ensure consistent results between runs.
      solver.RandomSeed = 0x248;

      // Create a solver parameter object and set a time limit for 
      // the solver. By default the solver will run until a solution
      // is found. Since this could take forever, it is a good idea to
      // set a reasonable time limit on the solve. Here we set the time
      // limit for ten seconds. If an optimal solution is not found within
      // the specified time limit the solver will exit and the solver's
      // Result property will be equal to SolverResult.SolverInterrupted.
      // We also specify that we want to presolve. By default there is no 
      // presolve step. For some problems presolve can reduce the size and 
      // complexity and result in fewer steps to reach a solution.
      var solverParams = new StochasticHillClimbingParameters 
      { 
        TimeLimitMilliSeconds = 10000,
        Presolve = true
      };

      // Attempt the solver and write out the results.
      solver.Solve( problem, solverParams );
      Console.WriteLine( "Solver Result = " + solver.Result );
      Console.WriteLine( "Number of steps = " + solver.Steps );
      Console.WriteLine( "Optimal x = " + solver.OptimalX.ToString( "F3" ) );
      Console.WriteLine( "Optimal function value = " + solver.OptimalObjectiveFunctionValue.ToString( "F3" ) );

      Console.WriteLine();
      Console.WriteLine( "Press Enter Key" );
      Console.Read();
    }


    /// <summary>
    /// Objective function. This is the function we want to minimize.
    /// </summary>
    class ObjectiveFunction : DoubleFunctional
    {
      /// <summary>
      /// Constants used in evaluating the objective function.
      /// </summary>
      private DoubleSymmetricMatrix c_;
      private DoubleVector d_;
      private DoubleVector e_;

      /// <summary>
      /// Constructs an instance of the objective function.
      /// </summary>
      public ObjectiveFunction()
        : base( 5 )
      {
        e_ = new DoubleVector( -15.0, -27.0, -36.0, -18.0, -12.0 );
        d_ = new DoubleVector( 4.0, 8.0, 10.0, 6.0, 2.0 );
        c_ = new DoubleSymmetricMatrix( 5 );
        c_[0, 0] = 30;
        c_[0, 1] = -20;
        c_[0, 2] = -10;
        c_[0, 3] = 32;
        c_[0, 4] = -10;

        c_[1, 1] = 39;
        c_[1, 2] = -6;
        c_[1, 3] = -31;
        c_[1, 4] = 32;

        c_[2, 2] = 10;
        c_[2, 3] = -6;
        c_[2, 4] = -10;

        c_[3, 3] = 39;
        c_[3, 4] = -20;

        c_[4, 4] = 30;
      }

      /// <summary>
      /// Evaluates the objective function at the given point.
      /// </summary>
      /// <param name="x">Evaluate at this point.</param>
      /// <returns>The objective function value at the point.</returns>
      public override double Evaluate( DoubleVector x )
      {
        double s1 = 0;
        double s2 = 0;
        double s3 = 0;
        for ( int i = 0; i < 5; i++ )
        {
          s1 += e_[i] * x[i];
          for ( int j = 0; j < 5; j++ )
          {
            s2 += c_[i, j] * x[i] * x[j];
          }
          s3 += d_[i] * Math.Pow( x[i], 3 );
        }
        return s1 + s2 + s3;
      }
    }

    /// <summary>
    /// Constraint functions for the nonlinear programming problem.
    /// Constraints contain five variables. Ten different constraint
    /// objects may be constructed.
    /// </summary>
    class ConstraintFunctions : DoubleFunctional
    {
      /// <summary>
      /// Coefficients for each of the ten different constraints.
      /// Each row of the matrix contains coefficients for the five
      /// variables.
      /// </summary>
      private static DoubleMatrix Adata;

      /// <summary>
      /// Constant values used in evaluating each of the ten different
      /// constraints.
      /// </summary>
      private static DoubleVector Bdata;

      /// <summary>
      /// References the variable coefficients for this constraint.
      /// </summary>
      private DoubleVector aRow_;

      /// <summary>
      /// The constant value for this constraint.
      /// </summary>
      private double bValue_;

      /// <summary>
      /// Initializes the static variable coefficient matrix and the vector
      /// of constants.
      /// </summary>
      static ConstraintFunctions()
      {
        var aData = new double[10, 5] { 
        {-16, 2, 0, 1, 0},
        {0, -2, 0, .4, 2},
        {-3.5, 0, 2, 0, 0},
        {0, -2, 0, -4, -1},
        {0, -9, -2, 1, -2.8},
        {2, 0, -4, 0, 0},
        {-1, -1, -1, -1, -1},
        {-1, -2, -3, -2, -1},
        {1, 2, 3, 4, 5},
        {1, 1, 1, 1, 1}
        };
        Adata = new DoubleMatrix( aData );
        Bdata = new DoubleVector( -40.0, -2.0, -.25, -4, -4, -1, -40, -60, 5, 1 );
      }

      /// <summary>
      /// Constructs an instance of one of the ten constraint functions. 
      /// </summary>
      /// <param name="i">Constraint function number. Must be between
      /// 0 and 9 inclusive.</param>
      /// <exception cref="InvalidArgumentException">Thrown if the constraint
      /// number is less than zero or greater than 9.</exception>
      public ConstraintFunctions( int i )
        : base( 5 )
      {
        if (i < 0 || i > Adata.Rows )
        {
          var msg = string.Format( "Invalid constraint number {0}. Must be between 0 and 9", i );
          throw new InvalidArgumentException( msg );
        }
        aRow_ = Adata.Row( i );
        bValue_ = Bdata[i];
      }

      /// <summary>
      /// Evaluates the constraint function at the given point.
      /// </summary>
      /// <param name="x">Point to evaluate at.</param>
      /// <returns>Constraint value at the given point.</returns>
      public override double Evaluate( DoubleVector x )
      {
        return NMathFunctions.Dot( aRow_, x ) - bValue_;
      }
    }
  }
}