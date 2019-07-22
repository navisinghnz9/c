INCLUDES='mem_monitor.h'
SRC='mem_monitor.c test.c'

#gcc $SRC -I $INCLUDES -o mm
gcc $SRC -o mm
