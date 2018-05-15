using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Windows.Forms;
using _3Dconnexion;
using System.IO;
using System.Runtime.InteropServices;
using System.Security.Permissions;
using KNRapp.Properties;


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


            hWnd = Handle;

            // Prepare log file
            File.Create(logFileName).Close();

            // Initialize the driver
            if (InitializeSiApp())
            {
                // Export the application commands to the driver
                ExportApplicationCommands();

                // Set the buttonbank / action set to use on the 3Dconnexion devices
                SiApp.SiAppCmdActivateActionSet(devHdl, @"ACTION_SET_ID");
            }
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
                    /*
                    textBox15.Text = "" + outputInverseKinematicsTab[0];
                    textBox14.Text = "" + outputInverseKinematicsTab[1];
                    textBox13.Text = "" + outputInverseKinematicsTab[2];
                    textBox12.Text = "" + outputInverseKinematicsTab[3];
                    textBox11.Text = "" + outputInverseKinematicsTab[4];
                    textBox10.Text = "" + outputInverseKinematicsTab[5];
                    textBox9.Text = "" + outputInverseKinematicsTab[6];
                    */
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
        #region mouse6d

        private const string appName = "Test Siapp";
        private const string logFileName = "log.txt";
        private const string templateTR = "TX: {1,-7}{0}TY: {2,-7}{0}TZ: {3,-7}{0}RX: {4,-7}{0}RY: {5,-7}{0}RZ: {6,-7}{0}P: {7}";

        private IntPtr hWnd = IntPtr.Zero;
        private IntPtr devHdl = IntPtr.Zero;
        private SiApp.SpwRetVal res;


        [PermissionSet(SecurityAction.Demand, Name = "FullTrust")]
        protected override void WndProc(ref Message msg)
        {
            TrackMouseEvents(msg);

            base.WndProc(ref msg);
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            CloseSiApp();
        }

        #region Methods

        private bool InitializeSiApp()
        {
            res = SiApp.SiInitialize();
            if (res != SiApp.SpwRetVal.SPW_NO_ERROR)
            {
                MessageBox.Show("Initialize function failed");
                return false;
            }

            Log("SiInitialize", res.ToString());

            SiApp.SiOpenData openData = new SiApp.SiOpenData();
            SiApp.SiOpenWinInit(openData, hWnd);
            if (openData.hWnd == IntPtr.Zero)
                MessageBox.Show("Handle is empty");
            Log("SiOpenWinInit", openData.hWnd + "(window handle)");

            devHdl = SiApp.SiOpen(appName, SiApp.SI_ANY_DEVICE, IntPtr.Zero, SiApp.SI_EVENT, openData);
            if (devHdl == IntPtr.Zero)
                MessageBox.Show("Open returns empty device handle");
            Log("SiOpen", devHdl + "(device handle)");

            return (devHdl != IntPtr.Zero);
        }

        private void CloseSiApp()
        {
            if (devHdl != IntPtr.Zero)
            {
                SiApp.SpwRetVal res = SiApp.SiClose(devHdl);
                Log("SiClose", res.ToString());
                int r = SiApp.SiTerminate();
                Log("SiTerminate", r.ToString());
            }
        }

        private void TrackMouseEvents(Message msg)
        {
            if (!SiApp.IsSpaceMouseMessage(msg.Msg)) // ogarniać warunek
                return;

            SiApp.SiGetEventData eventData = new SiApp.SiGetEventData();
            SiApp.SiGetEventWinInit(eventData, msg.Msg, msg.WParam, msg.LParam);

            SiApp.SiSpwEvent spwEvent = new SiApp.SiSpwEvent();
            SiApp.SpwRetVal val = SiApp.SiGetEvent(devHdl, SiApp.SI_AVERAGE_EVENTS, eventData, spwEvent);

            if (val == SiApp.SpwRetVal.SI_IS_EVENT)
            {
                Log("SiGetEventWinInit", eventData.msg.ToString());

                switch (spwEvent.type)
                {
                    case 0:
                        break;

                    case SiApp.SiEventType.SI_MOTION_EVENT:
                        {
                            
                            /*string motionData = string.Format(templateTR, "",
                              spwEvent.spwData.mData[0], spwEvent.spwData.mData[1], spwEvent.spwData.mData[2], // TX, TY, TZ
                              spwEvent.spwData.mData[3], spwEvent.spwData.mData[4], spwEvent.spwData.mData[5], // RX, RY, RZ
                              spwEvent.spwData.period); // Period (normally 16 ms)
                            Print("Motion event " + motionData);
                            */
                            for (int i = 0; i < 6; i++)
                            {
                                outputInverseKinematicsTab[i] = spwEvent.spwData.mData[i];
                                
                            }
                            if (inverseKinematics)
                            {
                                textBox15.Text = "" + outputInverseKinematicsTab[0];
                                textBox14.Text = "" + outputInverseKinematicsTab[1];
                                textBox13.Text = "" + outputInverseKinematicsTab[2];
                                textBox12.Text = "" + outputInverseKinematicsTab[3];
                                textBox11.Text = "" + outputInverseKinematicsTab[4];
                                textBox10.Text = "" + outputInverseKinematicsTab[5];
                                textBox9.Text = "" + outputInverseKinematicsTab[6];
                            }
                        }
                        break;

                    case SiApp.SiEventType.SI_ZERO_EVENT:
                        for(int i = 0; i < 6; i++)
                        {
                            outputInverseKinematicsTab[i] = 0;
                        }
                        break;

                    case SiApp.SiEventType.SI_CMD_EVENT:
                        Log("SI_APP_EVENT: ", string.Format("V3DCMD = {0}, pressed = {1}", spwEvent.cmdEventData.functionNumber, spwEvent.cmdEventData.pressed > 0));
                        Print("V3DCMD event: V3DCMD = {0}, pressed = {1}", spwEvent.cmdEventData.functionNumber, spwEvent.cmdEventData.pressed > 0);
                        break;

                    case SiApp.SiEventType.SI_APP_EVENT:
                        Log("SI_APP_EVENT: ", string.Format("appCmdID = \"{0}\", pressed = {1}", spwEvent.appCommandData.id.appCmdID, spwEvent.appCommandData.pressed > 0));
                        Print("App event: appCmdID = \"{0}\", pressed = {1}", spwEvent.appCommandData.id.appCmdID, spwEvent.appCommandData.pressed > 0);
                        break;

                    default:
                        Print("Event: type = \"{0}\"", spwEvent.type);
                        break;
                }

                Log("SiGetEvent", string.Format("{0}({1})", spwEvent.type, val));
            }
        }

        /// <summary>
        /// Method to export the application commands to 3dxware so that they can be assigned to
        /// 3Dconnexion device buttons.
        /// </summary>
        private void ExportApplicationCommands()
        {
            string imagesPath = string.Empty;
            string resDllPath = string.Empty;
            string dllName = "3DxService.dll";

            string homePath = Get3DxWareHomeDirectory();

            if (!string.IsNullOrEmpty(homePath))
            {
                imagesPath = Path.Combine(homePath, @"Cfg\Images\3DxService\{0}");
                resDllPath = Path.Combine(homePath, @"en-US\" + dllName);
            }

            using (ActionCache cache = new ActionCache())
            {
                // An actionset can also be considered to be a buttonbank, a menubar, or a set of toolbars
                ActionNode buttonBank = cache.Add(new ActionSet("ACTION_SET_ID", "Custom action set"));

                // Add a couple of categiores / menus / tabs to the buttonbank/menubar/toolbar
                ActionNode fileNode = buttonBank.Add(new Category("CAT_ID_FILE", "File"));
                ActionNode editNode = buttonBank.Add(new Category("CAT_ID_EDIT", "Edit"));

                // Add menu items to the menus. When the button on the 3D mouse is pressed the id will be sent to the application
                // in the SI_APP_EVENT event structure in the SiAppCmdID.appCmdID field

                // Add menu items / actions which use bitmaps loaded in memory of this application
                //fileNode.Add(new _3Dconnexion.Action("ID_OPEN", "Open", "Open file", ImageItem.FromImage(Resources.Open)));
                //fileNode.Add(new _3Dconnexion.Action("ID_CLOSE", "Close", "Close file", ImageItem.FromImage(Resources.Сlose)));
                //fileNode.Add(new _3Dconnexion.Action("ID_EXIT", "Exit", "Exit program", ImageItem.FromImage(Resources.Exit)));

                // Export a menu item / action using a bitmap from an external dll resource
                fileNode.Add(new _3Dconnexion.Action("ID_ABOUT", "About", "Info about the program", ImageItem.FromResource(resDllPath, "#172", "#2")));

                // Add menu items / actions using bitmaps located on the harddrive
                editNode.Add(new _3Dconnexion.Action("ID_CUT", "Cut", "Shortcut is Ctrl + X", ImageItem.FromFile(string.Format(imagesPath, "Macro_Cut.png"))));
                editNode.Add(new _3Dconnexion.Action("ID_COPY", "Copy", "Shortcut is Ctrl + C", ImageItem.FromFile(string.Format(imagesPath, "Macro_Copy.png"))));
                editNode.Add(new _3Dconnexion.Action("ID_PASTE", "Paste", "Shortcut is Ctrl + V", ImageItem.FromFile(string.Format(imagesPath, "Macro_Paste.png"))));

                // Add a menu item without an image associated with it
                editNode.Add(new _3Dconnexion.Action("ID_UNDO", "Undo", "Shortcut is Ctrl + Z"));

                // Now add an image and associate it with the menu item ID_UNDO by using the same id as the menu item / action
                cache.Add(ImageItem.FromFile(string.Format(imagesPath, "Macro_Undo.png"), 0, @"ID_UNDO"));
                try
                {
                    // Write the complete cache to the driver
                    cache.SaveTo3Dxware(devHdl);
                }
                catch (Exception e)
                {
                    Log("cache.SaveTo3Dxware", e.Message);
                }
            }
        }

        private string Get3DxWareHomeDirectory()
        {
            string softwareKeyName = string.Empty;
            string homeDirectory = string.Empty;

            if (IntPtr.Size == 8)
            {
                softwareKeyName = @"HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\3Dconnexion\3DxWare";
            }
            else
            {
                softwareKeyName = @"HKEY_LOCAL_MACHINE\SOFTWARE\3Dconnexion\3DxWare";
            }

            object regValue = Microsoft.Win32.Registry.GetValue(softwareKeyName, "Home Directory", null);
            if (regValue != null)
            {
                homeDirectory = regValue.ToString();
            }

            return homeDirectory;
        }

        private T PtrToStructure<T>(IntPtr ptr) where T : struct
        {
            return (T)Marshal.PtrToStructure(ptr, typeof(T));
        }

        #endregion Methods

        #region Logging

        private void Print(string format, params object[] args)
        {
            //Print(string.Format(format, args));
        }

        private void Print(string message)
        {
            //textBox1.AppendText(string.Format("{0}{1}", message, Environment.NewLine));
        }

        private void Log(string functionName, string result)
        {
            string msg = string.Format("{0}: Function {1} returns {2}{3}", DateTime.Now, functionName, result, Environment.NewLine);
            try
            {
                File.AppendAllText(logFileName, msg);
            }
            catch { };
        }

        #endregion Logging
    


        #endregion mouse6d
    }
}
