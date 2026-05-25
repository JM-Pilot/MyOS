<h1 align="center">My own hobby x86_32 Operating System</h1>
<h2>This will soon will be deprecated due to the new mOS64 being developed </h2>
<h3>Info</h3>
A kernel using GRUB as its bootloader and licensed under MIT License.

Written purely by me and helped by a bunch of tutorials such as: www.osdev.wiki, wiki.osdev.org, and bran's kernel dev so shout out to them

This is just a learning Operating System so nothing serious 

<h3>Compiling and Running</h3>
Before you run make sure you have these tools installed

```
grub
xorriso
qemu (optional or other vms)
i686-elf tools (compiled from source)
binutils (not i686-elf-binutils)
```

After getting these tools you should be ready to compile

```
make clean && make
```

or run after compiling

```
make clean && make run
```