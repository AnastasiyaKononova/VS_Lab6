obj-m += lab6.o
KDIR := /lib/modules/$(shell uname -r)/build

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
