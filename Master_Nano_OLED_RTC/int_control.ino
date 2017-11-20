void int_control()
{
  Serial.println(slave_reads[SLAVE3][0]);
  if(slave_reads[0][0]>100 &&  device_ls[0][0]==0)
   {
    Tdevice[0]=1;
   device_ls[0][0]=1;
   }
   else if(slave_reads[0][0]<110 && device_ls[0][0]==1)
   {
    Tdevice[0]=0;
   device_ls[0][0]=1;
   }
   else
   device_ls[0][0]=0;
  }

