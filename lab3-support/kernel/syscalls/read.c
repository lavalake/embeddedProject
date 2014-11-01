/*
 * Author: shang <shang@andrew.cmu.edu>
 *        
 * Date:   2014-10-30
 */


#include "bits/errno.h"
#include "bits/swi.h"
#include "bits/fileno.h"
#include <exports.h>

#define SDRAMStart 0xa0000000
#define SDRAMEnd 0xa3ffffff

ssize_t read(int fd, void* buf, size_t count){             
	unsigned i;	
	char *buffer = (char*) buf;
	char tmp;
	
	if(fd != STDIN_FILENO) 
		return -EBADF;   

	if((count > (SDRAMEnd - SDRAMStart)) || (buf < (void*)SDRAMStart) || (buf > (void*)SDRAMEnd))
		return -EFAULT;

	for(i = 0; i < count; i++){
		tmp = getc();
		if (tmp == 0x7f || tmp ==0x08){
			if(i > 0){
				puts("\b \b");
				buffer[i--] = '\0';
				i--;
			}
//			i--;

		}
		else if(tmp == 0x04)
			return i;
		else if( tmp == '\r' || tmp == '\n'){
			buffer[i] = '\n';
			putc('\n');
			return i;
		}
		else{
			buffer[i] = tmp;
			putc(tmp);
		}
		// buffer is full?
	}
	
	return count;

}
