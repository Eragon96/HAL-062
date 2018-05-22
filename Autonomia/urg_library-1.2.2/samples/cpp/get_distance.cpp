//  Connects to the sensor via serial interface and gets range data
#include <conio.h>
#include "c/urg_sensor.h"
#include "c/urg_utils.h"
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <list>
//#include "opencv2\highgui\highgui.hpp"
//#include "opencv2\imgproc\imgproc.hpp"

using namespace std;
//using namespace cv;

class CObserwator {
public:
	virtual void update_obstacle(int nr, long distance, bool all_range, int nr_obs) = 0;
	virtual void update_clear(int nr_obs) = 0;
	bool przeszkoda = false;
};

class CObserwator1 :public CObserwator {

	virtual void update_obstacle(int nr, long distance, bool all_range, int nr_obs)
	{
		if (nr_obs == 1) {
			przeszkoda = true;
			cout << "Przeszkoda: " << przeszkoda << endl;
			cout << "wykryto przeszkode w kierunku wybranym przez uzytkownika: " << nr*0.3516 << " , na odleglosci: " << distance << endl;
		}
	}

	virtual void update_clear(int nr_obs)
	{
		if (nr_obs == 1) {
			przeszkoda = false;
			cout << "Przeszkoda: " << przeszkoda << endl;
			cout << "czysto, jedz!" << endl;
		}
	}
};

class CObserwator2 :public CObserwator {

	virtual void update_obstacle(int nr, long distance, bool all_range, int nr_obs)
	{
		if (nr_obs == 2 && all_range == false) {
			przeszkoda = true;
			//cout << "Przeszkoda: " << przeszkoda << endl;
			cout << "wykryto przeszkode!\nWsp. biegunowe przeszkody: (" << distance << ", " << nr*0.3516 << ")" << endl;
		}
		if (nr_obs == 2 && all_range == true) {
			przeszkoda = true;
			//cout << "Przeszkoda: " << przeszkoda << endl;
			cout << "wykryto przeszkode w całym zakresie pomiarowym podanym przez uzytkownika!" << endl;
		}
	}

	virtual void update_clear(int nr_obs)
	{
		if (nr_obs == 2) {
			przeszkoda = false;
			cout << "Przeszkoda: " << przeszkoda << endl;
			cout << "czysto, jedz!" << endl;
		}
	}
};

class CObserwator3 :public CObserwator {
	virtual void update_obstacle(int nr, long distance, bool all_range, int nr_obs)
	{
		if (nr_obs == 3) {
			przeszkoda = true;
			cout << "Przeszkoda: " << przeszkoda << endl;
			cout << "wykryto przeszkode w kierunku wybranym przez uzytkownika: " << nr*0.3516 << " , na odleglosci: " << distance << endl;
		}
	}

	virtual void update_clear(int nr_obs)
	{
		if (nr_obs == 3) {
			przeszkoda = false;
			cout << "Przeszkoda: " << przeszkoda << endl;
			cout << "czysto, jedz!" << endl;
		}
	}
};

//-------------------------------------------------------------------------------------------------------------------------

class CLidar {

protected:
	list <CObserwator*> obserwatorzy;

public:
	void dodaj_obserwatora(CObserwator *o)
	{
		obserwatorzy.push_back(o);
	}

	void usun_obserwatora(CObserwator *o)
	{
		obserwatorzy.remove(o);
	}

	void powiadom(int nr, long distance, bool obstacle, bool all_range, int nr_obs)
	{
		list <CObserwator*>::iterator wsk;
		for (wsk = obserwatorzy.begin(); wsk != obserwatorzy.end(); wsk++)
		{
			if (obstacle == true) {
				(*wsk)->update_obstacle(nr, distance, all_range, nr_obs);
			}
			if (obstacle == false) {
				(*wsk)->update_clear(nr_obs);
			}
		}
	}

private:
	//urg_t urg;
	//int ret;
	long *length_data;
	int length_data_size;
	int wait;
	int counter = 0;
	int licz = 0;

