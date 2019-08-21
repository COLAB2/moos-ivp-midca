#!/usr/bin/env bash
# Variables to change
# iterations
# TIME_LIMIT : the maximum time the moos should run in seconds
# Note : please introduce a delay of 5 sec in the python script and terminate the program
#         only then it goes for another run


iterations=1 # no:of iterations
TIME_LIMIT=300 # the maximum amount of time moos should run
path=/home/sampath/Documents/git/moos-interface/world.py #path of the python program


counter=1

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
while [ $counter -le $iterations ]
do
  echo "Welcome $counter times"
  ((counter++))
  cd ..
  cd ..
  #source clean.sh
  #source build.sh
  sleep 2
  cd missions/gatars

  printf "Launching The Moos application \n"
  ./clean.sh
  ./launch.sh >& moos_output.txt & sleep 5
  uPokeDB meta_shoreside.moos DEPLOY=true MOOS_MANUAL_OVERIDE=false >& poke.txt & sleep 5
  python $path & echo $! > /tmp/python.pid & sleep $TIME_LIMIT
  printf "Killing the process ... \n"
  mykill
  kill -9 $(cat /tmp/python.pid)
  killall -9 pmidca pvisual prelocate pmine_distributor pmine_layer ppause_vessels
  printf "Done killing process.   \n"
  wait
done
  echo "Done, Completed all the iterations"
  exit 0
