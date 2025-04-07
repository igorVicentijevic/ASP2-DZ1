#include <iostream>
#include <cmath>
using namespace std;

// i = 1 ; Ternarno i interpolaciono pretrazivanje
int IzracunajElementLoznicevogTrougla(int r, int k);
void IspisiNiz(int *a,int n);
int InterpolacionaPretraga(int red, int key, int & br);

int * GenerisiKljuceveZaTestiranje(int red,int brKljuceva)
{
    int * a = new int[brKljuceva];


    for (int i = 0; i < brKljuceva; ++i) {
        int index = rand() % red;
        a[i] = IzracunajElementLoznicevogTrougla(red,index);
    }
    return a;

}

int TernarnaPretraga(int red, int key, int & br);


int Analiza(int red, double & prosekTernarna, double & prosekInterpolaciona,int brKljuceva = 50)
{
    int * kljucevi = GenerisiKljuceveZaTestiranje(red,brKljuceva);

    cout << "===================Ternarna pretraga===================" << endl;

    int brTernarna = 0;
    int brUspesnihKljuceva = 0;
    for (int i = 0; i < brKljuceva; ++i) {
        int t = 0;

        if (TernarnaPretraga(red,kljucevi[i],t) >= 0)
        {
            brTernarna += t;
            brUspesnihKljuceva ++ ;
        }

    }

    prosekTernarna = brTernarna/(brUspesnihKljuceva+0.0);

    cout<<endl;

    cout<<"=========================================================================="<<endl;
    cout << "===================Interpolaciona pretraga===================" << endl;


    int brInter = 0;
    brUspesnihKljuceva = 0;

    for (int i = 0; i < brKljuceva; ++i) {
        int t = 0;
        if(InterpolacionaPretraga(red,kljucevi[i],t) >= 0 )
        {
            brInter += t;
            brUspesnihKljuceva ++;
        }
    }

    cout<<endl;

    prosekInterpolaciona = brInter/(brUspesnihKljuceva+0.0);


}

int TernarnaPretraga(int red, int key, int & br)
{
    int low = 0;
    int high =(red+1)/2.0;

    br = 0;

    cout << "           ==> Trazenje kljuca: "<< key <<endl;
    while(low <= high)
    {
        br++;

        int mid1 = (high + 2*low) /3;
        int mid2 = (2*high + low)/3;

        cout<<"~~~~~~~" << br <<". korak simulacije" << "~~~~~~~"<< endl;
        cout << "Low: "<< low<< endl;
        cout << "High: "<< high << endl;
        cout << endl;
        cout << "Mid1: "<< mid1 << endl;
        cout << "Mid2: "<< mid2<<endl;


        int elem1 = IzracunajElementLoznicevogTrougla(red,mid1);
        int elem2 = IzracunajElementLoznicevogTrougla(red,mid2);

        if(key > elem1)
        {
            if(key > elem2)
            {
                low = mid2+1;
            }
            else if(key < elem2)
            {
                low = mid1 + 1;
            }
            else
            {
                cout<< "Nadjen element sa kljucem "<< key <<" na poziciji "<< mid2 << endl;

                return mid2;
            }
        }
        else if (key < elem1)
        {
            high = mid1 - 1;
        }
        else
        {
            cout<< "Nadjen element sa kljucem "<< key <<" na poziciji "<< mid1 << endl;

            return mid1;
        }
    }

    return -1;
}

int InterpolacionaPretraga(int red, int key, int & br)
{
    int low = 0;
    int high = (red+1)/2;

    int elemLow;
    int elemHigh;

    br = 0;

    cout << "           ==> Trazenje kljuca: "<< key <<endl;

    while(low <= high)
    {
        br++;


        elemLow = IzracunajElementLoznicevogTrougla(red,low);
        elemHigh = IzracunajElementLoznicevogTrougla(red, high);

        if(elemHigh - elemLow ==0 ) return -1;
        int mid =  low + (high - low)*(key - elemLow)/(elemHigh - elemLow) ;



        int elemMid = IzracunajElementLoznicevogTrougla(red,mid);

        if(elemMid < elemLow || elemMid > elemHigh) return -1;

        cout<<"~~~~~~~" << br <<". korak simulacije" << "~~~~~~~"<< endl;
        cout << "Low: "<< low<< endl;
        cout << "High: "<< high << endl;
        cout << endl;
        cout << "Mid: "<< mid << endl;



        if(key > elemMid)
        {
            low = mid + 1;
        }
        else if (key < elemMid)
        {
            high = mid - 1;
        }
        else
        {
            cout<< "Nadjen element sa kljucem "<< key <<" na poziciji "<< mid << endl;
            return mid;
        }
    }

    return -1;
}

