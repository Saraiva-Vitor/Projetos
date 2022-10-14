using Imsl.Chart2D;
using System;
using System.Drawing;

public class SampleFunction : FrameChart {

    public SampleFunction() {
        Chart chart = this.Chart;
        AxisXY axis = new AxisXY(chart);

        Data data = new Data(axis, new sinc(), -10.0, 10.0);
        data.LineColor = Color.Blue;
    }

    public static void Main(string[] argv) {
        System.Windows.Forms.Application.Run(new SampleFunction());
    }
}

class sinc : ChartFunction {
    public double F(double x) {
        if (x == 0.0) return 1.0;
        return Math.Sin(Math.PI*x) / (Math.PI*x);
    }
}
