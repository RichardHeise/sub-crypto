#include "utils.cpp"
using namespace std;

string encrypt(string txt) {
    string chave("criptografia");
    string encr_txt;

    printf("%d", 'á');
    for (int i = 0; i < txt.length(); i++) {
        encr_txt.push_back((txt[i] + chave[i % chave.length()]) % 127);
    }
    encr_txt.push_back('\n');

    cout << encr_txt << endl;
    return encr_txt;
}

int main() {
    printf("Hello, I'm an encrypter :D\n");
    printf("Waiting for text to ENCRYPT via stdin, output on stdout\n");

    string input;
    string encrypted_text;

    cin >> input;

    encrypted_text = encrypt(input);

    cout << encrypted_text << endl;

    return 0;
}