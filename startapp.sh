#!/bin/sh
#

#cd /opt/dws/
#./decoder & >/dev/null

#
# functions	This file contains functions to be used by most or all
#		shell scripts in the /etc/init.d directory.
#


SELFNAME=$0

# Read in our configuration
    # This all seem confusing? Look in /etc/sysconfig/init,
    # or in /usr/doc/initscripts-*/sysconfig.txt
    BOOTUP=color
    RES_COL=60
    MOVE_TO_COL="echo -en \\033[${RES_COL}G"
    SETCOLOR_SUCCESS="echo -en \\033[1;32m"
    SETCOLOR_FAILURE="echo -en \\033[1;31m"
    SETCOLOR_WARNING="echo -en \\033[1;33m"
    SETCOLOR_NORMAL="echo -en \\033[0;39m"
    LOGLEVEL=1

if [ "$BOOTUP" != "verbose" ]; then
   INITLOG_ARGS="-q"
else
   INITLOG_ARGS=
fi

# Check if $pid (could be plural) are running
checkpid() {
	while [ "$1" ]; do
	   [ -d /proc/$1 ] && return 0
	   shift
	done
	return 1
}
	
# A function to stop a program.
killproc() {
	RC=0
	# Test syntax.
	if [ $# = 0 ]; then
		echo "Usage: killproc {program} [signal]"
		return 1
	fi

	if [ "X$1" = "X-a" ]; then
		KILLALL=$1
		shift
	else
		KILLALL=
	fi

	notset=0
	# check for second arg to be kill level
	if [ "$2" != "" ] ; then
		killlevel=$2
	else
		notset=1
		killlevel="-9"
	fi

        # Save basename.
        base=`basename $1`

        # Find pid.
        pidlist=`pidofproc $1`
	
	if [ "X$KILLALL" = "X-a" ]; then
		pid=
		for apid in $pidlist ; do
		   [ -d /proc/$apid ] && pid="$pid $apid"
		done
	else
		pid=
		for apid in $pidlist ; do
		   [ -d /proc/$apid ] && pid="$apid"
		done
	fi

        # Kill it.
    if [ "$pid" != "" ] ; then
                [ $BOOTUP = "verbose" ] && echo -n "$base "
		if [ "$notset" = "1" ] ; then
		       if checkpid $pid 2>&1; then
			    # TERM first, then KILL if not dead
			    kill -TERM $pid >/dev/null 2>&1
			    sleep 1
			    left=5
			    while checkpid $pid >/dev/null 2>&1 ; do
				sleep 1
				left=`expr $left - 1`
				[ $left -eq 0 ] && break;
			    done
			    if checkpid $pid >/dev/null 2>&1 ; then
				kill -KILL $pid >/dev/null 2>&1
				usleep 100000
			    fi
		        fi
			checkpid $pid >/dev/null 2>&1
			RC=$?
			[ $RC -eq 0 ] && failure "$base shutdown" || success "$base shutdown"
			RC=$((! $RC))
		# use specified level only
		else
		        if checkpid $pid >/dev/null 2>&1; then
	                	kill $killlevel $pid
				RC=$?
				[ $RC -eq 0 ] && success "$base $killlevel" || failure "$base $killlevel"
				fi
		fi
	else
	    failure "$base shutdown"
	fi

        # Remove pid file if any.
	if [ "$notset" = "1" ]; then
            rm -f /var/run/$base.pid
	fi
	return $RC
}

# A function to find the pid of a program.
pidofproc() {
	base=`basename $1`

	# Test syntax.
	if [ $# = 0 ] ; then
		echo "Usage: pidofproc {program}"
		return 1
	fi

	# First try "/var/run/*.pid" files
	if [ -f /var/run/${base}.pid ] ; then
	        pid=`cat /var/run/${base}.pid | { read foo ; echo $foo ; }`
	        if [ "$pid" != "" ] ; then
	                echo $pid
	                return 0
	        fi
	fi

	# Next try "pidof"
	pid=`pidof -o $$ -o $PPID -o %PPID ${base}`
#	echo "${base}=$pid"
	if [ "$pid" != "" ] ; then
	        echo $pid
	        return 0
	fi
	return 1
}

status() {
	base=`basename $1`

	# Test syntax.
	if [ $# = 0 ] ; then
		echo "Usage: status {program}"
		return 1
	fi

	# First try "pidof"
	pid=`pidof -o $$ -o $PPID -o %PPID -x ${base}`
	if [ "$pid" != "" ] ; then
	        echo "${base} (pid $pid) is running..."
	        return 0
	fi

	# Next try "/var/run/*.pid" files
	if [ -f /var/run/${base}.pid ] ; then
	        pid=`cat /var/run/${base}.pid | { read foo ; echo $foo ; }`
	        if [ "$pid" != "" ] ; then
	                echo "${base} dead but pid file exists"
	                return 1
	        fi
	fi
	# See if /var/lock/subsys/${base} exists
	if [ -f /var/lock/subsys/${base} ]; then
		echo "${base} dead but subsys locked"
		return 2
	fi
	echo "${base} is stopped"
	return 3
}

echo_success() {
  [ "$BOOTUP" = "color" ] && $MOVE_TO_COL
  echo -n "  [  "
  [ "$BOOTUP" = "color" ] && $SETCOLOR_SUCCESS
  echo -n "OK"
  [ "$BOOTUP" = "color" ] && $SETCOLOR_NORMAL
  echo -n "  ]"
  echo -ne "\r\n"
  return 0
}

echo_failure() {
  [ "$BOOTUP" = "color" ] && $MOVE_TO_COL
  echo -n "  ["
  [ "$BOOTUP" = "color" ] && $SETCOLOR_FAILURE
  echo -n "FAILED"
  [ "$BOOTUP" = "color" ] && $SETCOLOR_NORMAL
  echo -n "]"
  echo -ne "\r\n"
  return 1
}

echo_passed() {
  [ "$BOOTUP" = "color" ] && $MOVE_TO_COL
  echo -n "["
  [ "$BOOTUP" = "color" ] && $SETCOLOR_WARNING
  echo -n "PASSED"
  [ "$BOOTUP" = "color" ] && $SETCOLOR_NORMAL
  echo -n "]"
  echo -ne "\r"
  return 1
}

# Log that something succeeded
success() {
  if [ -z "$IN_INITLOG" ]; then
     echo -n #initlog $INITLOG_ARGS -n $0 -s "$1" -e 1
  else
     # silly hack to avoid EPIPE killing rc.sysinit
     trap "" SIGPIPE
     echo "$INITLOG_ARGS -n $0 -s \"$1\" -e 1" >&21
     trap - SIGPIPE
  fi
  [ "$BOOTUP" != "verbose" ] && echo_success
  return 0
}

# Log that something failed
failure() {
  rc=$?
  if [ -z "$IN_INITLOG" ]; then
     echo -n #initlog $INITLOG_ARGS -n $0 -s "$1" -e 2
  else
     trap "" SIGPIPE
     echo "$INITLOG_ARGS -n $0 -s \"$1\" -e 2" >&21
     trap - SIGPIPE
  fi
  [ "$BOOTUP" != "verbose" ] && echo_failure
  return $rc
}

# Log that something passed, but may have had errors. Useful for fsck
passed() {
  rc=$?
  if [ -z "$IN_INITLOG" ]; then
     echo -n #initlog $INITLOG_ARGS -n $0 -s "$1" -e 1
  else
     trap "" SIGPIPE
     echo "$INITLOG_ARGS -n $0 -s \"$1\" -e 1" >&21
     trap - SIGPIPE
  fi
  [ "$BOOTUP" != "verbose" ] && echo_passed
  return $rc
}  

# Run some action. Log its output.
action() {
  STRING=$1
  echo -n "$STRING "
  shift
  initlog $INITLOG_ARGS -c "$*" && success "$STRING" || failure "$STRING"
  rc=$?
  echo
  return $rc
}

# Confirm whether we really want to run this service
confirm() {
  echo -n "Start service $1 (Y)es/(N)o/(C)ontinue? [Y] "
  read answer
  case $answer in
    y|Y|"")
      return 0
    ;;
    c|C)
      return 2
    ;;
    n|N)
      return 1
    ;;
    *)
      confirm $1
      return $?
    ;;
    esac
}

