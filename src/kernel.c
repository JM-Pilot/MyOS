void hcf(){
	asm volatile ("cli");
	for (;;)
		asm volatile ("hlt");
}
void kernel_main(){
	hcf();
}