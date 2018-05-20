using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Renci.SshNet;
using System.Diagnostics;
using System.Threading;

namespace KNRapp
{
    class DataTransfer
    {
        Process cmd;
        char[] output = new char[1000];
        bool useSSH;
        private System.IO.Ports.SerialPort serialPort1;

        public DataTransfer()
        {
            cmd = new Process();
            serialPort1 = new System.IO.Ports.SerialPort();
        }

        public void openSerial(string portName)
        {
            useSSH = false;
            serialPort1.BaudRate = 115200;
            serialPort1.ParityReplace = ((byte)(3));
            serialPort1.PortName = portName;
            serialPort1.Open();
            serialPort1.DiscardInBuffer();
        }

        public void closeSerial()
        {
            try
            {
                serialPort1.Close();
            }
            catch (System.IO.IOException)
            {

            }
        }

        public void openSSH()
        {
            useSSH = true;
            cmd.StartInfo.FileName = @".\plink.exe";
            cmd.StartInfo.UseShellExecute = false;
            cmd.StartInfo.RedirectStandardInput = true;
            cmd.StartInfo.RedirectStandardOutput = true;
            cmd.StartInfo.Arguments = "-ssh serial@192.168.1.2 -pw lubieroboty123";
            cmd.Start();
            //Thread.Sleep(1000);
            cmd.StandardOutput.Read(output, 0, 1000);
            Array.Clear(output, 0, 1000);

        }

        public void closeSSH()
        {
            try
            {
                cmd.Close();
            }
            catch (System.IO.IOException)
            {

            }
            useSSH = false;
        }

        public void Write(byte[] buffer, int offset, int count)
        {
            if (useSSH)
            {
                char[] bufferChar = new char[buffer.Length];
                for (int i = 0; i < buffer.Length; i++)
                {
                    //bufferChar[i] = GOWNOcoversionDoWyslania(buffer[i]);
                    bufferChar[i] = (char)buffer[i];
                }
                cmd.StandardInput.Write(bufferChar, offset, count);
                Console.WriteLine("ja to wysyłam");
            }
            else
            {
                serialPort1.Write(buffer, offset, count);
            }

        }

        public int Read(byte[] buffer, int offset, int count)
        {

            if (useSSH)
            {
                Char[] bufferChar = new Char[buffer.Length];
                int n = cmd.StandardOutput.Read(bufferChar, offset, count);
                for (int i = 0; i < n; i++)
                {
                    buffer[i] = GOWNOcoversion(bufferChar[i]);

                }
                return n;
            }
            else
            {
                int n = serialPort1.BytesToRead;
                if (n > count)
                {
                    n = count - 1;
                }
                n = serialPort1.Read(buffer, offset, n);
                return n;
            }

        }

        public bool IsOpen()
        {
            if (useSSH)
            {
                return !cmd.HasExited;
            }
            else
            {
                return serialPort1.IsOpen;
            }
        }

