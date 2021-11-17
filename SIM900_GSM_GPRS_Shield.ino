void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second

  mySerial.println("AT+CMGS=\"+2348057114467\"\r"); // Replace x with mobile number
  delay(1000);

  mySerial.print("Body Temperature: ");// The SMS text you want to send
  mySerial.print(mlx.readObjectTempC());
  mySerial.print(" , ");
  mySerial.print("ECG Values: ");
  mySerial.println(analogRead(A0));
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
