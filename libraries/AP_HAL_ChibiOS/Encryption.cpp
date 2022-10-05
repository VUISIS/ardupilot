#include "Encryption.h"

#include <hal.h>
#include <hal_crypto.h>

namespace ChibiOS 
{
    Encryption::Encryption() : _byteKey(new uint8_t[32] {0x2B, 0xED, 0x6F, 0x9B, 0xE8, 0x0B, 0x26, 0xA6, 0x11, 0xDB, 0x63, 0x92, 0xC4, 0x79, 0x6B, 0x95, 
                                                         0x35, 0x05, 0x16, 0x36, 0x17, 0xEF, 0xB7, 0x92, 0x63, 0x9B, 0xFA, 0x14, 0x0C, 0xCE, 0xDF, 0x02}),
                               _byteIV(new uint8_t[16] {0x0A, 0x82, 0x34, 0x63, 0x2F, 0x3D, 0x2E, 0x45, 0x42, 0xFE, 0x26, 0x90, 0xCD, 0xB6, 0x4B, 0xA3}),
                               _driver(new CRYDriver())
    {
        const CRYConfig config_Polling;

        cryInit();

        cryStart(&_driver, &config_Polling);

        cryerror_t ret = cryLoadAESTransientKey(_driver, 32, _byteKey);

        if(ret != CRY_NOERROR)
        {
            osalDbgAssert(ret, "Crypto loading key failed.");
        }
    }

    Encryption::~Encryption()
    {
        cryStop(_driver);
        delete _driver;
        delete[] _byteKey;
        delete[] _byteIV;
    }

    uint8_t* Encryption::encrypt(const uint8_t* msg, size_t size)
    {
        uint8_t* encoded_msg = new uint8_t[sizeof(msg)];

        cryerror_t ret = cryEncryptAES_CBC(_driver, 0, size, msg, encoded_msg, _byteIV);

        if(ret != CRY_NOERROR)
        {
            osalDbgAssert(ret, "Crypto failed encrypting message.");
        }

        return encoded_msg;
    }

    uint8_t* Encryption::decrypt(const uint8_t* msg, size_t size)
    {
        uint8_t* decoded_msg = new uint8_t[sizeof(msg)];

        cryerror_t ret = cryDecryptAES_CBC(_driver, 0, size, msg, decoded_msg, _byteIV);

        if(ret != CRY_NOERROR)
        {
            osalDbgAssert(ret, "Crypto failed decrypting message.");
        }

        return decoded_msg;
    }
}