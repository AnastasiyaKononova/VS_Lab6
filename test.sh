sudo insmod lab6.ko

sudo chmod a+w+r /sys/timers/inter

echo "#10"
echo 10 > /sys/timers/inter

sleep 10
echo 0 > /sys/timers/inter

