Debugging Linux
################################################################################

Register
********
----------------------------------------------------------------------------------------------------------------------------------
Number   |   Name     |   Purpose
----------------------------------------------------------------------------------------------------------------------------------
$0       |   $0       |   Always 0
----------------------------------------------------------------------------------------------------------------------------------
$1       |   $at      |   The assembler temporary used by the assembler in expanding pseudo-ops
----------------------------------------------------------------------------------------------------------------------------------
$1-$3    |   $v0-$v1  |   The registers contain the Returned Value of a subroutine; if the value is 1 word only $v0 is significant
----------------------------------------------------------------------------------------------------------------------------------
$4-$7    |   $a0-$a3  |   The argument registers, these registers contain the first 4 argument values for a subroutine call
----------------------------------------------------------------------------------------------------------------------------------
$8-$15   |   $t0-$t9  |   The temporary registers
$24-$25  |            |
----------------------------------------------------------------------------------------------------------------------------------
$16-$13  |   $s0-$s7  |   The saved registers
----------------------------------------------------------------------------------------------------------------------------------
$26-$27  |   $k0-$k1  |   The kernel reserved registers
----------------------------------------------------------------------------------------------------------------------------------
$28      |   $gp      |   The globals pointer used for addressing static global variables
----------------------------------------------------------------------------------------------------------------------------------
$29      |   $sp      |   The stack pointer
----------------------------------------------------------------------------------------------------------------------------------
$30      |   $fp      |   The frame pointer, if need. Programs that do not use an explicit frame pointer, can use register $30 as 
         |   $s8      |   another saved register
----------------------------------------------------------------------------------------------------------------------------------
$31      |   $ra      |   The return address in a subroutine call
----------------------------------------------------------------------------------------------------------------------------------

Deamon Crash
************
* Step 1: Capture signal.log when the daemon was crashed
  When read this file, the paramater include:
    Cp0_epc         :   Extended program counter - shows the address of the instruction that caused a crash
    Cp0_badvaddr    :   Describes a memory address at which address exeption occurred
    Stack dump      :   Complete dump of the memory used by the kernel
    regs            :   Value of MIPS register in first chapter
    
  Ex:
    Stack pointer: reg[29] 0x2B74BBF0

    Intructions around PC
    2402ffff    8e030000    90620000(PC)    1440fff0    00000000
----------------------------------------------------------------------------------------------------------------------------------
* Step 2: Create objectdump of lib, which includes the error instruction

  Ex:
    Find the line with address 0x90620000, which base on the before line address 0x8e030000
    
    3777c:  27bdffd0    addiu   sp,sp,-48
    .....................................
    .....................................
    37820:  2402ffff    li      v0,-1
    37024:  8e030000    lw      v1,0(s0)
    37828:  90620000    lbu     v0,0(v1)
    3782c:  1440fff0    bnez    v0,377f0<vfprintf+oxb40>

    Backtrace the stack pointer by add more 48 bytes: 0x2B74BBF0 + 0x30 = 0x2B74BC20
    Have the address contain RA (Return Address) by subtract 4 byte: 0x2B74BC20 - 0x04 = 0x2B74BC16 => RA = 0x2B9F4F9C
    Because the error instruction is in a shared library, so it is linear address is different from relative address shown by objectdump
    Offset jump to this address = Cpu_epc0 - 0x2B9F4F9C = 0x2B9F5828 - 0x2B9F4F9C = 0x88C 
    => 0x2B9F4F9C at line 0x307828 - 0x88c = 0x36f9c
    
    36f98:  00a08821    move    s1,a1
    36f9c:  0441000f    bgez    v0,36fdc <vfprintf+0x32c>
    36fa0:  8fbc0018    lw      gp, 24(sp)
----------------------------------------------------------------------------------------------------------------------------------
* Step 3: Continue use same way to trace back the stack and find out a back track 

Memory Leak
***********
* Definition and cause
  When a computer program incorrectly manages meory allocations in such a way that memory which is no longer needed is not released.
  A memory leak may also happen when an object is stored in memory but can not be accessed by the running code
  Two memory areas that can easily lead to memory leak is HEAP and thread memory
* Solution
  Need to find out and free up the leaked memory refions
  * Step 1: Use top command to display paramaters related to the memory area of processes. Noted the process takes high used memory percent overtime
  * Step 2: Use the command cat /pro/[pid]/maps to map the corresponding address space that the process uses. Performs twice to determone where specific memory areas increase
  * Step 3: See the heap memory of the process increase after each display, dump all the data of the heap area into a file and analyze them with the GDB tool.
    
    gdb -p [pid]
    gump memory ./dumpfile [range of address]
    
    Need to copy this dumpfile out and handle it to be readable. And then, open dumpfile.txt and analyze data inside. If you see data entryx is repeated many times 
    with its value. So it can be concluded that this is the cause of memory leak. Based on this and the data, you will look in the resource of the process to find error

Hang 
****
* After the user executes a command without any response from the device, or the process is hung while running normally but does not reboot
* To solve this problem, you will find out which resources the thread are waiting for each other by the GDB tool

    gdb -p [pid]                        :   Go into the process with PID
    thread apply all bt                 :   Display all of threads
    thread [thread number]              :   Go into thread of the process
    frame [frame number]                :   Go into the stack frame of the thread or the process
    p [value of argument or variable]   :   Examine and use the variable

Kernel Panic
************
* A linux kernel panic is a computer error from which the linux OS cannot quickly or easily recover
  The kernel provides basic services for all other parts of the OS, kernel panics are overtaxed memory and software bugs
* Solution
  * Step 1: Preparation steps for analyze kernel core dump
    Setting kernel build configuration
        CONFIG_DEBUG_INFO = y   : It will mix C code with assembly in file vmlinux.o
        CONFFI_KALLSYMS = y     : When kenel dump, kernel can translate $epc (exeption instruction) value to function name
    Dump vmlinux.o get information of kerne;
        objdump -D -S vmlinux.o > vmlinux.obj   :   Disassembly source code of all section in file vmlinux.o
        Kernel panic log get from system log (/data/log/messages) after kernel reboot
    Get kernel panic log from /data/log/messages after kernel reboot

    Sec 1: Header of kernel panic dump. It include common reason of error. Time error occur and device's common information
    Sec 2: Value of all common registers when error occur. Need to careful with value in $4 to $7, this is argument registers. Some time focus wit value in $2 to $3: It is return values.
        $2, $3  :   Store function result
        $4 - $7 :   Store function's argument
        $28     :   Global pointer
        $29     :   Stack pointer
        $31     :   Return address
    Sec 3: Value of special register. They include cause of error. $Cause, current instruction $epc, processor status when error occur
    $Status, invalid address which processor try to access, $BadVA, instruction call current function in parent
        $epc    :   Store current instruction's address when error occur
                    ploam_recv_upstream_overhead+0xac/0x620 with 0xac is the offset of current instruction in skb_dequeue asm code. 0x620 is total length of skb_dequeue assembly code
        $ra     :   Store next instruction in parent function
        $Status :   Store context of CPU when error occur (kernel mode or user mode)
        #BadVA  :   Store invalid address, which CPU try to access
    Sec 4: Fuction stack call trace. it stores the function name and argument value trace to current function
 * Step 2: Analyze kernel core dump
   With $epc = ploam_recv_upstream_overhead+0xac/0x620, we use GDB to locate the source code where EPC point to at file xpon.o. Then, you list the content of the memory address
   EPC=ploam_recv_upstream_overhead+0xf0 by command line: list*(ploam_recv_upstream_overhead+0xf0). You got error code line.
