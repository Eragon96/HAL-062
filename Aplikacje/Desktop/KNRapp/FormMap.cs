using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace KNRapp
{
    public partial class FormMap : Form
    {
        public FormMap()
        {
            InitializeComponent();
            this.pictureBox1.Image = Image.FromFile("../pics/MAP2.png");
            //pictureBox2.Location = pictureBox1.Location;
            //pictureBox2.Size = pictureBox1.Size;
            
        }

        

        private void FormMap_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                double latitude;
                double longitude = 100;
                double.TryParse(textBox1.Text,out latitude);
                double.TryParse(textBox2.Text,out longitude);
                drawPoint(coordinatesToPosition( latitude, longitude));
            }
            catch (System.FormatException)
            {
                textBox1.Text = "tak nie wolno";
            }

        }

        private Point coordinatesToPosition(double latitude, double longitude)
        {
            double left = 38.413416;    //longtitude
            double right = 38.400531;
            double top = 110.792499;   //latitude
            double bottom = 110.778914;
            double height = pictureBox1.Size.Height;
            double width = pictureBox1.Size.Width;
            double xd2 = right - left;
            double xd1 = latitude - left;
            double xd3 = width * ((latitude - left) / (right - left));

            int y = (int)(height * (((latitude) - left) / (right - left)));
            int x = (int)(width - (width * (((-longitude) - bottom) / (top - bottom))));
            textBox3.Text = "" + xd1;
            textBox4.Text = "" + xd2;
            textBox5.Text = "" + xd3;
            return new Point( x, y);
        }
        private void drawPoint(Point point)
        {
            Graphics g = this.pictureBox1.CreateGraphics();
            Pen pen = new Pen(Color.Black);
            g.DrawLine(pen, point,new Point( 1000, 1000));
        }
    }
}