	// Pomiar dla wybranego pojedynczego kąta
	void direct_angle(int ret, urg_t urg, double range)
	{
		double angle;
		cout << "Podaj kat dla ktorego ma byc wykonany pomiar: \n" << "Kat: ";
		cin >> angle;
		angle = check(angle);
		int num_measur = convert(angle);

		bool obstacle = false;

		// Allocates memory to hold received measurement data
		length_data = (long *)malloc(sizeof(long) * urg_max_data_size(&urg));


		while (!_kbhit()) {
			int i = 0;
			int k = 0;

			// Starts range data measurement
			ret = urg_start_measurement(&urg, URG_DISTANCE, 1, 0);

			// Receives the measurement data
			length_data_size = urg_get_distance(&urg, length_data, NULL);

			//cout << "-----------------------------------------------------------------------" << endl;
			for (int j = 0; j < length_data_size; ++j)
			{
				if (j == num_measur)
				{
					if ((range >(length_data[j] / 1000)) && (length_data[j] != 0)) {   //filtrowanie 
						counter++;
						obstacle = true;
						powiadom(j, length_data[j], obstacle, false, 1);
					}
					if (((range < (length_data[j] / 1000)) || (length_data[j] = 0)) && obstacle == true) {
						obstacle = false;
						powiadom(j, length_data[j], obstacle, false, 1);
					}

					//cout << "Pomiar: " << length_data[j];
				}
			}
			//cout << "\n";
			//cout << "-----------------------------------------------------------------------" << endl;
			licz++;
		}
		cout << "Licznik przeszkod: " << counter << endl << "Liczba pomiarow: " << licz;
	}

	// Pomiar dla wybranego zakresu kątowego
	void angular_range(int ret, urg_t urg, double range)
	{
		double angle1, angle2;

		cout << "Podaj zakres katow dla ktorych ma byc wykonany pomiar: \n" << "Kat poczatkowy: ";
		cin >> angle1;
		angle1 = check(angle1);

		cout << "Kat koncowy: ";
		cin >> angle2;
		angle2 = check(angle2);

		if (angle2 < angle1)
		{
			double tmp = angle1;
			angle1 = angle2;
			angle2 = tmp;
		}

		int num_measur1 = convert(angle1);
		int num_measur2 = convert(angle2);

		bool obstacle = false;
		bool start = false;
		bool end = false;

		// Allocates memory to hold received measurement data
		length_data = (long *)malloc(sizeof(long) * urg_max_data_size(&urg));

		while (!_kbhit()) {
			int k = 0; //słuzy do zapamietania ile kolejny potencjalnie niebezpiecznych punkow juz wykryto
			int i = 0; //zlicza kolejne punkty ktore z odczytow moga byc przeszkoda

					   // Starts range data measurement
			ret = urg_start_measurement(&urg, URG_DISTANCE, 1, 0);

			// Receives the measurement data
			length_data_size = urg_get_distance(&urg, length_data, NULL);

			//cout << "-----------------------------------------------------------------------" << endl;
			for (int j = 1; j <= length_data_size; ++j) {
				if (j >= num_measur1 && j <= num_measur2) {
					if ((range > (length_data[j] / 1000)) && (length_data[j] != 0)) {   //filtrowanie 
						i++;
						if (i == 1)
							k = j;
						else if (i == 2 && j - k == 1) {
							k++;
						}
						else if (i == 3 && j - k == 1) {
							k++;
						}
						else if (i == 4 && j - k == 1) {  // 4 kolejne potencjalnie niebezpieczne punkty odbierane sa juz jako przeszkoda 
							k++;
							counter++;
							//cout << "!!!---------------!!!" << endl;
							obstacle = true;
							powiadom(j - 3, length_data[j], obstacle, false, 2);
							powiadom(j - 2, length_data[j], obstacle, false, 2);
							powiadom(j - 1, length_data[j], obstacle, false, 2);
							powiadom(j, length_data[j], obstacle, false, 2);
							if (j - 3 == num_measur1)
								start = true;
						}
						else if (i > 4 && j - k == 1) {
							k++;
							if (j == num_measur2)
							{
								end = true;
								if (start == true)                               //sprawdzanie czy przeszkoda zagradza cały wskazany zakres kątowy
									powiadom(j, length_data[j], obstacle, true, 2);
								else
									powiadom(j, length_data[j], obstacle, false, 2);
							}
							else
								powiadom(j, length_data[j], obstacle, false, 2);
						}
						else {                            //zerowanie licznikow jezeli wykryto mniej niz 4 kolejne potencjalnie niebezpieczne punkty, lub ciag niebezpiecznych punktow sie zakonczy
							i = 0;
							k = 0;
							obstacle = false;
							powiadom(j, length_data[j], obstacle, false, 2);
						}

					}
					else if (obstacle == true) {
						obstacle = false;
						powiadom(j, length_data[j], obstacle, false, 2);
					}
					//cout << "\nPomiar: " << length_data[j] << " ,kat: " << 0.3516 * j;
				}
			}
			//cout << "\n";
			//cout << "-----------------------------------------------------------------------" << endl;
			licz++;
		}
		cout << "Licznik przeszkod: " << counter << endl << "Liczba pomiarow: " << licz;
	}

