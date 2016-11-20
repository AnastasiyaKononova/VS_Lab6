sudo insmod hello_timer.ko

sudo chmod a+w+r /sys/timer/interval

echo "#1"
echo "10" > /sys/timer/interval

sleep 6
echo 0 > /sys/timer/interval

sudo rmmod hello_timer
