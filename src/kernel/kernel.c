#include <kernel/init.h>
void kernel_main(){
	init_all();
	for (;;);
}