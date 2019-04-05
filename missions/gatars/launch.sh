#!/bin/bash
#-------------------------------------------------------
#  Part 1: Check for and handle command-line arguments
#-------------------------------------------------------
TIME_WARP= 7
JUST_MAKE="no"
HAZARD_FILE="hazards5.txt"
PEN_MISSED_HAZ=150
PEN_FALARM=25
MAX_TIME=7200

for ARGI; do
    if [ "${ARGI}" = "--help" -o "${ARGI}" = "-h" ] ; then
	printf "%s [SWITCHES] [time_warp]   \n" $0
	printf "  --just_make, -j    \n"
	printf "  --hazards=file.txt \n"
	printf "  --help, -h         \n"
	exit 0;
    elif [ "${ARGI:0:10}" = "--hazards=" ] ; then
        HAZARD_FILE="${ARGI#--hazards=*}"

    elif [ "${ARGI:0:11}" = "--max_time=" ] ; then
        MAX_TIME="${ARGI#--max_time=*}"
    elif [ "${ARGI:0:17}" = "--pen_missed_haz=" ] ; then
        PEN_MISSED_HAZ="${ARGI#--pen_missed_haz=*}"
    elif [ "${ARGI:0:13}" = "--pen_falarm=" ] ; then
        PEN_FALARM="${ARGI#--pen_falarm=*}"

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
  echo "             Max Time: $MAX_TIME"
  echo "Penalty Missed Hazard: $PEN_MISSED_HAZ"
  echo "  Penalty False Alarm: $PEN_FALARM"
else
  echo "$HAZARD_FILE not found. Exiting"
  exit 0
fi

#-------------------------------------------------------
#  Part 2: Create the .moos and .bhv files.
#-------------------------------------------------------
VNAME1="remus"      # The first   vehicle community
START_POS1="55,80"
ANGLE="180,0"

VNAME2="Titanic"      # The SHIP
START_POS2="-90,-80"
ship_angle="90,0"

VNAME3="Cruise"      # The SHIP
START_POS3="-70,-70"

VNAME4="ship"      # The SHIP
START_POS4="-50,-60"

VNAME5="Titanic1"      # The SHIP
START_POS5="-80,-77"
ship_angle="90,0"

VNAME6="Cruise1"      # The SHIP
START_POS6="-60,-85"

VNAME7="ship1"      # The SHIP
START_POS7="-93,-70"

# What is nsplug? Type "nsplug --help" or "nsplug --manual"

nsplug meta_shoreside.moos targ_shoreside.moos -f WARP=$TIME_WARP \
    VNAME="shoreside"         HAZARD_FILE=$HAZARD_FILE            \
    SHOREIP=localhost         SHORE_LISTEN=9200                   \
    MAX_TIME=$MAX_TIME        PEN_MISSED_HAZ=$PEN_MISSED_HAZ      \
    PEN_FALARM=$PEN_FALARM

nsplug meta_vehicle.moos targ_$VNAME1.moos -f WARP=$TIME_WARP  \
    VNAME=$VNAME1         START_POS=$START_POS1                \
    VPORT="9001"          SHARE_LISTEN="9301"                  \
    SHOREIP="localhost"   SHORE_LISTEN="9200"                  \
    VNAME1=$VNAME1        ANGLE=$ANGLE		                       \
    VTYPE=UUV

nsplug meta_ship.moos targ_$VNAME2.moos -f WARP=$TIME_WARP  \
    VNAME=$VNAME2         START_POS=$START_POS2               \
    VPORT="9002"          SHARE_LISTEN="9302"                  \
    SHOREIP="localhost"   SHORE_LISTEN="9200"                  \
    VNAME1=$VNAME2        ANGLE=$ship_angle    		                       \
    VTYPE=SHIP

nsplug meta_ship.moos targ_$VNAME3.moos -f WARP=$TIME_WARP  \
    VNAME=$VNAME3         START_POS=$START_POS3               \
    VPORT="9003"          SHARE_LISTEN="9303"                  \
    SHOREIP="localhost"   SHORE_LISTEN="9200"                  \
    VNAME1=$VNAME3        ANGLE=$ship_angle                                   \
    VTYPE=SHIP

