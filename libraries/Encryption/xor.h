#include <string>

static void xor_crypto(char message[])
{
    char key = 'X';

    int len = strlen(message);
  
    for (int i = 0; i < len; i++)
    {
        message[i] = message[i] ^ key;
    }
}