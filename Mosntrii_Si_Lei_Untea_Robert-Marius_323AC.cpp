// Untea Robert-Marius
// 323AC

#include <iostream>
#include <conio.h>
#include <fstream>
#include <iomanip>
#include <chrono>

#define lin_db_1 800
#define nrFiguranti 132
#define nrOfNames 1000
#define cursDolar 4.9
#define priceBus 5680

using namespace std;

// generator de numere random de la 0 la parametru
template <typename rndNrRng>
rndNrRng randomNumberInRange(rndNrRng var)
{
    return rand() % var;
}

// citire fisier pentru generarea de nume pentru figuranti 
// 2 coloane a cate 1000 de nume, ne folosim de random number generator 
void readNameDb(string v1[nrOfNames][2])
{
    ifstream data_base_2_read;
    data_base_2_read.open("namegendatabase.csv");

    char delimeter1(';');           // delimitatori pentru fisierul csv
    char delimeter2('\n');
    cout<<">> Deschidere fisier dictionar pentru generarea numelor de figuranti..."<<endl;
    // am folosit exceptii la fiecare lucru cu fisiere (ifstream/ofstream) la verificarea deschiderii acestuia
    try
    {
        if(!data_base_2_read.is_open())
            throw '1';
        else
        {
            for(unsigned int i = 0; i < nrOfNames; i++)
            {
                getline(data_base_2_read, v1[i][0], delimeter1);
                getline(data_base_2_read, v1[i][1], delimeter2);
            }
            cout<<">> Deschis cu succes!"<<endl;
            cout<<endl;
        }
    }
    catch(char error)
    {
        if(error == '1')
        {
            cout<<">> Whops, a intervenit o eroare in citirea fisierului CSV."<<endl;
            cout<<">> Va rugam verificati integritatea fisierului si redeschideti aplicatia."<<endl;
        }
    }
}
// return random string din dictionar
class RandomString
{
    public:
    string mancare[3] =  {"Apt sa manance orice", "Vegetarian", "Flexitarian"};
    string rol[5] =      {"Vampir", "Varcolac", "Sirena", "Clarvazator", "Om"};
    // return random string din mancare
        string rndMancare(string v1[3])
        {
            return v1[randomNumberInRange(3)];
        }
    // return random string din machiaj
        string rndRol(string v1[5])
        {
            return v1[randomNumberInRange(5)];
        }
    // return random string din cele 2x 1000 nume petnru figuranti + concatenare
        string rndFigName(string v1[1000][2])
        {
            return v1[randomNumberInRange(1000)][0] + " " + v1[randomNumberInRange(1000)][1];
        }
};

// parametrii generali
class Database
{
    public:
        string c1[lin_db_1];
        string c2[lin_db_1];
        string figuranti[nrFiguranti];
        unsigned int nrCastInit;
        unsigned int nrActori;
        ~Database();
};
// destructor
Database::~Database(void){}

// clasa de citire din csv
class DatabaseReader
{
    public:
        // functie de citire pentru 2 coloane, folosit la csv-ul initial
        unsigned int nrCol2(string col_1[lin_db_1], string col_2[lin_db_1])
        {
            ifstream data_base_1_read;
            data_base_1_read.open("wednesdayCast.csv");

            char delimeter1(';');           // delimitatori pentru fisierul csv 
            char delimeter2('\n');

            unsigned int indexBuffer = 0;   // index pentru deducerea numarului de membrii initiali, se returneaza la sfarsitul functiei
            
            try
            {
                if(!data_base_1_read.is_open())
                    throw '1';
                else
                {
                    while (!data_base_1_read.eof( ))   // citire din fisier pana la eof
                    {
                        getline(data_base_1_read, col_1[indexBuffer], delimeter1);
                        getline(data_base_1_read, col_2[indexBuffer], delimeter2);
                        indexBuffer++;
                    }
                    indexBuffer--;      // decrementam pentru a nu lua in considerare eof
                }
            }
            catch(char error)
            {
                if(error == '1')
                {
                    cout<<">> Whops, a intervenit o eroare in citirea fisierului CSV."<<endl;
                    cout<<">> Va rugam verificati integritatea fisierului si redeschideti aplicatia."<<endl;
                    return 0;
                }
            }
            return indexBuffer;
        }
        ~DatabaseReader();
};
DatabaseReader::~DatabaseReader(void){}

