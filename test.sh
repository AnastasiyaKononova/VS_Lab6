sudo insmod hello_timer.ko

sudo chmod a+w+r /sys/timer/interval

echo "7" > /sys/timer/interval

sleep 10
echo 0 > /sys/timer/interval

