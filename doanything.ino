void doAnything(){

        GSMmodem.println("ATH");
        if(lastline.substring(8,15)=="7906608"){
          //GSMmodem.println("ATA");
          ledStatus=1;
          smsNumber = lastline.substring(8,15);
          SendSMS(smsNumber);
        }else {
          //GSMmodem.println("ATH");
          ledStatus=0;
          }
  
}
       
