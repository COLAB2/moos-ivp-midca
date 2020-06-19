# moos-ivp-midca 
Moos-ivp is currently not supported to work on windows.
Works best on Ubuntu.
Works fine on mac-os.

# Installation Instructions

1. Download MOOS from the website "http://oceanai.mit.edu/moos-ivp/pmwiki/pmwiki.php?n=Site.Download"
2. Navigate to the moos-ivp directory you recently downloaded, you will find seperate README files for the installation     instructions depending on the platform you are using. Please follow those instuctions and install moos-ivp.
3. Navigate to the moos-ivp directory, and clone the moos-ivp-midca directory.
   ```
   $ cd moos-ivp
   $ git clone https://github.com/COLAB2/moos-ivp-midca.git
   $ cd moos-ivp-midca
   $ git checkout moos_agda
   ```
4. Navigate to the moos-ivp-midca directory, you will find a README file follow the instruction to install moos-ivp-midca
5. Navigate to the moos-ivp/ivp/src directory, delete the folder named "uFldHazardSensor" and follow the instructions below
    ```
    $ cd moos-ivp/ivp/src
    $ git clone https://github.com/COLAB2/uFldHazardSensor.git
    ```
6. Install Zmq from the website http://zeromq.org/intro:get-the-software
7. In you bash_profile or bashrc please export the paths for moos-ivp/bin and moos-ivp/moos-ivp-midca/bin.


# Run the Demo
1. Run the mooos applications
    ```
    $ cd moos-ivp/moos-ivp-midca/missions/new
    $ ./clean.sh
    $ ./launch.sh
    ```
   A GUI Window will appear, please hit Deploy button.
   
   
 If there are any problems please feel free to contact "Sravya Kondrakunta" (kondrakunta.2@wright.edu).


