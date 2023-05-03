#include <stdio.h>
#include <string.h>
#define ull unsigned long long int
#define ul unsigned long int
#include<math.h>


unsigned int SBox(unsigned int b) //Feistel Network with roundfunction f(x)=S(x+k), where S(x)=(x+1)%16;
{
    static unsigned int s[16];
    for (int i =0; i<16;i++)
    {
        s[i] = (i+1)% 16;
    }
    return s[b];
}

/*void bin(unsigned n)
{
    unsigned i;
    for (i = 1 << 31; i > 0; i = i / 2)
        (n & i) ? printf("1") : printf("0");
}*/



ul RoundFunc(ul key, ul r)
{
    ul temp = key^r;
    unsigned i ;
    ul y=0;
    static ul output=0;
    for (int p=8;p>0;p--)
    {
        unsigned int b=0,sb;
        int j=3;
        for (i=1<<((4*p)-1); i>0;i=i/2)
        {
            if(j<0)
            {
                break;
            }
            if((temp&i)!=0)
            {
                b = b | 1<<j;
            }
            j--;
        }

        sb = SBox(b);
        y = y | sb<<((p-1)*4);
    }
    
    return y;

}


ull FeistelRound(ul k, ul l, ul r)
{
    printf("Encryption: \n\n");
    ul Newl,Newr;
    static ull NewString;
    Newl = r;
    Newr = l^RoundFunc(k,r);

    NewString = ((ull)Newl) << 32 | Newr;

    printf("\n");
    printf("Encrypted ciphertext: %llu \n",NewString);

    return NewString;
}

ull FeistelRoundInverse(ul k,ul l,ul r)
{
    ul Newl,Newr;
    ull NewString;
    Newr = l;
    Newl = r^RoundFunc(k,l);
    NewString = ((ull)Newl) << 32 | Newr;
    printf("\n\n");
    printf("Decrypted text: %llu\n",NewString);
    return NewString;
}


int main() 
{
    ull plaintext;
    ul key = 0;
    printf("\n");
    printf("Enter the 64 bit plaintext:\n");
    scanf("%llu",&plaintext);
    printf("Enter the 32 bit key:\n");
    scanf("%lu",&key);

    // Dividing plaintext into 2 parts each of 32 bit
    unsigned long int l0 = (unsigned long int)((plaintext >> 32));  // First 32 bits which is l0
    unsigned long int r0 = (unsigned long int)(plaintext); // Nextt 32 bits which is r0

    ull enc = FeistelRound(key,l0,r0);

    // Dividing the 64 bit encrypted ciphertext into 2 parts of 32 bits each
    unsigned long int l1 = (unsigned long int)((enc >> 32)); // First 32 bits which is l1
    unsigned long int r1 = (unsigned long int)(enc); // Next 32 bits which is r1

    FeistelRoundInverse(key,l1,r1);
    return 0;
}

// Note: The program is for 64 bit integers only.
