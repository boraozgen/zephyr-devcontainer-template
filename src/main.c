#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

int main(void)
{
	uint32_t counter = 0U;

	printk("Zephyr application started\n");

	while (1) {
		printk("tick %u\n", counter++);
		k_sleep(K_SECONDS(1));
	}

	return 0;
}