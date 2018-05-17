using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
//using Timers = System.Timers;
//using Timer = System.Windows.Forms.Timer;
using Timer = System.Threading.Timer;

namespace KNRapp
{
    class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Run();
        }


        static private DataTransfer dataTrans = new DataTransfer();
        static private Form1 mainForm;
        static private FormManipulator manipulatorForm;
        static private FormLab labForm;
        static private FormAdmin adminForm;
        static private FormMap mapForm;




        static public void timerTask()
        {
            
            if (Program.getDataTrans().IsOpen())
            {
                Program.serialRead();
            }
            if (mainForm != null)
            {
                mainForm.timerTask();
            }
            if (manipulatorForm != null)
            {
                manipulatorForm.timerTask();
            }
            if (labForm != null)
            {
                labForm.timerTask();
            }
        }


        static private int licznik = 0;
        static private byte[] inputBuffor = new byte[1000];
        static private int znakiPolecenia;
        static private Boolean nowePolecenie = false;
        static private byte[] polecenie = new byte[100];

        static private void serialRead()
        {
            Array.Clear(inputBuffor, 0, 1000);
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
                            case 105:
                                znakiPolecenia = 6;
                                break;
                            case 104:
                                znakiPolecenia = 6;
                                break;
                            case 106:
                                znakiPolecenia = 6;
                                break;
                            case 107:
                                znakiPolecenia = 6;
                                break;
                            case 113:
                                znakiPolecenia = 3;
                                break;
                            case 114:
                                znakiPolecenia = 3;
                                break;
                            case 116:
                                znakiPolecenia = 1;
                                break;
                            case 117:
                                znakiPolecenia = 1;
                                break;
                            case 163:
                                znakiPolecenia = 7;
                                break;
                            case (byte)'T':
                                mainForm.testTime();
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
                        int tag = (int)polecenie[0];
                        if (tag > 99 && tag < 160 && mainForm != null)   //info z platformy
                        {
                            mainForm.wykonajPolecenie(polecenie);
                        }
                        if (tag > 159 && tag < 200 && manipulatorForm != null)  //info z manipulatorka
                        {
                            manipulatorForm.wykonajPolecenie(polecenie);
                        }
                        if (tag > 199 && tag < 240 && labForm != null)  //info z labka
                        {
                            labForm.wykonajPolecenie(polecenie);
                        }
                        Array.Clear(polecenie, 0, 20);
                        licznik = 0;
                    }
                }
            }
        }

        static public void setNewDataTrans()
        {
            dataTrans = new DataTransfer();
        }

        static public DataTransfer getDataTrans()
        {
            return dataTrans;
        }

        static private void Run()
        {
            mainForm = new Form1();
            Application.Run(mainForm);
        }

        public static void runManipulatorForm()
        {
            manipulatorForm = new FormManipulator();
            manipulatorForm.Show();
        }

        public static void runLabForm()
        {
            labForm = new FormLab();
            labForm.Show();
        }

        public static void runAdminForm()
        {
            adminForm = new FormAdmin();
            adminForm.Show();
        }

        public static FormManipulator getManipulatorFormInfo()
        {
            return manipulatorForm;
        }

        public static void runMapForm()
        {
            mapForm = new FormMap();
            mapForm.Show();
        }

        public static Form1 getMainFormInfo()
        {
            return mainForm;
        }

        public static FormLab getLabFormInfo()
        {
            return labForm;
        }

        public static FormAdmin getAdminFormInfo()
        {
            return adminForm;
        }

        public static void closeManipulatorForm()
        {
            manipulatorForm = null;
        }

        public static void closeLabForm()
        {
            labForm = null;
        }

        public static void closeAdminForm()
        {
            adminForm = null;
        }
    }
}
