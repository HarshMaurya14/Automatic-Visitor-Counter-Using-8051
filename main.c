#include<reg51.h>
#include<intrins.h>

// LCD Pin Definitions
sbit RS = P2^0;
sbit RW = P2^1;
sbit EN = P2^2;
#define LCD_DATA P2

// Sensor Pin Definitions
sbit entry_sensor = P3^2;  // Entry sensor (INT0)
sbit exit_sensor = P3^3;   // Exit sensor (INT1)
sbit relay_bulb = P3^5; 
// Global variable for visitor count
unsigned int count = 0;

// Function prototypes
void lcd_init();
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_string(char *);
void delay(unsigned int);
void display_count();
void relay( );

void main() {
 relay_bulb = 0; // Initialize LCD
    lcd_init();
    
    // Display initial message
    lcd_cmd(0x80);  // Move cursor to first line
    lcd_string("Visitor Counter");
    lcd_cmd(0xC0);  // Move cursor to second line
    lcd_string("Count: 0");
    
    // Configure interrupts for sensors
    IT0 = 1;        // Edge triggered interrupt for INT0 (entry)
    IT1 = 1;        // Edge triggered interrupt for INT1 (exit)
    EX0 = 1;        // Enable INT0 interrupt
    EX1 = 1;        // Enable INT1 interrupt
    EA = 1;         // Global interrupt enable
    
    while(1) {
     // Main loop does nothing, all work is done in interrupts
    }
}

// Entry sensor interrupt (INT0)
void entry_sensor_isr() interrupt 0 {
    delay(10);      // Debounce delay
    if(entry_sensor == 0) { // Confirm sensor is still active
        count++;    // Increment visitor count
        display_count();
				relay();
    }
}

// Exit sensor interrupt (INT1)
void exit_sensor_isr() interrupt 2 {
    delay(10);      // Debounce delay
    if(exit_sensor == 0) {  // Confirm sensor is still active
        if(count > 0) {     // Prevent negative count
            count--;        // Decrement visitor count   
					display_count();
					relay ();
        }
    }
}

// Display count on LCD
void display_count() {
    lcd_cmd(0xC6);  // Position cursor at count location
    
    if(count < 10) {
        lcd_data(count + '0');
        lcd_data(' ');  // Clear extra digit if count decreased from 2-digit to 1-digit
    }
    else if(count < 100) {
        lcd_data((count/10) + '0');
        lcd_data((count%10) + '0');
    }
    else {
        // If count exceeds 99, display "FF" (full)
        lcd_string("FF");
    }
}

void relay( )
	
{
	
if(count > 0)
{
	relay_bulb = 1;
}
else
{
	relay_bulb = 0;
}}

// LCD Initialization
void lcd_init() {
    delay(20);      // Power-on delay
    
    // 4-bit initialization sequence
    lcd_cmd(0x02);  // 4-bit mode
    lcd_cmd(0x28);  // 2 lines, 5x7 matrix
    lcd_cmd(0x0C);  // Display on, cursor off
    lcd_cmd(0x06);  // Increment cursor
    lcd_cmd(0x01);  // Clear display
    delay(2);
}

// Send command to LCD
void lcd_cmd(unsigned char cmd) {
    RS = 0;         // Command mode
    RW = 0;         // Write mode
    
    // Send higher nibble
    LCD_DATA = (LCD_DATA & 0x0F) | (cmd & 0xF0);
    EN = 1;
    delay(1);
    EN = 0;
    delay(1);
    
    // Send lower nibble
    LCD_DATA = (LCD_DATA & 0x0F) | ((cmd << 4) & 0xF0);
    EN = 1;
    delay(1);
    EN = 0;
    delay(1);
}

// Send data to LCD
void lcd_data(unsigned char dat) {
    RS = 1;         // Data mode
    RW = 0;         // Write mode
    
    // Send higher nibble
    LCD_DATA = (LCD_DATA & 0x0F) | (dat & 0xF0);
    EN = 1;
    delay(1);
    EN = 0;
    delay(1);
    
    // Send lower nibble
    LCD_DATA = (LCD_DATA & 0x0F) | ((dat << 4) & 0xF0);
    EN = 1;
    delay(1);
    EN = 0;
    delay(1);
}

// Send string to LCD
void lcd_string(char *str) {
    while(*str) {
        lcd_data(*str++);
    }
}

// Delay function
void delay(unsigned int ms) {
    unsigned int i, j;
    for(i=0; i<ms; i++)
        for(j=0; j<1275; j++);
}