nsplug meta_ship.moos targ_$VNAME4.moos -f WARP=$TIME_WARP  \
    VNAME=$VNAME4         START_POS=$START_POS4               \
    VPORT="9004"          SHARE_LISTEN="9304"                  \
    SHOREIP="localhost"   SHORE_LISTEN="9200"                  \
    VNAME1=$VNAME4        ANGLE=$ship_angle                                   \
    VTYPE=SHIP

nsplug meta_ship.moos targ_$VNAME5.moos -f WARP=$TIME_WARP  \
    VNAME=$VNAME5         START_POS=$START_POS5               \
    VPORT="9005"          SHARE_LISTEN="9305"                  \
    SHOREIP="localhost"   SHORE_LISTEN="9200"                  \
    VNAME1=$VNAME5        ANGLE=$ship_angle                                   \
    VTYPE=SHIP

nsplug meta_ship.moos targ_$VNAME6.moos -f WARP=$TIME_WARP  \
    VNAME=$VNAME6         START_POS=$START_POS6               \
    VPORT="9006"          SHARE_LISTEN="9306"                  \
    SHOREIP="localhost"   SHORE_LISTEN="9200"                  \
    VNAME1=$VNAME6        ANGLE=$ship_angle                                   \
    VTYPE=SHIP

nsplug meta_ship.moos targ_$VNAME7.moos -f WARP=$TIME_WARP  \
    VNAME=$VNAME7         START_POS=$START_POS7               \
    VPORT="9007"          SHARE_LISTEN="9307"                  \
    SHOREIP="localhost"   SHORE_LISTEN="9200"                  \
    VNAME1=$VNAME7        ANGLE=$ship_angle                                   \
    VTYPE=SHIP

nsplug meta_vehicle.bhv targ_$VNAME1.bhv -f VNAME=$VNAME1   \
    START_POS=$START_POS1 VNAME1=$VNAME1

nsplug meta_ship.bhv targ_$VNAME2.bhv -f VNAME=$VNAME2   \
    START_POS=$START_POS2 VNAME1=$VNAME2

nsplug meta_ship1.bhv targ_$VNAME3.bhv -f VNAME=$VNAME3   \
    START_POS=$START_POS3 VNAME1=$VNAME3

nsplug meta_ship2.bhv targ_$VNAME4.bhv -f VNAME=$VNAME4   \
    START_POS=$START_POS4 VNAME1=$VNAME4

nsplug meta_ship3.bhv targ_$VNAME5.bhv -f VNAME=$VNAME5   \
    START_POS=$START_POS5 VNAME1=$VNAME5

nsplug meta_ship4.bhv targ_$VNAME6.bhv -f VNAME=$VNAME6   \
    START_POS=$START_POS6 VNAME1=$VNAME6

nsplug meta_ship5.bhv targ_$VNAME7.bhv -f VNAME=$VNAME7   \
    START_POS=$START_POS7 VNAME1=$VNAME7

if [ ${JUST_MAKE} = "yes" ] ; then
    exit 0
fi

#-------------------------------------------------------
#  Part 3: Launch the processes
#-------------------------------------------------------
printf "Launching $VNAME1 MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_$VNAME1.moos >& /dev/null &

printf "Launching $VNAME2 MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_$VNAME2.moos >& /dev/null &

printf "Launching $VNAME3 MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_$VNAME3.moos >& /dev/null &

printf "Launching $VNAME4 MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_$VNAME4.moos >& /dev/null &

printf "Launching $VNAME5 MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_$VNAME5.moos >& /dev/null &

printf "Launching $VNAME6 MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_$VNAME6.moos >& /dev/null &

printf "Launching $VNAME7 MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_$VNAME7.moos >& /dev/null &

printf "Launching $SNAME MOOS Community (WARP=%s) \n"  $TIME_WARP
pAntler targ_shoreside.moos >& /dev/null &
printf "Done \n"


uMAC targ_shoreside.moos

printf "Killing all processes ... \n"
kill %1 %2 %3 %4 %5 %6 %7 %8
mykill
printf "Done killing processes.   \n"
