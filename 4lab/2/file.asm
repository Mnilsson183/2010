.data 
src BYTE "src", 0
dest BYTE LENGTHOF src DUP(?), 0
.code
mov ecx, LENGTHOF src
l1:
	mov dest[ecx * 2], src[ecx * 2]
	loop l1

