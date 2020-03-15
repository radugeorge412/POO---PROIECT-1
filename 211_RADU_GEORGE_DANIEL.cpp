#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

class actor
{
private:

    char *nume_actor;
    int varsta;

public:

    actor(char*,int);
    ~actor();
    actor(actor&);
    int get_Varsta()
    {
        return varsta;
    };
    char *get_Nume_actor()
    {
        return nume_actor;
    };
    friend istream& operator>>(istream &in, actor& z);
    friend ostream& operator<<(ostream &out, actor& z);
    void citire_actor(istream &in);
    void afisare_actor(ostream &out);
    void set_nume_actor(char*);
    void set_varsta(int);
    actor &operator=(const actor &z);
    friend class teatru;

};


//constructor initializare
actor::actor (char *num =NULL,int varsta = 0 )
{
    if (num!=NULL)
    {
        this->nume_actor=new char[strlen(num)+1];
        strcpy(nume_actor,num);
    }
    else
        this->nume_actor=num;
    this->varsta=varsta;
}

//destructor
actor::~actor()
{
    delete []nume_actor;
    varsta=0;
}

//constructor de copiere
actor::actor(actor &A)
{
    this->nume_actor=new char[strlen(A.nume_actor)+1];
    strcpy(this->nume_actor,A.nume_actor);
    this->varsta=A.varsta;
}


//SET
void actor::set_nume_actor(char *z)
{
    delete []nume_actor;
    nume_actor= new char[strlen(z)+1];
    strcpy(nume_actor,z);

}

void actor::set_varsta(int x)
{
    this->varsta = x;
}



//SUPRAINCARCARE PE OPERATORI SI CITIRE/AFISARE

void actor::citire_actor(istream &in)
{
    cout<<"Numele actorului: ";
    char num[256];
    cin.get();
    in.getline(num,256);
    nume_actor=new char[strlen(num)+1];
    strcpy(nume_actor,num);
    cout<<endl;
    cout<<"Varsta actorului: ";
    in>>varsta;
    cout<<endl;

}

istream& operator>>(istream& in, actor& z)
{
    z.citire_actor(in);
    return in;
}

void actor::afisare_actor(ostream& out)
{
    out<<"Numele este: "<<nume_actor<<" si varsta sa este: "<<varsta;

}

ostream& operator<<(ostream& out,actor& z)
{
    z.afisare_actor(out);
    return out;
}

//supraincarcare pe =
actor &actor::operator=(const actor &z)
{
    if(this==&z)
        return (*this);
    else
    {
        if(nume_actor)
        {
            delete []nume_actor;
            nume_actor=new char[strlen(z.nume_actor)+1];
            strcpy(nume_actor,z.nume_actor);
        }
        else
            nume_actor=z.nume_actor;
        varsta=z.varsta;
    }
    return (*this);
}

//----------------------------------------------------

class teatru
{
private:
    char *denumire_piesa;
    int numar_actori;
    actor *actori;
    float rating;

public:

    teatru(char*, int, actor*, float);
    ~teatru();
    teatru(teatru &);

    char* get_denumire_piesa()
    {
        return denumire_piesa;
    };
    int get_numar_actori()
    {
        return numar_actori;
    };
    float get_rating()
    {
        return rating;
    };
    //actor get_actori()
    friend class actor;
    friend istream& operator>>(istream &in, teatru& z);
    friend ostream& operator<<(ostream &out, teatru& z);
    void citire(istream &in);
    void afisare(ostream &out);
    void set_piesa(char*);
    void set_numar_actori(int);
    void set_rating(float);
    void set_actori(actor*);
    teatru &operator=(const teatru &z);
    friend bool operator<(teatru &t1, teatru &t2);
    friend bool operator==(teatru &t1, teatru &t2);


};


//constructor de initializare
teatru::teatru(char *den_piesa = NULL, int numar_actori = 0, actor *actori=0, float rating=0)
{
    if(den_piesa!=NULL)
    {
        this->denumire_piesa=new char[strlen(den_piesa)+1];
        strcpy(denumire_piesa,den_piesa);
    }
    else
        denumire_piesa=den_piesa;
    this->numar_actori=numar_actori;
    this->rating=rating;
    this->actori=0;

}

//destructor
teatru::~teatru()
{
    delete[] denumire_piesa;
    denumire_piesa=new char('\0');
    numar_actori=0;
    delete[] actori;
    rating=0;
}

//constructor de copiere
teatru::teatru(teatru &z)
{
    denumire_piesa=new char[strlen(z.denumire_piesa)+1];
    strcpy(denumire_piesa,z.denumire_piesa);
    numar_actori=z.numar_actori;
    rating=z.rating;
    actori=new actor[numar_actori];
    int i;
    for(i=0; i<numar_actori; i++)
    {
        actori[i]=z.actori[i];
    }
}

//SET
void teatru::set_piesa(char *x)
{
    delete []denumire_piesa;
    denumire_piesa=new char[strlen(x)+1];
    strcpy(denumire_piesa,x);
}

void teatru::set_numar_actori(int x)
{
    numar_actori=x;
}

void teatru::set_rating(float x)
{
    rating=x;
}


