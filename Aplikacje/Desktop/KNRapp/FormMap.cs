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
            imgOrginal = pictureBox1.Image;
            pictureBox2.Location = pictureBox1.Location;
            pictureBox2.Size = pictureBox1.Size;
            pictureBox2.Image = pictureBox1.Image;
            this.MouseWheel += new MouseEventHandler(mouse_Wheel);
            this.trackBar1.ValueChanged += new EventHandler(trackBar1_Scroll);
        }

        Image imgOrginal;

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
            
            return new Point( x, y);
        }

        private void drawPoint(Point point)
        {
            Graphics g = this.pictureBox1.CreateGraphics();
            Pen pen = new Pen(Color.Black);
            g.DrawLine(pen, point,new Point( 1000, 1000));
        }

        Image zoom(Image img, Size size)
        {
            Bitmap bmp = new Bitmap ( img, img.Width + (img.Width * size.Width / 100), img.Height + (img.Height * size.Height / 100));
            Graphics g = Graphics.FromImage(bmp);
            g.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.HighQualityBicubic;
            return bmp;
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            if(trackBar1.Value > 0)
            {
                pictureBox2.Image = zoom(pictureBox1.Image,new Size(trackBar1.Value,trackBar1.Value));
            }
        }

        private void mouse_Wheel(object sender, MouseEventArgs e)
        {
            textBox5.Text = "" + e.Delta / 120;
            try
            {
                if (trackBar1.Value < trackBar1.Maximum - 1 && e.Delta > 0) { trackBar1.Value += e.Delta / 120; }
                else if (trackBar1.Value > trackBar1.Minimum + 1 && e.Delta < 0) { trackBar1.Value += e.Delta / 120; }
            } catch (ArgumentOutOfRangeException) {
                if (e.Delta > 0) trackBar1.Value = trackBar1.Maximum;
                else if (e.Delta < 0) trackBar1.Value = trackBar1.Minimum;
            }

            pictureBox2.Location = new Point((int)((double)e.X - (double)e.X * ((100.0 + (double)trackBar1.Value) / 100.0)), (int)((double)e.Y - (double)e.Y * ((100.0 + (double)trackBar1.Value) / 100.0)));
            pictureBox2.Size = new Size(pictureBox1.Width - pictureBox2.Location.X,pictureBox1.Height - pictureBox2.Location.Y);
        }

        public void makeTask(byte[] task)
        {
            switch (task[0])
            {
                case 110:
                    byte[] tabLongitude = { task[1], task[2], task[3], task[4] };
                    byte[] tabLatitude = { task[5], task[6], task[7], task[8] };
                    drawPoint(coordinatesToPosition(byteToFloatConv(tabLatitude), byteToFloatConv(tabLongitude)));
                    break;
            }
        }

        private Single byteToFloatConv (byte[] tab)
        {
            return BitConverter.ToSingle(tab, 0);
        }
    }
}
