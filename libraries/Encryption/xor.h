static void xor_crypto(char message[], int len)
{
    char key = 'X';
  
    for (int i = 0; i < len; i++)
    {
        message[i] = message[i] ^ key;
    }
}