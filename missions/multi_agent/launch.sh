#!/bin/bash
#-------------------------------------------------------
#  Part 1: Check for and handle command-line arguments
#-------------------------------------------------------
TIME_WARP=8
JUST_MAKE="no"
HAZARD_FILE="tags.txt"

for ARGI; do
    if [ "${ARGI}" = "--help" -o "${ARGI}" = "-h" ] ; then
      	printf "%s [SWITCHES] [time_warp]   \n" $0
      	printf "  --just_make, -j    \n"
      	printf "  --hazards=file.txt \n"
      	printf "  --help, -h         \n"
      	exit 0;
    elif [ "${ARGI:0:10}" = "--hazards=" ] ; then
        HAZARD_FILE="${ARGI#--hazards=*}"
    elif [ "${ARGI//[^0-9]/}" = "$ARGI" -a "$TIME_WARP" = 1 ]; then
        TIME_WARP=$ARGI
    elif [ "${ARGI}" = "--just_build" -o "${ARGI}" = "-j" ] ; then
	      JUST_MAKE="yes"
    else
      	printf "Bad Argument: %s \n" $ARGI
      	exit 0
    fi
done

if [ -f $HAZARD_FILE ]; then
  echo "          Hazard File: $HAZARD_FILE"
else
  echo "$HAZARD_FILE not found. Exiting"
  exit 0
fi

#-------------------------------------------------------
#  Part 2: Create the .moos and .bhv files.
#-------------------------------------------------------
ANGLE="180,0"
VNAME16="Grace"      # The SHIP
#START_POS16="168.16,-194.85"
START_POS16="-108,-41"

ANGLE1="180,0"
VNAME17="franklin"      # The SHIP
START_POS17="-20,-172"

ANGLE1="0,0"
VNAME18="remus"      # The SHIP
START_POS18=52,-310

# What is nsplug? Type "nsplug --help" or "nsplug --manual"

nsplug meta_shoreside.moos targ_shoreside.moos -f WARP=$TIME_WARP \
    VNAME="shoreside"         HAZARD_FILE=$HAZARD_FILE            \
    SHOREIP=localhost         SHORE_LISTEN=9200

nsplug meta_vehicle.moos targ_$VNAME16.moos -f WARP=$TIME_WARP  \
    VNAME=$VNAME16         START_POS=$START_POS16               \
    VPORT="9016"          SHARE_LISTEN="9316"                  \
    SHOREIP="localhost"   SHORE_LISTEN="9200"                  \
    VNAME1=$VNAME16        ANGLE=$ANGLE                                  \
    VTYPE=GLIDER

nsplug meta_vehicle0.moos targ_$VNAME17.moos -f WARP=$TIME_WARP  \
        VNAME=$VNAME17         START_POS=$START_POS17               \
        VPORT="9017"          SHARE_LISTEN="9317"                  \
        SHOREIP="localhost"   SHORE_LISTEN="9200"                  \
        VNAME1=$VNAME16        ANGLE=$ANGLE                                  \
        VTYPE=GLIDER

nsplug meta_vehicle1.moos targ_$VNAME18.moos -f WARP=$TIME_WARP  \
        VNAME=$VNAME18         START_POS=$START_POS18               \
        VPORT="9018"          SHARE_LISTEN="9318"                  \
        SHOREIP="localhost"   SHORE_LISTEN="9200"                  \
        VNAME1=$VNAME16        ANGLE=$ANGLE1                                  \
        VTYPE=GLIDER

nsplug meta_vehicle.bhv targ_$VNAME16.bhv -f VNAME=$VNAME16   \
    START_POS=$START_POS16 VNAME1=$VNAME16

nsplug meta_vehicle.bhv targ_$VNAME17.bhv -f VNAME=$VNAME17   \
        START_POS=$START_POS17 VNAME1=$VNAME17

nsplug meta_vehicle.bhv targ_$VNAME18.bhv -f VNAME=$VNAME18   \
        START_POS=$START_POS18 VNAME1=$VNAME18

if [ ${JUST_MAKE} = "yes" ] ; then
    exit 0
fi

#-------------------------------------------------------
#  Part 3: Launch the processes
#-------------------------------------------------------

printf "Launching $VNAME16 MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_$VNAME16.moos >& /dev/null &

#printf "Launching $VNAME17 MOOS Community (WARP=%s) \n" $TIME_WARP
#pAntler targ_$VNAME17.moos >& /dev/null &

#printf "Launching $VNAME18 MOOS Community (WARP=%s) \n" $TIME_WARP
#pAntler targ_$VNAME18.moos >& /dev/null &

printf "Launching $SNAME MOOS Community (WARP=%s) \n"  $TIME_WARP
pAntler targ_shoreside.moos >& /dev/null &
printf "Done \n"


uMAC targ_shoreside.moos

printf "Killing all processes ... \n"
kill %1 %2 %3 %4
mykill
printf "Done killing processes.   \n"
