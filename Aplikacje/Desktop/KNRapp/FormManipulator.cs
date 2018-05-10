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
    public partial class FormManipulator : Form
    {
        static private HashSet<Keys> pressedKeys;
        int[] outputTab = new int[7];
        int[] outputInverseKinematicsTab = new int[7];
        bool inverseKinematics = false;

        public FormManipulator()
        {
            InitializeComponent();
            this.KeyPreview = true;
            this.KeyDown += new KeyEventHandler(Form1_KeyDown);
            this.KeyUp += new KeyEventHandler(Form1_KeyUp);
            this.FormClosing += new FormClosingEventHandler(Form_Closing);
            pressedKeys = new HashSet<Keys>();
        }

        private void FormManipulator_Load(object sender, EventArgs e)
        {

        }



        public void timerTask()
        {
            clearTabs();
            handleKeys();
            sendInfo();
        }

        private void handleKeys()
        {
            foreach (Keys key in pressedKeys)
            {
                textBox1.Text += key;
                switch (key)
                {
                    case Keys.Q:
                        outputTab[0] += speedModuleTrackBar.Value;
                        break;
                    case Keys.A:
                        outputTab[0] -= speedModuleTrackBar.Value;
                        break;
                    case Keys.W:
                        outputTab[1] += speedModuleTrackBar.Value;
                        break;
                    case Keys.S:
                        outputTab[1] -= speedModuleTrackBar.Value;
                        break;
                    case Keys.E:
                        outputTab[2] += speedModuleTrackBar.Value;
                        break;
                    case Keys.D:
                        outputTab[2] -= speedModuleTrackBar.Value;
                        break;
                    case Keys.R:
                        outputTab[3] += speedModuleTrackBar.Value;
                        break;
                    case Keys.F:
                        outputTab[3] -= speedModuleTrackBar.Value;
                        break;
                    case Keys.T:
                        outputTab[4] += speedModuleTrackBar.Value;
                        break;
                    case Keys.G:
                        outputTab[4] -= speedModuleTrackBar.Value;
                        break;
                    case Keys.Y:
                        outputTab[5] += speedModuleTrackBar.Value;
                        break;
                    case Keys.H:
                        outputTab[5] -= speedModuleTrackBar.Value;
                        break;
                    case Keys.U:
                        outputTab[6] += speedModuleTrackBar.Value;
                        outputInverseKinematicsTab[6] += speedModuleTrackBar.Value;
                        break;
                    case Keys.J:
                        outputTab[6] -= speedModuleTrackBar.Value;
                        outputInverseKinematicsTab[6] -= speedModuleTrackBar.Value;
                        break;
                }
            }
        }

        private void sendInfo()
        {
            byte[] outputByte = new byte[9];
            outputByte[0] = (byte)('#');
            switch (inverseKinematics)
            {
                case true:
                    outputByte[1] = (byte)(161);
                    for(int i = 0; i < 7; i++)
                    {
                        outputByte[i + 2] = (byte)outputInverseKinematicsTab[i];
                    }
                    textBox15.Text = "" + outputInverseKinematicsTab[0];
                    textBox14.Text = "" + outputInverseKinematicsTab[1];
                    textBox13.Text = "" + outputInverseKinematicsTab[2];
                    textBox12.Text = "" + outputInverseKinematicsTab[3];
                    textBox11.Text = "" + outputInverseKinematicsTab[4];
                    textBox10.Text = "" + outputInverseKinematicsTab[5];
                    textBox9.Text = "" + outputInverseKinematicsTab[6];
                    break;
                case false:
                    outputByte[1] = (byte)(160);
                    for (int i = 0; i < 7; i++)
                    {
                        outputByte[i + 2] = (byte)outputTab[i];
                    }
                    textBox15.Text = "" + outputTab[0];
                    textBox14.Text = "" + outputTab[1];
                    textBox13.Text = "" + outputTab[2];
                    textBox12.Text = "" + outputTab[3];
                    textBox11.Text = "" + outputTab[4];
                    textBox10.Text = "" + outputTab[5];
                    textBox9.Text = "" + outputTab[6];
                    break;
            }
            try
            {
                if (Program.getDataTrans().IsOpen())
                {
                    Program.getDataTrans().Write(outputByte, 0, outputByte.Length);
                }
            }
            catch (System.IO.IOException)
            {
                Program.getMainFormInfo().textBox_diagnostics.Text = "Przerwano połączenie";
                Program.getMainFormInfo().closePort();
            }
        }

        private void clearTabs()
        {
            textBox1.Text = "";
            for (int x = 0; x < 7; x++)
            {
                outputTab[x] = 0;
                outputInverseKinematicsTab[x] = 0;
            }
        }

        public void wykonajPolecenie(byte[] polecenie)
        {
            switch (polecenie[0])
            {
                case 163:
                    setManipulatorPosition(polecenie);
                    break;
            }
        }

        private void setManipulatorPosition(byte[] actPosition)
        {
            double position1 = (double)actPosition[1];
            double position2 = (double)actPosition[2];
            double position3 = (double)actPosition[3];
            double position4 = (double)actPosition[4];
            double position5 = (double)actPosition[5];
            double position6 = (double)actPosition[6];
            double position7 = (double)actPosition[7];
            position1TextBox.Text = position1.ToString();
            position2TextBox.Text = position2.ToString();
            position3TextBox.Text = position3.ToString();
            position4TextBox.Text = position4.ToString();
            position5TextBox.Text = position5.ToString();
            position6TextBox.Text = position6.ToString();
            position7TextBox.Text = position7.ToString();
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            speedModuleTextBox.Text = "" + speedModuleTrackBar.Value; 
        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            pressedKeys.Add(e.KeyCode);
        }

        private void Form1_KeyUp(object sender, KeyEventArgs e)
        {
            pressedKeys.Remove(e.KeyCode);
        }

        public HashSet<Keys> getPressedKeys()
        {
            return pressedKeys;
        }

        private void Form_Closing(object sender, CancelEventArgs e)
        {
            Program.closeManipulatorForm();
        }

        private void START_Click(object sender, EventArgs e)
        {
            if (Program.getDataTrans().IsOpen())
            {
                byte[] valByte = { (byte)('#'), (byte)(162), (byte)('1') };
                Program.getDataTrans().Write(valByte, 0, valByte.Length);
            }
        }

        private void STOP_Click(object sender, EventArgs e)
        {
            if (Program.getDataTrans().IsOpen())
            {
                byte[] valByte = { (byte)('#'), (byte)(101), (byte)('0') };
                Program.getDataTrans().Write(valByte, 0, valByte.Length);
            }
        }

        private void changeButton_Click(object sender, EventArgs e)
        {
            inverseKinematics = !inverseKinematics;
            kinematicsTextBox.Text = "Inverse Kinematics: " + inverseKinematics;
        }

        private void speedModuleTextBox_TextChanged(object sender, EventArgs e)
        {
            try
            {
                if (Convert.ToInt64(speedModuleTextBox.Text) < 101 && Convert.ToInt64(speedModuleTextBox.Text) > 0)
                {
                    speedModuleTrackBar.Value = Convert.ToInt16(speedModuleTextBox.Text);
                }
            }
            catch (System.FormatException)
            {
                speedModuleTextBox.Text = "1";
            }
        }
    }
}