        private byte GOWNOcoversion(char data)
        {
            switch (data)
            {
                case (char)8364: return 128;
                case (char)8218: return 130;
                case (char)8222: return 132;
                case (char)8230: return 133;
                case (char)8224: return 134;
                case (char)8225: return 135;
                case (char)8240: return 137;
                case (char)352:  return 138;
                case (char)8249: return 139;
                case (char)346:  return 140;
                case (char)356:  return 141;
                case (char)381:  return 142;
                case (char)377:  return 143;
                case (char)8216: return 145;
                case (char)8217: return 146;
                case (char)8220: return 147;
                case (char)8221: return 148;
                case (char)8226: return 149;
                case (char)8211: return 150;
                case (char)8212: return 151;
                case (char)152:  return 152;
                case (char)8482: return 153;
                case (char)353:  return 154;
                case (char)8250: return 155;
                case (char)347: return 156;
                case (char)357: return 157;
                case (char)382: return 158;
                case (char)378: return 159;
                case (char)160: return 160;
                case (char)711: return 161;
                case (char)728: return 162;
                case (char)321: return 163;
                case (char)164: return 164;
                case (char)260: return 165;
                case (char)166: return 166;
                case (char)167: return 167;
                case (char)168: return 168;
                case (char)169: return 169;
                case (char)350: return 170;
                case (char)171: return 171;
                case (char)172: return 172;
                case (char)173: return 173;
                case (char)174: return 174;
                case (char)379: return 175;
                case (char)176: return 176;
                case (char)177: return 177;
                case (char)731: return 178;
                case (char)322: return 179;
                case (char)180: return 180;
                case (char)181: return 181;
                case (char)182: return 182;
                case (char)183: return 183;
                case (char)184: return 184;
                case (char)261: return 185;
                case (char)351: return 186;
                case (char)187: return 187;
                case (char)317: return 188;
                case (char)733: return 189;
                case (char)318: return 190;
                case (char)380: return 191;
                case (char)340: return 192;
                case (char)193: return 193;
                case (char)194: return 194;
                case (char)258: return 195;
                case (char)196: return 196;
                case (char)313: return 197;
                case (char)262: return 198;
                case (char)199: return 199;
                case (char)268: return 200;
                case (char)201: return 201;
                case (char)280: return 202;
                case (char)203: return 203;
                case (char)282: return 204;
                case (char)205: return 205;
                case (char)206: return 206;
                case (char)270: return 207;
                case (char)272: return 208;
                case (char)323: return 209;
                case (char)327: return 210;
                case (char)211: return 211;
                case (char)212: return 212;
                case (char)336: return 213;
                case (char)214: return 214;
                case (char)215: return 215;
                case (char)344: return 216;
                case (char)366: return 217;
                case (char)218: return 218;
                case (char)368: return 219;
                case (char)220: return 220;
                case (char)221: return 221;
                case (char)354: return 222;
                case (char)223: return 223;
                case (char)341: return 224;
                case (char)225: return 225;
                case (char)226: return 226;
                case (char)259: return 227;
                case (char)228: return 228;
                case (char)314: return 229;
                case (char)263: return 230;
                case (char)231: return 231;
                case (char)269: return 232;
                case (char)233: return 233;
                case (char)281: return 234;
                case (char)235: return 235;
                case (char)283: return 236;
                case (char)237: return 237;
                case (char)238: return 238;
                case (char)271: return 239;
                case (char)273: return 240;
                case (char)324: return 241;
                case (char)328: return 242;
                case (char)243: return 243;
                case (char)244: return 244;
                case (char)337: return 245;
                case (char)246: return 246;
                case (char)247: return 247;
                case (char)345: return 248;
                case (char)367: return 249;
                case (char)250: return 250;
                case (char)369: return 251;
                case (char)252: return 252;
                case (char)253: return 253;
                case (char)355: return 254;
                case (char)729: return 255;
                default:
                    return (byte)data;
            }
        }

        private char GOWNOcoversionDoWyslania(byte data)
        {
            switch (data)
            {
                case 128: return (char) 8364;
                case 129: return (char)129;
                case 130: return (char)8218;
                case 131: return (char)131;
                case 132: return (char)8222;
                case 133: return (char)8230;
                case 134: return (char)8224;
                case 135: return (char)8225;
                case 136: return (char)136;
                case 137: return (char)8240;
                case 138: return (char)352;
                case 139: return (char)8249;
                case 140: return (char)346;
                case 141: return (char)356;
                case 142: return (char)381;
                case 143: return (char)377;
                case 144: return (char)144;
                case 145: return (char)8216;
                case 146: return (char)8217;
                case 147: return (char)8220;
                case 148: return (char)8221;
                case 149: return (char)8226;
                case 150: return (char)8211;
                case 151: return (char)8212;
                case 152: return (char)152;
                case 153: return (char)8482;
                case 154: return (char)353;
                case 155: return (char)8250;
                case 156: return (char)347;
                case 157: return (char)357;
                case 158: return (char)382;
                case 159: return (char)378;
                case 160: return (char)160;
                case 161: return (char)711;
                case 162: return (char)728;
                case 163: return (char)321;
                case 164: return (char)164;
                case 165: return (char)260;
                case 166: return (char)166;
                case 167: return (char)167;
                case 168: return (char)168;
                case 169: return (char)169;
                case 170: return (char)350;
                case 171: return (char)171;
                case 172: return (char)172;
                case 173: return (char)173;
                case 174: return (char)174;
                case 175: return (char)379;
                case 176: return (char)176;
                case 177: return (char)177;
                case 178: return (char)731;
                case 179: return (char)322;
                case 180: return (char)180;
                case 181: return (char)181;
                case 182: return (char)182;
                case 183: return (char)183;
                case 184: return (char)184;
                case 185: return (char)261;
                case 186: return (char)351;
                case 187: return (char)187;
                case 188: return (char)317;
                case 189: return (char)733;
                case 190: return (char)318;
                case 191: return (char)380;
                case 192: return (char)340;
                case 193: return (char)193;
                case 194: return (char)194;
                case 195: return (char)258;
                case 196: return (char)196;
                case 197: return (char)313;
                case 198: return (char)262;
                case 199: return (char)199;
                case 200: return (char)268;
                case 201: return (char)201;
                case 202: return (char)280;
                case 203: return (char)203;
                case 204: return (char)282;
                case 205: return (char)205;
                case 206: return (char)206;
                case 207: return (char)270;
                case 208: return (char)272;
                case 209: return (char)323;
                case 210: return (char)327;
                case 211: return (char)211;
                case 212: return (char)212;
                case 213: return (char)336;
                case 214: return (char)214;
                case 215: return (char)215;
                case 216: return (char)344;
                case 217: return (char)366;
                case 218: return (char)218;
                case 219: return (char)368;
                case 220: return (char)220;
                case 221: return (char)221;
                case 222: return (char)354;
                case 223: return (char)223;
                case 224: return (char)341;
                case 225: return (char)225;
                case 226: return (char)226;
                case 227: return (char)259;
                case 228: return (char)228;
                case 229: return (char)314;
                case 230: return (char)263;
                case 231: return (char)231;
                case 232: return (char)269;
                case 233: return (char)233;
                case 234: return (char)281;
                case 235: return (char)235;
                case 236: return (char)283;
                case 237: return (char)237;
                case 238: return (char)238;
                case 239: return (char)271;
                case 240: return (char)273;
                case 241: return (char)324;
                case 242: return (char)328;
                case 243: return (char)243;
                case 244: return (char)244;
                case 245: return (char)337;
                case 246: return (char)246;
                case 247: return (char)247;
                case 248: return (char)345;
                case 249: return (char)367;
                case 250: return (char)250;
                case 251: return (char)369;
                case 252: return (char)252;
                case 253: return (char)253;
                case 254: return (char)355;
                case 255: return (char)729;
                default:
                    return (char)data;
            }
        }

