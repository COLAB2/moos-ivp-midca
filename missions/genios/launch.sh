#!/bin/bash
#-------------------------------------------------------
#  Part 1: Check for and handle command-line arguments
#-------------------------------------------------------
TIME_WARP=70
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
START_POS16="113.90385542493838,-1230.5131160105248"
#START_POS16="6500,-4300"

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

nsplug meta_vehicle.bhv targ_$VNAME16.bhv -f VNAME=$VNAME16   \
    START_POS=$START_POS16 VNAME1=$VNAME16

if [ ${JUST_MAKE} = "yes" ] ; then
    exit 0
fi

#-------------------------------------------------------
#  Part 3: Launch the processes
#-------------------------------------------------------

printf "Launching $VNAME16 MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_$VNAME16.moos >& /dev/null &

printf "Launching $SNAME MOOS Community (WARP=%s) \n"  $TIME_WARP
pAntler targ_shoreside.moos >& /dev/null &
printf "Done \n"


uMAC targ_shoreside.moos

printf "Killing all processes ... \n"
kill %1
killall -9 pvisual pmidca pvisualGenios ploc
mykill
printf "Done killing processes.   \n"
