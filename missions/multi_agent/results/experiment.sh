#!/usr/bin/env bash
# Variables to change
# iterations
# TIME_LIMIT : the maximum time the moos should run in seconds
# Note : please introduce a delay of 5 sec in the python script and terminate the program
#         only then it goes for another run

Experiments=24
iterations=0 # no:of iterations
path=/home/sampath/Documents/git/midca/midca/examples/midca_structured_search_grace.py #path of the python program


counter=0
# For safety
kill -9 $(cat /tmp/python.pid) >& /dev/null
# to safe kill all the process
trap "printf 'Killing all processes ... \n';
     mykill;
     killall -9 python;
     killall -9 pmidca pvisual prelocate pmine_distributor pmine_layer ppause_vessels;
     printf 'Done killing process ... \n';
     exit $?" SIGINT


# change the iteration number from 2 to number of runs
cd ..
initialize=0
while [ $counter -le $Experiments ]
do
  while [ $initialize -le $iterations ]
  do
    echo "Experiment: $counter Iteration: $initialize"

    #source clean.sh
    #source build.sh
    sleep 2
    printf "Launching The Moos application \n"
    ./clean.sh
    ./launch.sh &>/dev/null & sleep 5
    uPokeDB meta_shoreside.moos DEPLOY=true MOOS_MANUAL_OVERIDE=false >& results/terminal_output/poke.txt & sleep 5 &
    printf "Launching MIDCA \n" &
    python $path $counter &>/dev/null
    printf "Killing the process ... \n"
    mykill
    kill -9 $(cat /tmp/python.pid)
    killall -9 pmidca pvisual prelocate pmine_distributor pmine_layer ppause_vessels
    printf "Done killing process.   \n"


    ((initialize++))
  done
  ((counter++))
  initialize=0
done
  echo "Done, Completed all the iterations"
  exit 0
