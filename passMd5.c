#include <openssl/md5.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#define CRYPT_LEN 30

unsigned int crypted[CRYPT_LEN] = {
  0x000003c8, 0x00000032, 0x000002ce, 0x00000302, 0x0000007f, 
  0x000001b8, 0x0000037e, 0x00000188, 0x00000349, 0x0000027f, 
  0x0000005e, 0x00000234, 0x00000354, 0x000001a3, 0x00000096, 
  0x00000340, 0x00000128, 0x000002fc, 0x00000300, 0x0000028e, 
  0x00000126, 0x0000001b, 0x0000032a, 0x000002f5, 0x0000015f, 
  0x00000368, 0x000001eb, 0x00000079, 0x0000011d, 0x0000024e, 
   };

int main(int argv,char *argc[])
{
	int i;
	unsigned char hash[20];
	unsigned char answer[64];
	int m;
	//all possible XORed totals
	for(m=0;m<=0xffff;m++)
	{
		MD5_CTX ctx;
		MD5_Init(&ctx);

		srand(m);
		//crypted[] length
		for(i=0;i<=CRYPT_LEN-1;i++)
		{
			void *data=(void*)malloc(sizeof(char)*16);
			int64_t x = rand();
		
	
			//emulate imul edx/eax
				int64_t y = x*0x10624dd3; 
				int32_t edx = (y>>32);
				int32_t eax = y&0x00000000ffffffff;
			
			
			int signBit = edx & 0x80000000;
			edx=(edx>>6) | signBit; //shift and preserve Sign bit
	
			signBit = x & 0x80000000;
			int q=x>>0x1f | signBit; //ditto..
			int k=edx-q;
			k=k*1000;
			unsigned int g = x - k;
			answer[i]=crypted[i]^g;
			sprintf(data,"%d",g);
			int len = strlen(data); 
			MD5_Update(&ctx, data, len);
		}
	MD5_Final(hash,&ctx);
	unsigned char *b=(unsigned char*)malloc(sizeof(unsigned char)*32);
	//hash hex to string
	for(i=0;i<=0xf;i++)
	{
		sprintf((b+i*2),"%02x",hash[i]);

	}
	
	if(!strcmp(b,"5eba99aff105c9ff6a1a913e343fec67"))
		printf("%s:%s\n",answer, b);

	}
}
