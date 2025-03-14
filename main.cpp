#include <iostream>
#include <chrono>
#include <thread>
#include <cctype>
#include <cstdlib>
#include <ctime>
#ifndef NO_SFML
#include <SFML/Audio.hpp>
#endif
#define POCET_OTAZEK 15
#define POCET_ODPOVEDI 4

using namespace std;

uint8_t listPadesatNaPadesat[2];
uint8_t procentaPublika[4];
struct UNap {
    bool padesat_na_padesat = false;
    bool publikum = false;
    bool pritel_na_telefonu = false;
} u_Nap;

void divaci_hlasovani() {
    cout << "Výsledky hlasování:\n";
    for (int i = 0; i < 4; i++) {
        if (procentaPublika[i] == 255) continue;
        cout << char('a' + i) << ") " << to_string(procentaPublika[i]) << '\n';
    }
}

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
        uint8_t pade_pade_count = 0;
        for (string odpoved : odpovedi) {
            if (u_Nap.padesat_na_padesat) {
                bool je_pade_pade = false;
                for (char pade_pade : listPadesatNaPadesat) {
                    if (pade_pade == odpoved[0] - 'a') {
                        je_pade_pade = true;
                        pade_pade_count++;
                        break;
                    }
                }
                if (!je_pade_pade) continue;
            }
            cout << odpoved << (((odpoved != odpovedi[POCET_ODPOVEDI - 1] && pade_pade_count < 1) || pade_pade_count == 1) ? "\n" : " (N = Nápovědy): ");
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    }
};

const string odpovedi[POCET_OTAZEK][POCET_ODPOVEDI] = {
    {"a) Napíše Hello, world!", "b) Čeká na input, poté napíše Hello, world!", "c) Je kompatibilní s C", "d) Hodí seg fault"},
    {"a) 012", "b) 122", "c) 013", "d) 112"},
    {"a) 8 4 2 1", "b) 64 32 16 8", "c) 40 20 10 5", "d) Hodí seg fault"},
    {"a) 9", "b) 10", "c) 12", "d) 14"},
    {"a) Odpověď 1", "b) Odpověď 2", "c) Odpověď 3", "d) Odpověď 4"},
    {"a) Odpověď 1", "b) Odpověď 2", "c) Odpověď 3", "d) Odpověď 4"},
    {"a) Odpověď 1", "b) Odpověď 2", "c) Odpověď 3", "d) Odpověď 4"},
    {"a) Odpověď 1", "b) Odpověď 2", "c) Odpověď 3", "d) Odpověď 4"},
    {"a) Odpověď 1", "b) Odpověď 2", "c) Odpověď 3", "d) Odpověď 4"},
    {"a) Odpověď 1", "b) Odpověď 2", "c) Odpověď 3", "d) Odpověď 4"},
    {"a) Odpověď 1", "b) Odpověď 2", "c) Odpověď 3", "d) Odpověď 4"},
    {"a) Odpověď 1", "b) Odpověď 2", "c) Odpověď 3", "d) Odpověď 4"},
    {"a) Odpověď 1", "b) Odpověď 2", "c) Odpověď 3", "d) Odpověď 4"},
    {"a) Odpověď 1", "b) Odpověď 2", "c) Odpověď 3", "d) Odpověď 4"},
    {"a) Odpověď 1", "b) Odpověď 2", "c) Odpověď 3", "d) Odpověď 4"}
};

