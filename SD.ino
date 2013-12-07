int ListWP(void)
{
  //int Antall = -2;
  //int StringLength = RECORDSIZE;
  myFile = SD.open("test.txt");
  if (myFile) 
     {
        while (myFile.available())
        {
          chkLine = myFile.read();
          //Serial.print(chkLine);
          buf[0] = chkLine;
          //Serial.print(buf[0]); // debug
         if (chkLine =='\n') //break;
          {
            listWP++;
          }
        }
     } else
     {
     }
    //error("file.open");
    myFile.close();
    return (listWP);
   // return (buf[0]);
};

char WP(void)
{  
 // Serial.print("Store WP");
  //int Antall = -2;
  //int StringLength = RECORDSIZE;
  myFile = SD.open("test.txt");
  if (myFile) 
     {
        while (myFile.available())
        {
          chkLine = myFile.read();
          //Serial.print(chkLine);// debug line
         // for (int x=1; x <= listWP; x++)
         // {
          //Serial.print("Loading the array"); // debug
          buf[0]= chkLine;
          Serial.print(buf[0]); // debug
          if (chkLine =='\n') break;
          
          //Serial.print(buf); // debug
         //if (chkLine =='\n')// break;
        // Serial.print(buf[1]);
         // {
         //   listWP++;
         // }
        //}
        //Serial.println(buf[5]);
        }
       // Serial.print(buf[0]);
     } else
     {
     }
    //error("file.open");
    myFile.close();
    //Serial.print("wqewqeqwewqeqwqweqweqwe");
    //return (listWP);
    //Serial.print(buf[0]);
    return (buf[0]);
};
