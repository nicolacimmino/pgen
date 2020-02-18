
//  Copyright (C) 2020 Nicola Cimmino
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//   This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see http://www.gnu.org/licenses/.
//

#include "EncryptedStore.h"
#include "EncryptedStoreKey.h"
#include "sha256.h"

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for Leonardo only
    }
    delay(500);
}

EncryptedStore encryptedStore;
EncryptedStoreKey encryptedStoreKey;

void loop()
{
    encryptedStoreKey.setMasterPassword("mysecuremasterpassword");

    char text[32] = "myzeropassword                                   ";

    encryptedStore.init(encryptedStoreKey.key);
    //encryptedStore.set(0, text);
    //encryptedStore.set(1, text);

    encryptedStore.get(0, text);

    for (int ix = 0; ix < 32; ix++)
    {
        Serial.print(text[ix]);
    }
    Serial.println(" ");

    encryptedStore.get(1, text);

    for (int ix = 0; ix < 32; ix++)
    {
        Serial.print(text[ix]);
    }
    Serial.println(" ");

    delay(1000);
}