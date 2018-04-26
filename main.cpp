#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

struct Stare
{
    char litera;
    int nr_nodStanga, nr_nodDreapta;
};
/**  
 *
 *@param litera este litera pe care o caut in automat
 *@param litera2 este a doua litera cautata
 *@param Nr_Stari este numarul total de stari ale automatului
 *@param Nr_Total_Tranzitii este numarul de tranzitii citite din date.in
 *@param este un vector de elemente de tip structura denumita "Stare"
 *@param drum este matricea in care vor fi puse lambda tranzitiile aplicate fiecarei stari
 */   
void Tranzitie_Litera( char litera, char litera2, int Nr_Stari, int Nr_Total_Tranzitii, Stare vector_Stari[20], int drum[20][20])
{
    /// se construieste matrice in care retin pe linia fiecarei stari unde pot ajunge cu o lambda tranzitie aplicata
    /// de mai multe ori
   for( int i = 0; i < Nr_Stari; i ++ )
   {
       drum[i][0] = i;
       int Indice_Coloana=1;
       for( int j = 0; j < Nr_Total_Tranzitii; j ++ )
       {
           if( vector_Stari[j].nr_nodStanga == i )
                if( vector_Stari[j].litera == litera )
                {
                    drum[i][Indice_Coloana] = vector_Stari[j].nr_nodDreapta;
                    Indice_Coloana ++;
                }
       }
       /// parcurg elementele adaugate pe linia i sa vad unde duc lambda-tranzitiile
       /// fiecaruia
       for( int j = 1; j < Indice_Coloana; j ++ )
        {
            for( int k = 0; k < Nr_Total_Tranzitii; k ++ )
            {
            if( vector_Stari[k].nr_nodStanga == drum[i][j] )
                if( litera2 != '0' )
                {
                if( vector_Stari[k].litera == litera || vector_Stari[k].litera == litera2)
                {
                    int ok = 1; /// presupun ca nu am mai adaugat acest element in linia lui i
                    for( int ver = 0; ver < Indice_Coloana; ver ++ )
                        if( drum[i][ver] == vector_Stari[k].nr_nodDreapta)
                            ok = 0;
                    if( ok == 1 )
                    {
                        drum[i][Indice_Coloana] = vector_Stari[k].nr_nodDreapta;
                        Indice_Coloana ++;
                    }
                }
                }
                else{
                    if( vector_Stari[k].litera == litera)
                {
                    int ok = 1; /// presupun ca nu am mai adaugat acest element in linia lui i
                    for( int ver = 0; ver < Indice_Coloana; ver ++ )
                        if( drum[i][ver] == vector_Stari[k].nr_nodDreapta)
                            ok = 0;
                    if( ok == 1 )
                    {
                        drum[i][Indice_Coloana] = vector_Stari[k].nr_nodDreapta;
                        Indice_Coloana ++;
                    }
                }
                }
            }

           }

    drum[i][Indice_Coloana] = -1;
   }
}
/**
*@param v este un vector in care este inserat elementul "element"
*@param element este elementul care trebuie inserat
*@param nr_elemente este transmis prin referinta si reprezinta numarul
*total de elemente din vectorul v
*/
void Inserare( int v[20], int element, int &nr_elemente)
{
    int i, ok = 1;
    for(i = 0; i < nr_elemente; i++)
        if( v[i] == element)
            ok = 0;
    if(ok == 1)
   {
        v[nr_elemente] = element;
        nr_elemente ++;
   }
}
/**
*@param numar_stare este un paramentru transmis prin referinta si 
*reprezinta un numar obtinut in urma alipirii parametrului 
*"element nou". Acest parametru va fi folosit pentru a 
*diferentia starile AFD-ului rezultat
*@param element_nou este o cifra care trebuie sa fie adaugata 
*numarului "numar_stare
*/
void MAKE_NUMBER(int &numar_stare, int element_nou)
{
    if(numar_stare==0) numar_stare = element_nou;
    else numar_stare = numar_stare*10 + element_nou;
}
/**
*@param numar_de_transformat este un numar care va fi pus in
*vectorul "vector_rezultat" pentru a manipula datele mai usor
*@param vector_rezultat este vectorul format din componentele 
*numarului din primul parametru al functiei
*@param nr_cifre reprezinta numarul total de cifre al vectorului
*vector_rezultate
*/
void Become_Vector( int numar_de_transformat, int vector_rezultat[20], int &nr_cifre)
{
    nr_cifre = 0;
    while(numar_de_transformat)
    {
        vector_rezultat[nr_cifre] = numar_de_transformat%10;
        numar_de_transformat = numar_de_transformat/10;
        nr_cifre++;
    }
}
int main()
{
    int matrice[20][20]; /// unde retin lambda-a-lambda, lambda-b-lambda etc
    int Nr_Stari, Nr_Stari_Finale, Stari_Finale[10], Nr_Total_Tranzitii, drum_Lambda[20][20];
    char vector_Litere[20], litera;
    int  drum_Litera[20][20], Nr_Litere;
    Stare vector_Stari[20], AFD_Stari[20];
    int AFD_Nr_Tranzitii = 0;
    ifstream f("date.in");
    f >> Nr_Stari >> Nr_Stari_Finale >> Nr_Total_Tranzitii;
    for( int i = 0; i < Nr_Stari_Finale; i ++ )
        f >> Stari_Finale[i];
    for( int i = 0; i < Nr_Total_Tranzitii; i ++ )
        f >> vector_Stari[i].nr_nodStanga >> vector_Stari[i].litera >> vector_Stari[i].nr_nodDreapta;
   f >> Nr_Litere;
   for( int i = 0; i < Nr_Litere; i ++)
        f >> vector_Litere[i];
   for( int i = 0; i < 20; i ++)
        for( int j = 0; j < 20; j ++)
            drum_Lambda[i][j] = -1;
    Nr_Stari ++;

    ///creez lambda tranzitiile pentru fiecare stare
    Tranzitie_Litera( 'l', '0', Nr_Stari, Nr_Total_Tranzitii, vector_Stari, drum_Lambda );
    int nod_Curent = 0, Coloana = 0, pozitie = 0, stare_noua = 0, adauga_nod0 = 0;
    int vector_Reuniune[20], vector_Curent[20];
    while(drum_Lambda[0][Coloana] != -1) /// creez primul nod al noului automat
    {
        MAKE_NUMBER(stare_noua,drum_Lambda[0][Coloana]);
        if(drum_Lambda[0][Coloana] == 0)
            adauga_nod0 = 1;
        Coloana ++;
    }
    if(adauga_nod0 == 1)
         MAKE_NUMBER(stare_noua, 0);
    int STARE_INITIALA = stare_noua;
    int Nr_Tranzitie_Noua = 0;
    int vector2[20];
    int indiceLitera = 0;
    for( int i = 0; i < Nr_Litere; i ++ )
        {for(nod_Curent = 0; nod_Curent < Nr_Stari; nod_Curent ++)
        {
            adauga_nod0 = 0;
            stare_noua = 0;
            pozitie = 0;
            Coloana = 0;
            litera = vector_Litere[i];
            while(drum_Lambda[nod_Curent][Coloana] != -1) /// caut tranzitiile cu litera 'litera'
            {
                for( int k = 0; k < Nr_Total_Tranzitii; k ++ )
                    if( vector_Stari[k].nr_nodStanga == drum_Lambda[nod_Curent][Coloana] )
                        if( vector_Stari[k].litera == litera )
                        {
                            Inserare(vector_Curent, vector_Stari[k].nr_nodDreapta, pozitie);
                        }
                Coloana ++;
            }
            int pozitie2 = 0;
            for(int w = 0; w < pozitie; w ++)
            {
                Coloana = 0;
                while(drum_Lambda[vector_Curent[w]][Coloana] != -1)
                {
                    Inserare(vector2, drum_Lambda[vector_Curent[w]][Coloana], pozitie2);
                    Coloana++;
                }
            }
            for( int w = 0; w < pozitie; w++) ///caut lambda tranzitiile din nou
            {
                for( int k = 0; k < Nr_Total_Tranzitii; k ++ )
                    if( vector_Curent[w] == vector_Stari[k].nr_nodStanga )
                        if( vector_Stari[k].litera == 'l' )
                            Inserare(vector2, vector_Stari[k].nr_nodDreapta, pozitie2);
            }
            for(int w = 0; w < pozitie2; w ++)
                    {
                        MAKE_NUMBER(stare_noua, vector2[w]);
                        if(vector2[w] == 0)
                            adauga_nod0 = 1;
                    }
            if(adauga_nod0 == 1) MAKE_NUMBER(stare_noua,0);
            matrice[nod_Curent][indiceLitera%Nr_Litere] = stare_noua; /// pune elementul pe coloana 0 daca
            ///este prima litera, pe coloana 1 daca este a doua litera etc;

        }
                    indiceLitera++;

        }
    char Litera_Tranzitie = 'a';
    int vec[20];
    pozitie = 0;
    int matrice_AFD[20][20], Nr_Linii_AFD = Nr_Litere + 1;
    matrice_AFD[0][0] = STARE_INITIALA;
    for(int i = 0; i < Nr_Litere; i ++)
        matrice_AFD[0][(i%Nr_Litere)+1] = matrice[0][i%Nr_Litere];
    int aux = 1;
    for(int i = 0; i < Nr_Litere; i ++)
        {
            matrice_AFD[i+1][0] = matrice_AFD[0][aux];
            aux++;
        }
    for(int i = 0; i < Nr_Linii_AFD; i ++ )
    for( int w = 0; w < Nr_Litere; w ++) ///facem tranzitia cu fiecare litera, nr col din matrice
    {
        stare_noua = 0;
        int copie = matrice_AFD[i+1][0];
        int poz_vector_curent = 0;
        int vector_aux[20], poz_vector_aux = 0;
        Become_Vector(copie,vector_aux,poz_vector_aux); /// linia devine vector_aux
        for(int p = 0; p < poz_vector_aux; p++) ///el de pe col 0 matrice_AFD
        {
            int x = matrice[p][w]; ///coloana literei w a liniei p
            int vector_matrice[20];
            int nr_elem = 0;
            Become_Vector(x,vector_matrice,nr_elem);
            for(int q = 0; q < nr_elem; q++)
                Inserare(vector_Curent, vector_matrice[q],poz_vector_curent);
        }
        adauga_nod0 = 0;
        for(int y = 0; y < poz_vector_curent; y ++)
                {
                    MAKE_NUMBER(stare_noua, vector_Curent[y]);
                    if(vector_Curent[y] == 0)
                        adauga_nod0 = 1;
                }
        if(adauga_nod0 == 1) MAKE_NUMBER(stare_noua,0);
        matrice_AFD[i+1][w+1] = stare_noua;
    }
    for(int i=0;i<Nr_Linii_AFD;i++) ///afisare tranzitii
        {
            for(int j=1;j<Nr_Litere+1; j++)
                cout<<matrice_AFD[i][0]<<" "<<vector_Litere[j-1]<<" "<<matrice_AFD[i][j]<<" "<<endl;
        cout<<endl;
        }

   return 0;

}
