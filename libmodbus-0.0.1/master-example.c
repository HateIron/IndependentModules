#include <modbus.h>

/* compiling : gcc master-example.c -o master-example -lmodbus */

int main()
{
   int device;
   Mbm_trame trame;
   int result;
   int data_in[256];
   int data_out[256];

   /* open device */
   device=Mb_open_device("/dev/ttyS0",9600,0,8,1);

   /* print debugging informations */
   Mb_verbose=1;
   
   /* setup master packet */
   trame.device=device;
   trame.function=16;			/* send data */
   trame.slave=1;					/* slave number*/ 
   trame.address=0xb000;
   trame.length=8;
   trame.timeout=1000;
   
   /* setup data to send */
   data_in[0]=1;
   data_in[1]=2;
   data_in[2]=3;
   data_in[3]=4;
   data_in[4]=5;
   data_in[5]=5;
   data_in[6]=5;
   data_in[7]=5;
   data_in[8]=5;
   result=Mb_master(trame,data_in,data_out,NULL,NULL);
   /* return 0 if ok */
   if (result<0)
   {
      if (result==-1) printf("error : unknow function\n");
      if (result==-2) printf("crc error\n");
      if (result==-3) printf("timeout error\n");
      if (result==-4) printf("error : bad slave answer\n");
   }
   else
      printf("ok\n");
   Mb_close_device(device);

   return 0;
}

