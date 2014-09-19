SPI Readme

I added this line to my .bashrc file 
echo BB-SPI0-01 > /sys/devices/bone_capemgr.9/slots
yours may be bone_capemgr.8 
copy the dts file into your root and then run command below
dtc -O dtb -o BB-SPI0-01-00A0.dtbo -b 0 -@ BB-SPI0-01-00A0.dts
move the resulting .dtbo file into 
/lib/firmware
restart the BB. and then your ready to execute spi_test.  I shorted MOSI to MISO.  The program takes a
hexidecimal input from the command line and sends it out on MOSI and then prints out the data received
on MISO