using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SlimDX.DirectInput;
using System.IO.Ports;

namespace KNRapp
{
    class Joy
    {   
        public Joy()
        {
            GetSticks(); //Start the process
            Sticks = GetSticks();
        }
        

        SlimDX.DirectInput.Joystick stick;
        DirectInput Input = new DirectInput();
        Joystick[] Sticks;

        public Joystick[] GetSticks()
        {
            List<SlimDX.DirectInput.Joystick> sticks = new List<SlimDX.DirectInput.Joystick>();
            foreach (DeviceInstance device in Input.GetDevices(DeviceClass.GameController, DeviceEnumerationFlags.AttachedOnly))
            {
                try
                {
                    stick = new SlimDX.DirectInput.Joystick(Input, device.InstanceGuid);
                    stick.Acquire();

                    foreach (DeviceObjectInstance deviceObject in stick.GetObjects())
                    {
                        if ((deviceObject.ObjectType & ObjectDeviceType.Axis) != 0)
                        {
                            stick.GetObjectPropertiesById((int)deviceObject.ObjectType).SetRange(-100, 100);
                        }
                    }
                    sticks.Add(stick);
                }
                catch (DirectInputException)
                {
                    Form1.myForm1.diagnosticPrint("Nie wykryto Joysticku");
                }
            }
            return sticks.ToArray();
        }

        public JoystickState getCurrentState()
        {
            try
            {
                return stick.GetCurrentState();
            }
            catch (System.NullReferenceException)
            {
                Form1.myForm1.diagnosticPrint("Nie wykryto Joysticku");
            }
            return null;
        }

        public int getXValue()
        {
            try
            {
                return stick.GetCurrentState().X;
        }
            catch (System.NullReferenceException)
            {
                Form1.myForm1.diagnosticPrint("Nie wykryto Joysticku");
            }
            return 0;
        }

        public int getYValue()
        {
            try
            {
                return stick.GetCurrentState().Y;
}
            catch (System.NullReferenceException)
            {
                Form1.myForm1.diagnosticPrint("Nie wykryto Joysticku");
            }
            return 0;
        }

        public int getZValue()
        {
            try
            {
                return stick.GetCurrentState().Z;
}
            catch (System.NullReferenceException)
            {
                Form1.myForm1.diagnosticPrint("Nie wykryto Joysticku");
            }
            return 0;
        }

        public bool[] getButtons()
        {
            try
            {
                return stick.GetCurrentState().GetButtons();
}
            catch (System.NullReferenceException)
            {
                Form1.myForm1.diagnosticPrint("Nie wykryto Joysticku");
            }
            return null;
        }
    }
}
