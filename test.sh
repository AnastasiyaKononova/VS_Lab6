sudo insmod lab6.ko

sudo chmod 777 /sys/timer/interval

echo "7" > /sys/timer/interval

sleep 10
echo 0 > /sys/timer/interval

sudo rmmod lab6
