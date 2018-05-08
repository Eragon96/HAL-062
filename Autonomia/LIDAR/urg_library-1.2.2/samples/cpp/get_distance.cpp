//  Connects to the sensor via serial interface and gets range data
#include <conio.h>
#include "c/urg_sensor.h"
#include "c/urg_utils.h"
#include <stdlib.h>
#include <iostream>
//#include "opencv2\highgui\highgui.hpp"
//#include "opencv2\imgproc\imgproc.hpp"

using namespace std;
//using namespace cv;

class CLidar {

private:
	//urg_t urg;
	//int ret;
	long *length_data;
	int length_data_size;
	int wait;        // DH
	int counter = 0;   // DH

					   // Pomiar dla wybranego pojedynczego kąta
	void direct_angle(int ret, urg_t urg)
	{
		double angle;
		cout << "Podaj kat dla ktorego ma byc wykonany pomiar: \n" << "Kat: ";
		cin >> angle;
		angle = check(angle);
		int num_measur = convert(angle);

		// Allocates memory to hold received measurement data
		length_data = (long *)malloc(sizeof(long) * urg_max_data_size(&urg));


		while (!_kbhit()) {

			// Starts range data measurement
			ret = urg_start_measurement(&urg, URG_DISTANCE, 1, 0);

			// Receives the measurement data
			length_data_size = urg_get_distance(&urg, length_data, NULL);

			cout << "-----------------------------------------------------------------------" << endl;
			for (int i = 0; i < length_data_size; ++i) {
				if (i == num_measur)
					cout << "Pomiar: " << length_data[i];
			}
			cout << "\n";
			cout << "-----------------------------------------------------------------------" << endl;
		}
	}

	// Pomiar dla wybranego zakresu kątowego
	void angular_range(int ret, urg_t urg)
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

		// Allocates memory to hold received measurement data
		length_data = (long *)malloc(sizeof(long) * urg_max_data_size(&urg));

		while (!_kbhit()) {

			// Starts range data measurement
			ret = urg_start_measurement(&urg, URG_DISTANCE, 1, 0);

			// Receives the measurement data
			length_data_size = urg_get_distance(&urg, length_data, NULL);

			cout << "-----------------------------------------------------------------------" << endl;
			for (int i = 1; i <= length_data_size; ++i) {
				if (i >= num_measur1 && i <= num_measur2)
					cout << "\nPomiar: " << length_data[i] << " ,kat: " << 0, 3516 * i;
			}
			cout << "\n";
			cout << "-----------------------------------------------------------------------" << endl;
		}
	}

	// Pomiar ciągły
	void continuous_measurment(int ret, urg_t urg)
	{
		// Allocates memory to hold received measurement data
		length_data = (long *)malloc(sizeof(long) * urg_max_data_size(&urg));

		while (!_kbhit()) {

			// Starts range data measurement
			ret = urg_start_measurement(&urg, URG_DISTANCE, 1, 0);

			// Receives the measurement data
			length_data_size = urg_get_distance(&urg, length_data, NULL);
			cout << "-----------------------------------------------------------------------" << endl;
			for (int j = 0; j < length_data_size; ++j) {           //DISPLAY MEASUREMENTS
				printf("%ld, ", length_data[j]);
			}
			counter++;
			printf("\n");
			cout << "-----------------------------------------------------------------------" << endl;
		}
		cout << "Licznik: " << counter << endl;
	}

	//Wybór typu pomiaru
	int choice()
	{
		int x;
		cout << "Wybierz typ pracy: \n1. Pomiar pojedynczego kata\n2. Pomiar danego zakresu katowego\n3. Pomiar ciągły w całym zakresie\n";
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
			cout << "Niepoprawna wartość, ponownie wpisz: \n" << "Kat: ";
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

	void Measurment(int ret, urg_t urg)
	{
		int num = choice();
		if (num == 1)
			direct_angle(ret, urg);
		else if (num == 2)
			angular_range(ret, urg);
		else if (num == 3)
			continuous_measurment(ret, urg);
	}

	CLidar(int *ret, urg_t *urg) {
		// "COM3" is, in this case, the device name detected for the sensor
		const char connect_device[] = "COM3";
		const long connect_baudrate = 115200;

		// Connects to the sensor
		*ret = urg_open(urg, URG_SERIAL, connect_device, connect_baudrate);
	}

	/*
	~CLidar() {
		// Disconnects from the sensor
		urg_close(&urg);
	}
	*/
};
//682 pomiary, max kat: 239,77 , jeden pomiar to 0,3516 stopnia;

int main(void)
{
	urg_t urg;
	int ret;
	int wait;

	CLidar obj(&ret, &urg);
	obj.Measurment(ret, urg);

	cin >> wait;    //DH

	// Disconnects from the sensor
	urg_close(&urg);

	return 0;
}