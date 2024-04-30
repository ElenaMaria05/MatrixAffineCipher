#include <iostream> 
#include <string> 
#include <random> 
using namespace std;

int simetric(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return 1;
}

string criptareAfina(string message, int a, int b) {
    string result = "";
    int m = 26;

    for (char ch : message) { //ch reprez el din iteratia curenta din mesaj 
        if (isalpha(ch)) { //daca e parte din alfabet 
            char encryptedChar = ((a * (ch - 'A') + b) % m) + 'A'; //caracterul actual criptat dupa form matem
            result += encryptedChar; //baga caracterul actual criptat in rezultat. e ca si cum as fii facut cu push_back
        }
        else { //daca nu e e din alfabet nu il cripteaza, il baga in rezultat asa cum e
                result += ch;
        }
    }
    return result;
}

string decriptareAfina(string ciphertext, int a, int b) {
    string result = "";
    int m = 26;
    int aSimetric = simetric(a, m);

    for (char ch : ciphertext) {
        if (isalpha(ch)) {
            char decryptedChar = ((aSimetric * (ch - 'A' - b + m)) % m) + 'A';
            result += decryptedChar;
        }
        else {
            result += ch;
        }
    }
    return result;
}

string criptare(string mesaj) {
    char matrice[100][100]{ 0 };
    int size = 3 + mesaj.size() / 2; // liniile si coloanele matricei 

    int index = 0; // pentru a lua toate elementele din mesaj ca j-ul se reseteaza 
    // punem elementele mesajului in matrice, restul matricei ramane gol 
    for (int i = 0; i < size; i += 2)
    {
        for (int j = 0; j < size; j += 2)
        {
            if (index == mesaj.size()) {
                i = size; // ca sa se opreasca primul for 
                break;    // al doilea for 
            }
            matrice[i][j] = mesaj[index];
            index++;
        }
    }

    string random = "QWERTYUIOPASDFGHJKLZXCVBNM12345678901234567890";
    shuffle(random.begin(), random.end(), mt19937(random_device()()));

    index = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (index == random.size()) { // cand au fost inserate toate elementele din random resetam index si dam iar shuffle la random
                    index = 0;
                    shuffle(random.begin(), random.end(), mt19937(random_device()()));
            }
            if (matrice[i][j] == '\0') { // umplem golurile din matrice cu gunoiul  din random
                    matrice[i][j] = random[index];
            }
            index++;
        }
    }

    // luam totalul de elemente care reprezinta cate litere sunt din mesajul nostru initial
        string mesajSize = to_string(mesaj.size());

    // inseram elementele din mseajSize la finalul matricei 
    // (mesajSize reprezinta numarul caracterelor din mesajul initial) 
    index = 0;
    for (int i = 1; i < size; i++)
    {
        if (index == mesajSize.size()) {
            matrice[size - 1][size - i] = 'X'; // "bariera" ca sa stim cand sa ne oprim din luat elemente in decriptare
                break;
        }
        matrice[size - 1][size - i] = mesajSize[index];
        index++;
    }

    ////printare 
    /*for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
             cout << matrice[i][j];
        }
         cout <<  endl;
    }
    cout << endl;*/

    // punem toata matricea pe randuri in mesajCriptat 
    string mesajCriptat;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            mesajCriptat.push_back(matrice[i][j]);
        }
    }

    return mesajCriptat;
}

string decriptare(string mesajCriptat) {
    char matrice[100][100]{ 0 };

    // luam numarul caracterelor din mesajul initial 
    int size = 0;
    for (int i = mesajCriptat.size() - 1; mesajCriptat[i] != 'X'; i--) // ne oprim la 'X' care e "bariera"
    {
        size = size * 10 + (int)(mesajCriptat[i] - '0');
    }

    // randurile si coloanele matricei  
    int sizeMatrice = 3 + size / 2;
    int index = 0;

    // refacem matricea 
    for (int i = 0; i < sizeMatrice; i++)
    {
        for (int j = 0; j < sizeMatrice; j++)
        {
            matrice[i][j] = mesajCriptat[index];
            index++;
        }
    }

    // luam numarul caracterelor din mesajul initial din matrice (15 in cazul asta) 
    string mesajDecriptat;
    index = 0;
    for (int i = 0; i < sizeMatrice; i += 2)
    {
        for (int j = 0; j < sizeMatrice; j += 2)
        {
            if (index == size) {
                i = sizeMatrice; // ca sa se opreasca primul for 
                break;           // ca sa iesim din al 2 lea for 
            }
            mesajDecriptat.push_back(matrice[i][j]);
            index++;
        }
    }
    ////printare 
    // cout <<  endl; 
    //for (int i = 0; i < size; i++) 
    //{ 
    //    for (int j = 0; j < size; j++) 
    //    { 
    //         cout << matrice[i][j]; 
    //    } 
    //     cout <<  endl; 
    //} 
    /*cout << endl;*/
    return mesajDecriptat;
}

int main() {
    string message = "ELENA";
    int a = 3;
    int b = 1;

    string encryptedMessage = criptareAfina(message, a, b);
    encryptedMessage = criptare(encryptedMessage);
    string decryptedMessage = decriptare(encryptedMessage);
    decryptedMessage = decriptareAfina(decryptedMessage, a, b);
    cout << "Mesaj initial: " << message << endl;
    cout << "Mesaj criptat: " << encryptedMessage << endl;
    cout << "Mesaj decriptat: " << decryptedMessage << endl;
}
