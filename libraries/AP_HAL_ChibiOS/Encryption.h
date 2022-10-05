struct CRYDriver;

typedef unsigned char uint8_t;

namespace ChibiOS 
{
    class Encryption 
    {
        public:
            Encryption();
            ~Encryption();

            uint8_t* encrypt(const uint8_t* msg, size_t size);
            uint8_t* decrypt(const uint8_t* msg, size_t size);

        private:
            const uint8_t* _byteKey;

            const uint8_t* _byteIV;

            CRYDriver* _driver;
    };
}