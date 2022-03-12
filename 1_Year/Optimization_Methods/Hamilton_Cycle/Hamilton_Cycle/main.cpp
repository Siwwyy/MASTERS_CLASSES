#include <fstream>
#include <iomanip>
#include <iostream>



const int MAXINT = 2147483647;

// Zmienne globalne

int n, m, v0, d, dh, sptr, shptr;
bool** A;                         // Macierz s¹siedztwa
int** W;                          // Macierz wag krawêdzi
int* S, * Sh;                      // Stosy w tablicy
bool* visited;                    // Tablica odwiedzin

// Rekurencyjna procedura poszukiwania cyklu Hamiltona
// o najmniejszej sumie wag krawêdzi
// v - wierzcho³ek bie¿¹cy
//----------------------------------------------------
void TSP(int v)
{
    int u;

    Sh[shptr++] = v;              // zapamiêtujemy na stosie bie¿¹cy wierzcho³ek

    if (shptr < n)                  // jeœli brak œcie¿ki Hamiltona, to jej szukamy
    {
        visited[v] = true;          // Oznaczamy bie¿¹cy wierzcho³ek jako odwiedzony
        for (u = 0; u < n; u++)       // Przegl¹damy s¹siadów wierzcho³ka v
            if (A[v][u] && !visited[u]) // Szukamy nieodwiedzonego jeszcze s¹siada
            {
                dh += W[v][u];        // Dodajemy wagê krawêdzi v-u do sumy
                TSP(u);                 // Rekurencyjnie wywo³ujemy szukanie cyklu Hamiltona
                dh -= W[v][u];        // Usuwamy wagê krawêdzi z sumy
            }
        visited[v] = false;         // Zwalniamy bie¿¹cy wierzcho³ek
    }
    else if (A[v0][v])         // Jeœli znaleziona œcie¿ka jest cyklem Hamiltona
    {
        dh += W[v][v0];           // to sprawdzamy, czy ma najmniejsz¹ sumê wag
        if (dh < d)                   // Jeœli tak, 
        {
            d = dh;                      // To zapamiêtujemy tê sumê
            for (u = 0; u < shptr; u++) // oraz kopiujemy stos Sh do S
                S[u] = Sh[u];
            sptr = shptr;
        }
        dh -= W[v][v0];           // Usuwamy wagê krawêdzi v-v0 z sumy
    }
    shptr--;                         // Usuwamy bie¿¹cy wierzcho³ek ze œcie¿ki
}



//4 4
//1   2   3   4
//1 0  100 200 300
//2 100 0   50 150
//3 200 50  0   75
//4 300 150 75  0

int main(int argc, char* argv[])
{
    using std::cout;
    using std::endl;
    using std::cin;
    using std::fstream;
    using std::ios;

    int i, j, x, y, z;

    fstream my_file("graph.in", ios::in);
    if(!my_file.is_open())
    {
        std::cout << "Cannot read file\n";
    }
    my_file >> n >> m; // Czytamy liczbê wierzcho³ków i krawêdzi

    // Tworzymy struktury dynamiczne i inicjujemy je

    S = new int[n];
    Sh = new int[n];
    visited = new bool[n];
    A = new bool* [n];
    W = new int* [n];
    for (i = 0; i < n; i++)
    {
        A[i] = new bool[n];
        W[i] = new int[n];
        for (j = 0; j < n; j++)
        {
            A[i][j] = false;
            W[i][j] = 0;
        }
        visited[i] = false;
    }
    sptr = shptr = 0;

    // Odczytujemy dane wejœciowe
    for (i = 0; i < m; i++)
    {
        int elem{};
        for (int j = 0; j < n; j++)
        {
            my_file >> elem;
            A[i][j] = A[j][i] = true; // KrawêdŸ x-y
            W[i][j] = W[j][i] = elem;    // Waga krawêdzi x-y

            std::cout << elem << ' ';
        }
        std::cout << std::endl;
    }

    cout << endl;

    // Rozpoczynamy algorytm

    d = MAXINT;
    dh = v0 = 0;
    TSP(v0);
    if (sptr)
    {
        for (i = 0; i < sptr; i++) cout << S[i] << " ";
        cout << v0 << endl;
        cout << "d = " << d << endl;
    }
    else cout << "NO HAMILTONIAN CYCLE" << endl;

    cout << endl;

    // Usuwamy tablice dynamiczne

    delete[] S;
    delete[] Sh;
    delete[] visited;

    for (i = 0; i < n; i++)
    {
        delete[] A[i];
        delete[] W[i];
    }

    delete[] A;
    delete[] W;

    std::cin.get();
    return EXIT_SUCCESS;
}