// clasa de scriere csv
class DatabaseWriter
{
    public:
        RandomString ranStrGen;
        // scriere csv pentru 4 coloane (nume, functie, mancare, machiaj/rol) 
        // am ales o scriere in urmatoarea ordine: actori, figuranti, restul castului pentru o utilitate mai buna in calculul costurilor (anume numarul fiecarei diete/machiaj)
        unsigned int nrCol4(string col_1[lin_db_1], string col_2[lin_db_1], string col_3[nrFiguranti], unsigned int index)
        {
            string names[nrOfNames][2];
            readNameDb(names);
            ofstream data_base_write;
            // supra scrie csv-ul la rurale, deci vom avea la fiecare rulare un csv diferit de fiecare data, inclusiv dieta, machiaj, nume figuranti
            // se pastreaza numarul
            data_base_write.open("castdetailed.csv"/*,ios::app*/);

            char delimeter1(';');           // delimitatori pentru fisierul csv
            char delimeter2('\n');

            unsigned int indexBuffer = 0;   // index
            try
            {
                if(!data_base_write.is_open())
                    throw '1';
                else
                {
                    cout<<">> Scriere in fisier actori..."<<endl;
                    // scriere doar actori din csv initial in noul csv + rol/dieta generare random
                    for(unsigned int i = 0; i < index; i++)
                    {
                        if(col_2[i].find("actor/actress") != string::npos)
                        {
                            data_base_write<<col_1[i];
                            data_base_write<<delimeter1;
                            data_base_write<<"actor";
                            data_base_write<<delimeter1;
                            data_base_write<<ranStrGen.rndMancare(ranStrGen.mancare); 
                            data_base_write<<delimeter1;
                            data_base_write<<ranStrGen.rndMancare(ranStrGen.rol); 
                            data_base_write<<delimeter2;
                            indexBuffer++;
                        }
                    }
                    cout<<">> Scriere in fisier figuranti..."<<endl;
                    // scriere cu generare a figurantilor in noul csv + rol/dieta generare random
                    for(unsigned int i = 0; i < nrFiguranti; i++)
                    {
                        
                        data_base_write<<ranStrGen.rndFigName(names);
                        data_base_write<<delimeter1;
                        data_base_write<<"Figurant";
                        data_base_write<<delimeter1;
                        data_base_write<<ranStrGen.rndMancare(ranStrGen.mancare);
                        data_base_write<<delimeter1;

                        data_base_write<<ranStrGen.rndRol(ranStrGen.rol);
                        data_base_write<<delimeter2;
                    }
                    cout<<">> Scriere in fisier restul cast-ului..."<<endl;
                    // scriere din vechiul csv in noul csv restul castului
                    for(unsigned int i = 0; i < index; i++)
                    {
                        if(col_2[i].find("actor/actress") == string::npos)

                        {
                            data_base_write<<col_1[i];
                            data_base_write<<delimeter1;

                            data_base_write<<col_2[i];
                            data_base_write<<delimeter2;
                        }
                    }
                    data_base_write.close();
                }
            }
            catch(char error)
            {
                if(error == '1')
                {
                    cout<<">> Whops, a intervenit o eroare in scrierea fisierului CSV."<<endl;
                    cout<<">> Va rugam verificati integritatea fisierului si redeschideti aplicatia."<<endl;
                    return 0;
                }
            }
            return indexBuffer;
        }
};
// functie master de citire csv intial  
unsigned int loading_init_CSV(string data1[lin_db_1], string data2[lin_db_1])
{
    cout<<">> Se incarca baza de date..."<<endl;
    DatabaseReader database1;
    unsigned int indexBuffer;
    // apelare cu salvare parametru returnat
    indexBuffer = database1.nrCol2(data1, data2);
    if(indexBuffer!=0)
    {
        cout<<endl;
        cout<<">> Incarcare reusita!"<<endl
            <<">> Apasati orice tasta pentru continuare."
        <<endl;
        getch();
        system("cls");
        return indexBuffer;
    }
    return 0;
}
// functie master de generare a primului csv
unsigned int generate_CSV_1(string data1[lin_db_1], string data2[lin_db_1], string figuranti[nrFiguranti], unsigned int index)
{
    cout<<">> Se genereaza CSV cu membrii cast-ului ..."<<endl<<endl;
    DatabaseWriter database1;
    unsigned int indexBuffer;
    // apelare cu salvare parametru returnat
    indexBuffer = database1.nrCol4(data1, data2, figuranti, index);
    if(indexBuffer!=0)
    {
        cout<<endl;
        cout<<">> Incarcare reusita!"<<endl
            <<">> Apasati orice tasta pentru continuare."
        <<endl;
        getch();
        system("cls");
        return indexBuffer;
    }
    return 0;
}
// citeste, compara si contorizeaza cate tipuri de machiaj sunt de fiecare, folosita la calcul cost
void readNverifyCSV1_machiaj(unsigned int contor[5], unsigned int castTotal)
{
    ifstream data_base_read;
    data_base_read.open("castdetailed.csv");
    char delimeter1(';');           // delimitatori pentru fisierul csv
    char delimeter2('\n');
    string s[2];
    try
    {
        if(!data_base_read.is_open())
            throw '1';
        else
        {
            for(unsigned int i = 0; i < castTotal; i++)
            {
                getline(data_base_read, s[0], delimeter1);
                getline(data_base_read, s[0], delimeter1);
                getline(data_base_read, s[0], delimeter1);
                getline(data_base_read, s[1], delimeter2);
                if(s[1] == "Vampir")
                    contor[0]++;
                else
                if(s[1] == "Varcolac")
                    contor[1]++;
                else
                if(s[1] == "Sirena")
                    contor[2]++;
                else
                if(s[1] == "Clarvazator")
                    contor[3]++;
                else
                if(s[1] == "Om")
                    contor[4]++;
            }
            data_base_read.close();
        }
    }
    catch(char error)
    {
        if(error == '1')
        {
            cout<<">> Whops, a intervenit o eroare in citirea fisierului CSV."<<endl;
            cout<<">> Va rugam verificati integritatea fisierului si redeschideti aplicatia."<<endl;
        }
    }
}

