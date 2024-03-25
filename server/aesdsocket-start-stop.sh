#!/bin/bash

DAEMON_PATH="/usr/bin"
DAEMON_NAME="aesdsocket"
DAEMON="$DAEMON_PATH/$DAEMON_NAME"
DAEMON_OPTS="-d"
PIDFILE="$DAEMON_PATH/$DAEMON_NAME.pid"

case "$1" in
    start)
        echo "Starting $DAEMON_NAME..."
        start-stop-daemon --start --quiet --background --make-pidfile --pidfile $PIDFILE --exec $DAEMON -- $DAEMON_OPTS
        ;;
    stop)
        echo "Stopping $DAEMON_NAME..."
        start-stop-daemon --stop --quiet --pidfile $PIDFILE
        if [ -e $PIDFILE ]; then
            rm $PIDFILE
        fi
        ;;
    restart)
        $0 stop
        $0 start
        ;;
    *)
        echo "Usage: $0 {start|stop|restart}"
        exit 1
esac

exit 0
