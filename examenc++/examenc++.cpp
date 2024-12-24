#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <iomanip>



using namespace std;
// Функция для шифрования и дешифрования слов с использованием XOR с ключом
void encryptDecrypt(string& text, char key) {
    for (char& c : text) {
        c ^= key;
    }
}
// Функция для чтения слов из зашифрованного файла
vector<string> loadWords(const string& filename, char key) {
    ifstream file(filename);
    vector<string> words;
    string word;

    if (file.is_open()) {
        while (getline(file, word)) {
			encryptDecrypt(word, key); // Дешифрация слова
            words.push_back(word);
        }
        file.close();
    }
    else {
        cerr << "Ne udalos otkrit file: " << filename << endl;
    }
    return words;
}
// Функция для выбора случайного слова
string chooseWord(const vector<string>& words) {
    srand(static_cast<unsigned>(time(0)));
    return words[rand() % words.size()];
}
// Основной игровой процесс с использованием char для хранения одного символа (управляющего или печатного) в определённой кодировке
void playGame(const string& word) {
    string guessedWord(word.size(), '_');
    int mistakes = 0;
    vector<char> guessedLetters;
    const int maxMistakes = 6;
                                               
    cout << "Dobro pozhalovat v igru \"Viselis\"!" << endl;

    while (guessedWord != word && mistakes < maxMistakes) {
        cout << "\nTekushee slovo: " << guessedWord << endl;
        cout << "Oshibki: " << mistakes << " iz " << maxMistakes << endl;
        cout << "Ispolzovannie bukvi: ";
        for (char c : guessedLetters) cout << c << " ";
        cout << "\n Vvedi bukvu: ";

        char guess;
        cin >> guess;
        // Проверка на повторное введение буквы               
        if (find(guessedLetters.begin(), guessedLetters.end(), guess) != guessedLetters.end()) {
            cout << "Ti uzhe vvodil etu bukvu." << endl;
            continue;
        }
        guessedLetters.push_back(guess);
        // Проверка есть ли буква в слове
        bool found = false;
        for (size_t i = 0; i < word.size(); i++) {
            if (word[i] == guess) {
                guessedWord[i] = guess;
                found = true;
            }
        }
        if (!found) {
            mistakes++;
            cout << "Nepravilnyi bukva!" << endl;
        }
        else {
            cout << "pravilnyi bukva!" << endl;
        }
    }
            
    if (guessedWord == word) {
        cout << "\nPozdravlayem! Ti ugadal slovo: " << word << endl;
    }
    else {
        cout << "\nTi proigral! slovo bilo: " << word << endl;
    }
    cout << "kolichestvo oshibok: " << mistakes << endl;
}
// Функция для создания зашифрованного файла слов
void createEncryptedFile(const string& filename, const vector<string>& words, char key) {
    ofstream file(filename);
    if (file.is_open()) {
        for (string word : words) {
            encryptDecrypt(word, key); // зашифрованный слово
            file << word << endl;
        }
        file.close();
        cout << "file " << filename << " uspeshno sozdano!" << endl;
    }
    else {
        cerr << "ne udalos sozdat file: " << filename << endl;
    }
}

int main() {
    const string filename = "words.txt";
    const char encryptionKey = 'X'; // Ключ шифрования

    // наш зашифрованный файл слов 
    vector<string> wordList = { "apple", "banana", "cherry", "grape", "orange" };
    createEncryptedFile(filename, wordList, encryptionKey);

    // из зашифрованного файла грузим слова которые та зашифрованы
    vector<string> words = loadWords(filename, encryptionKey);
    if (words.empty()) {
        cerr << "spisok slov pust, zavershenie programmy." << endl;
        return 1;
    }
    // Выбирается случайное слово и запускается игра
    string word = chooseWord(words);
    playGame(word);

    return 0;
}s