#
# Stop the Program
#
stop_self() {
	echo -n "Stoping ${SELFNAME}..."
	killproc -a $SELFNAME
}

stop_app() {
	echo -n "Stopping decoder Server..."
	killproc decoder
	return 0
}

start_app_proc()
{
	while true; do
		if [ -x /opt/dws/decoder ]; then
			cd /opt/dws	
			echo_success
			./decoder >/dev/tty2
			sleep 10
		else 
			echo_failure
			sleep 10	
		fi
	done
}

start_app() {
	echo -n "Starting decoder Server..."
	start_app_proc >/dev/null 2>&1 &
	echo_success
	return 0
}

STARTDIR=`dirname $0`
PRES=`dirname $0 | cut -c 1`

if [ ! "X$PRES" = "X/" ]; then
STARTDIR=`pwd`/$STARTDIR
fi

STARTDIR=`cd $STARTDIR;pwd`

ACTION=$1
case "$ACTION" in
    status)
	status $SELFNAME
	;;
    start)
	stop_self
	wait
	stop_app
	wait
	start_app
	;;
    restart)
	stop_self
	wait
	stop_app
	wait
	start_app
	;;
    stop)
	stop_self
	wait
	stop_app
	;;
    "")
	stop_self
	wait
	stop_app
	wait
	start_app
	;;
    *)
	echo "Usage $0 {(start)|restart|stop}"
	sleep 1
	;;
esac



