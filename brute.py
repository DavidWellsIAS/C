from random import randint
flag=False
while(flag is False):
        x=[]
        for i in range(0,10):
                x.append(randint(16,0xffff))

        xORval=0
        for i in x:
                xORval=xORval^i

        cnt=0;
        while(xORval!=0):
                tmp = xORval-1
                xORval = tmp & xORval
                cnt=cnt+1
        if(cnt==10):
                print x
                flag=True

