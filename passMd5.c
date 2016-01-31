#include <openssl/md5.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>

int64_t main(int argv,char *argc[])
{
	int i;
	unsigned char hash[20];
	int m;
	for(m=0;m<=0xffff;m++)
	{
		MD5_CTX ctx;
		MD5_Init(&ctx);

		srand(m);
		for(i=0;i<=0x1d;i++)
		{
			void *data=(void*)malloc(sizeof(char)*16);
			int x = rand();
			
			int64_t y = x*0x10624dd3; //@ 0x00400b73
			//emulate imul edx/eax
				int32_t edx = (y>>32);
				int32_t eax = y&0x00000000ffffffff;
			
			int signBit = edx & 0x80000000;
			edx=(edx>>6) | signBit; //shift and preserve Sign bit
	
			signBit = x & 0x80000000;
			int q=x>>0x1f | signBit; //ditto
			int k=edx-q;
			k=k*1000;
			int g = x - k;
			sprintf(data,"%d",g);
			int len = strlen(data); 
			MD5_Update(&ctx, data, len);
		}
	MD5_Final(hash,&ctx);
	unsigned char *b=(unsigned char*)malloc(sizeof(unsigned char)*32);
	
	for(i=0;i<=0xf;i++)
	{
		sprintf((b+i*2),"%02x",hash[i]);
	}
	printf("%s\n",b);
	}
}
