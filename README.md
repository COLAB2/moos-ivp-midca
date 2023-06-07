# moos-ivp-midca 
Moos-ivp is currently not supported to work on windows.
Works best on Ubuntu.
Works fine on mac-os.

# Installation Instructions
1. Download MOOS using the following link:
```
   $ svn co https://oceanai.mit.edu/svn/moos-ivp-aro/releases/moos-ivp-17.7 moos-ivp
```
2. Navigate to the moos-ivp directory you recently downloaded, you will find seperate README files for the installation instructions depending on the platform you are using. Please follow those instuctions and install moos-ivp.

3. Install `cppzmq` using Macports
```
   $ sudo port install cppzmq
```

4. Navigate to the moos-ivp directory, and clone the moos-ivp-midca directory.
   ```
   $ cd moos-ivp
   $ git clone https://github.com/COLAB2/moos-ivp-midca.git
   $ cd moos-ivp-midca
   $ git checkout multi_agent
   $ mkdir lib
   ```
5. Navigate to the moos-ivp-midca directory, you will find a README file follow the instruction to install moos-ivp-midca. (NOTE: If you are building MOOS for the very first time, then must run commands from lines 47 - 51 in the README file.
   $ mkdir -p build
   $ cd build
   $ cmake ../
   $ make
   $ cd .. )

6. Navigate to the moos-ivp/ivp/src directory, delete the folders "uFldHazardSensor" (follow the instructions below)
    ```
    $ cd moos-ivp/ivp/src
    $ sudo rm -rf uFldHazardSensor
    $ git clone https://github.com/COLAB2/uFldHazardSensor.git
    # go to the moos-ivp folder and build moos by following the bellow commands
    $ cd moos-ivp
    $ ./build-ivp.sh
    ```
  
7. Navigate to the moos-ivp/ivp/src directory, delete the folder named "uFldHazardMgr" (follow the instructions below)
    ```
    $ cd moos-ivp/ivp/src
    $ sudo rm -rf uFldHazardMgr
    $ git clone https://github.com/COLAB2/uFldHazardMgr.git
    # go to the moos-ivp folder and build moos by following the bellow commands
    $ cd moos-ivp
    $ ./build-ivp.sh
    ```

8. In your bash_profile or bashrc or zshrc please export the paths for moos-ivp/bin and moos-ivp/moos-ivp-midca/bin and moos-ivp/moos-ivp-midca/scripts
   ```
   $ sudo nano ~/.zshrc
   export PATH="/Users/sravya1/moos-ivp/bin:$PATH"
   export PATH="/Users/sravya1/moos-ivp/moos-ivp-midca/bin:$PATH"
   export PATH="/Users/sravya1/moos-ivp/moos-ivp-midca/scripts:$PATH"
   ```

9. Install java
   ```
   $ brew install openjdk@11
   $ sudo ln -sfn $(brew --prefix)/opt/openjdk@11/libexec/openjdk.jdk /Library/Java/JavaVirtualMachines/openjdk-11.jdk
   ```
   
10. Install MIDCA
   ```
   $ git clone https://github.com/COLAB2/midca.git
   $ cd midca
   $ git checkout nsf-py3.9
   $ python setup.py develop
   ```

# Run the Demo
1. Run the mooos applications
    ```
    $ cd moos-ivp/moos-ivp-midca/missions/multi_agent
    $ ./clean.sh
    $ ./launch.sh
    ```
   A GUI Window will appear, please hit Deploy button.
   
2. Run MIDCA, navigate to the midca directory
    ```
    $ cd midca/midca
    $ cd examples
    $ python midca_structured_search_grace.py 0
    ```
   And then hit Enter.
   
   
 If there are any problems please feel free to contact "Sravya Kondrakunta" (kondrakunta.2@wright.edu).


