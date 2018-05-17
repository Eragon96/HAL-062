using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using SlimDX.DirectInput;
using Renci.SshNet;
using System.Diagnostics;

namespace KNRapp
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            getAvailablePorts();
            joy = new Joy();
            timer1.Enabled = true;
            myForm1 = this;
            //dataTrans = new DataTransfer();
            stopWatch.Start();
        }


        //DataTransfer dataTrans;
        Joy joy;
        public static Form1 myForm1;
        GPSfile gps = new KNRapp.GPSfile();
        Boolean speedTest = false;
        long[] testTimes;
        Stopwatch stopWatch = new Stopwatch();
        


        
        //=================================================================================
        public void diagnosticPrint(string text)
        {
            textBox_diagnostics.Text = text;
        }

        //=================================================================================
        public void gpsPrint(string x, string y)
        {
            textBox2.Text = x;
            textBox3.Text = y;

        }
        //=======================================================================================================
        void getAvailablePorts()
        {
            String[] ports = SerialPort.GetPortNames(); //sczytaj dostepne porty szeregowe
            comboBox_portNames.Items.Clear();
            comboBox_portNames.Items.AddRange(ports); //zapisz je w liscie comboBox'a
        }


        //============================================================================================================
        public void closePort()
        {
            try
            {
                // serialPort1.Close();
                //dataTrans.closeSerial();
                Program.getDataTrans().closeSerial();
             
            }
            catch (System.IO.IOException)
            {

            }
            progressBar_status.Value = 0;
            textBox_diagnostics.Enabled = false;
            button_closePort.Enabled = false; //disable close_button
            button_openPort.Enabled = true; //re-enable the open_button
            button_closeSSH.Enabled = false;
            button_openSSH.Enabled = true;
        }


        //=========================================================================================================
        //StickHandle function gets the state of the controller and sets button values into variables
        void stickHandle()
        {
            joyParamBarUpdate();      //wyswietlaj pozycje joysticka
            int yValue = joy.getXValue();
            if (Math.Abs(yValue) < 4) yValue = 0;
            int xValue = joy.getYValue();
            if (Math.Abs(xValue) < 4) xValue = 0;
            int zValue = joy.getZValue();

            //Wysylaj info po szeregu
            try
            {
                if (Program.getDataTrans().IsOpen())
                {
                    byte[] valByte = { (byte)('#'), (byte)(100), (byte)(xValue), (byte)(yValue) }; //xValue jest w (-100, 100)
                    Program.getDataTrans().Write(valByte, 0, valByte.Length);
                }
            }
            catch (System.IO.IOException)
            {
                textBox_diagnostics.Text = "Przerwano połączenie";
                this.closePort();
            }
        }







        //=======================================================================================================
        /*
        int licznik = 0;
        byte[] inputBuffor = new byte[1000];
        int znakiPolecenia;
        Boolean nowePolecenie = false;
        byte[] polecenie = new byte[100];
        
        
        private void serialRead()
        {
            // int n = serialPort1.BytesToRead;
            Array.Clear(inputBuffor, 0, 1000);
            //serialPort1.Read(inputBuffor, 0, n);
            int n = dataTrans.Read(inputBuffor, 0, 1000);
            if (n != 0)
            {
                for (int i = 0; i < n; i++)
                {
                    if (nowePolecenie)
                    {
                        polecenie[0] = inputBuffor[i];
                        switch (inputBuffor[i])
                        {
                            case 106:
                                znakiPolecenia = 8;
                                break;
                            case 105:
                                znakiPolecenia = 6;
                                break;
                            case 104:
                                znakiPolecenia = 6;
                                break;
                            case 103:
                                znakiPolecenia = 6;
                                break;
                            case 102:
                                znakiPolecenia = 6;
                                break;
                            case 107:
                                znakiPolecenia = 6;
                                break;
                            case 111:
                                znakiPolecenia = 3;
                                break;
                            case 112:
                                znakiPolecenia = 3;
                                break;
                            case 114:
                                znakiPolecenia = 1;
                                break;
                            case 115:
                                znakiPolecenia = 1;
                                break;
                            case (byte)'G':
                                znakiPolecenia = 48;
                                break;
                            case (byte)'T':
                                for(int x = 0; i < 9; i++) { testTimes[9 - x] = testTimes[8 - x]; }
                                testTimes[0] = stopWatch.ElapsedMilliseconds;
                                stopWatch.Restart();
                                break;
                            default:
                                polecenie[0] = 0;
                                break;
                        }
                        nowePolecenie = false;
                    }
                    else if (inputBuffor[i] == '#' && znakiPolecenia == 0)
                    {
                        nowePolecenie = true;
                        licznik = 1;
                    }
                    else if (znakiPolecenia > 0)
                    {
                        polecenie[licznik] = inputBuffor[i];
                        licznik++;
                        znakiPolecenia--;
                    }
                    if (znakiPolecenia == 0 && licznik > 1)
                    {
                        this.wykonajPolecenie();
                        Array.Clear(polecenie, 0, 20);
                        licznik = 0;
                    }
                }
            }
        }
        */
        private void joyParamBarUpdate()
        {
            textBox_X.Text = joy.getXValue().ToString();
            textBox_Y.Text = joy.getYValue().ToString();
            textBox_Z.Text = joy.getZValue().ToString();

            bool[] buttons = joy.getButtons();
            if (buttons != null)
            {
                if (buttons[0])
                {
                    checkBox1.Checked = true;
                }
                else
                {
                    checkBox1.Checked = false;
                }
                if (buttons[1])
                {

                    byte[] valByte1 = { (byte)('#'), (byte)(101), (byte)('0') };
                    Program.getDataTrans().Write(valByte1, 0, valByte1.Length);
                    checkBox2.Checked = true;
                }
                else
                {
                    checkBox2.Checked = false;
                }
                if (buttons[2])
                {

                    byte[] valByte1 = { (byte)('#'), (byte)(101), (byte)('1') };
                    Program.getDataTrans().Write(valByte1, 0, valByte1.Length);
                    checkBox3.Checked = true;
                }
                else
                {
                    checkBox3.Checked = false;
                }
                if (buttons[3])
                {
                    checkBox4.Checked = true;

                }
                else
                {
                    checkBox4.Checked = false;
                }
                if (buttons[4])
                {
                    checkBox5.Checked = true;
                }
                else
                {
                    checkBox5.Checked = false;
                }
            }
        }

        //=============================================================================================================
        //rozpoznaje polecenie odebrane przez serial port i podejmuje odpowiednią akcję 
        public void wykonajPolecenie(byte[] polecenie)
        {
            switch (polecenie[0])
            {
                case 108:
                    this.ustawBatTemp(polecenie);
                    break;
                case 109:
                    this.ustawBatVolt(polecenie);
                    break;
                case 106:
                    this.prawyPredkosc(polecenie);
                    break;
                case 107:
                    this.lewyPredkosc(polecenie);
                    break;
                case 104:
                    this.prawyPrad(polecenie);
                    break;
                case 105:
                    this.lewyPrad(polecenie);
                    break;
                case 113:
                    this.prawyTemp(polecenie);
                    break;
                case 114:
                    this.lewyTemp(polecenie);
                    break;
                case 116:
                    this.prawyStatus(polecenie);
                    break;
                case 117:
                    this.lewyStatus(polecenie);
                    break;
                case (byte)'G':
                    gps.GPSset(polecenie);
                    break;
                case (byte)'b':
                    //  temp1.Text = System.Text.Encoding.UTF8.GetString(polecenie);
                    break;
            }

        }

        //================================================
        public void testTime()
        {
            for (int x = 0; x < 9; x++) { testTimes[9 - x] = testTimes[8 - x]; }
            testTimes[0] = stopWatch.ElapsedMilliseconds;
            stopWatch.Restart();
        }

        //=============================================================================================================
        private void lewyPrad(byte[] polecenie)
        {

            // tutaj trzeba zamieścić odpowiednie obliczenia 
            double prad1 = (double)lowHighToInt16(polecenie[1], polecenie[2]) / 22.6;
            double prad2 = (double)lowHighToInt16(polecenie[3], polecenie[4]) / 22.6;
            double prad3 = (double)lowHighToInt16(polecenie[5], polecenie[6]) / 22.6;
            pradL1.Text = prad1.ToString("N2");
            pradL2.Text = prad2.ToString("N2");
            pradL3.Text = prad3.ToString("N2");
            //addSpeed1((float)prad1,0,0);
        }

        //=============================================================================================================
        private void prawyPrad(byte[] polecenie)
        {

            // tutaj trzeba zamieścić odpowiednie obliczenia 
            double prad1 = (double)lowHighToInt16(polecenie[1], polecenie[2]) / 22.6;
            double prad2 = (double)lowHighToInt16(polecenie[3], polecenie[4]) / 22.6;
            double prad3 = (double)lowHighToInt16(polecenie[5], polecenie[6]) / 22.6;
            pradP1.Text = prad1.ToString("N2");
            pradP2.Text = prad2.ToString("N2");
            pradP3.Text = prad3.ToString("N2");
        }

        //=============================================================================================================
        private void lewyPredkosc(byte[] polecenie)
        {
            float speed1 = (float)lowHighToInt16(polecenie[1], polecenie[2]) / 10;
            float speed2 = (float)lowHighToInt16(polecenie[3], polecenie[4]) / 10;
            float speed3 = (float)lowHighToInt16(polecenie[5], polecenie[6]) / 10;

            speedL1.Text = speed1.ToString("N1");
            speedL2.Text = speed2.ToString("N1");
            speedL3.Text = speed3.ToString("N1");
            /// addSpeed1(speed1,speed2,speed3);
        }

        //=============================================================================================================
        private void prawyPredkosc(byte[] polecenie)
        {
            float speed1 = (float)lowHighToInt16(polecenie[1], polecenie[2]) / 10;
            float speed2 = (float)lowHighToInt16(polecenie[3], polecenie[4]) / 10;
            float speed3 = (float)lowHighToInt16(polecenie[5], polecenie[6]) / 10;

            speedP1.Text = speed1.ToString("N1");
            speedP2.Text = speed2.ToString("N1");
            speedP3.Text = speed3.ToString("N1");
            //addSpeed2(speed1, speed2, speed3);
        }

        //=============================================================================================================
        private Int16 lowHighToInt16(byte low, byte high)
        {
            return (Int16)(low | high << 8);
        }

        //=============================================================================================================
        private void ustawBatVolt(byte[] polecenie)
        {
            double batteryPomiar1 = lowHighToInt16(polecenie[1], polecenie[2]) * 3.315 / 4096 * (6.8 + 22) / 22;
            double batteryPomiar2 = lowHighToInt16(polecenie[3], polecenie[4]) * 3.315 / 4096 * (22 + 12.4) / 12.4;
            double batteryPomiar3 = lowHighToInt16(polecenie[5], polecenie[6]) * 3.315 / 4096 * (33 + 10) / 10;
            double batteryPomiar4 = lowHighToInt16(polecenie[7], polecenie[8]) * 3.315 / 4096 * (47 + 10) / 10;

            Vbat1.Text = batteryPomiar1.ToString("F");
            Vbat2.Text = batteryPomiar2.ToString("F");
            Vbat3.Text = batteryPomiar3.ToString("F");
            Vbat4.Text = batteryPomiar4.ToString("F");
            if (batteryPomiar4 < 11)
            {
                this.Vbat1.BackColor = System.Drawing.Color.Red;
                this.Vbat2.BackColor = System.Drawing.Color.Red;
                this.Vbat3.BackColor = System.Drawing.Color.Red;
                this.Vbat4.BackColor = System.Drawing.Color.Red;
            }
            else
            {
                this.Vbat1.BackColor = System.Drawing.Color.White;
                this.Vbat2.BackColor = System.Drawing.Color.White;
                this.Vbat3.BackColor = System.Drawing.Color.White;
                this.Vbat4.BackColor = System.Drawing.Color.White;
            }
        }

        private void ustawBatTemp(byte[] polecenie)
        {
            tempB1.Text = (polecenie[1] / 2).ToString();
            tempB2.Text = (polecenie[2] / 2).ToString();
            tempB3.Text = (polecenie[3] / 2).ToString();
            tempB4.Text = (polecenie[4] / 2).ToString();
            tempB5.Text = (polecenie[5] / 2).ToString();
            tempB6.Text = (polecenie[6] / 2).ToString();
        }

        private void prawyTemp(byte[] polecenie)
        {
            tempP1.Text = (polecenie[1] / 2).ToString();
            tempP2.Text = (polecenie[2] / 2).ToString();
            tempP3.Text = (polecenie[3] / 2).ToString();
        }

        private void lewyTemp(byte[] polecenie)
        {
            tempL1.Text = (polecenie[1] / 2).ToString();
            tempL2.Text = (polecenie[2] / 2).ToString();
            tempL3.Text = (polecenie[3] / 2).ToString();
        }

        private void prawyStatus(byte[] polecenie)
        {
            resetStatusCount(0);
            if (polecenie[1] == 2)
            {
                RightStatus.Text = "Power OFF";
            }
            else if (polecenie[1] == 3)
            {
                RightStatus.Text = "Enable";
            }
            else if (polecenie[1] == 1)
            {
                RightStatus.Text = "Disable";
            }
            else
            {
                RightStatus.Text = "";
            }
        }

        private void lewyStatus(byte[] polecenie)
        {
            resetStatusCount(1);
            if (polecenie[1] == 2)
            {
                LeftStatus.Text = "Power OFF";
            }
            else if (polecenie[1] == 3)
            {
                LeftStatus.Text = "Enable";
            }
            else if (polecenie[1] == 1)
            {
                LeftStatus.Text = "Disable";
            }
            else
            {
                LeftStatus.Text = "";
            }
        }

        int[] licznikStatus = { 0, 0 };

        private void resetStatusCount(int i)
        {
            licznikStatus[i] = 20;
        }

        private void statusTimerDecrement()
        {
            licznikStatus[0]--;
            licznikStatus[1]--;
            if (licznikStatus[0] < 0)
            {
                licznikStatus[0] = 0;
                RightStatus.Text = "Error";
            }
            if (licznikStatus[1] < 0)
            {
                licznikStatus[1] = 0;
                LeftStatus.Text = "Error";
            }
        }
        //=============================================================================================================


        //=======================================================================================================
        //#######################################################################################################
        //=======================================================================================================
        private void button_openPort_Click(object sender, EventArgs e)
        {
            try
            {
                if (comboBox_portNames.Text == "")
                {
                    textBox_diagnostics.Text = "Please select port settings";
                }
                else
                {
                    //serialPort1.PortName = comboBox_portNames.Text; //assign port name selected to serial port
                    //dataTrans.openSerial(comboBox_portNames.Text);
                    Program.setNewDataTrans();
                    Program.getDataTrans().openSerial(comboBox_portNames.Text);

                    progressBar_status.Value = 100;
                    textBox_diagnostics.Enabled = true;
                    button_openPort.Enabled = false; //you cannot open the port again
                    button_closePort.Enabled = true;
                    button_closeSSH.Enabled = false;
                    button_openSSH.Enabled = false;
                    textBox_diagnostics.ResetText();
                    //serialPort1.DiscardInBuffer();
                }
            }
            catch (UnauthorizedAccessException)
            {
                textBox_diagnostics.Text = "Nieautoryzowany dostęp";
            }
            catch (System.IO.IOException)
            {
                textBox_diagnostics.Text = "Wybrano zły port COM";
            }
        }
        //========================================================================================================
        private void button_closePort_Click(object sender, EventArgs e)
        {
            this.closePort();
        }
        //========================================================================================================
        public void timerTask()
        {
            statusTimerDecrement();
            if (Program.getDataTrans().IsOpen())
            {
                //serialRead();
                stickHandle();
            }
            // tu wyślij znak
            if (Program.getDataTrans().IsOpen() && speedTest == true)
            {
                byte[] tester = { (byte)('O')};
                Program.getDataTrans().Write(tester, 0,1);
                long avg = 0;
                for(int i = 0; i < 10; i++) { avg += testTimes[i]; }
                avg = avg / 10;
                speedTestAVG.Text = ("" + avg + "");
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            Program.timerTask();
        }
        //========================================================================================================
        private void Form1_Load(object sender, EventArgs e)
        {

        }

        //========================================================================================================
        private void stopButton_Click(object sender, EventArgs e)
        {
            if (Program.getDataTrans().IsOpen())
            {
                byte[] valByte1 = { (byte)('#'), (byte)(101), (byte)('0') };
                Program.getDataTrans().Write(valByte1, 0, valByte1.Length);
            }
        }
        //========================================================================================================
        private void startButton_Click(object sender, EventArgs e)
        {
            if (Program.getDataTrans().IsOpen())
            {
                byte[] valByte1 = { (byte)('#'), (byte)(101), (byte)('1') };
                Program.getDataTrans().Write(valByte1, 0, valByte1.Length);
            }
        }

        //========================================================================================================
        private void mapaStart_Click(object sender, EventArgs e)
        {
            //gps.GPSstart();
            Program.runMapForm();
        }
        //========================================================================================================
        private void ResetMap_Click(object sender, EventArgs e)
        {
            //gps.GPSreset(true);
        }

        private void comboBox_portNames_SelectedIndexChanged(object sender, EventArgs e)
        {
            getAvailablePorts();
        }

        private void button_openSSH_Click(object sender, EventArgs e)
        {
            //dataTrans.openSSH();
            Program.getDataTrans().openSSH();
            progressBar_status.Value = 100;
            textBox_diagnostics.Enabled = true;
            button_openPort.Enabled = false; //you cannot open the port again
            button_closePort.Enabled = false;
            button_openSSH.Enabled = false;
            button_closeSSH.Enabled = true;
            textBox_diagnostics.ResetText();
        }

        private void button_closeSSH_Click(object sender, EventArgs e)
        {
            //dataTrans.closeSSH();
            Program.getDataTrans().closeSSH();
            progressBar_status.Value = 0;
            button_openPort.Enabled = true; //you cannot open the port again
            button_closePort.Enabled = false;
            button_openSSH.Enabled = true;
            button_closeSSH.Enabled = false;
        }

        private void speedTestButton_Click(object sender, EventArgs e)
        {
            if(speedTest == true) { speedTest = false; speedTestBUL.Text = "TRUE"; }
            else { speedTest = true; speedTestBUL.Text = "FALSE"; }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if(Program.getManipulatorFormInfo() == null)
            {
                Program.runManipulatorForm();
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (Program.getLabFormInfo() == null)
            {
                Program.runLabForm();
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (Program.getAdminFormInfo() == null)
            {
                Program.runAdminForm();
            }
        }

        //int n = 0;
        //private void addSpeed1(float speed1, float speed2, float speed3)
        //{
        //    n++;
        //    chart1.Series["Series1"].Points.AddY(speed1);
        //    chart1.Series["Series2"].Points.AddY(speed2);
        //    chart1.Series["Series3"].Points.AddY(speed3);
        //    chart1.ChartAreas["ChartArea1"].AxisX.Maximum = n;
        //    chart1.ChartAreas["ChartArea1"].AxisX.Minimum = n-30;
        //    chart1.ChartAreas["ChartArea1"].AxisX.LabelStyle.Enabled = false;
        //}

        //int k = 0;
        //private void addSpeed2(float speed1, float speed2, float speed3)
        //{
        //    k++;
        //    chart2.Series["Series1"].Points.AddY(speed1);
        //    chart2.Series["Series2"].Points.AddY(speed2);
        //    chart2.Series["Series3"].Points.AddY(speed3);
        //    chart2.ChartAreas["ChartArea1"].AxisX.Maximum = n;
        //    chart2.ChartAreas["ChartArea1"].AxisX.Minimum = n - 30;
        //    chart2.ChartAreas["ChartArea1"].AxisX.LabelStyle.Enabled = false;
        //}
    }
}
