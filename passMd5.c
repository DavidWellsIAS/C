#include <openssl/md5.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argv,char *argc[])
{
	MD5_CTX ctx;
	MD5_Init(&ctx);
	int i;
	unsigned char hash[16];
	for(i=0;i<=0x1d;i++)
	{
		int xORval = atoi(argc[1]);
		char *data=(char*)malloc(sizeof(char)*16);
		srand(xORval);
		int x = rand();
		int y = x*0x10624dd3;
		int signBit = y & 0x10000000;
		y=(y>>6) | signBit; //shift and preserve Sign bit
		signBit = x & 0x10000000;
		int q=x>>0x1f | signBit; //ditto
		y=y-q;
		y=y*1000;
		x=x-y;	
		sprintf(data,"%d",y);
		int len=strlen(data); 
		MD5_Update(&ctx,data,len);
		
	}
	MD5_Final(hash,&ctx);
	for(i=0;i<=0xf;i++)
	{
		printf("%02x",hash[i]);
		
	}
}
