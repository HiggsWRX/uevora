# Code formating: Tab Size = 4

		.data
fin:			.asciiz "/home/hiago/Documents/ASC1/trabalho/car.rgb"
fout:			.asciiz "/home/hiago/Documents/ASC1/trabalho/carfinal.gray"
shmatrix:		.byte 1, 0, -1, 2, 0, -2, 1, 0, -1
svmatrix:		.byte 1, 2, 1, 0, 0, 0, -1, -2, -1
orig:			.space 786432				# Reserved space for
gray:			.space 262144				# processed images
hsobel:			.space 262144				#
vsobel:			.space 262144				#
final:			.space 262144				# ---

		.text
Main:
				la $a0, fin					# File name to read
				jal Read_RGB_Image
				nop
				
				la $a0, orig				# Original buffer to convert
				la $a1, gray				# Buffer to save grayscale image
				jal RGB_to_Gray
				nop
				
				la $a0, gray				# Grayscale image
				la $a1, shmatrix			# Horizontal sobel matrix
				la $a2, hsobel				# Buffer with horizontal
				jal Convolution				# Filtered image...
				nop
				
				la $a0, gray				# Same as above, but this time
				la $a1, svmatrix			# for the vertical filter
				la $a2, vsobel				#
				jal Convolution				#
				nop
				
				la $a0, hsobel				# Horizontal buffer
				la $a1, vsobel				# Vertical buffer
				la $a2, final				# Place to store the final
				jal Contour					# buffer
				nop
				
				la $a0, fout				# New file name to create
				la $a1, final				# Buffer to be writen to the file
				li $a2, 262144				# Buffer size
				jal Write_Gray_Image
				nop
				
				j end
				nop

###############################################################################
# Open RGB image in memory and read it to buffer space
# Takes: file location ($a0)
# Returns: number of bytes read ($v0)
Read_RGB_Image:	
				li $a1, 0					# Read Only flag
				li $a2, 0					#
				li $v0, 13					# Open file in memory
				syscall						# Syscall to open file

				# Now we read the image to the buffer space reserved
				move $a0, $v0
				la $a1, orig				# Adress of reserved space
				li $a2, 786432				# Number of bytes to read
				li $v0, 14					# Syscall to read file
				syscall
				
				li $v0, 16					# Close the file
				syscall

				jr $ra						# Return to the main body
				nop
###############################################################################
# Write Gray Image to disk
# Takes: file name/location ($a0),  buffer to save ($a1), buffer size ($a2)
# Returns: none
Write_Gray_Image:
				addi $sp, $sp, -12			# Store register values
				sw $s0, 0($sp)				# from previous methods
				sw $s1, 4($sp)				# and functions...
				sw $s2, 8($sp)				#
				
				move $s1, $a1				# Save buffer
				move $s2, $a2				# Save buffer size
				
				li $a1, 1					# Set modes and flags
				li $a2, 0					# ....
				li $v0, 13					# Syscall to open/create
				syscall						# File
				
				move $s0, $v0				# Store file descriptor and
				move $a0, $s0				# Move it to $a0
				move $a1, $s1				# Buffer to write
				move $a2, $s2				# Buffer size
				li $v0, 15
				syscall
				
				move $a0, $s0				# Load file descriptor to close
				li $v0, 16					# Syscall to close file
				syscall	
				
				lw $s0, 0($sp)				# Restore registers to
				lw $s1, 4($sp)				# the original values...
				lw $s2, 8($sp)				#
				addi $sp, $sp, 12
				
				jr $ra
				nop
###############################################################################
# Convert RGB image to GRAYSCALE
# Takes: buffer with data read from file ($a0), buffer to save
# converted file ($a1)
# Returns: ?
RGB_to_Gray:
				li $t3, 786432
process:
				beqz $t3, endprocess
				nop
				# Formula to be used -- I = 0.30R + 0.59G + 0.11B	
				lbu $t0, 0($a0)				# Load Red Byte from current pixel
				mul $t0, $t0, 30			# and apply the formula
				div $t0, $t0, 100			#
				lbu $t1, 1($a0)				# Load Green Byte...
				mul $t1, $t1, 59			# ...
				div $t1, $t1, 100			#
				lbu $t2, 2($a0)      		# Load Blue Byte...
				mul $t2, $t2, 11			# ...
				div $t2, $t2, 100			#

				add $t1, $t1, $t2			# Start adding them all
				add $t0, $t0, $t1			# to fit one byte
				sb $t0, 0($a1)				# Store it
				
				addi $a0, $a0, 3			# Increment $a0 by 3 to load
				addi $a1, $a1, 1			# next 3 bytes and $a1 by 1
											# for the next byte to be
											# saved
				
				j process					# Buffer size acts like a
				addi $t3, $t3, -3			# counter
				
endprocess:		
				jr $ra
				nop
