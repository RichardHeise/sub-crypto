#include <iostream>
#include <locale>
#include <string>

using namespace std;

// The default key to use for the One-Time Pad algorithm
const string DEFAULT_KEY = "whatever";

// The polyalphabetic key to use for the polyalphabetic encryption (the first 26 hiragana characters)
const string POLYALPHABETIC_KEY = "ぁあぃいぅうぇえぉおかがきぎくぐけげこごさざし";

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
    encryptedMessage += message[i] ^ keyChar;
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
    char encryptedChar = messageChar ^ keyChar;
    encryptedMessage += encryptedChar;
  }

  return encryptedMessage;
}

int main()
{

  // The message to encrypt
  string message;
  getline(cin, message);

  // Encrypt the message using the One-Time Pad algorithm
  string encryptedMessage = encryptMessage(message);

  // Encrypt the message again using the polyalphabetic encryption
  encryptedMessage = encryptPolyalphabetically(encryptedMessage, POLYALPHABETIC_KEY);

  size_t bufferSize = mbstowcs(nullptr, encryptedMessage.c_str(), 0) + 1;
  wchar_t* buffer = new wchar_t[bufferSize];

  // Convert the string to a wstring and store it in the buffer
  mbstowcs(buffer, encryptedMessage.c_str(), bufferSize);

  // Print the encrypted message
  wcout << "Texto cifrado: " << buffer << endl;

    return 0;
}