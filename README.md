This project uses an ATSAML10 microcontroller to communicate with an ESP 01S to get image data from a server to then upload via SPI to an E-paper display from Pervaise Displays.  

This is the current setup.  One comment to be made is that the PICKit doesn't supply enough power (limited to 150 mA assuming I read the manual correctly; in other words it wasn't working), so that's why I have a random dev board there
![thumbnail_1000000126](https://github.com/user-attachments/assets/1de35a19-0d15-4cdd-99b9-565199b78156)
The server application is a very short C# application that just listens for a TCP connection request.  
This readme will be updated more.