// citeste, compara si contorizeaza cate tipuri de diete sunt de fiecare, folosita la calcul cost
void readNverifyCSV1_tipHrana(unsigned int contor[3], unsigned int castTotal)
{
    ifstream data_base_read;
    data_base_read.open("castdetailed.csv");
    char delimeter1(';');           // delimitatori pentru fisierul csv
    char delimeter2('\n');
    string s[2];
    try
    {
        if(!data_base_read.is_open())
            throw '1';
        else
        {
            for(unsigned int i = 0; i < castTotal; i++)
            {
                getline(data_base_read, s[0], delimeter1);
                getline(data_base_read, s[0], delimeter1);
                getline(data_base_read, s[1], delimeter1);
                getline(data_base_read, s[0], delimeter2);
                if(s[1] == "Apt sa manance orice")
                    contor[0]++;
                else
                if(s[1] == "Vegetarian")
                    contor[1]++;
                else
                if(s[1] == "Flexitarian")
                    contor[2]++;
            }
            data_base_read.close();
        }
    }
    catch(char error)
    {
        if(error == '1')
        {
            cout<<">> Whops, a intervenit o eroare in citirea fisierului CSV."<<endl;
            cout<<">> Va rugam verificati integritatea fisierului si redeschideti aplicatia."<<endl;
        }
    }
}
// supra scrie csv-ul de cost, scrie prima linie pentru structurare vizuala in functie de numarul de zile per perioada 
void preWriteCSV2()
{
    ofstream data_base_write;
    data_base_write.open("castprices.csv");
    char delimeter1(';');           // delimitatori pentru fisierul csv
    char delimeter2('\n');
    try
    {
        if(!data_base_write.is_open())
            throw '1';
        else
        {
            data_base_write<<"Zile";    data_base_write<<delimeter1;
            data_base_write<<"30";      data_base_write<<delimeter1;
            data_base_write<<"45";      data_base_write<<delimeter1;
            data_base_write<<"60";      data_base_write<<delimeter1;
            data_base_write<<"100";     data_base_write<<delimeter2;
        }
    }
    catch(char error)
    {
        if(error == '1')
        {
            cout<<">> Whops, a intervenit o eroare in scrierea fisierului CSV."<<endl;
            cout<<">> Va rugam verificati integritatea fisierului si redeschideti aplicatia."<<endl;
        }
    }
}
// scriere in continuare dupa supra scriere a fiecarul cost  
void writeCSV2(unsigned int price[4], string sInput)
{
    ofstream data_base_write;
    // pentru scriere in continuare, nu supra scriere
    data_base_write.open("castprices.csv",ios::app);
    char delimeter1(';');           // delimitatori pentru fisierul csv
    char delimeter2('\n');
    try
    {
        if(!data_base_write.is_open())
            throw '1';
        else
        {
            data_base_write<<sInput;
            data_base_write<<delimeter1;
            for(unsigned int i = 0; i < 3; i++)
            {

                data_base_write<<price[i];
                data_base_write<<delimeter1;
            }
            data_base_write<<price[3];
            data_base_write<<delimeter2;
        }
    }
    catch(char error)
    {
        if(error == '1')
        {
            cout<<">> Whops, a intervenit o eroare in scrierea fisierului CSV."<<endl;
            cout<<">> Va rugam verificati integritatea fisierului si redeschideti aplicatia."<<endl;
        }
    }

}
// functie generala de calcul pret/zi * numarul de zile
void calculPretPerioade(unsigned int pretZi, unsigned int pretPerioada[4], unsigned int zilePerioada[4])
{
    pretPerioada[0] = pretZi * zilePerioada[0];
    pretPerioada[1] = pretZi * zilePerioada[1];
    pretPerioada[2] = pretZi * zilePerioada[2];
    pretPerioada[3] = pretZi * zilePerioada[3];
}

