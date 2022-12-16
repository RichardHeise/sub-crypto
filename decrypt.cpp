#include <iostream>
#include <locale>
#include <string>
#include <cmath>

using namespace std;

// The default key to use for the One-Time Pad algorithm
const string DEFAULT_KEY = "whatever";

// The polyalphabetic key to use for the polyalphabetic encryption (the first 26 hiragana characters)
const string POLYALPHABETIC_KEY = "ぁあぃいぅうぇえぉおかがきぎくぐけげこごさざし";

string removeAccentuations(string str)
{
    locale loc("");
    string result;

    for (auto ch : str)
    {
        result += tolower(ch, loc);
    }

    return result;
}


// The function that encrypts a message using the One-Time Pad algorithm
string encryptMessage(const string& message, const string& key = DEFAULT_KEY)
{
  // Set the global locale to Unicode-8
  locale::global(locale("pt_BR.UTF-8"));

  // Use the One-Time Pad algorithm to encrypt the message
  string encryptedMessage = "";
  for (size_t i = 0; i < message.length(); ++i)
  {
    char keyChar = key[i % key.length()];
    unsigned char messageChar = message[i];
    encryptedMessage += (int)(fmod(message[i] ^ keyChar, 233)) + 32;
  }

  return encryptedMessage;
}

// The function that encrypts a message using a polyalphabetic encryption
string encryptPolyalphabetically(const string& message, const string& key)
{
  // Set the global locale to Unicode-8
  locale::global(locale("pt_BR.UTF-8"));

  // Use the polyalphabetic encryption to encrypt the message
  string encryptedMessage = "";
  for (size_t i = 0; i < message.length(); ++i)
  {
    char keyChar = key[i % key.length()];
    char messageChar = message[i];
    unsigned char encryptedChar = ((messageChar ^ keyChar) % 233) + 32;
    printf("%d\n", encryptedChar);
    encryptedMessage += encryptedChar;
  }

  return encryptedMessage;
}

int main()
{

  // The message to encrypt
  string message;
  getline(cin, message);
  message = removeAccentuations(message);

  // Encrypt the message using the One-Time Pad algorithm
  string encryptedMessage = encryptMessage(message);

  // Encrypt the message again using the polyalphabetic encryption
  // encryptedMessage = encryptPolyalphabetically(encryptedMessage, POLYALPHABETIC_KEY);

  for (int i = 0; i < encryptedMessage.length(); i++)
    printf("%d\n", encryptedMessage[i]);
  // Print the encrypted message
  cout << "Texto cifrado: " << encryptedMessage << endl;

    return 0;
}