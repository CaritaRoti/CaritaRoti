/* Encyption
*
* Introductory exercise to strings, characters and program shut-downs in C++.
* Cmd line based program that asks user to input a string with 26 unique lowercase characters
* that will be used as an encryption key similar to Caesar cipher.
* After key creation, the user can input a string and the program will print the same 
* line using the encryption key.
*/

#include <iostream>
#include <cctype>

using namespace std;


/**
 * @brief check_if_lowercase checks if all the letters of a given string are lowercase anglican letters
 * @param str string to be checked
 * @return True if all lowercase, False if non-lowercase found
 */
bool check_if_lowercase(string str) {
    for (char c : str) {
        if (!islower(c)) {
            return false;
        }
    }
    return true;
}


/**
 * @brief check_key_validity checks if an encryption key is valid (all anglican lowercase, 
 * with 26 non-duplicate letters only)
 * @param key key to be checked
 * @return True if valid, False if invalid
 */
bool check_key_validity(string key) {
    // key length
    if (key.length() != 26) {
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return false;
    }

    // lowercase anglican alphabet
    if (!check_if_lowercase(key)) {
        cout << "Error! The encryption key must contain lower case characters only." << endl;
        return false;
    }


    // contains all anglican letters = has no duplicate letters
    for (string::size_type i = 0; i < key.length()-1; ++i)
        for (string::size_type j = i+1; j < key.length(); ++j)
            if (key[i] == key[j]) {
                cout << "Error! The encryption key must contain all alphabets a-z." << endl;
                return false;
            }
    return true;
}


/**
 * @brief encrypt encrypts a string
 * @param str string to be encrypted
 * @param key encryption key to be used
 * @return encrypted string
 */
string encrypt(string str, string key) {
    string encrypted_string = "";
    string alphabets = "abcdefghijklmnopqrstuvwxyz";
    for (char c : str) {
        for (string::size_type i = 0; i < alphabets.length(); ++i) {
            if (c == alphabets[i]) {
                encrypted_string += key[i];
            }
        }
    }
    return encrypted_string;
}


int main()
{
    string key;
    cout << "Enter the encryption key: (26 unique lowercase characters a-z, no spaces) ";
    cin >> key;

    if (!check_key_validity(key))
        return EXIT_FAILURE;

    string text_to_be_encrypted;
    cout << "Enter the text to be encrypted: (lowercase letters only)";
    cin >> text_to_be_encrypted;

    if (!check_if_lowercase(text_to_be_encrypted)) {
        cout << "Error! The encryption key must contain only lowercase characters." << endl;
        return EXIT_FAILURE;
    }

    string encrypted_text = encrypt(text_to_be_encrypted, key);
    cout << "Encrypted text: " << encrypted_text << endl;

    return 0;
}