###############################################################################
# Convolution (detect changes)
# Takes: buffer with Grayscale ($a0), buffer with 'h' or 'v' sobel matrix ($a1)
# and buffer to save image B after sobel filter applied ($a2)
# Returns: none
Convolution:	
				# Used: t0, t1, t2, t3, t4, t5, t6, t7, t8
				# s0, s1, s2, s3, s4, s5
				addi $sp, $sp, -24
				sw $s0, ($sp)
				sw $s1, 4($sp)
				sw $s2, 8($sp)
				sw $s3, 12($sp)
				sw $s4, 16($sp)
				sw $s5, 20($sp)
				
				li $t0, 262144				# Buffer size
				li $t1, 1					# i pixel aid
				li $t2, 1					# j pixel aid
				li $t3, -1					# p from sobel formula
				li $t4, -1					# q ...
				li $s0, 2					# constant 2
				li $s4, 0					#
				
for:			beqz $t0, endconvo
				nop
				
				bne $t1, 513, hop			# Corrects the x coordinate...
				nop							# Something like
				li $t1, 1					# if(x == 65): x == 1
				addi $t2, $t2, 1
				
hop:            beq $t1, 1, isborder		# Since convolution is not well
				nop							# defined in the borders, we will
				beq $t1, 512, isborder		# catch every border pixel and 
				nop							# give it a special treatment
				beq $t2, 1, isborder		#
				nop							#
				beq $t2, 512, isborder		#
				nop
				
pcicle:			beq $t3, 2, endcicle
				nop
qcicle:			beq $t4, 2, nextpcicle
				nop
				
				add $t5, $t1, $t3			# t5: A(i+p)
				add $t6, $t2, $t4			# t6: A(j+q)
				sub $t7, $s0, $t3			# t7: Shv(2-p)
				sub $t8, $s0, $t4			# t8: Shv(2-q)
				
				# Formula to get desired pixel from array
				# P(i, j) = size * (j-1) + i
				# This will give the ijth place on the array
				
				# A matrix
				addi $t6, $t6, -1			# j-1
				mul $t6, $t6, 512			# size * j-1
				add $t5, $t5, $t6			# size * (j-1) + i
				move $s3, $a0				# s3: gray buffer (a0)
				add $t5, $t5, $s3			# equivalent to lbu $s1, $t5($a0)
				addi $t5, $t5, -1			# small correction
				lbu $s1, ($t5)				# s1: A(i+p)(j+q)
				# Sobel matrix
				addi $t8, $t8, -1			# j-1
				mul $t8, $t8, 3				# size * (j-1) + i
				add $t7, $t7, $t8			# size * (j-1) + i
				move $s3, $a1				# s3: matrix number
				add $t7, $t7, $s3			# get pixel
				addi $t7, $t7, -1			# small correction
				lb $s2, ($t7)				# s2: H(2-p)(2-q)
				
				mul $s4, $s1, $s2			# s4: A(i,j) * S(i, j)
				
				add $s5, $s5, $s4			# sum
				j qcicle
				addi $t4, $t4, 1			# q + 1
				
nextpcicle:		li $t4, -1
				j pcicle
				addi $t3, $t3, 1			# p + 1
				
isborder:		li $s5, 0					# Load black pixel

endcicle:		abs $s5, $s5
				div $s5, $s5, 4
				sb $s5, ($a2)				# Save sobel filter pixel
				addi $a2, $a2, 1			# Next buffer space
				li $s5, 0					# Reset sum
				
				addi $t1, $t1, 1			# Next pixel to be processed
				
				li $t3, -1					# Reset q and p
				li $t4, -1					#
				
				
				j for
				addi $t0, $t0, -1
				
endconvo:		lw $s0, ($sp)				# Restore original values
				lw $s1, 4($sp)				# of all preserved
				lw $s2, 8($sp)				# temporary registers
				lw $s3, 12($sp)				#
				lw $s4, 16($sp)				#
				lw $s5, 20($sp)				#
				
				jr $ra
				addi $sp, $sp, 24
###############################################################################
# Contour
# Takes: horizontal buffer ($a0), vertical buffer ($a1), final result ($a2)
# Returns: none
Contour:
				li $t0, 262144				# Related to image size
				li $t4, 255					# Constant to invert
				
joinmatrix:		beqz $t0, endcontour
				nop
				lbu $t1, ($a0)				# Load pixel from horizontal
				lbu $t2, ($a1)				# ... from vertical
				add $t3, $t1, $t2			# Add them
				div $t3, $t3, 2				# Divide... (and conquer!)
				sub $t3, $t4, $t3			# D(i,j) = 255 - C(i,j)
				sb $t3, ($a2)				# Store in final buffer
				addi $a0, $a0, 1			# Prepare to load next byte
				addi $a1, $a1, 1			# ...
				addi $a2, $a2, 1			# ...
				
				j joinmatrix
				addi $t0, $t0, -1			# Do it while t0 > 0
				
endcontour:		jr $ra
				nop
###############################################################################
# End program execution here...
end:
