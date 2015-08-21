# crelay
#### Controlling different relay cards for home automation with a Linux software

### About
This software is intended to run on Linux systems to control different relay cards in a unified way. It provides several interfaces for controlling the relays locally or remotely. The relays can be controlled by a human being via a device like smartphone or web browser, or directly by an intelligent device as used in the Internet of Things.  
The software was designed with the following requirements in mind:  

 - simple, intuitive usage and interface
 - as little dependencies as possible (libraries, external programs)
 - runs on different Linux distributions, different hardware platforms
 - lightweight, can run on simple devices
 - easily expandable (adding relay card types and user interfaces)

New relay cards support can be added by providing the cards driver code for detecting the card, reading and setting the relays.
Currently the following relay cards are supported:  

- Conrad USB 4-channel relay card (http://www.conrad.de/ce/de/product/393905), see <i>Note 1</i> below
- Sainsmart USB 4-channel relay card (http://www.sainsmart.com/sainsmart-4-channel-5v-usb-relay-board-module-controller-for-automation-robotics.html), see <i>Note 2</i> below
- HID API compatible relay cards (1/2/4/8 channel)
- Generic GPIO controlled relays, see <i>Note 3</i> below  
<br>

The following picture shows a high level view on the modular software architecture.  
![Software architechture](screenshots/sw-architecture.png)
<br><br>

### Features
- Command line mode and daemon mode with Web GUI
- Automatic detection of relay card
- Reading of current relay states
- Setting of new relay states
- Single pulse generation on relay contact
- HTTP API for external clients (e.g. Smartphone/tablet apps)
- Multiple relay card type support  
- Support for configuration file with custom parameters
<br>

### Nice to have (wishlist)
- ThingSpeak Talkback App (https://thingspeak.com/docs/talkback)
- Multiple cards support
- Access control for Web GUI and HTTP API
- Programmable timers for relay actions  
<br>

### Screenshots

#### Web GUI
![Screenshot](screenshots/crelay-screenshot1.png)
<br><br>
![Screenshot](screenshots/crelay-screenshot2.png)
<br><br>

#### Command line interface
    $ crelay 
    crelay, version 0.9
    
    This utility provides a unified way of controlling different types of relay cards.
    Currently supported relay cards:
      - Conrad USB 4-channel relay card
      - Sainsmart USB 4-channel relay card
      - Generic GPIO relays
      - HID API compatible relay card
    The card which is detected first will be used. 
    
    The program can be run in interactive (command line) mode or in daemon mode with
    built-in web server.

    Interactive mode:
        crelay -i | [<relay number>] [ON|OFF]

           The state of any relay can be read or it can be changed to a new state.
           If only the relay number is provided then the current state is returned,
           otherwise the relays state is set to the new value provided as second parameter.
           The USB communication port is auto detected. The first compatible device
           found will be used.

    Daemon mode:
        crelay -d [<relay1_label> [<relay2_label> [<relay3_label> [<relay4_label>]]]] 
    
           In daemon mode the built-in web server will be started and the relays
           can be completely controlled via a Web browser GUI or HTTP API.
           Optionally a personal label for each relay can be supplied which will
           be displayed next to the relay name on the web page.
    
           To access the web interface point your Web browser to the following address:
           http://<my-ip-address>:8000
    
           To use the HTTP API send a POST or GET request from the client to this URL:
           http://<my-ip-address>:8000/gpio
<br>  

### HTTP API
An HTTP API is provided to access the server from external clients. This API is compatible with the PiRelay Android app. Therefore this app can be used on your Android phone to control <i>crelay</i> remotely.

- API url:  
<pre><i>ip_address[:port]</i>/gpio</pre>  

- Method:  
<pre>POST or GET</pre>  

- Reading relay states  
Required Parameter: none  

- Setting relay state  
Required Parameter: <pre>pin=[1|2|3|4], status=[0|1|2] where 0=off 1=on 2=pulse</pre>  

- Response from server:  
<pre>
Relay 1:[0|1]
Relay 2:[0|1]
Relay 3:[0|1]
Relay 4:[0|1]
</pre>  
<br>

### Installation from source
The installation procedure is usually perfomed directly on the target system. Therefore a C compiler and friends should already be installed. Otherwise a cross compilation environment needs to be setup on a PC (this is not described here).  

* Install dependencies (package names may vary depending on your distribution):
<pre>
    apt-get install libftdi1 libftdi-dev libhidapi-libusb0 libhidapi-dev libusb-1.0-0 libusb-1.0-0-dev
</pre>

* Build dependencies from source (optional):  
On some not so recent Linux distributions (like Debian Weezy) the HIDAPI library is not yet packaged, so it needs to be build from the source code. Follow these instructions to do that:
<pre>
    apt-get install libudev-dev libusb-1.0-0-dev
    git clone git://github.com/signal11/hidapi.git
    ./bootstrap
    ./configure
    make
    sudo make install
</pre>

* Clone crelay git repository :  
<pre>
    git clone https://github.com/ondrej1024/crelay
    cd crelay
</pre>

* Alternatively get latest source code version :  
<pre>
    wget https://github.com/ondrej1024/crelay/archive/master.zip
    unzip master.zip
    cd crelay-master
</pre>

* Build and install :  
<pre>
    cd src
    make [DRV_CONRAD=n] [DRV_SAINSMART=n] [DRV_HIDAPI=n]
    sudo make install
</pre>
<i>Note:</i> Optionally, you can exclude specific relay card drivers (and their dependencies) from the build, if you don't need them. To do this, specify the driver name as parameter of the "make" command as shown above.
<br>

### Installation of prebuilt binaries
To save you the hassle of building crelay from source, prebuild binaries are provided for selected architectures. Just save the binary from the bin/<arch> directory on your host system and execute it.  

<i>Note:</i> The binaries use shared librabries, so you might need to install the needed libs to your system, if not already done previously:  
<pre>
    apt-get install libftdi1 libhidapi-libusb0 libusb-1.0-0
</pre>  

### Configuration
The parameters for *crelay* can be customized via the configuration file crelay.conf which should be placed in the `/etc/` system folder. An example file is provided together with the programs source code in the `conf/` folder.

<pre>
################################################
#
# crelay config file
#
# This file is read by crelay in daemon mode
# from /etc/crelay.conf
#
################################################

# HTTP server parameters
################################################
[HTTP server]
server_iface = 0.0.0.0    # listen interface IP address
#server_iface = 127.0.0.1 # to listen on localhost only
server_port  = 8000       # listen port
relay1_label = Device 1   # label for relay 1
relay2_label = Device 2   # label for relay 2
relay3_label = Device 3   # label for relay 3
relay4_label = Device 4   # label for relay 4
relay5_label = Device 5   # label for relay 5
relay6_label = Device 6   # label for relay 6
relay7_label = Device 7   # label for relay 7
relay8_label = Device 8   # label for relay 8
    
# GPIO driver parameters
################################################
[GPIO drv]
#num_relays = 8    # Number of GPIOs connected to relays (1 to 8)
#relay1_gpio_pin = 17   # GPIO pin for relay 1 (17 for RPi GPIO0)
#relay2_gpio_pin = 18   # GPIO pin for relay 2 (18 for RPi GPIO1)
#relay3_gpio_pin = 27   # GPIO pin for relay 3 (27 for RPi GPIO2)
#relay4_gpio_pin = 22   # GPIO pin for relay 4 (22 for RPi GPIO3)
#relay5_gpio_pin = 23   # GPIO pin for relay 5 (23 for RPi GPIO4)
#relay6_gpio_pin = 24   # GPIO pin for relay 6 (24 for RPi GPIO5)
#relay7_gpio_pin = 25   # GPIO pin for relay 7 (25 for RPi GPIO6)
#relay8_gpio_pin = 4    # GPIO pin for relay 8 ( 4 for RPi GPIO7)
    
# Sainsmart driver parameters
################################################
[Sainsmart drv]
num_relays = 4   # Number of relays on the Sainsmart card (4 or 8)
</pre>

<br>
  
### Adding new relay card drivers
The modular architecture of *crelay* makes it possible to easily add new relay card drivers.  
See example files `relay_drv_sample.c` and `relay_drv_sample.h` in the src directory for details on how to write your own low level driver functions.  
<br>  

##### <i>Note 1 (Conrad USB 4-channel relay card)</i>:
The relay card software provided by Conrad is Windows only and uses a binary runtime DLL which implements the communication protocol between the host computer and the card. Thanks to a raspberrypi.org forum member, the communication protocol was discovered and made public. This made it possible to develop an open source driver for the Conrad card which can run on any Linux distribution.

Earlier versions of this program needed the cp210x kernel driver for the Silabs CP2104 chip with GPIO support. The official in-kernel cp210x driver does not  support GPIO operations. Therefore the Silabs driver from their home page needed to be used:
http://www.silabs.com/products/mcu/pages/usbtouartbridgevcpdrivers.aspx

The current version of *crelay* uses libusb to talk directly to the CP2104 on the Conrad card, therefore the cp210x kernel driver is **not needed** anymore.
<br>  

##### <i>Note 2 (Sainsmart USB 4-channel relay card)</i>:
The Sainsmart card uses the FTDI FT245RL chip. This chip is controlled directly through the open source libFTDI library. No Kernel driver is needed. However on most Linux distributions, the *ftdi_sio* serial driver is automatically loaded when the FT245RL chip is detected. In order to grant the <i>crelay</i> software access to the card, the default driver needs to be unloaded:  

    rmmod ftdi_sio

To prevent automatic loading of the driver, add the following line to /etc/modprobe.d/blacklist.conf:  

    blacklist ftdi_sio
    
<br>  

##### <i>Note 3 (GPIO controlled relays)</i>:
Since GPIO pin configuration is strictly device specific, the generic GPIO mode is disabled by default and can only be used in daemon mode. In order to enable it, the specific GPIO pins used as relay control lines have to be specified in the configuration file, `[GPIO drv]` section.