// clasa parinte pentru cost 
class Membrii
{
    protected:
        unsigned int nrCastInit;
        unsigned int nrActori;
    public:
        Membrii();
        Membrii(unsigned int nrCas, unsigned int nrAct)
        {
            nrCastInit = nrCas;
            nrActori = nrAct;
        }
        unsigned int getNrCas()
        {
            return this->nrCastInit;
        }
        unsigned int getNrAct()
        {
            return this->nrActori;
        }
        ~Membrii();
};

// clasa mostenita pentru cost 
class Preturi : private Membrii
{
    private:
        unsigned int pretAutocar[4];
        unsigned int pretMachiaj[4];
        unsigned int pretCazare[4];
        unsigned int pretChirie[4];

        unsigned int pretLichide[4];
        unsigned int pretMancare[4];

        unsigned int zilePerioada[4] = {30, 45, 60, 100};
        unsigned int nrZile;

    public:
        Preturi(unsigned int nrCas, unsigned int nrAct) : Membrii(nrCas, nrAct)
        {
            nrCastInit = nrCas;
            nrActori = nrAct;
            cout<<">> Se genereaza CSV cu costurile cast-ului ..."<<endl<<endl;
        }
        Preturi();

        getch();
        // calculeaza pretul autocarelor (care este acelasi indiferent de perioada)
        void getPretAutocar()
        {
            unsigned int castTotal = nrCastInit + nrFiguranti;
            pretAutocar[0] = castTotal / 50;
            if(castTotal%50 != 0)
                pretAutocar[0]++;
            pretAutocar[0] = pretAutocar[0] * priceBus *2 / cursDolar;

            for(unsigned int i = 1; i < 4; i++)
                pretAutocar[i] = pretAutocar[0];
            // scrie in csv 2 rezultatul
            writeCSV2(pretAutocar, "$ Autocar");
        }
        // calculeaza pretul machiajului
        void getPretMachiaj()
        {
            unsigned int castTotal = nrCastInit + nrFiguranti - nrActori;
            unsigned int contor[5] = { 0 };
            unsigned int pretZi;
            // citire si contorizare din csv initial 
            readNverifyCSV1_machiaj(contor, castTotal);

            pretZi = (contor[0]*230 + contor[1]*555 + contor[2]*345 + contor[3]*157 + contor[4]*55)/cursDolar;

            // calcul pret/zi * numarul de zile
            calculPretPerioade(pretZi, pretMachiaj, zilePerioada);

            // scire in csv 2 rezultatul
            writeCSV2(pretMachiaj, "$ Machiaj");
        }
        // calculeaza pretul cazarii
        void getPretCazare()
        {
            unsigned int castTotal = nrCastInit + nrFiguranti;
            unsigned int contor[2] = { 0 };
            unsigned int pretZi;
            contor[0] = nrCastInit / 2;
            if(nrCastInit%2 != 0)
                contor[0]++;
            contor[1] = nrFiguranti / 3;
            if(nrFiguranti%3 != 0)
                contor[1]++;

            pretZi = (contor[0]*350 + contor[1]*420) / cursDolar;

            // calcul pret/zi * numarul de zile
            calculPretPerioade(pretZi, pretCazare, zilePerioada);

            // scrie in csv 2 rezultatul
            writeCSV2(pretCazare, "$ Cazare");
        }
        // calculeaza pretul inchirierii castelului
        void getPretChirie()
        {
            unsigned int pretZi = 10000;

            calculPretPerioade(pretZi, pretChirie, zilePerioada);
            // aplicarea reducerii in functie de numarul de zile
            for(unsigned int i = 0; i < 4; i++)
                pretChirie[i] = pretChirie[i]*(1-0.02*(zilePerioada[i] / 10)) / cursDolar;

            // scrie in csv 2 rezultatul
            writeCSV2(pretChirie, "$ Chirie");
        }
        // calculeaza pretul lichidelor consumate 
        void getPretLichide()
        {
            unsigned int castTotal = nrCastInit + nrFiguranti;
            unsigned int pretZi;
            unsigned int contor[3] = { 0 };

            // recipientele au volumuri fixe
            // exemplu : pentru 3l de apa trebuie cumparate 2 sticle de 2l
            contor[0] = castTotal *1 / 2;
            if(castTotal%2 != 0)
                contor[0]++;

            contor[1] = castTotal *0.5 / 1;
            if(castTotal%1 != 0)
                contor[1]++;

            contor[2] = castTotal *0.8 / 2;
            if(castTotal%1 != 0)
                contor[2]++;

            pretZi = (contor[0] * 6 + contor[1] * 30 + contor[2] * 8) / cursDolar;

            // calcul pret/zi * numarul de zile
            calculPretPerioade(pretZi, pretLichide, zilePerioada);

            // scrie in csv 2 rezultatul
            writeCSV2(pretLichide, "$ Lichide");
        }
        // calculeaza pretul mancarii
        void getPretMancare()
        {
            unsigned int castTotal = nrActori + nrFiguranti;
            unsigned int pretZi;
            unsigned int contor[3] = { 0 };
            // citire si contorizare din csv initial 
            readNverifyCSV1_tipHrana(contor, castTotal);

            pretZi = (contor[0] * 40 + contor[1] * 33 + contor[2] * 46) / cursDolar;
            calculPretPerioade(pretZi, pretMancare, zilePerioada);

            // scrie in csv 2 rezultatul
            writeCSV2(pretMancare, "$ Mancare");

            // mesaj final
            cout<<">> Incarcare reusita!"<<endl
                <<">> Apasati orice tasta pentru continuare."
                <<endl;
        }
};
Membrii::~Membrii(void){}



void afisareDb_1(unsigned int indexBuffer, string col1[lin_db_1], string col2[lin_db_1])
{
     // afisare
    for(unsigned int i = 0; i < indexBuffer; i++)
    {
            cout<<right<<setw(3)<<i+1<<") ";
            cout<<right<<setw(36)<<col1[i]<<" - ";
            cout<<left<<setw(9)<<col2[i];
        cout<<endl;
    }
}

int main()
{
    srand(time(NULL));
    Database database1;

    database1.nrCastInit = loading_init_CSV(database1.c1, database1.c2);
    database1.nrActori = generate_CSV_1(database1.c1, database1.c2, database1.figuranti, database1.nrCastInit);

    Membrii membrii(database1.nrCastInit, database1.nrActori);

    Preturi preturi(membrii.getNrCas(), membrii.getNrAct());
    preWriteCSV2();
    preturi.getPretAutocar();
    preturi.getPretMachiaj();
    preturi.getPretCazare();
    preturi.getPretChirie();
    preturi.getPretLichide();
    preturi.getPretMancare();

    return 0;
}
// Untea Robert-Marius
// 323AC