//OPERATORI & CITIRE/AFISARE
void teatru::citire(istream &in)
{
    int i;
    cout<<"Numele piesei: ";
    cin.get();
    char num[256];
    in.getline(num,256);
    denumire_piesa=new char[strlen(num)+1];
    strcpy(denumire_piesa,num);

    cout<<endl<<"Numarul actorilor: ";
    in>>numar_actori;

    actori= new actor[numar_actori];
    for (i=0; i<numar_actori; i++)
    {
        cout<<endl<<"Informatii despre actorul "<<i+1<<" :"<<endl;
        in>>actori[i];
    }

    cout<<endl<<"Ratingul piesei: ";
    in>>rating;
    cout<<endl;


}

istream& operator>>(istream &in, teatru &z)
{
    z.citire(in);
    return in;
}

void teatru::afisare(ostream& out)
{
    int i;
    out<<"Piesa se numeste "<<denumire_piesa<<endl;
    out<<"Numarul de actori din piesa este: "<<numar_actori<<endl;
    out<<"Detaliile despre actori sunt: "<<endl;
    for(i=0; i<numar_actori; i++)
    {
        out<<actori[i]<<endl;
    }
    out<<"Ratingul este: "<<rating<<endl;

}

ostream& operator<<(ostream &out, teatru &z)
{
    z.afisare(out);
    return out;
}

teatru &teatru::operator=(const teatru &z)
{
    if(this==&z)
        return (*this);
    else
    {
        delete[]denumire_piesa;
        denumire_piesa=new char[strlen(z.denumire_piesa)+1];
        numar_actori=z.numar_actori;
        rating=z.rating;
        delete []actori;
        actori=new actor[numar_actori];
        int i;
        for(i=0; i<numar_actori; i++)
        {
            actori[i]=z.actori[i];
        }

    }
    return (*this);

}

bool operator <(teatru &t1, teatru &t2)
{
    return (t1.rating<t2.rating);
}

bool operator==(teatru &t1,teatru &t2)
{
    return (t1.rating==t2.rating);
}

//-----------------------------------------------------

void menu_output()
{
    cout<<endl<<"RADU GEORGE-DANIEL, GRUPA 211, PROIECT - 19"<<endl;
    cout<<"MENIU"<<endl;
    cout<<"Optiunea 0.EXIT"<<endl;
    cout<<"Optiunea 1.CITIREA DATELOR"<<endl;
    cout<<"Optiunea 2.AFISAREA DATELOR"<<endl;
    cout<<"Optiunea 3.MODIFICAREA DATELOR"<<endl;
    cout<<"Optiunea 4.COMPARAREA A DOUA OBIECTE"<<endl;
}

//-----------------------------------------------------

void menu()
{
    int option=0,ok=0,n,i;
    teatru *v;
    menu_output();


    do
    {
        cout<<"CITITI OPTIUNEA:"<<endl;
        cin>>option;
        if(option==1)
        {
            cout<<"DA-TI NUMARUL DE OBIECTE"<<endl;
            cin>>n;
            v=new teatru[n];
            for(i=0; i<n; i++)
            {
                cout<<"TEATRUL "<<i<<" :"<<endl;
                cin>>v[i];

            }
            ok=1;
            cout<<endl;

        }
        if(option==2)
        {
            if(ok==0)
            {
                cout<<"NU SE POATE, DATELE NU AU FOST CITITE"<<endl;
                option=0;
            }
            else
            {
                for(i=0; i<n; i++)

                {
                    cout<<endl<<"TEATRUL "<<i<<" ARE URMATOARELE INFORMATII:"<<endl;
                    cout<<v[i];

                }
            }
            cout<<endl;
        }

        if(option==3)
        {
            if(ok==0)
            {
                cout<<"NU SE POATE, DATELE NU AU FOST CITITE"<<endl;
                option=0;
            }
            else
            {
                int j;
                cout<<"INFORMATIILE CARUI TEATRU DORITI SA FIE MODIFICATE?"<<endl;
                cin>>j;
                cout<<"INTRODUCE-TI NOILE INFORMATII:"<<endl;
                teatru z;
                cin>>z;
                v[j]=z;
                cout<<"TEATRUL "<<j<<" ARE ACUM DATELE:"<<endl;
                cout<<v[j];
            }

        }

        if(option==4)
        {
            if(ok==0)
            {
                cout<<"NU SE POATE, DATELE NU AU FOST CITITE"<<endl;
                option=0;
            }
            else
            {
                int j;
                cout<<"CITITI INDICII CELOR DOUA TEATRE:"<<endl;
                cout<<"PRIMUL INDICE: ";
                cin>>i;
                cout<<endl<<"AL DOILEA INDICE:";
                cin>>j;
                if(v[i]==v[j])
                    cout<<"CELE DOUA TEATRE SUNT LA FEL DE BINE COTATE"<<endl;
                else
                {
                    if(v[i]<v[j])
                        cout<<"TEATRUL "<<j<<" ESTE MAI BINE COTAT"<<endl;
                    else
                        cout<<"TEATRUL "<<i<<" ESTE MAI BINE COTAT"<<endl;
                }
            }

        }

    }
    while(option!=0);

}

//------------------------------------------------------

int main()
{
    menu();
    return 0;
}
