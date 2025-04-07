#include <iostream>
#include <string>
using namespace std;

typedef struct node{
    int broj;
    int nivo;

    int balans;
    node * levi;
    node * desni;
} cvor;

typedef struct{
    string ime;
    cvor * root;
} skup;

skup * skupovi[100];
int brojSkupova = 0;

string trenutniSkup;

skup * PronadjiSkup(const string ime)
{
    for (int i = 0; i < brojSkupova; ++i) {
        if(skupovi[i] -> ime == ime)
        {
            return skupovi[i];
        }
    }

    return nullptr;
}

skup * FormirajPraznoStablo(string ime, bool ubaciUNiz = false)
{
    skup *a = new skup;
    a -> root = nullptr;
    a -> ime = ime;
    if(ubaciUNiz)
    {
        skupovi[brojSkupova++] = a;
    }
    return a;
}

cvor * NapraviNoviCvor(int vrednost)
{
    cvor * x = new cvor;
    x -> broj = vrednost;
    x -> levi = nullptr;
    x -> desni = nullptr;
    x -> balans = 0;
    return x;
}

skup * DesnaRotacija(skup *a,cvor * x)
{
    bool isRoot = a->root == x;

    cvor * y = x -> levi;
    cvor * temp = y -> desni;
    y -> desni = x;
    x->levi = temp;

    if(isRoot) a -> root = y;
    return a;
}

skup * LevaRotacija(skup *a,cvor * x)
{
    bool isRoot = a->root == x;

    cvor * y = x -> desni;
    cvor * temp = y -> levi;
    y -> levi = x;
    x->desni = temp;

    if(isRoot) a -> root = y;
    return a;
}


skup * UbaciNoviElementUSkup(skup * a,int elem) {
    cvor * fp, *fx, *q;
    fp = fx = nullptr;
    cvor * p = a->root;
    cvor * x = p;

    if(!p)
    {
        q = NapraviNoviCvor(elem);
        a -> root = q;
        return a;
    }
    while(p)
    {
        if(elem == p->broj)
            return a;

        if(elem < p->broj)
            q = p->levi;
        else
            q = p->desni;

        if(q)
            if(q -> balans != 0)
            {
                fx = p;
                x = q;
            }

        fp = p;
        p = q;
    }

    q = NapraviNoviCvor(elem);
    if(elem < fp->broj)
        fp -> levi = q;
    else
        fp -> desni = q;

    if(elem < x->broj)
        p = x->levi;
    else
        p = x->desni;

    cvor * y = p;

    while(p != q)
    {
        if(elem < p -> broj)
        {
            p -> balans = 1;
            p = p -> levi;
        }
        else
        {
            p -> balans = -1;
            p = p->desni;
        }
    }

    int imbal;
    if(elem < x->broj)
        imbal = 1;
    else
        imbal = -1;

    if(x->balans ==0)
    {
        x -> balans = imbal;
        return a;
    }

    if(x->balans != imbal)
    {
        x -> balans = 0;
        return a;
    }
    if(y->balans == imbal)
    {
        p = y;
        if(imbal == 1)
            a = DesnaRotacija(a,x);
        else
            a = LevaRotacija(a,x);

        x -> balans = y->balans = 0;
    }
    else
    {
        if(imbal == 1)
        {
            p = y -> desni;
            a = LevaRotacija(a,y);
            x -> levi = p;
            a = DesnaRotacija(a,x);
        }
        else
        {
            p = y -> levi;
            x -> desni = p;
            DesnaRotacija(a,y);
            LevaRotacija(a,x);
        }
        if(p->balans == 0)
            x->balans = y->balans =0;
        else
        {
            if(p->balans == imbal)
            {
                x -> balans = -imbal;
                y -> balans = 0;
            }
            else
            {
                x -> balans = 0;
                y -> balans = imbal;
            }
            p->balans = 0;
        }
    }

    if(!fx)
        a-> root = p;
    else
    {
        if( x == fx->desni)
            fx -> desni = p;
        else
            fx -> levi = p;

    }
    return a;

}

bool DaLiElementPripadaSkupu(skup *a, int elem)
{
    cvor *p = a->root;
    while (p) {
        if(p -> broj == elem)
        {
            return true;
        }

        if(elem < p -> broj)
        {
            p = p -> levi;
        }
        else
        {
            p = p-> desni;
        }
    }
    return false;

}

void BrisanjeSkupa(string ime,skup * skupZaBrisanje = nullptr)
{
    cvor * stek[100] = {};
    int vrh = 0;

    int indeks;

    if(skupZaBrisanje == nullptr) {
        for (int i = 0; i < brojSkupova; ++i) {
            if (skupovi[i]->ime == ime) {
                indeks = i;
                break;
            }
        }
    }
    skup *a = skupZaBrisanje ? skupZaBrisanje :skupovi[indeks];

    cvor * prev;
    stek[vrh++] = a -> root;
    while(vrh != 0)
    {
        cvor * next = stek[--vrh];
        while(next)
        {
            prev = next;
            if(next -> desni)
            {
                stek[vrh++] = next -> desni;
            }
            next = next -> levi;
            delete prev;

        }
    }

    if(skupZaBrisanje == nullptr) {
        brojSkupova--;
        for (int i = indeks; i < brojSkupova; i++) {
            skupovi[i] = skupovi[i + 1];
        }
    }

    a -> root = nullptr;

}

