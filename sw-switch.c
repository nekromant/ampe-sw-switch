#include <linux/module.h>
// #include <linux/config.h>
#include <linux/init.h>


#define param_check_power(a,b) ;;

int pwr[2]; 


int sw_usb_enable_hcd(int hnum);
int sw_usb_disable_hcd(int hnum);

static int param_set_power(const char *val, struct kernel_param *kp)
{
	int hnum, state;
	sscanf(val, "host %d %d", &hnum, &state);
	if (hnum>1)
		printk("sw-switcher: no such host\n");
	printk("sw-switcher: Powering %s host %d\n", state ? "on" : "off", hnum);
	pwr[hnum]=state;
	state ? sw_usb_enable_hcd(hnum) : sw_usb_disable_hcd(hnum) ;
	
	return 0;
}

static void update_values(void)
{
	printk("sw-switch: host 1 is %s; host 2 is %s\n", 
		pwr[0] ? "on" : "off", 
		pwr[1] ? "on" : "off");
}

static int param_get_power(char *buffer, struct kernel_param *kp)
{
	update_values();
	sprintf(buffer, "1:%d \n2:%d \n",pwr[0],pwr[1]);
	return strlen(buffer);
}



struct kernel_param_ops param_ops_power =
{
	.set = &param_set_power,
	.get = &param_get_power
};

int g_power;

// module_param_named(power, g_power, power,  (S_IRUGO | S_IWUSR));
module_param_named(power, g_power, power,  (S_IRUGO | S_IWUSR));

static int __init switch_init(void)
{
 printk ("sw-swicth: For the greater justice!!11\n");
 
 return 0;
}

static void __exit switch_exit(void)
{
 printk ("sw-switch: Bailing out...\n");
        return;
}

module_init(switch_init);
module_exit(switch_exit);

MODULE_AUTHOR("Andrew 'Necromant' Andrianov <kernel@ncrmnt.org>");
MODULE_LICENSE("GPL");
