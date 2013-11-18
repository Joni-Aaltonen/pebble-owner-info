pebble-owner-info
=================

Add's an application called "Owner Info" to your device.
The application shows the contact information of the user.

**Notes** 
* Contact info needs to be edited in src/owner_info.c before building
* QR Code containing the user's contact details needs to be replaced in

	```
	resources/images/qr_contact.png (size 144 x 154 px)
	```
	[QR Code generator](http://qrcode.littleidiot.be)
	

#Building

```
./waf configure
./waf build
python -m SimpleHTTPServer 8000
// Browse to your http://<computer_ip>:8000/build/pebble-owner-info.pbw to install
```

Note that you need to have the pebble SDK installed and configured first. [https://developer.getpebble.com/1/GettingStarted/MacOS/](See instructions here)
