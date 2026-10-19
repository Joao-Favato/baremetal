#include <kernel.h>
#include <drivers/gpio.h>

#define LED0_NODE DT_ALIAS(led0)
static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(DT_ALIAS(led2), gpios);

#define MY_STACK_SIZE 512
#define MY_PRIORITY 1

void pisca_thread_main_verde(void *p1, void *p2, void *p3)
{
  
    gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);

    gpio_pin_set_dt(&led0, 0);

    while (1) {
        gpio_pin_set_dt(&led0, 1);
        k_msleep(100);
        gpio_pin_set_dt(&led0, 0);
        k_msleep(900);
    }
}

void pisca_thread_main_vermelho(void *p1, void *p2, void *p3) {
    
    gpio_pin_configure_dt(&led2, GPIO_OUTPUT_ACTIVE);

    gpio_pin_set_dt(&led2, 0);
    while (1) {
        gpio_pin_set_dt(&led2, 1);
        k_msleep(100);
        gpio_pin_set_dt(&led2, 0);
        k_msleep(400);
    }
}

K_THREAD_DEFINE(pisca_thread_verde, MY_STACK_SIZE,
                pisca_thread_main_verde, NULL, NULL, NULL,
                MY_PRIORITY, 0, 0);

K_THREAD_DEFINE(pisca_thread_vermelho, MY_STACK_SIZE,
                pisca_thread_main_vermelho, NULL, NULL, NULL,
                MY_PRIORITY, 0, 0);