// Caesar Cipher Encryption and Decryption
#include <stdio.h>
#include <string.h>
#include <ctype.h> // For isalpha, isupper, islower

// Function to encrypt a message using Caesar Cipher
void encryptCaesar(char text[], int key) {
    int i;
    for (i = 0; text[i] != '\0'; ++i) {
        char ch = text[i];

        // Encrypt uppercase letters
        if (isupper(ch)) {
            ch = (char)(((ch - 'A' + key) % 26) + 'A');
        }
        // Encrypt lowercase letters
        else if (islower(ch)) {
            ch = (char)(((ch - 'a' + key) % 26) + 'a');
        }
        // Non-alphabetic characters remain unchanged
        text[i] = ch;
    }
}

// Function to decrypt a message using Caesar Cipher
void decryptCaesar(char text[], int key) {
    int i;
    for (i = 0; text[i] != '\0'; ++i) {
        char ch = text[i];

        // Decrypt uppercase letters
        if (isupper(ch)) {
            ch = (char)(((ch - 'A' - key + 26) % 26) + 'A'); // Add 26 to handle negative results of (ch - 'A' - key)
        }
        // Decrypt lowercase letters
        else if (islower(ch)) {
            ch = (char)(((ch - 'a' - key + 26) % 26) + 'a'); // Add 26 for similar reasons
        }
        text[i] = ch;
    }
}

