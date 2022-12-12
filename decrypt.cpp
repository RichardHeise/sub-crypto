#include "utils.cpp"

using namespace std;

string decrypt(string text) {
    string encrypted_text = text;

    return encrypted_text;
}

int main() {
    printf("Hello, I'm a decrypter :D\n");
    printf("Waiting for text to DECRYPT via stdin, output on stdout\n");

    string input;
    string encr_txt;

    cin >> input;

    encr_txt = decrypt(input);

    cout << encr_txt << endl;

    return 0;
}