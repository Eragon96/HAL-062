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
    public partial class FormAdmin : Form
    {
        public FormAdmin()
        {
            InitializeComponent();
            this.FormClosing += new FormClosingEventHandler(Form_Closing);
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            textBox1.Text = "" + trackBar1.Value;
        }

        private void trackBar2_Scroll(object sender, EventArgs e)
        {
            textBox2.Text = "" + trackBar2.Value;
        }

        private void trackBar3_Scroll(object sender, EventArgs e)
        {
            textBox3.Text = "" + trackBar3.Value;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (Program.getDataTrans().IsOpen())
            {
                byte[] valByte = { (byte)('#'), (byte)(115), (byte)(trackBar1.Value) };
                Program.getDataTrans().Write(valByte, 0, valByte.Length);
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (Program.getDataTrans().IsOpen())
            {
                byte[] valByte = { (byte)('#'), (byte)(119), (byte)(trackBar2.Value) };
                Program.getDataTrans().Write(valByte, 0, valByte.Length);
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (Program.getDataTrans().IsOpen())
            {
                byte[] valByte = { (byte)('#'), (byte)(120), (byte)(trackBar3.Value) };
                Program.getDataTrans().Write(valByte, 0, valByte.Length);
            }
        }

        private void Form_Closing(object sender, CancelEventArgs e)
        {
            Program.closeAdminForm();
        }

        private void pictureBox2_Click(object sender, EventArgs e)
        {
            pictureBox1.Image = Image.FromFile("../Pics/siekiera.png");
            this.ClientSize = new System.Drawing.Size(828, 289);
        }
    }
}