const Otazka listOtazek[POCET_OTAZEK] = {
    Otazka("Co je pravda o programu:\n\n#include <iostream>\n\nusing namespace std;\nint main() {\n    cout << \"Hello, world!\" << endl;\n}", odpovedi[0], 'a'),
    Otazka("Jaký je output tohoto programu?\n\n#include <iostream>\n\nusing namespace std;\nint main() {\n    int i = 0;\n    cout << ++i << i++ << i << endl;\n}" , odpovedi[1], 'd'),
    Otazka("Jaký je output tohoto programu?\n\n#include <iostream>\n\nint main() {\n    size_t cisla_64bit[5];\n    int cisla_32bit[5];\n    short int cisla_16bit[5];\n    int8_t cisla_8bit[5];\n\n    std::cout << sizeof(cisla_64bit) << ' ' << sizeof(cisla_32bit) << ' ' << sizeof(cisla_16bit) << ' ' << sizeof(cisla_8bit) << '\\n';\n}", odpovedi[2], 'c'),
    Otazka("Jaký je output tohoto programu převedený z binárního čísla na decimální?\n\n#include <iostream>\n\nusing namespace std;\nnamespace matika {\n    int pridat(int& cislo, int i) {\n        i += (i - 2 == cislo);\n        return ++cislo + i;\n    }\n\n    int odebrat(int& cislo, int i) {\n        return --cislo + i;\n    }\n}\nint main() {\n    int cislo = 0;\n    string cislo_str;\n    for (int i = 0; i < 4; i++) {\n        int (*funkce)(int&, int) = i % 2 == 0 ? matika::pridat : matika::odebrat;\n        int vysledek = funkce(cislo, i);\n        cislo_str += to_string(vysledek > 1 ? vysledek - 3 : vysledek);\n    }\n    cout << cislo_str << '\\n';\n}", odpovedi[3], 'd'),
    Otazka("Test č. 5:", odpovedi[4], 'b'),
    Otazka("Test č. 6:", odpovedi[5], 'a'),
    Otazka("Test č. 7:", odpovedi[6], 'd'),
    Otazka("Test č. 8:", odpovedi[7], 'c'),
    Otazka("Test č. 9:", odpovedi[8], 'c'),
    Otazka("Test č. 10:", odpovedi[9], 'a'),
    Otazka("Test č. 11:", odpovedi[10], 'a'),
    Otazka("Test č. 12:", odpovedi[11], 'b'),
    Otazka("Test č. 13:", odpovedi[12], 'c'),
    Otazka("Test č. 14:", odpovedi[13], 'b'),
    Otazka("Test č. 15:", odpovedi[14], 'd')
};

enum class Napoveda {
    nic,
    padesat_na_padesat,
    publikum,
    pritel_na_telefonu,
};

struct Nap {
    bool padesat_na_padesat = true;
    bool publikum = true;
    bool pritel_na_telefonu = true;
} s_Nap;

Napoveda vyber_napoved() {
    cout << "\nMožné nápovědy:\n";
    char pismeno = 'a';
    char pnp = '-';
    char pub = '-';
    char tel = '-';
    if (!s_Nap.padesat_na_padesat && !s_Nap.publikum && !s_Nap.pritel_na_telefonu) cout << "Žádné nápovědy nejsou k dispozici";
    if (s_Nap.padesat_na_padesat) {
        cout << pismeno << ") 50:50";
        if (s_Nap.publikum || s_Nap.pritel_na_telefonu)
            cout << '\n';
        pnp = 'a';
        pismeno++;
    }
    if (s_Nap.publikum) {
        cout << pismeno << ") Hlasování publika";
        if (s_Nap.pritel_na_telefonu)
            cout << '\n';
        if (s_Nap.padesat_na_padesat) pub = 'b';
        else pub = 'a';
        pismeno++;
    }
    if (s_Nap.pritel_na_telefonu) {
        cout << pismeno << ") Přítel na telefonu";
        if (s_Nap.padesat_na_padesat) {
            if (s_Nap.publikum)
                tel = 'c';
            else
                tel = 'b';
        }
        else if (s_Nap.publikum)
            tel = 'b';
        else
            tel = 'a';
        pismeno++;
    }
    cout << ": ";
    string user_napoveda;
    cin >> user_napoveda;
    const char chr_user_napoveda = tolower(user_napoveda[0]);
    if (user_napoveda.size() > 1 || chr_user_napoveda == '-')
        return Napoveda::nic;
    if (chr_user_napoveda == pnp)
        return Napoveda::padesat_na_padesat;
    if (chr_user_napoveda == pub)
        return Napoveda::publikum;
    if (chr_user_napoveda == tel)
        return Napoveda::pritel_na_telefonu;
    return Napoveda::nic;
}

void fce_napoved(Napoveda napoveda, const char spravnaOdpoved) {
    if (napoveda == Napoveda::padesat_na_padesat) {
        u_Nap.padesat_na_padesat = true;
        listPadesatNaPadesat[0] = spravnaOdpoved - 'a';
        do {
            listPadesatNaPadesat[1] = rand() % 4;
        } while (listPadesatNaPadesat[0] == listPadesatNaPadesat[1]);
    }
    if (napoveda == Napoveda::publikum) {
        u_Nap.publikum = true;
        for (int i = 0; i < 4; i++)
            procentaPublika[i] = 255;
        if (u_Nap.padesat_na_padesat) {
            int cislo1 = rand() % 51;
            int cislo2 = 100 - cislo1;
            procentaPublika[listPadesatNaPadesat[0]] = cislo1;
            procentaPublika[listPadesatNaPadesat[1]] = cislo2;
        } else {
            int cislo1 = rand() % 26;
            int cislo2 = rand() % 26;
            int cislo3 = rand() % 26;
            int cislo4 = 100 - (cislo1+cislo2+cislo3);
            procentaPublika[0] = cislo1;
            procentaPublika[1] = cislo2;
            procentaPublika[2] = cislo3;
            procentaPublika[3] = cislo4;
        }
        cout << "Diváci v sále hlasují, počkejte prosím..." << endl;
        this_thread::sleep_for(chrono::milliseconds(8000));
    }
    if (napoveda == Napoveda::pritel_na_telefonu)
        u_Nap.pritel_na_telefonu = true;
}

