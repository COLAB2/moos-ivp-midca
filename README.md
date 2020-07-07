# moos-ivp-midca 
Moos-ivp is currently not supported to work on windows.
Works best on Ubuntu.
Works fine on mac-os.

# Installation Instructions
1. Download MOOS using the following link:
```
   $ svn co https://oceanai.mit.edu/svn/moos-ivp-aro/releases/moos-ivp-17.7 moos-ivp
```
2. Navigate to the moos-ivp directory you recently downloaded, you will find seperate README files for the installation     instructions depending on the platform you are using. Please follow those instuctions and install moos-ivp.
3. Navigate to the moos-ivp directory, and clone the moos-ivp-midca directory.
   ```
   $ cd moos-ivp
   $ git clone https://github.com/COLAB2/moos-ivp-midca.git
   $ cd moos-ivp-midca
   $ git checkout moos_agda
   ```
4. Navigate to the moos-ivp-midca directory, you will find a README file follow the instruction to install moos-ivp-midca
5. Navigate to the moos-ivp/ivp/src directory, delete the folder named "uFldHazardSensor" (follow the instructions below)
    ```
    $ cd moos-ivp/ivp/src
    $ sudo rm -rf uFldHazardSensor
    $ git clone https://github.com/COLAB2/uFldHazardSensor.git
    # go to the moos-ivp folder and build moos by following the bellow commands
    $ cd moos-ivp
    $ ./build-ivp.sh
    ```
6. Navigate to the moos-ivp/ivp/src directory, delete the folder named "uFldHazardMgr" (follow the instructions below)
    ```
    $ cd moos-ivp/ivp/src
    $ sudo rm -rf uFldHazardMgr
    $ git clone https://github.com/COLAB2/uFldHazardMgr.git
    # go to the moos-ivp folder and build moos by following the bellow commands
    $ cd moos-ivp
    $ ./build-ivp.sh
    ```
7. Install Zmq from the website http://zeromq.org/intro:get-the-software as well as pyzmq using pip
8. In you bash_profile or bashrc please export the paths for moos-ivp/bin and moos-ivp/moos-ivp-midca/bin and moos-ivp/moos-ivp-midca/scripts
   ```
   $ sudo nano ~/.bashrc
   export PATH="/home/sampath/moos-ivp/bin:$PATH"
   export PATH="/home/sampath/moos-ivp/moos-ivp-midca/bin:$PATH"
   export PATH="/home/sampath/moos-ivp/moos-ivp-midca/scripts:$PATH"
   ```


# Run the Demo
1. Run the mooos applications
    ```
    $ cd moos-ivp/moos-ivp-midca/missions/agda
    $ ./clean.sh
    # please change line 11 in the script experiment.sh to the path where your python program is (world.py)
    $ ./experiment.sh
    ```
   
   
 If there are any problems please feel free to contact "Sravya Kondrakunta" (kondrakunta.2@wright.edu).


