using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//using EARTHLib;
using System.IO;

namespace KNRapp
{
    public partial class GPSfile
    {
        string plikGPS = @"..\GPSdata.kml";
        //private EARTHLib.ApplicationGE ge = null;
        static Encoding enc8 = Encoding.UTF8;

        public GPSfile()
        {
            plikGPS = Path.GetFullPath(plikGPS);

            if (!File.Exists(plikGPS))
            {
                GPSreset(false);
            }
        }

        public void GPSstart()
        {
            try
            {
                //ge = new ApplicationGEClass();
                if (File.Exists(plikGPS))
                {
                    //ge.OpenKmlFile(plikGPS, 0);
                    System.Diagnostics.Process.Start(plikGPS);
                }
            }
            catch (Exception e)
            {

            }
        }

        public void GPSreset(Boolean czyWyswietlic)
        {
            File.Delete(plikGPS);
            FileStream fs = File.Create(plikGPS);
            fs.Close();
            File.WriteAllLines(plikGPS, emptyFile);
            if (czyWyswietlic)
            {
                if ( File.Exists(plikGPS))
                {
                    //ge.OpenKmlFile(plikGPS, 0);
                    System.Diagnostics.Process.Start(plikGPS);
                }
            }
        }

        public void GPStoFile(string X, string Y)
        {
            string[] GPSdata = File.ReadAllLines(plikGPS);
            int n = GPSdata.Length;
            GPSdata[n - 6] = X + "," + Y + ",20";
            GPSdata[n - 17] = GPSdata[n - 17] + "\n\t" + X + "," + Y + ",20";
            File.WriteAllLines(plikGPS, GPSdata);
            if ( File.Exists(plikGPS))
            {
                //ge.OpenKmlFile(plikGPS, 0);
                System.Diagnostics.Process.Start(plikGPS);
            }
        }

        public void GPSset(byte[] polecenie)
        {
            byte[] X=null;
            byte[] Y=null;
            Array.Copy(polecenie, 19, X, 1, 9);
            Array.Copy(polecenie, 31, Y, 1, 10);
            if (polecenie[29] == 'S')
            {
                X[0] = (byte)'-';
            }
            else
            {
                X[0] = (byte)' ';
            }
            if (polecenie[42] == 'W')
            {
                Y[0] = (byte)'-';
            }
            else
            {
                Y[0] = (byte)' ';
            }

            string Yconverted = enc8.GetString(GPSconvert(Y));
            string Xconverted = enc8.GetString(GPSconvert(X));

            Form1.myForm1.gpsPrint(Xconverted, Yconverted);

            GPStoFile(Yconverted, Xconverted);
        }

        //konwersja danych GPS w formacie DDMM.MMMM na DD.DDDDDD
        private byte[] GPSconvert(byte[] dane)
        {
            int i = 0;
            for (i = 0; i < dane.Length; i++)
            {
                if (dane[i] == '.')
                {
                    break;
                }
            }

            double daneDouble = 0; //zmienna zawiera tylko część MM.MMMM czyli minuty 
            daneDouble += (dane[i - 2] - '0') * 10;
            daneDouble += (dane[i - 1] - '0') * 1;
            daneDouble += (dane[i + 1] - '0') * 0.1;
            daneDouble += (dane[i + 2] - '0') * 0.01;
            daneDouble += (dane[i + 3] - '0') * 0.001;
            daneDouble += (dane[i + 4] - '0') * 0.0001;

            daneDouble = daneDouble / 60.0;

            byte[] wynik = Encoding.ASCII.GetBytes(daneDouble.ToString("0.000000"));  //wynik konwersji minut na stopnie

            int k = 0;
            for (k = 0; k < wynik.Length; k++)
            {
                if (wynik[k] == (byte)',')
                {
                    break;
                }
            }
            int j = 0;
            byte[] wynikKoncowy = new byte[30];
            for (j = 0; j < (i - 2); j++)
            {
                wynikKoncowy[j] = dane[j];
            }

            wynikKoncowy[i - 2] = (byte)'.';

            for (j = i - 1; j < i + 5; j++, k++)
            {
                wynikKoncowy[j] = wynik[k + 1];
            }
            Array.Resize(ref wynikKoncowy, j);

            if (wynikKoncowy[0] == ' ')
            {
                wynikKoncowy = wynikKoncowy.Skip(1).ToArray();
            }
            return wynikKoncowy;
        }

        string[] emptyFile ={"<?xml version=\"1.0\" encoding=\"UTF-8\"?>",
"<kml xmlns=\"http://earth.google.com/kml/2.2 \">",
"<Document>",
"<name>Pozycja pojazdu</name>",
"<open>1</open>",
"<Style id=\"yellowLineGreenPoly\">",
"<LineStyle>",
"<color>7f00ffff</color>",
"<width>4</width>",
"</LineStyle>",
"<PolyStyle>",
"<color>7f00ff00</color>",
"</PolyStyle>",
"</Style>",
"<Style id=\"downArrowIcon\">",
"<IconStyle>",
"<Icon>",
"<href>http://maps.google.com/mapfiles/kml/pal4/icon28.png</href>",
"</Icon>",
"</IconStyle>",
"</Style>",
"<Placemark>",
"<name>Przejechana trasa</name>",
"<description></description>",
"<styleUrl>#yellowLineGreenPoly</styleUrl>",
"<LineString>",
"<extrude>1</extrude>",
"<tessellate>1</tessellate>",
"<altitudeMode>relativeToGround</altitudeMode>",
"<coordinates>",
" ",
"</coordinates>",
"</LineString>",
"</Placemark>",
"<Placemark>",
"<name>Nasz Pojazd</name>",
"<visibility>1</visibility>",
"<styleUrl>#downArrowIcon</styleUrl>",
"<Point>",
"<altitudeMode>relativeToGround</altitudeMode>",
"<coordinates>",
" ",
"</coordinates>",
"</Point>",
"</Placemark>",
"</Document>",
"</kml>"};
    }
}
