#include<iostream>
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include<iomanip>
#include<fstream>
#include<stdlib.h>
using namespace std;

#define N 4
#define W 10
#define Q 13

class Wektor
{
	public:
		double* wektor;
		int n;
		Wektor(int n)
        {
            this->n = n;
            this->wektor = new double[n];
            for(int i=0; i<n; i++)
            {
                this->wektor[i] = 0;
            }
        }
		Wektor(double *wektor,int n)
		{
			this->n = n;
			this->wektor = new double[n];
			for(int i=0;i<n;i++)
			{
				this->wektor[i] = wektor[i];
			}
		}
		void ZamienWiersze(int i1, int i2)
		{
			double pom = this->wektor[i1];
			this->wektor[i1] = this->wektor[i2];
			this->wektor[i2] = pom;
		}
		void WypiszWektor()
		{
			for (int i = 0; i < n; i++)
			{
				cout << setw(W) << this->wektor[i];
			}
			cout << endl << endl;
		}
		
};

class Macierz
{
	public:
		double** macierz;
		int n;
		Macierz(double** m,int n)
		{
			this->n = n;
            this->macierz = new double*[n];
            for(int i=0; i<n; i++)
            {
                macierz[i] = new double[n];
                for (int j = 0; j < n; j++)
                {
                    this->macierz[i][j] = m[i][j];
                }
            }
		}
		
		void WypiszMacierz()
        {
            for (int i=0; i<n; i++)
            {
                for(int j=0; j<n; j++)
                {
                   cout << setw(Q) << this->macierz[i][j] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
        
		int IndexMaxColumn(int wiersz ,int kolumna)
		{
			int index = wiersz;
			double max = fabs(this->macierz[wiersz][kolumna]);

			for (int i = wiersz+1; i < n; i++)
			{
				if(fabs(this->macierz[i][kolumna]) > max)
				{
					
					index = i;
					max = fabs(this->macierz[i][kolumna]);
				}
			}
			
			return index;
		}
		
		void EliminacjaGaussa(int StartWiersz, int StartKolumna)
		{
			double pom;
			for (int Wiersz = StartWiersz + 1; Wiersz < n; Wiersz++)
			{
				pom = this->macierz[Wiersz][StartKolumna]/ this->macierz[StartWiersz][StartKolumna];
				
				//this->macierz[Wiersz][StartKolumna] = pom;
				for (int Kolumna = StartKolumna + 1; Kolumna < n; Kolumna++)
				{
					//pom = this->macierz[Wiersz][Kolumna] - this->macierz[Wiersz][StartKolumna] * this->macierz[StartWiersz][Kolumna];
					this->macierz[Wiersz][Kolumna] -= pom * this->macierz[StartWiersz][Kolumna];
					//this->macierz[Wiersz][Kolumna] = pom;
				}
				//this->macierz[Wiersz][StartKolumna] = pom;
			}
			
		}
		
		void ZamienWiersze(int wiersz1, int wiersz2)
		{
			double temp_tab[n];
            for(int kolumna=0; kolumna<n; kolumna++)
            {
                temp_tab[kolumna] = this->macierz[wiersz1][kolumna];
                this->macierz[wiersz1][kolumna] = this->macierz[wiersz2][kolumna];
                this->macierz[wiersz2][kolumna] = temp_tab[kolumna];
            }
		}	
		
		void DekompozycjaA(Wektor vector)
		{
			for (int i = 0; i < n; i++)
			{
				if (this->macierz[i][i] == 0)
				{
					int maxIndex = IndexMaxColumn(i,i);
					ZamienWiersze(i, maxIndex);
					vector.ZamienWiersze(i, maxIndex);

				}
				
				EliminacjaGaussa(i,i);
						
			}
		}

        Wektor DekompozycjaB(Wektor vector)
		{
			double y[vector.n];
			
			for (int wiersz = 0; wiersz < n; wiersz++)
			{
				double sum = 0.0;
				for (int kolumna = 0; kolumna <= wiersz - 1; kolumna++)
				{

					sum += this->macierz[wiersz][kolumna] * y[kolumna];

				}

				y[wiersz] = (vector.wektor[wiersz] - sum); 
			}
			
	
			
			Wektor vectorY(y,vector.n);
			return vectorY;
		}

		Wektor RozwiazanieX(Wektor vector)
		{
			double x[vector.n];
			for (int i = n-1; i >= 0; i--)
			{
				double sum = 0.0;
				for (int j = n-1; j >i; j--)
				{
					
					sum += this->macierz[i][j] * x[j];
				}
				
				x[i] = (vector.wektor[i] - sum) / this->macierz[i][i];
			}
			Wektor vectorX(x,vector.n);
			return vectorX;
		
		}

};




int main()
{
    double **a = new double*[N];
    for(int i=0; i<N; i++)
    {
        a[i] = new double[N];
    }

            a[0][0] = 1;    a[0][1] = 20;    a[0][2] = -30;    a[0][3] = -4;
            a[1][0] = 4;    a[1][1] = 20;    a[1][2] = -6;    a[1][3] = 50;
            a[2][0] = 9;    a[2][1] = -18;    a[2][2] = 12;    a[2][3] = -11;
            a[3][0] = 16;    a[3][1] = -15;    a[3][2] = 14;    a[3][3] = 130;

    double *b = new double[N];

            b[0] = 0;  b[1] = 114;  b[2] = -5;  b[3] = 177;

    Macierz m = Macierz(a,N);
    cout<<"Macierz A"<<endl;
	m.WypiszMacierz();
	
	Wektor vector(b,4);
	cout<<"Wektor B"<<endl;
	vector.WypiszWektor();
	
	m.DekompozycjaA(vector);
	cout<<"Macierz A Po dekompozycji"<<endl;
	m.WypiszMacierz();
	
	Wektor y = m.DekompozycjaB(vector);
	
	Wektor x = m.RozwiazanieX(y);

	cout << "Wektor B po dekompozycji" << endl;
 	y.WypiszWektor();

	cout << " Wektor rozwiazan x" << endl;
 	x.WypiszWektor();
	return 0;
}

