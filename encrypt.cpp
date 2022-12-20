#include "utils.cpp"
using namespace std;

string encrypt(string plaintext, string key) {
  string ciphertext = "";

  // Make sure the key is at least as long as the plaintext
  while (key.length() < plaintext.length()) {
    key += key;
  }

  // Perform the one-time pad encryption
  for (int i = 0; i < plaintext.length(); i++) {
    int c = plaintext[i] ^ key[i];
    // If the result is not within the range of 32 to 126, add 95 until it is
    while (c < 32 || c > 126) {
      c += 95;
    }
    ciphertext += c;
  }

  return ciphertext;
}


int main() {
    printf("Hello, I'm an encrypter :D\n");
    printf("Waiting for text to ENCRYPT via stdin, output on stdout\n");

    string input;
    string encrypted_text;

    getline(cin, input);

    encrypted_text = encrypt(input, "key");

    cout << encrypted_text << endl;

    return 0;
}