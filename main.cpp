#include <iostream>
#include <chrono>
#include <thread>
#include <cctype>

using namespace std;
const int POCET_OTAZEK = 15;
const int POCET_ODPOVEDI = 4;

class Otazka {
    private:
        string otazka;
        string odpovedi[POCET_ODPOVEDI];
        //vector<string> odpovedi;
        char spravnaOdpoved;
    public:
        Otazka(const string otazka, const string odpovedi[], const char spravnaOdpoved) {
            this->otazka = otazka;
            for (int i = 0; i < POCET_ODPOVEDI; i++)
                this->odpovedi[i] = odpovedi[i];
            //for (int i = 0; i < 4; i++)
            //    this->odpovedi.push_back(odpovedi[i]);
            this->spravnaOdpoved = spravnaOdpoved;
        }

        string returnOtazka() {
            return otazka;
        }

        char returnSpravnaOdpoved() {
            return spravnaOdpoved;
        }

        void printOdpovedi() {
            for (string odpoved : odpovedi) {
                cout << odpoved << ((odpoved != odpovedi[POCET_ODPOVEDI - 1]) ? "\n" : ": ");
                this_thread::sleep_for(chrono::milliseconds(100));
            }
        }
};

const string odpovedi[POCET_OTAZEK][POCET_ODPOVEDI] = {
    {"a) Napíše Hello, world!", "b) Čeká na input, poté napíše Hello, world!", "c) Je kompatibilní s C", "d) Hodí seg fault"},
    {"a) 012", "b) 122", "c) 013", "d) 112"},
    {"a) Odpověď 1", "b) Odpověď 2", "d) Odpověď 3", "d) Odpověď 4"},
    {"a) Odpověď 1", "b) Odpověď 2", "d) Odpověď 3", "d) Odpověď 4"},
    {"a) Odpověď 1", "b) Odpověď 2", "d) Odpověď 3", "d) Odpověď 4"},
    {"a) Odpověď 1", "b) Odpověď 2", "d) Odpověď 3", "d) Odpověď 4"},
    {"a) Odpověď 1", "b) Odpověď 2", "d) Odpověď 3", "d) Odpověď 4"},
    {"a) Odpověď 1", "b) Odpověď 2", "d) Odpověď 3", "d) Odpověď 4"},
    {"a) Odpověď 1", "b) Odpověď 2", "d) Odpověď 3", "d) Odpověď 4"},
    {"a) Odpověď 1", "b) Odpověď 2", "d) Odpověď 3", "d) Odpověď 4"},
    {"a) Odpověď 1", "b) Odpověď 2", "d) Odpověď 3", "d) Odpověď 4"},
    {"a) Odpověď 1", "b) Odpověď 2", "d) Odpověď 3", "d) Odpověď 4"},
    {"a) Odpověď 1", "b) Odpověď 2", "d) Odpověď 3", "d) Odpověď 4"},
    {"a) Odpověď 1", "b) Odpověď 2", "d) Odpověď 3", "d) Odpověď 4"},
    {"a) Odpověď 1", "b) Odpověď 2", "d) Odpověď 3", "d) Odpověď 4"}
};

const Otazka listOtazek[POCET_OTAZEK] = {
    Otazka("Co je pravda o programu:\n\n#include <iostream>\n\nusing namespace std;\nint main() {\n    cout << \"Hello, world!\" << endl;\n}", odpovedi[0], 'a'),
    Otazka("Co napíše tento program?\n\n#include <iostream>\n\nusing namespace std;\nint main() {\n    int i = 0;\n    cout << ++i << i++ << i << endl;" , odpovedi[1], 'd'),
    Otazka("Test č. 3:", odpovedi[2], 'c'),
    Otazka("Test č. 4:", odpovedi[3], 'b'),
    Otazka("Test č. 5:", odpovedi[4], 'b'),
    Otazka("Test č. 6:", odpovedi[5], 'a'),
    Otazka("Test č. 7:", odpovedi[6], 'd'),
    Otazka("Test č. 8:", odpovedi[7], 'c'),
    Otazka("Test č. 9:", odpovedi[8], 'c'),
    Otazka("Test č. 10:", odpovedi[9], 'a'),
    Otazka("Test č. 11:", odpovedi[10], 'c'),
    Otazka("Test č. 12:", odpovedi[11], 'b'),
    Otazka("Test č. 13:", odpovedi[12], 'b'),
    Otazka("Test č. 14:", odpovedi[13], 'b'),
    Otazka("Test č. 15:", odpovedi[14], 'd')
};

bool otazky(int index) {
    auto otazka = listOtazek[index];
    cout << otazka.returnOtazka() << endl << endl;
    this_thread::sleep_for(chrono::milliseconds(2000));

    otazka.printOdpovedi();
    string user_odpoved;
    cin >> user_odpoved;
    const char chr_user_odpoved = tolower(user_odpoved[0]);

    if (user_odpoved.size() > 1 || chr_user_odpoved != 'a' && chr_user_odpoved != 'b' && chr_user_odpoved != 'c' && chr_user_odpoved != 'd') {
        cout << "Špatné zadání!" << endl;
        return otazky(index);
    }

    return chr_user_odpoved == otazka.returnSpravnaOdpoved();
}

int main() {
    bool vyhra = true;
    for (int i = 0; i < POCET_OTAZEK; i++) {
        if (not otazky(i)) {
            cout << "Je mi líto, ale toto byla špatná odpověď." << endl;
            this_thread::sleep_for(chrono::milliseconds(2000));
            cout << "Zabijí vás agenti KGB!" << endl;
            this_thread::sleep_for(chrono::milliseconds(2000));
            vyhra = false;
            break;
        }
        cout << "Ano správně, je to tak!" << endl;
        this_thread::sleep_for(chrono::milliseconds(1200));

    }
    if (vyhra) {
        cout << "Právě jste vyhrál hru chcete být c++ářem, GRATULUJEME!!!" << endl;
        this_thread::sleep_for(chrono::milliseconds(3000));
    }
}