        private void TestTrans()
        {
            char[] data = new char[10];
            data[0] = (char)128;
            data[1] = (char)729;
            cmd.StandardInput.Write(data, 0, 2);
        }

        static void Main1()
        {
            DataTransfer d = new DataTransfer();
            d.openSSH();
            d.TestTrans();
        }

        /*  static void Main1()
          {

              [10]: 261 'ą'
    [11]: 351 'ş'
    [12]: 187 '»'
    [13]: 317 'Ľ'
    [14]: 733 '˝'
    [15]: 318 'ľ'
    [16]: 380 'ż'
    [17]: 340 'Ŕ'
    [18]: 193 'Á'
    [19]: 194 'Â'
    [20]: 258 'Ă'
    [21]: 196 'Ä'
    [22]: 313 'Ĺ'
    [23]: 262 'Ć'
    [24]: 199 'Ç'
    [25]: 268 'Č'
    [26]: 201 'É'
    [27]: 280 'Ę'
    [28]: 203 'Ë'
    [29]: 282 'Ě'
    [30]: 205 'Í'
    [31]: 206 'Î'
    [32]: 270 'Ď'
    [33]: 272 'Đ'
    [34]: 323 'Ń'
    [35]: 327 'Ň'
    [36]: 211 'Ó'
    [37]: 212 'Ô'
    [38]: 336 'Ő'
    [39]: 214 'Ö'
    [40]: 215 '×'
    [41]: 344 'Ř'
    [42]: 366 'Ů'
    [43]: 218 'Ú'
    [44]: 368 'Ű'
    [45]: 220 'Ü'
    [46]: 221 'Ý'
    [47]: 354 'Ţ'
    [48]: 223 'ß'
    [49]: 341 'ŕ'
    [50]: 225 'á'
    [51]: 226 'â'
    [52]: 259 'ă'
    [53]: 228 'ä'
    [54]: 314 'ĺ'
    [55]: 263 'ć'
    [56]: 231 'ç'
    [57]: 269 'č'
    [58]: 233 'é'
    [59]: 281 'ę'
    [60]: 235 'ë'
    [61]: 283 'ě'
    [62]: 237 'í'
    [63]: 238 'î'
    [64]: 271 'ď'
    [65]: 273 'đ'
    [66]: 324 'ń'
    [67]: 328 'ň'
    [68]: 243 'ó'
    [69]: 244 'ô'
    [70]: 337 'ő'
    [71]: 246 'ö'
    [72]: 247 '÷'
    [73]: 345 'ř'
    [74]: 367 'ů'
    [75]: 250 'ú'
    [76]: 369 'ű'
    [77]: 252 'ü'
    [78]: 253 'ý'
    [79]: 355 'ţ'
    [80]: 729 '˙'
              Process cmd = new Process();
              cmd.StartInfo.FileName = @".\plink.exe";
              cmd.StartInfo.UseShellExecute = false;
              cmd.StartInfo.RedirectStandardInput = true;
              cmd.StartInfo.RedirectStandardOutput = true;
              cmd.StartInfo.Arguments = "-ssh serial@192.168.1.2 -pw lubieroboty123";
              cmd.Start();
              char[] output = new char[1000];
              Thread.Sleep(3000);
             // cmd.StandardOutput.DiscardBufferedData();
              Thread.Sleep(1000);

              Console.WriteLine(cmd.StandardOutput.Read(output,0,1000));
              Array.Clear(output, 0, 1000);
              Thread.Sleep(1000);
              Console.WriteLine(cmd.StandardOutput.Read(output, 0, 1000));
              Console.WriteLine(output);
              Console.WriteLine();
              */
        // }
    }
}