bool otazky(int index) {
    auto otazka = listOtazek[index];
    if (u_Nap.publikum)
        divaci_hlasovani();
    cout << otazka.returnOtazka() << endl << endl;
    this_thread::sleep_for(chrono::milliseconds(2000));

    otazka.printOdpovedi();
    string user_odpoved;
    cin >> user_odpoved;
    const char chr_user_odpoved = tolower(user_odpoved[0]);

    if (user_odpoved.size() > 1 || chr_user_odpoved != 'a' && chr_user_odpoved != 'b' && chr_user_odpoved != 'c' && chr_user_odpoved != 'd' && chr_user_odpoved != 'n') {
        cout << "Špatné zadání!" << endl;
        return otazky(index);
    }
    if (chr_user_odpoved == 'n') {
        Napoveda napoveda = vyber_napoved();
        if (napoveda == Napoveda::nic) {
            cout << "Špatné zadání!" << endl;
            return otazky(index);
        }
        if (napoveda == Napoveda::padesat_na_padesat) {
            cout << "Padesát na padesát!"<< endl;
            s_Nap.padesat_na_padesat = false;
        }
        if (napoveda == Napoveda::publikum) {
            cout << "Hlasování publika!" << endl;
            s_Nap.publikum = false;
        }
        if (napoveda == Napoveda::pritel_na_telefonu) {
            cout << "Přítel na telefonu!" << endl;
            s_Nap.pritel_na_telefonu = false;
        }
        fce_napoved(napoveda, otazka.returnSpravnaOdpoved());
        return otazky(index);
    }
    u_Nap.padesat_na_padesat = false;
    u_Nap.publikum = false;
    u_Nap.pritel_na_telefonu = false;

    return chr_user_odpoved == otazka.returnSpravnaOdpoved();
}

int main() {
    srand(time(0));
    #ifndef NO_SFML
    sf::Music music;
    music.setLoop(true);
    sf::SoundBuffer buffer;
    sf::Sound sound;
    sound.setBuffer(buffer);
    // Intro WIP
    // music.openFromFile("songy/chcete být c++ářem znělka.ogg"))

    music.openFromFile("songy/chcete být c++ářem první otázky.ogg");
    music.play();
    #endif
    bool vyhra = true;
    for (int i = 0; i < POCET_OTAZEK; i++) {
        #ifndef NO_SFML
        if (i > 4) {
            music.openFromFile("songy/chcete být c++ářem otázka " + to_string(i + 1) + (string)".ogg");
            music.play();
        }
        buffer.loadFromFile("songy/začátek otázky.ogg");
        sound.play();
        #endif

        cout <<  i + 1 << ". otázka:" << endl;
        this_thread::sleep_for(chrono::milliseconds(2000));
        if (not otazky(i)) {
            this_thread::sleep_for(chrono::milliseconds(1200));
            #ifndef NO_SFML
            music.openFromFile("songy/chcete být c++ářem prohra.ogg");
            music.play();
            #endif
            cout << "Je mi líto, ale toto byla špatná odpověď." << endl;
            this_thread::sleep_for(chrono::milliseconds(2000));
            cout << "Zabijí vás agenti KGB!" << endl;
            this_thread::sleep_for(chrono::milliseconds(5500));
            vyhra = false;
            break;
        }

        #ifndef NO_SFML
        buffer.loadFromFile("songy/správná odpověď.ogg");
        #endif
        this_thread::sleep_for(chrono::milliseconds(1500));
        cout << "Ano správně, je to tak!" << endl << endl;
        #ifndef NO_SFML
        sound.play();
        #endif
        this_thread::sleep_for(chrono::milliseconds(2000));
    }

    if (vyhra) {
        #ifndef NO_SFML
        music.openFromFile("songy/chcete být c++ářem výhra.ogg");
        music.play();
        #endif
        cout << "Právě jste vyhrál hru chcete být c++ářem, GRATULUJEME!!!" << endl;
        this_thread::sleep_for(chrono::milliseconds(23000));
    }
}
