void SendSMS(String smsNumber)
{  // for multiple number testing
  delay(250);
  GSMmodem.print("AT+CMGS=\"");
  GSMmodem.print(smsNumber);
  GSMmodem.println("\"");
  delay(500);
  GSMmodem.print("I am a Robot so why calling me...");
  GSMmodem.print("\n");
  GSMmodem.write(byte(26));
  delay(100);
  return;

} 
