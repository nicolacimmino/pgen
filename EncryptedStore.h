#ifndef __PGEN__ENCRYPTED_STORE_H__
#define __PGEN__ENCRYPTED_STORE_H__

#include "Arduino.h"
#include "aes256_ctr.h"
#include "NoiseSource.h"
#include <EEPROM.h>

#define ENCRYPTED_STORE_KEY_SIZE 32
#define ENCRYPTED_STORE_IV_SIZE 16
#define ENCRYPTED_STORE_DATA_SIZE 64

class EncryptedStore
{
private:
    byte key[ENCRYPTED_STORE_KEY_SIZE];
    byte iv[ENCRYPTED_STORE_IV_SIZE];
    void generateIV();    
    
    struct EncryptedEntry
    {
        byte iv[ENCRYPTED_STORE_IV_SIZE];
        byte cipher[ENCRYPTED_STORE_DATA_SIZE];        
    };

public:
    void init(byte *key);
    void get(byte index, char *plainText);
    void set(byte index, char *plainText);
};

#endif