void IspisiStablo(skup * a)
{

    cvor * stek[100] = {};
    int vrh = 0;

    cvor * stablo = a -> root;

    if(!stablo) return;

    bool jeLevi = true;

    stablo -> nivo = 0;

    stek[vrh++] = stablo;

    while(vrh > 0)
    {
        cvor* next = stek[--vrh];

        while(next) {


            for (int i = 0; i < next -> nivo; ++i) {
                cout << ( i == next -> nivo - 1 ? " |" : "   ") ;// mozda treba endl
            }

            cout <<(next != a -> root ? jeLevi ? "l_":"d_" :" ")<< next -> broj <<endl;
            if (next->desni)
            {
                next -> desni -> nivo = next -> nivo +1;
                stek[vrh++] = next -> desni;
            }

            jeLevi = true;
            int t = next -> nivo;
            next = next->levi;
            if(next ) next -> nivo = t+1;

        }

        jeLevi = false;

    }

}

skup * RazlikaSkupova(skup *a, skup *b)
{
    cvor * stek[100] = {};
    int vrh = 0;

    cvor * stabloA = a -> root;

    skup * c = FormirajPraznoStablo("");

    stek[vrh++] = stabloA;

    while(vrh > 0)
    {
        cvor* next = stek[--vrh];



        while(next) {

            if(!DaLiElementPripadaSkupu(b,next -> broj))
            {
                c = UbaciNoviElementUSkup(c,next -> broj);
            }

            if (next->desni)
            {
                stek[vrh++] = next -> desni;
            }
            next = next->levi;

        }

    }

    return c;
}

void IspisiMeni()
{
    cout << "================================" << endl;
    cout << "1. Formiranje praznog skupa" << endl;
    cout << "2. Umetanje novog elementa u skup" << endl;
    cout << "3. Provera pripadnosti elementa skupu"<<endl;
    cout << "4. Ispis stabla" << endl;
    cout << "5. Brisanje skupa iz memorije" << endl;
    cout << "6. Razlika dva skupa" << endl;
    cout << "7. Promena trenutnog skupa" << endl;
    cout << "8. Izlaz iz programa" << endl;
    cout << "================================" << endl;

}

void PromenaTrenutnogSkupa()
{
    cout << "~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout << "Ime skupa sa koji zelite da selektujete:"<< endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cin >> trenutniSkup;


}

void Opcija_1()
{
//    string ime;
//    cout << "Unesite ime skupa: "<< endl;
//    cin >> ime;

    skup *a = PronadjiSkup(trenutniSkup);
    if(a == nullptr) skupovi[brojSkupova++] = FormirajPraznoStablo(trenutniSkup);
    else BrisanjeSkupa(trenutniSkup);
}

void Opcija_2()
{
    skup * skup =PronadjiSkup(trenutniSkup);

    if(!skup)
    {
        cout<<"Morate prvo formirati skup pre ubacivanja elemenata!"<<endl;
        return;
    }

    int elem;
    cout << "Unesite vrednost elementa: "<< endl;
cin >> elem;



    UbaciNoviElementUSkup(PronadjiSkup(trenutniSkup),elem);
}

void Opcija_3()
{
    skup * skup =PronadjiSkup(trenutniSkup);

    if(!skup)
    {
        cout<<"Morate prvo formirati skup!"<<endl;
        return;
    }

    int elem;
    cout << "Unesite vrednost elementa za koji se proverava pripadnost skupa: "<< endl;
    cin >> elem;
    cout << (DaLiElementPripadaSkupu(skup,elem) ? "Element pripada skupu!": "Element ne pripada skupu!")
    << endl;
}

void Opcija_4()
{
    skup * skup =PronadjiSkup(trenutniSkup);

    if(!skup)
    {
        cout<<"Morate prvo formirati skup!"<<endl;
        return;
    }
    IspisiStablo(skup);
}

void Opcija_5()
{
    skup * skup =PronadjiSkup(trenutniSkup);

    if(!skup)
    {
        cout<<"Morate prvo formirati skup!"<<endl;
        return;
    }
    BrisanjeSkupa(trenutniSkup);

    PromenaTrenutnogSkupa();
}

void Opcija_6()
{
    string imeA;
    cout << "Unesite ime prvog skupa: "<< endl;
    cin >> imeA;

    skup * skupA =PronadjiSkup(imeA);

    if(!skupA)
    {
        cout<<"Morate prvo formirati skup!"<<endl;
        return;
    }

    string imeB;
    cout << "Unesite ime drugog skupa: "<< endl;
    cin >> imeB;

    skup * skupB =PronadjiSkup(imeB);

    if(!skupB)
    {
        cout<<"Morate prvo formirati skup!"<<endl;
        return;
    }

    skup * razlika = RazlikaSkupova(skupA, skupB);
    IspisiStablo(razlika);
    BrisanjeSkupa("",razlika);
}

bool krajPrograma = false;


void Meni()
{
    IspisiMeni();

    int opcija;
    cin >> opcija;



    switch (opcija) {

        case 1: Opcija_1(); break;
        case 2: Opcija_2(); break;
        case 3: Opcija_3(); break;
        case 4: Opcija_4(); break;
        case 5: Opcija_5(); break;
        case 6: Opcija_6(); break;
        case 7: PromenaTrenutnogSkupa(); break;
        case 8: krajPrograma = true;break;
        default: cout << "Unesli ste pogresan broj!" << endl; Meni(); break;

    }

    if(!krajPrograma) Meni();
}

int main() {
    cout << "~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout << "Ime skupa sa koji zelite da selektujete:"<< endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cin >> trenutniSkup;
    Meni();
    cout<<"Program prekinut!";
    return 0;
}