	// Pomiar ciągły
	void continuous_measurment(int ret, urg_t urg, double range)
	{
		bool obstacle = false;
		bool start = false;
		bool end = false;

		// Allocates memory to hold received measurement data
		length_data = (long *)malloc(sizeof(long) * urg_max_data_size(&urg));

		while (!_kbhit()) {
			int i = 0;  //słuzy do zapamietania ile kolejny potencjalnie niebezpiecznych punkow juz wykryto
			int k = 0;  //zlicza kolejne punkty ktore z odczytow moga byc przeszkoda

						// Starts range data measurement
			ret = urg_start_measurement(&urg, URG_DISTANCE, 1, 0);

			// Receives the measurement data
			length_data_size = urg_get_distance(&urg, length_data, NULL);
			//cout << "-----------------------------------------------------------------------" << endl;
			for (int j = 0; j < length_data_size; ++j) {           //DISPLAY MEASUREMENTS
				if ((range >(length_data[j] / 1000)) && (length_data[j] != 0)) {   //filtrowanie 
					i++;
					if (i == 1)
						k = j;
					else if (i == 2 && j - k == 1) {
						k++;
					}
					else if (i == 3 && j - k == 1) {
						k++;
					}
					else if (i == 4 && j - k == 1) {     // 4 kolejne potencjalnie niebezpieczne punkty odbierane sa juz jako przeszkoda 
						k++;
						counter++;
						//cout << "!!!---------------!!!" << endl;
						obstacle = true;
						powiadom(j - 3, length_data[j], obstacle, false, 2);
						powiadom(j - 2, length_data[j], obstacle, false, 2);
						powiadom(j - 1, length_data[j], obstacle, false, 2);
						powiadom(j, length_data[j], obstacle, false, 2);
						if (j - 3 == 0)
							start = true;
					}
					else if (i > 4 && j - k == 1) {
						k++;
						if (j == length_data_size - 1)
						{
							end = true;
							if (start == true)                               //sprawdzanie czy przeszkoda zagradza cały zakres kątowy (od o do 240)
								powiadom(j, length_data[j], obstacle, true, 2);
							else
								powiadom(j, length_data[j], obstacle, false, 2);
						}
						else
							powiadom(j, length_data[j], obstacle, false, 2);
					}
					else {                               //zerowanie licznikow jezeli wykryto mniej niz 4 kolejne potencjalnie niebezpieczne punkty
						i = 0;
						k = 0;
						obstacle = false;
						powiadom(j, length_data[j], obstacle, false, 2);
					}

				}
				else if (obstacle == true) {
					obstacle = false;
					powiadom(j, length_data[j], obstacle, false, 2);
				}
				//printf("%ld, ", length_data[j]);
			}
			//printf("\n");
			//cout << "-----------------------------------------------------------------------" << endl;
			licz++;
		}
		cout << "Licznik przeszkod: " << counter << endl << "Liczba pomiarow: " << licz;
	}

