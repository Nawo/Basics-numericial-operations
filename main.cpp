#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main()
{

	string wynik;

	//========================[ODCZYTYWANIE X_SIGNAL}========================

	vector <double> x_signal;
	fstream x_signal_file;
	x_signal_file.open("x_signal.txt", std::ios::in | std::ios::out);

	while (getline(x_signal_file, wynik))
	{

		x_signal.push_back(atof(wynik.c_str()));

	}

	x_signal_file.close();

	//========================[ODCZYTYWANIE Y_SIGNAL}========================

	vector <double> y_signal;
	fstream y_signal_file;
	y_signal_file.open("y_signal.txt", std::ios::in | std::ios::out);

	while (getline(y_signal_file, wynik))
	{

		y_signal.push_back(atof(wynik.c_str()));

	}

	y_signal_file.close();

	//========================[ODCZYTYWANIE Y_NOISED_SIGNAL}========================

	vector <double> y_noiced;
	fstream y_noiced_file;
	y_noiced_file.open("y_noised_signal.txt", std::ios::in | std::ios::out);

	while (getline(y_noiced_file, wynik))
	{

		y_noiced.push_back(atof(wynik.c_str()));

	}

	y_noiced_file.close();

	//========================[OBLICZANIE BLEDU WZGLEDNEGO/BEZWZGLEDNEGO/SREDNIEGO}========================

	vector <double> blad_wzgledny;
	vector <double> blad_bezwzgledny;
	double suma_bezwzglednego = 0;
	double suma_wzglednego = 0;
	double srednia_bezwzglednego = 0;
	double srednia_wzglednego = 0;

	for (int i = 0; i < x_signal.size(); i++)
	{

		blad_bezwzgledny.push_back(y_noiced[i] - y_signal[i]);

		blad_wzgledny.push_back((y_noiced[i] - y_signal[i]) / y_noiced[i]);


		suma_bezwzglednego = suma_bezwzglednego + y_noiced[i] - y_signal[i];

		suma_wzglednego = suma_wzglednego + (y_noiced[i] - y_signal[i]) / y_noiced[i];


	}

	srednia_bezwzglednego = suma_bezwzglednego / y_noiced.size();

	cout << "srednia bezwzgledna: " << srednia_bezwzglednego << endl;

	srednia_wzglednego = suma_wzglednego / y_noiced.size();

	cout << "srednia wzgledna: " << srednia_wzglednego << endl;


	//========================[WARTOSCI SKUTECZNE SYGNALOW ODPOWIEDZI}========================

	double suma_probek_kwadratowych = 0;
	double wartosc_skuteczna;

	for (int i = 0; i < y_signal.size(); i++)
	{
		suma_probek_kwadratowych = suma_probek_kwadratowych + (y_signal[i] * y_signal[i]);
	}

	wartosc_skuteczna = sqrt(suma_probek_kwadratowych / y_signal.size());

	cout << "wartosc skuteczna: " << wartosc_skuteczna << endl;

	//========================[WARIANCJA, ODCHYLENIE, MEDIANA}========================

	double wariancja_wzgledny;
	double wariancja_bezwzgledny;

	double wariancja_czastkowa_wzgledny = 0;
	double wariancja_czastkowa_bezwzgledny = 0;

	for (int i = 0; i < x_signal.size(); i++)
	{
		wariancja_czastkowa_wzgledny += (blad_wzgledny[i] - srednia_wzglednego) * (blad_wzgledny[i] - srednia_wzglednego);
		wariancja_czastkowa_bezwzgledny += (blad_bezwzgledny[i] - srednia_bezwzglednego) * (blad_bezwzgledny[i] - srednia_bezwzglednego);
	}

	wariancja_wzgledny = wariancja_czastkowa_wzgledny / x_signal.size();
	cout << "wariancja wzgledna: " << wariancja_wzgledny << endl;
	wariancja_bezwzgledny = wariancja_czastkowa_bezwzgledny / x_signal.size();
	cout << "wariancja bezwzgledna: " << wariancja_bezwzgledny << endl;


	double odchylenie_wzgledny = sqrt(wariancja_wzgledny);
	cout << "odchylenie wzgledne: " << odchylenie_wzgledny << endl;
	double odchylenie_bezwzgledny = sqrt(wariancja_bezwzgledny);
	cout << "odchylenie bezwzgledne: " << odchylenie_bezwzgledny << endl;
	


	for (int i = 0; i < blad_wzgledny.size(); i++)
	{
		for (int j = 0; j < blad_wzgledny.size() - 1; j++)
		{
			if (blad_wzgledny[j] > blad_wzgledny[j + 1])
				swap(blad_wzgledny[j], blad_wzgledny[j + 1]);

		}
	}

	for (int i = 0; i < blad_bezwzgledny.size(); i++)
	{
		for (int j = 0; j < blad_bezwzgledny.size() - 1; j++)
		{
			if (blad_bezwzgledny[j] > blad_bezwzgledny[j + 1])
				swap(blad_bezwzgledny[j], blad_bezwzgledny[j + 1]);

		}
	}

	double mediana_bezwzgledny = 0;
	double mediana_wzgledny = 0;

	if (blad_bezwzgledny.size() % 2 == 0)
	{
		int a = ceil(blad_bezwzgledny.size() / 2);
		int b = floor(blad_bezwzgledny.size() / 2);
		mediana_bezwzgledny = (blad_bezwzgledny[a] + blad_bezwzgledny[b]) / 2;
	}

	if (blad_bezwzgledny.size() % 2 != 0)
		mediana_bezwzgledny = blad_bezwzgledny[blad_bezwzgledny.size() / 2];

	cout << "mediana bledu bezwzglednego: " << mediana_bezwzgledny << endl;

	if (blad_wzgledny.size() % 2 == 0)
	{
		int a = ceil(blad_wzgledny.size() / 2);
		int b = floor(blad_wzgledny.size() / 2);
		mediana_wzgledny = (blad_wzgledny[a] + blad_wzgledny[b]) / 2;
	}

	if (blad_wzgledny.size() % 2 != 0)
	mediana_wzgledny = blad_wzgledny[blad_wzgledny.size() / 2];

	cout << "mediana bledu wzglednego: " << mediana_wzgledny << endl;

	return 0;


}