#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <cctype>

using namespace std;
const int POCET_OTAZEK = 15;
class Otazka {
    private:
        string otazka;
        vector<string> odpovedi;
        char spravnaOdpoved;
    public:
        Otazka(string otazka, const string odpovedi[], char spravnaOdpoved) {
            this->otazka = otazka;
            for (int i = 0; i < 4; i++)
                this->odpovedi.push_back(odpovedi[i]);
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
                cout << odpoved << ((odpoved != odpovedi[odpovedi.size() - 1]) ? "\n" : ": ");
                this_thread::sleep_for(chrono::milliseconds(100));
            }
        }
};

const string odpovedi[POCET_OTAZEK][4] = {
    {"a) Ano", "b) Ne", "c) Nevim", "d) Tvoje máma je kokot!"},
    {"a) Ano 2", "b) Ne 2", "c) Nevim 2", "d) Tvoje máma je kokot 2!"}
};

const Otazka listOtazek[POCET_OTAZEK] = {
    Otazka("Co udělá tento program?\n\n#include <iostream>\n\nusing namespace std;\nint main() {\n    cout << \"Hello, world!\";\n}", odpovedi[0], 'a'),
    Otazka("Test č. 2:", odpovedi[1], 'b'),
    Otazka("Test č. 3:", odpovedi[1], 'b'),
    Otazka("Test č. 4:", odpovedi[1], 'b'),
    Otazka("Test č. 5:", odpovedi[1], 'b'),
    Otazka("Test č. 6:", odpovedi[1], 'b'),
    Otazka("Test č. 7:", odpovedi[1], 'b'),
    Otazka("Test č. 8:", odpovedi[1], 'b'),
    Otazka("Test č. 9:", odpovedi[1], 'b'),
    Otazka("Test č. 10:", odpovedi[1], 'b'),
    Otazka("Test č. 11:", odpovedi[1], 'b'),
    Otazka("Test č. 12:", odpovedi[1], 'b'),
    Otazka("Test č. 13:", odpovedi[1], 'b'),
    Otazka("Test č. 14:", odpovedi[1], 'b'),
    Otazka("Test č. 15:", odpovedi[1], 'b')
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
        this_thread::sleep_for(chrono::milliseconds(800));

    }
    if (vyhra) {
        cout << "Právě jste vyhrál hru chcete být c++ářem, GRATULUJEME!!!";
        this_thread::sleep_for(chrono::milliseconds(3000));
    }
}
