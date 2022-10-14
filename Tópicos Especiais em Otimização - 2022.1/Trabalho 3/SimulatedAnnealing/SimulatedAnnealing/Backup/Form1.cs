using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;

namespace SimulatedAnnealing
{
	/// <summary>
	/// created by assaad chalhoub
	/// 2006
	/// </summary>
	public class Form1 : System.Windows.Forms.Form
	{
		private System.Windows.Forms.Button BtnAnnealing;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;
Annealing ann = new Annealing();
		public Form1()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
		}
		
		
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if (components != null) 
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.BtnAnnealing = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// BtnAnnealing
			// 
			this.BtnAnnealing.Location = new System.Drawing.Point(88, 48);
			this.BtnAnnealing.Name = "BtnAnnealing";
			this.BtnAnnealing.Size = new System.Drawing.Size(104, 23);
			this.BtnAnnealing.TabIndex = 0;
			this.BtnAnnealing.Text = "Go Annealing!";
			this.BtnAnnealing.Click += new System.EventHandler(this.BtnAnnealing_Click);
			// 
			// Form1
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(292, 266);
			this.Controls.Add(this.BtnAnnealing);
			this.Name = "Form1";
			this.Text = "Form1";
			this.ResumeLayout(false);

		}
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new Form1());
		}

		private void BtnAnnealing_Click(object sender, System.EventArgs e)
		{
			string distance=	ann.StartAnnealing();
		MessageBox.Show(distance);
		}
	}
}
