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
    public partial class FormLab : Form
    {
        int[] outputEngineSpeed = new int[7];
        int[] outputServoPosition = new int[6];
        public FormLab()
        {
            InitializeComponent();
            this.FormClosing += new FormClosingEventHandler(Form_Closing);

        }

        public void timerTask()
        {

        }

        public void wykonajPolecenie(byte[] polecenie)
        {

        }

        private void FormLab_Load(object sender, EventArgs e)
        {

        }

        private void Form_Closing(object sender, CancelEventArgs e)
        {
            Program.closeLabForm();
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            outputEngineSpeed[0] = trackBar1.Value;
            textBox1.Text = "" + trackBar1.Value;
        }

        private void trackBar2_Scroll(object sender, EventArgs e)
        {
            outputEngineSpeed[1] = trackBar2.Value;
            textBox2.Text = "" + trackBar2.Value;
        }

        private void trackBar3_Scroll(object sender, EventArgs e)
        {
            outputEngineSpeed[2] = trackBar3.Value;
            textBox3.Text = "" + trackBar3.Value;
        }

        private void trackBar4_Scroll(object sender, EventArgs e)
        {
            outputEngineSpeed[3] = trackBar4.Value;
            textBox4.Text = "" + trackBar4.Value;
        }

        private void trackBar5_Scroll(object sender, EventArgs e)
        {
            outputEngineSpeed[4] = trackBar5.Value;
            textBox5.Text = "" + trackBar5.Value;
        }

        private void trackBar6_Scroll(object sender, EventArgs e)
        {
            outputEngineSpeed[5] = trackBar6.Value;
            textBox6.Text = "" + trackBar6.Value;
        }

        private void trackBar7_Scroll(object sender, EventArgs e)
        {
            outputEngineSpeed[6] = trackBar7.Value;
            textBox7.Text = "" + trackBar7.Value;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            trackBar1.Value = 0;
            trackBar1_Scroll(sender,e);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            trackBar2.Value = 0;
            trackBar2_Scroll(sender, e);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            trackBar3.Value = 0;
            trackBar3_Scroll(sender, e);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            trackBar4.Value = 0;
            trackBar4_Scroll(sender, e);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            trackBar5.Value = 0;
            trackBar5_Scroll(sender, e);
        }

        private void button6_Click(object sender, EventArgs e)
        {
            trackBar6.Value = 0;
            trackBar6_Scroll(sender, e);
        }

        private void button7_Click(object sender, EventArgs e)
        {
            trackBar7.Value = 0;
            trackBar7_Scroll(sender, e);
        }

        private void button8_Click(object sender, EventArgs e)
        {
            button1_Click(sender, e);
            button2_Click(sender, e);
            button3_Click(sender, e);
            button4_Click(sender, e);
            button5_Click(sender, e);
            button6_Click(sender, e);
            button7_Click(sender, e);
        }

        private void trackBar8_Scroll(object sender, EventArgs e)
        {
            outputServoPosition[0] = trackBar8.Value;
            textBox8.Text = "" + trackBar8.Value;
        }

        private void trackBar9_Scroll(object sender, EventArgs e)
        {
            outputServoPosition[1] = trackBar9.Value;
            textBox9.Text = "" + trackBar9.Value;
        }

        private void trackBar10_Scroll(object sender, EventArgs e)
        {
            outputServoPosition[2] = trackBar10.Value;
            textBox10.Text = "" + trackBar10.Value;
        }

        private void trackBar11_Scroll(object sender, EventArgs e)
        {
            outputServoPosition[3] = trackBar11.Value;
            textBox11.Text = "" + trackBar11.Value;
        }

        private void trackBar12_Scroll(object sender, EventArgs e)
        {
            outputServoPosition[4] = trackBar12.Value;
            textBox12.Text = "" + trackBar12.Value;
        }

        private void trackBar13_Scroll(object sender, EventArgs e)
        {
            outputServoPosition[5] = trackBar13.Value;
            textBox13.Text = "" + trackBar13.Value;
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            try
            {
                if (Convert.ToInt64(textBox1.Text) < 21 && Convert.ToInt64(textBox1.Text) > -21)
                {
                    trackBar1.Value = Convert.ToInt16(textBox1.Text);
                }
            }
            catch (System.FormatException)
            {
                textBox1.Text = "0";
            }
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            try
            {
                if (Convert.ToInt64(textBox2.Text) < 21 && Convert.ToInt64(textBox2.Text) > -21)
                {
                    trackBar2.Value = Convert.ToInt16(textBox2.Text);
                }
            }
            catch (System.FormatException)
            {
                textBox2.Text = "0";
            }
        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {
            try
            {
                if (Convert.ToInt64(textBox3.Text) < 21 && Convert.ToInt64(textBox3.Text) > -21)
                {
                    trackBar3.Value = Convert.ToInt16(textBox3.Text);
                }
            }
            catch (System.FormatException)
            {
                textBox3.Text = "0";
            }
        }

        private void textBox4_TextChanged(object sender, EventArgs e)
        {
            try
            {
                if (Convert.ToInt64(textBox4.Text) < 21 && Convert.ToInt64(textBox4.Text) > -21)
                {
                    trackBar4.Value = Convert.ToInt16(textBox4.Text);
                }
            }
            catch (System.FormatException)
            {
                textBox4.Text = "0";
            }
        }

        private void textBox5_TextChanged(object sender, EventArgs e)
        {
            try
            {
                if (Convert.ToInt64(textBox5.Text) < 21 && Convert.ToInt64(textBox5.Text) > -21)
                {
                    trackBar5.Value = Convert.ToInt16(textBox5.Text);
                }
            }
            catch (System.FormatException)
            {
                textBox5.Text = "0";
            }
        }

        private void textBox6_TextChanged(object sender, EventArgs e)
        {
            try
            {
                if (Convert.ToInt64(textBox6.Text) < 21 && Convert.ToInt64(textBox6.Text) > -21)
                {
                    trackBar6.Value = Convert.ToInt16(textBox6.Text);
                }
            }
            catch (System.FormatException)
            {
                textBox6.Text = "0";
            }
        }

        private void textBox7_TextChanged(object sender, EventArgs e)
        {
            try
            {
                if (Convert.ToInt64(textBox7.Text) < 21 && Convert.ToInt64(textBox7.Text) > -21)
                {
                    trackBar7.Value = Convert.ToInt16(textBox7.Text);
                }
            }
            catch (System.FormatException)
            {
                textBox7.Text = "0";
            }
        }

        private void textBox8_TextChanged(object sender, EventArgs e)
        {
            try
            {
                if (Convert.ToInt64(textBox8.Text) < 91 && Convert.ToInt64(textBox8.Text) > -91)
                {
                    trackBar8.Value = Convert.ToInt16(textBox8.Text);
                }
            }
            catch (System.FormatException)
            {
                textBox8.Text = "" + outputServoPosition[0];
            }
        }

        private void textBox9_TextChanged(object sender, EventArgs e)
        {
            try
            {
                if (Convert.ToInt64(textBox9.Text) < 91 && Convert.ToInt64(textBox9.Text) > -91)
                {
                    trackBar9.Value = Convert.ToInt32(textBox9.Text);
                }
            }
            catch (System.FormatException)
            {
                textBox9.Text = "" + outputServoPosition[1];
            }
        }

        private void textBox10_TextChanged(object sender, EventArgs e)
        {
            try
            {
                if (Convert.ToInt64(textBox10.Text) < 91 && Convert.ToInt64(textBox10.Text) > -91)
                {
                    trackBar10.Value = Convert.ToInt16(textBox10.Text);
                }
            }
            catch (System.FormatException)
            {
                textBox10.Text = "" + outputServoPosition[2];
            }
        }

        private void textBox11_TextChanged(object sender, EventArgs e)
        {
            try
            {
                if (Convert.ToInt64(textBox11.Text) < 91 && Convert.ToInt64(textBox11.Text) > -91)
                {
                    trackBar11.Value = Convert.ToInt16(textBox11.Text);
                }
            }
            catch (System.FormatException)
            {
                textBox11.Text = "" + outputServoPosition[3];
            }
        }

        private void textBox12_TextChanged(object sender, EventArgs e)
        {
            try
            {
                if (Convert.ToInt64(textBox12.Text) < 91 && Convert.ToInt64(textBox12.Text) > -91)
                {
                    trackBar12.Value = Convert.ToInt16(textBox12.Text);
                }
            }
            catch (System.FormatException)
            {
                textBox12.Text = "" + outputServoPosition[4];
            }
        }

        private void textBox13_TextChanged(object sender, EventArgs e)
        {
            try
            {
                if (Convert.ToInt64(textBox13.Text) < 91 && Convert.ToInt64(textBox13.Text) > -91)
                {
                    trackBar13.Value = Convert.ToInt16(textBox13.Text);
                }
            }
            catch (System.FormatException)
            {
                textBox13.Text = "" + outputServoPosition[5];
            }
        }
    }
}
