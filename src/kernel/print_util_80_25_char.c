unsigned char* vidmem = (char*)0xB8000+HIGHER_HALF; //It would be 0xb8000, but we mapped the kernel to 0xc0000000.
void putch_color(char c, char color){
	if(c == '\r'){
		xpos = 0;
	}else if(c == '\n'){
		xpos = 0;
		ypos++;
	}else if(c == '\t'){
		for(uint8_t i = 0; i < 5; i++)
			putch_color(' ',color);
	}else{
		int pos = (xpos+(ypos*80))*2;
		vidmem[pos] = c;
		vidmem[pos+1] = color;
		xpos++;
		if(xpos >= 80){
			ypos++;
			xpos = 0;
		}
	}
	while(ypos >= 25){
		scroll();
	}
	update_cursor();
}

void clearScreen(){
	for(int y=0; y<25; y++){
		for(int x=0; x<80; x++){
			vidmem[(x+(y*80))*2] = ' ';
		}
	}
	xpos = 0;
	ypos = 0;
}

void setAllColor(char color){
	for(int y=0; y<25; y++){
		for(int x=0; x<80; x++){
			vidmem[(x+(y*80))*2+1] = color;
		}
	}
	setColor(color);
}

void center_print(char* c, char color){
	center_print_base(c, color, 80);
}

void update_cursor(){
	uint16_t position=(ypos*80) + xpos;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(position&0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((position>>8)&0xFF));
}

void scroll(){
	uint16_t i = 80*2;
	while(i < 80*25*2){
		vidmem[i-(80*2)] = vidmem[i];
		i++;
	}
	i = 80*2*24;
	while(i < 80*25*2){
		vidmem[i++] = ' ';
		vidmem[i++] = 0x07;
	}
	ypos--;
}

void PANIC_base(char *error, char *msg){
	clearScreen();
	setAllColor(0x9f);
	println("Good job, you crashed it.\nAnyway, here's the details, since you probably need them.\nDon't mess it up again.\n");
	println(error);
	println(msg);
}