	//Wybór typu pomiaru
	int choice()
	{
		int x;
		cout << "Wybierz typ pracy: \n1. Pomiar pojedynczego kata\n2. Pomiar danego zakresu katowego\n3. Pomiar ciagly w calym zakresie\n";
		cin >> x;
		if (x > 3 && x < 0)
		{
			cout << "wybierz ponownie: \n";
			cin >> x;
		}
		return x;
	}

	double check(double angle)
	{
		while (angle > 240 && angle < 0)
		{
			cout << "Niepoprawna wartość (wybierz z zakresu od 0 do 240), ponownie wpisz: \n" << "Kat: ";
			cin >> angle;
		}
		return angle;
	}

	int convert(double angle)
	{
		int measurement = (int)(angle * 681) / 239.7912;
		return measurement;
	}

public:

	void Measurment(int ret, urg_t urg, double range, bool error)
	{
		if (error == true) {
			exit;
		}
		else {
			int num = choice();
			if (num == 1)
				direct_angle(ret, urg, range);
			else if (num == 2)
				angular_range(ret, urg, range);
			else if (num == 3)
				continuous_measurment(ret, urg, range);
		}
	}

	CLidar(int *ret, urg_t *urg, bool *error) {
		// "COM3" is, in this case, the device name detected for the sensor
		const char connect_device[] = "COM3";
		const long connect_baudrate = 115200;

		// Connects to the sensor
		*ret = urg_open(urg, URG_SERIAL, connect_device, connect_baudrate);
		if (*ret < 0) {
			cout << "!Brak polaczenia!" << endl;
			*error = true;
		}
	}
};
//682 pomiary ; max kat: 239,77, min kat 0 ; jeden pomiar to 0,3516 stopnia;


//Określenie parametrow początkowych - z jakiej odległości i jakiej wysokości przeszkody klasyfikowane są jako nie do przejsci 
void detection_range(double *range, double *lean)
{
	double high;
	double high_urg = 0.40;  //!wysokość na której znajduje się lidar!

	cout << "Podaj min odleglosc po ktorej wykryta przeszkoda ma byc ominieta (w metrach): ";
	cin >> *range;
	while (*range > 4 && *range < 0)
	{
		cout << "Niepoprawna wartość (wybierz z zakresu od 0 do 4), ponownie wpisz: \n" << "Kat: ";
		cin >> *range;
	}

	cout << "Podaj wysokosc przeszkod ktore maja byc omijane (w metrach): ";
	cin >> high;
	while (high > 0.5 && high < 0)
	{
		cout << "Niepoprawna wartość (wybierz z zakresu od 0 do 0,5), ponownie wpisz: \n" << "Kat: ";
		cin >> high;
	}

	*lean = atan((high_urg - high) / *range);  //wyliczony kąt pochylenia lidara
	cout << "Wyliczony kat pochylenia lidara wynosi: " << lean << endl;

}

int main(void)
{
	urg_t urg;
	int ret;
	bool error;
	int wait;
	double range, lean;

	detection_range(&range, &lean);

	CLidar obj(&ret, &urg, &error);

	CObserwator *obs1 = new CObserwator1;
	obj.dodaj_obserwatora(obs1);
	CObserwator *obs2 = new CObserwator2;
	obj.dodaj_obserwatora(obs2);
	CObserwator *obs3 = new CObserwator3;
	obj.dodaj_obserwatora(obs3);

	obj.Measurment(ret, urg, range, error);

	cin >> wait;    

	// Disconnects from the sensor
	urg_close(&urg);

	delete obs1;
	delete obs2;
	delete obs3;

	return 0;
}