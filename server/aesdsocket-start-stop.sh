#! /bin/sh

case "$1" in
	start)
	  echo "Load aesdchar driver"
	  aesdchar_load
	  
	  echo "Starting aesdsocket server"
	  start-stop-daemon -S -n aesdsocket -a /usr/bin/aesdsocket -- -d
	  ;;
	stop)
	  echo "Unload aesdchar driver"
	  aesdchar_unload
	  
	  echo "Stopping aesdsocket server"
	  start-stop-daemon -K -n aesdsocket --signal SIGTERM
	  ;;
	*)
	  echo "Usage: $0 {start | stop}"
	exit 1
esac

exit 0