void IspisiMeni()
{
    cout << "========================="<< endl;
    cout << "Izaberite neku od opcija:"<< endl;
    cout<< "1. Unos rednog broja reda Lozanicevog trougla"
           "za pretrazivanje i generisanje sekvence kljuceva "
           "za pretrazivanje"<< endl;
    cout << "2. Pokretanje i ispis koraka simulacija, tj. pretrage" << endl;
    cout << "3. Ispis rezultata i poredjenje performanski na standarnom izlazu" << endl;
    cout << "4. Prekid programa" << endl;
    cout <<"==========================="<< endl;
}

//int binomialCoefficients(int n, int k) {
//    if(k > n)
//        return 0;
//    if (k == 0 || k == n )
//        return 1;
//    return binomialCoefficients(n - 1, k - 1) + binomialCoefficients(n - 1, k);
//}

int binomialCoefficients(int n, int k) {
    long long rez = 1;

    //if (k <= 0) return 0;

    for (int i = 0; i < k; ++i) {
        rez *= n--;
    }

    while(k > 1)
    {
        rez /= k--;
    }

    return rez;
}




int IzracunajElementLoznicevogTrougla(int r, int k)
{
    int element  = (binomialCoefficients(r,k) + binomialCoefficients(r%2, k%2) *
                                                             binomialCoefficients(r/2, k/2))/2;
    return element;

}


int * GenerisiElementeReda(int r, int & n)
{
    n = r+1;
    int * a = new int[n];

    for (int i = 0; i < n; ++i) {
        a[i] = IzracunajElementLoznicevogTrougla(r,i);
    }
    return a;

}

void IspisiNiz(int *a,int n)
{
    for (int i = 0; i < n; ++i) {
        cout<<a[i]<<" ";
    }
    cout << endl;
}

void IspisRezultataIPoredjenjePerformansi(double prosekTernarna,double prosekInterpolaciona)
{
    cout << "============================" << endl;
    cout << "Prosecan broj pristupa ternarna pretraga: "<<prosekTernarna<<endl;
    cout << "Prosecan broj pristupa interpolaciona pretraga: "<< prosekInterpolaciona << endl;

    if(prosekTernarna < prosekInterpolaciona)
    {
        cout << "   ===> Ternarna pretraga je brza!" << endl;
    }
    else
    {
        cout << "   ===> Interpolaciona pretraga je brza!" << endl;

    }

}

int red;
int * kljuceviZaPretrazivanje;
double prosekTernarna;
double prosekInterpolaciona;

void Opcija_1()
{

   cout << "=========================="<< endl;
   cout << "Unesite redni broj reda:" << endl;
   cin >> red;

   delete kljuceviZaPretrazivanje;

   kljuceviZaPretrazivanje = GenerisiKljuceveZaTestiranje(red,100);

   cout<< "Generisani kljucevi su:"<<endl;
    IspisiNiz(kljuceviZaPretrazivanje,100);



}

void Opcija_2()
{
    Analiza(red,prosekTernarna,prosekInterpolaciona,100);
}

void Opcija_3()
{
    IspisRezultataIPoredjenjePerformansi(prosekTernarna,prosekInterpolaciona);
}



void Meni()
{
    int opcija;


    IspisiMeni();

    cin >> opcija;

    switch (opcija) {
        {
            case 1:
                Opcija_1();
            break;
            case 2:
                Opcija_2();
            break;
            case 3:
                Opcija_3();
            break;
            case 4: cout << "Izlaz iz programa..." << endl;
                break;

            default:
                cout << "Uneli ste nedozvoljenu vrednost!" << endl;

        }

    }

    if(opcija != 4) Meni();
}
void InicijalizujRNG()
{
    cout << "Unesite seed: "<<endl;
    int seed;
    cin >> seed;
    srand(seed);
}
int main() {

    InicijalizujRNG();

    Meni();




    return 0;
}

