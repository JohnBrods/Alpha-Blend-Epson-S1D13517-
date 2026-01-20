                                                    /*Anyone is free to copy, modify, publish, use, compile or
                                                    distribute this software, either in source code form or as a compiled
                                                    binary, for non-commercial use only. (i.e. YOU MAY NOT SELL IT)
                                                    John B 4/12/2022
                                                    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
                                                    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
                                                    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
                                                    IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
                                                    OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
                                                    ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
                                                    OTHER DEALINGS IN THE SOFTWARE.*/
                                                    //This C file contains my everything to get a Seiko Epson S1D13517-
                                                    //Display Controller to work with a 24 bit colour LCD, 800x480 LCD.
                                                    //Initialise_SDCARD & Read pictures, no library required. It will load 13-
                                                    // pictures into the SDRAM then display them from the memory.
                                                    //It will 'Alpha Blend' 2 images then show the result.
                                                    //Demonstrated on YouTube 4/12/2022.
                                                    //Another First of it's kind on YouTube.
                                                    //Inproved Text Message For Whole Program 2nd December 2022
                                                    //Improved Sd Card Init with debug tools.
                                                    //Now With Simeple Write_Text Function
                                                    //Write_number and write hexbyte too.

//Started Epson Programming 18:30 11/November 2022  Alpha blend working 4th December 2022.
//This Is A Very Similar C File  The Original, Just Improved, Big Changes So Version 2.
//20 - 01 - 2026

#include <stdint.h>
//FontName : Tahoma18x20
//FontSize : 18 x 20

const uint8_t Letter_Font[] = {     //letter font now includes zero to nine

   0x00,0x3E,0x00,0x80,0xFF,0x00,0x80,0xE3,0x00,0xC0,0xC1,0x01,0xC0,0xC1,0x01,0xE0,0x80,0x03,0xE0,0x80,0x03,0xE0,0x80,0x03,0xE0,0x80,0x03,0xE0,0x80,0x03,
   0xE0,0x80,0x03,0xE0,0x80,0x03,0xE0,0x80,0x03,0xE0,0x80,0x03,0xE0,0x80,0x03,0xC0,0xC1,0x01,0xC0,0xC1,0x01,0x80,0xE3,0x00,0x80,0xFF,0x00,0x00,0x3E,0x00, // Code for char num 48
   0x00,0x18,0x00,0x00,0x1C,0x00,0x00,0x1E,0x00,0xC0,0x1F,0x00,0xC0,0x1F,0x00,0x00,0x1C,0x00,0x00,0x1C,0x00,0x00,0x1C,0x00,0x00,0x1C,0x00,0x00,0x1C,0x00,
   0x00,0x1C,0x00,0x00,0x1C,0x00,0x00,0x1C,0x00,0x00,0x1C,0x00,0x00,0x1C,0x00,0x00,0x1C,0x00,0x00,0x1C,0x00,0x00,0x1C,0x00,0xC0,0xFF,0x01,0xC0,0xFF,0x01, // Code for char num 49
   0x00,0x3F,0x00,0xC0,0x7F,0x00,0xC0,0xE1,0x00,0x40,0xC0,0x01,0x00,0xC0,0x01,0x00,0xC0,0x01,0x00,0xC0,0x01,0x00,0xC0,0x01,0x00,0xE0,0x00,0x00,0xE0,0x00,
   0x00,0x70,0x00,0x00,0x78,0x00,0x00,0x3C,0x00,0x00,0x1C,0x00,0x00,0x0E,0x00,0x00,0x07,0x00,0x80,0x03,0x00,0xC0,0x01,0x00,0xC0,0xFF,0x03,0xC0,0xFF,0x03, // Code for char num 50
   0x00,0x3F,0x00,0xC0,0xFF,0x00,0xC0,0xE1,0x01,0x40,0xC0,0x01,0x00,0xC0,0x01,0x00,0xC0,0x01,0x00,0xC0,0x01,0x00,0xF0,0x00,0x00,0x3E,0x00,0x00,0x3E,0x00,
   0x00,0xE0,0x00,0x00,0xC0,0x00,0x00,0xC0,0x01,0x00,0xC0,0x01,0x00,0xC0,0x01,0x00,0xC0,0x01,0x20,0xE0,0x00,0xE0,0xF0,0x00,0xE0,0x7F,0x00,0x80,0x1F,0x00, // Code for char num 51
   0x00,0x70,0x00,0x00,0x78,0x00,0x00,0x7C,0x00,0x00,0x76,0x00,0x00,0x76,0x00,0x00,0x73,0x00,0x80,0x71,0x00,0xC0,0x70,0x00,0x60,0x70,0x00,0x60,0x70,0x00,
   0x30,0x70,0x00,0xF0,0xFF,0x03,0xF0,0xFF,0x03,0x00,0x70,0x00,0x00,0x70,0x00,0x00,0x70,0x00,0x00,0x70,0x00,0x00,0x70,0x00,0x00,0x70,0x00,0x00,0x70,0x00, // Code for char num 52
   0xC0,0xFF,0x01,0xC0,0xFF,0x01,0xC0,0x01,0x00,0xC0,0x01,0x00,0xC0,0x01,0x00,0xC0,0x01,0x00,0xC0,0x01,0x00,0xC0,0x3F,0x00,0xC0,0x7F,0x00,0x00,0xF0,0x00,
   0x00,0xE0,0x01,0x00,0xC0,0x01,0x00,0xC0,0x01,0x00,0xC0,0x01,0x00,0xC0,0x01,0x00,0xC0,0x01,0x20,0xE0,0x00,0xE0,0xF0,0x00,0xE0,0x7F,0x00,0x80,0x1F,0x00, // Code for char num 53
   0x00,0xF8,0x00,0x00,0xFE,0x00,0x00,0x87,0x00,0x80,0x03,0x00,0xC0,0x01,0x00,0xC0,0x01,0x00,0xC0,0x00,0x00,0xE0,0x7C,0x00,0xE0,0xFF,0x00,0xE0,0xE1,0x01,
   0xE0,0xC0,0x03,0xE0,0x80,0x03,0xE0,0x80,0x03,0xE0,0x80,0x03,0xE0,0x80,0x03,0xC0,0x81,0x03,0xC0,0xC1,0x01,0x80,0xE3,0x01,0x80,0xFF,0x00,0x00,0x3E,0x00, // Code for char num 54
   0xE0,0xFF,0x01,0xE0,0xFF,0x01,0x00,0xC0,0x01,0x00,0xC0,0x01,0x00,0xE0,0x00,0x00,0xE0,0x00,0x00,0x70,0x00,0x00,0x70,0x00,0x00,0x38,0x00,0x00,0x38,0x00,
   0x00,0x1C,0x00,0x00,0x1C,0x00,0x00,0x0E,0x00,0x00,0x0E,0x00,0x00,0x0E,0x00,0x00,0x07,0x00,0x00,0x07,0x00,0x80,0x03,0x00,0x80,0x03,0x00,0xC0,0x01,0x00, // Code for char num 55
   0x00,0x7E,0x00,0x80,0xFF,0x00,0xC0,0xC1,0x01,0xE0,0x80,0x03,0xE0,0x80,0x03,0xE0,0x80,0x03,0xE0,0x81,0x03,0xC0,0xC3,0x01,0x80,0xFF,0x00,0x00,0x7F,0x00,
   0xC0,0xFF,0x00,0xC0,0xE1,0x01,0xE0,0xC0,0x03,0xE0,0x80,0x03,0xE0,0x80,0x03,0xE0,0x80,0x03,0xE0,0xC1,0x03,0xC0,0xE3,0x01,0x80,0xFF,0x00,0x00,0x3E,0x00, // Code for char num 56
   0x00,0x3E,0x00,0x80,0xFF,0x00,0xC0,0xE3,0x00,0xC0,0xC1,0x01,0xE0,0xC0,0x01,0xE0,0x80,0x03,0xE0,0x80,0x03,0xE0,0x80,0x03,0xE0,0x80,0x03,0xE0,0x81,0x03,
   0xC0,0xC3,0x03,0x80,0xFF,0x03,0x00,0x9F,0x03,0x00,0x80,0x01,0x00,0xC0,0x01,0x00,0xC0,0x01,0x00,0xE0,0x00,0x80,0x70,0x00,0x80,0x3F,0x00,0x80,0x0F,0x00, // Code for char num 57
   0x80,0x07,0x00,0x80,0x07,0x00,0x80,0x07,0x00,0xC0,0x0F,0x00,0xC0,0x0F,0x00,0xC0,0x0F,0x00,0xE0,0x1C,0x00,0xE0,0x1C,0x00,0xE0,0x1C,0x00,0x70,0x38,0x00,0x70,
   0x38,0x00,0x70,0x38,0x00,0xF8,0x7F,0x00,0xF8,0x7F,0x00,0x38,0x70,0x00,0x3C,0xF0,0x00,0x1C,0xE0,0x00,0x1C,0xE0,0x00,0x1E,0xE0,0x01,0x0E,0xC0,0x01, // Code for char num 65
   0xFC,0x07,0x00,0xFC,0x1F,0x00,0x1C,0x3C,0x00,0x1C,0x38,0x00,0x1C,0x38,0x00,0x1C,0x38,0x00,0x1C,0x38,0x00,0x1C,0x1C,0x00,0xFC,0x0F,0x00,0xFC,0x1F,0x00,0x1C,
   0x38,0x00,0x1C,0x70,0x00,0x1C,0x70,0x00,0x1C,0x70,0x00,0x1C,0x70,0x00,0x1C,0x70,0x00,0x1C,0x38,0x00,0x1C,0x3C,0x00,0xFC,0x1F,0x00,0xFC,0x07,0x00, // Code for char num 66
   0x80,0x1F,0x00,0xC0,0xFF,0x00,0xF0,0xE0,0x00,0x70,0xC0,0x00,0x38,0x80,0x00,0x38,0x00,0x00,0x1C,0x00,0x00,0x1C,0x00,0x00,0x1C,0x00,0x00,0x1C,0x00,0x00,0x1C,
   0x00,0x00,0x1C,0x00,0x00,0x1C,0x00,0x00,0x1C,0x00,0x00,0x38,0x00,0x00,0x38,0x80,0x00,0x70,0xC0,0x00,0xF0,0xE0,0x00,0xE0,0xFF,0x00,0x80,0x1F,0x00, // Code for char num 67
   0xFE,0x03,0x00,0xFE,0x0F,0x00,0x0E,0x1E,0x00,0x0E,0x38,0x00,0x0E,0x70,0x00,0x0E,0x70,0x00,0x0E,0xE0,0x00,0x0E,0xE0,0x00,0x0E,0xE0,0x00,0x0E,0xE0,0x00,0x0E,
   0xE0,0x00,0x0E,0xE0,0x00,0x0E,0xE0,0x00,0x0E,0xE0,0x00,0x0E,0x70,0x00,0x0E,0x70,0x00,0x0E,0x38,0x00,0x0E,0x1E,0x00,0xFE,0x0F,0x00,0xFE,0x03,0x00, // Code for char num 68
   0xF8,0x7F,0x00,0xF8,0x7F,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0xF8,0x3F,0x00,0xF8,0x3F,0x00,0x38,
   0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0xF8,0x7F,0x00,0xF8,0x7F,0x00, // Code for char num 69
   0xF8,0x7F,0x00,0xF8,0x7F,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0xF8,0x7F,0x00,0xF8,0x7F,0x00,0x38,
   0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00, // Code for char num 70
   0x80,0x3F,0x00,0xE0,0xFF,0x00,0xF0,0xE0,0x01,0x38,0x80,0x01,0x1C,0x00,0x01,0x1C,0x00,0x00,0x0E,0x00,0x00,0x0E,0x00,0x00,0x0E,0x00,0x00,0x0E,0x00,0x00,0x0E,
   0xFC,0x01,0x0E,0xFC,0x01,0x0E,0xC0,0x01,0x0E,0xC0,0x01,0x1C,0xC0,0x01,0x1C,0xC0,0x01,0x38,0xC0,0x01,0xF0,0xC0,0x01,0xE0,0xFF,0x01,0x80,0x3F,0x00, // Code for char num 71
   0x1C,0xE0,0x00,0x1C,0xE0,0x00,0x1C,0xE0,0x00,0x1C,0xE0,0x00,0x1C,0xE0,0x00,0x1C,0xE0,0x00,0x1C,0xE0,0x00,0x1C,0xE0,0x00,0xFC,0xFF,0x00,0xFC,0xFF,0x00,0x1C,
   0xE0,0x00,0x1C,0xE0,0x00,0x1C,0xE0,0x00,0x1C,0xE0,0x00,0x1C,0xE0,0x00,0x1C,0xE0,0x00,0x1C,0xE0,0x00,0x1C,0xE0,0x00,0x1C,0xE0,0x00,0x1C,0xE0,0x00, // Code for char num 72
   0xF0,0x1F,0x00,0xF0,0x1F,0x00,0x80,0x03,0x00,0x80,0x03,0x00,0x80,0x03,0x00,0x80,0x03,0x00,0x80,0x03,0x00,0x80,0x03,0x00,0x80,0x03,0x00,0x80,0x03,0x00,0x80,
   0x03,0x00,0x80,0x03,0x00,0x80,0x03,0x00,0x80,0x03,0x00,0x80,0x03,0x00,0x80,0x03,0x00,0x80,0x03,0x00,0x80,0x03,0x00,0xF0,0x1F,0x00,0xF0,0x1F,0x00, // Code for char num 73
   0xF0,0xFF,0x00,0xF0,0xFF,0x00,0x00,0x0E,0x00,0x00,0x0E,0x00,0x00,0x0E,0x00,0x00,0x0E,0x00,0x00,0x0E,0x00,0x00,0x0E,0x00,0x00,0x0E,0x00,0x00,0x0E,0x00,0x00,
   0x0E,0x00,0x00,0x0E,0x00,0x00,0x0E,0x00,0x00,0x0E,0x00,0x00,0x0E,0x00,0x00,0x0E,0x00,0x00,0x0E,0x00,0x0C,0x07,0x00,0xFC,0x07,0x00,0xF8,0x01,0x00, // Code for char num 74
   0x1C,0xF0,0x00,0x1C,0x78,0x00,0x1C,0x3C,0x00,0x1C,0x1E,0x00,0x1C,0x0F,0x00,0x9C,0x07,0x00,0xDC,0x03,0x00,0xDC,0x01,0x00,0xFC,0x00,0x00,0xFC,0x00,0x00,0xFC,
   0x01,0x00,0xDC,0x03,0x00,0x9C,0x07,0x00,0x1C,0x07,0x00,0x1C,0x0F,0x00,0x1C,0x1E,0x00,0x1C,0x1C,0x00,0x1C,0x38,0x00,0x1C,0x78,0x00,0x1C,0xF0,0x00, // Code for char num 75
   0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,
   0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0x38,0x00,0x00,0xF8,0x3F,0x00,0xF8,0x3F,0x00, // Code for char num 76
   0x0F,0xE0,0x01,0x1F,0xF0,0x01,0x1F,0xF0,0x01,0x3F,0xF0,0x01,0x37,0xD8,0x01,0x37,0xD8,0x01,0x67,0xCC,0x01,0x67,0xCC,0x01,0xE7,0xCC,0x01,0xC7,0xC6,0x01,0xC7,
   0xC7,0x01,0x87,0xC3,0x01,0x87,0xC3,0x01,0x07,0xC1,0x01,0x07,0xC0,0x01,0x07,0xC0,0x01,0x07,0xC0,0x01,0x07,0xC0,0x01,0x07,0xC0,0x01,0x07,0xC0,0x01, // Code for char num 77
   0x3C,0xE0,0x00,0x7C,0xE0,0x00,0x7C,0xE0,0x00,0xFC,0xE0,0x00,0xDC,0xE0,0x00,0xDC,0xE1,0x00,0x9C,0xE1,0x00,0x9C,0xE1,0x00,0x1C,0xE3,0x00,0x1C,0xE3,0x00,0x1C,
   0xE7,0x00,0x1C,0xE6,0x00,0x1C,0xEE,0x00,0x1C,0xEC,0x00,0x1C,0xEC,0x00,0x1C,0xF8,0x00,0x1C,0xF8,0x00,0x1C,0xF8,0x00,0x1C,0xF0,0x00,0x1C,0xF0,0x00, // Code for char num 78
   0xE0,0x0F,0x00,0xF0,0x1F,0x00,0x3C,0x78,0x00,0x1C,0x70,0x00,0x0E,0xE0,0x00,0x0E,0xE0,0x00,0x07,0xC0,0x01,0x07,0xC0,0x01,0x07,0xC0,0x01,0x07,0xC0,0x01,0x07,
   0xC0,0x01,0x07,0xC0,0x01,0x07,0xC0,0x01,0x07,0xC0,0x01,0x0E,0xE0,0x00,0x0E,0xE0,0x00,0x1C,0x70,0x00,0x3C,0x78,0x00,0xF8,0x1F,0x00,0xE0,0x0F,0x00, // Code for char num 79
   0xFC,0x07,0x00,0xFC,0x1F,0x00,0x1C,0x3C,0x00,0x1C,0x38,0x00,0x1C,0x70,0x00,0x1C,0x70,0x00,0x1C,0x70,0x00,0x1C,0x70,0x00,0x1C,0x70,0x00,0x1C,0x38,0x00,0x1C,
   0x3C,0x00,0xFC,0x1F,0x00,0xFC,0x07,0x00,0x1C,0x00,0x00,0x1C,0x00,0x00,0x1C,0x00,0x00,0x1C,0x00,0x00,0x1C,0x00,0x00,0x1C,0x00,0x00,0x1C,0x00,0x00, // Code for char num 80
   0xE0,0x0F,0x00,0xF0,0x1F,0x00,0x3C,0x78,0x00,0x1C,0x70,0x00,0x0E,0xE0,0x00,0x0E,0xE0,0x00,0x07,0xC0,0x01,0x07,0xC0,0x01,0x07,0xC0,0x01,0x07,0xC0,0x01,0x07,
   0xC0,0x01,0x07,0xC3,0x01,0x07,0xC3,0x01,0x07,0xC3,0x01,0x0E,0xE7,0x00,0x0E,0xE6,0x00,0x1C,0x7E,0x00,0x3C,0x78,0x00,0xF0,0x3F,0x00,0xE0,0x1F,0x00, // Code for char num 81
   0xFC,0x07,0x00,0xFC,0x0F,0x00,0x1C,0x1C,0x00,0x1C,0x38,0x00,0x1C,0x38,0x00,0x1C,0x38,0x00,0x1C,0x38,0x00,0x1C,0x38,0x00,0x1C,0x1C,0x00,0x1C,0x1E,0x00,0xFC,
   0x0F,0x00,0xFC,0x03,0x00,0x9C,0x07,0x00,0x1C,0x0F,0x00,0x1C,0x1E,0x00,0x1C,0x1C,0x00,0x1C,0x3C,0x00,0x1C,0x78,0x00,0x1C,0xF0,0x00,0x1C,0xE0,0x01, // Code for char num 82
   0xC0,0x0F,0x00,0xF0,0x3F,0x00,0x78,0x38,0x00,0x1C,0x20,0x00,0x1C,0x00,0x00,0x1C,0x00,0x00,0x1C,0x00,0x00,0x3C,0x00,0x00,0xF8,0x00,0x00,0xF0,0x0F,0x00,0xC0,
   0x1F,0x00,0x00,0x3C,0x00,0x00,0x78,0x00,0x00,0x70,0x00,0x00,0x70,0x00,0x04,0x70,0x00,0x0C,0x38,0x00,0x3C,0x3C,0x00,0xFC,0x1F,0x00,0xE0,0x07,0x00, // Code for char num 83
   0xFF,0xFF,0x01,0xFF,0xFF,0x01,0x80,0x03,0x00,0x80,0x03,0x00,0x80,0x03,0x00,0x80,0x03,0x00,0x80,0x03,0x00,0x80,0x03,0x00,0x80,0x03,0x00,0x80,0x03,0x00,0x80,
   0x03,0x00,0x80,0x03,0x00,0x80,0x03,0x00,0x80,0x03,0x00,0x80,0x03,0x00,0x80,0x03,0x00,0x80,0x03,0x00,0x80,0x03,0x00,0x80,0x03,0x00,0x80,0x03,0x00, // Code for char num 84
   0x1C,0xE0,0x00,0x1C,0xE0,0x00,0x1C,0xE0,0x00,0x1C,0xE0,0x00,0x1C,0xE0,0x00,0x1C,0xE0,0x00,0x1C,0xE0,0x00,0x1C,0xE0,0x00,0x1C,0xE0,0x00,0x1C,0xE0,0x00,0x1C,
   0xE0,0x00,0x1C,0xE0,0x00,0x1C,0xE0,0x00,0x1C,0xE0,0x00,0x1C,0xE0,0x00,0x1C,0xE0,0x00,0x38,0x70,0x00,0x78,0x78,0x00,0xF0,0x3F,0x00,0xC0,0x0F,0x00, // Code for char num 85
   0x0E,0xC0,0x01,0x1E,0xE0,0x01,0x1C,0xE0,0x00,0x1C,0xE0,0x00,0x3C,0xF0,0x00,0x38,0x70,0x00,0x38,0x70,0x00,0x78,0x78,0x00,0x70,0x38,0x00,0x70,0x38,0x00,0xF0,
   0x3C,0x00,0xE0,0x1C,0x00,0xE0,0x1C,0x00,0xE0,0x1C,0x00,0xC0,0x0F,0x00,0xC0,0x0F,0x00,0xC0,0x0F,0x00,0x80,0x07,0x00,0x80,0x07,0x00,0x80,0x07,0x00, // Code for char num 86
   0x06,0x18,0x60,0x06,0x3C,0x60,0x0E,0x3C,0x70,0x0E,0x3C,0x70,0x0E,0x3C,0x70,0x0E,0x76,0x70,0x1C,0x66,0x38,0x1C,0x66,0x38,0x1C,0x66,0x38,0x1C,0xE3,0x38,0x38,
   0xC3,0x1C,0x38,0xC3,0x1C,0x38,0xC3,0x1C,0xB8,0xC1,0x1D,0xF0,0x81,0x0F,0xF0,0x81,0x0F,0xF0,0x81,0x0F,0xF0,0x81,0x0F,0xE0,0x00,0x07,0xE0,0x00,0x07, // Code for char num 87
   0x0E,0xC0,0x01,0x1C,0xE0,0x00,0x38,0x70,0x00,0x38,0x70,0x00,0x70,0x38,0x00,0xE0,0x1C,0x00,0xE0,0x1C,0x00,0xC0,0x0F,0x00,0xC0,0x07,0x00,0x80,0x07,0x00,0x80,
   0x07,0x00,0xC0,0x07,0x00,0xC0,0x0F,0x00,0xE0,0x1C,0x00,0xE0,0x1C,0x00,0x70,0x38,0x00,0x38,0x70,0x00,0x38,0x70,0x00,0x1C,0xE0,0x00,0x0E,0xC0,0x01, // Code for char num 88
   0x0E,0xE0,0x00,0x0E,0xE0,0x00,0x1C,0x70,0x00,0x3C,0x78,0x00,0x38,0x38,0x00,0x78,0x3C,0x00,0x70,0x1E,0x00,0xE0,0x0E,0x00,0xE0,0x0F,0x00,0xC0,0x07,0x00,0xC0,
   0x03,0x00,0x80,0x03,0x00,0x80,0x03,0x00,0x80,0x03,0x00,0x80,0x03,0x00,0x80,0x03,0x00,0x80,0x03,0x00,0x80,0x03,0x00,0x80,0x03,0x00,0x80,0x03,0x00, // Code for char num 89
   0xFC,0x7F,0x00,0xFC,0x7F,0x00,0x00,0x70,0x00,0x00,0x38,0x00,0x00,0x1C,0x00,0x00,0x1C,0x00,0x00,0x0E,0x00,0x00,0x0E,0x00,0x00,0x07,0x00,0x80,0x03,0x00,0x80,
   0x03,0x00,0xC0,0x01,0x00,0xE0,0x00,0x00,0xE0,0x00,0x00,0x70,0x00,0x00,0x70,0x00,0x00,0x38,0x00,0x00,0x1C,0x00,0x00,0xFC,0x7F,0x00,0xFC,0x7F,0x00, // Code for char num 90
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x03,0x00,0x80,0x03,0x00,0x80,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00 // Code for char 46 DOT
  };

const uint8_t Letter_Font_Start = 0;
const uint8_t Letter_Font_Length_Bytes = 60;
const uint8_t Letter_Font_Width = 24;      // full bytes of pixels   8,16,24,32,40 etc
const uint8_t Letter_Font_Height = 20;
const uint8_t Letter_Font_Spacing = 2;

#define black_Out         Write_Data_EpsonS1D13517(0b0000000000000000)
#define red_Out           Write_Data_EpsonS1D13517(0b1111100000000000)
#define orange_Out        Write_Data_EpsonS1D13517(0b1111110011100001)
#define yellow_Out        Write_Data_EpsonS1D13517(0b1111111111100000)
#define green_Out         Write_Data_EpsonS1D13517(0b0000011111100000)
#define blue_Out          Write_Data_EpsonS1D13517(0b0000000000010111)
#define violet_Out        Write_Data_EpsonS1D13517(0b1000100100011111)
#define olive_Out         Write_Data_EpsonS1D13517(0b1000010010100011)
#define white_Out         Write_Data_EpsonS1D13517(0b1111111111111111)
#define magenta_Out       Write_Data_EpsonS1D13517(0b1111100000011111)
#define lime_Out          Write_Data_EpsonS1D13517(0b1010111100100000)
#define babypowder_Out   Write_Data_EpsonS1D13517(0b1110111010001111)
#define cyan_Out          Write_Data_EpsonS1D13517(0b0000011111111111)
#define lavenderblush_Out Write_Data_EpsonS1D13517(0b1111101111000111)
#define beige_Out         Write_Data_EpsonS1D13517(0b1111010011000111)


  const uint8_t black = 1;
  const uint8_t red = 2;
  const uint8_t orange = 3;
  const uint8_t yellow = 4;
  const uint8_t green = 5;
  const uint8_t blue = 6;
  const uint8_t violet = 7;
  const uint8_t olive = 8;
  const uint8_t white = 9;
  const uint8_t magenta = 10;
  const uint8_t lime = 11;
  const uint8_t baby_Powder = 12;
  const uint8_t cyan = 13;
  const uint8_t lavenderblush = 14;
  const uint8_t beige = 15;

 //sbit TFT_RD  at LATC4_bit;
  //sbit TFT_WR  at LATC3_bit;
  //sbit TFT_RST_Direction at TRISD0_bit;   //RESET  Active low input

  #define  SD_Card_Chip_Select  LATA9_bit
  #define  Epson_CS LATG15_bit              //WIRED TO LATD9 BUT THAT IS AN ADDRESS LINE SO BRIDGED TO LATG15 //EPSON CHIP SELECT (WITH PULL-UP) NOT FITTED RESISTOR YET
  #define  Epson_HDC    LATG12_bit          //THE HD/C# INPUT PIN IS USED TO DISTINGUISH BETWEEN ADDRESS AND DATA LINKED ON PCB FROM PIC PIN 140 TO HD/C PIN
  #define  PMP_WRITE    LATC3_bit           //PMWR  WRITE  EBIWE/AN20/RPC3/PMWR/RC3 PIN 12
  #define  PMP_READ     LATC4_bit           //PMRD  READ   EBIOE/AN19/RPC4/PMRD/RC4 PIN 13


void Write_Command_EpsonS1D13517(uint8_t Command) {
  Epson_HDC = 0;                              //RS = 0 NOT DATA  D/C = 0    SET RS LINE LOW FOR COMMAND ON EPSON CHIP
  PMDIN = Command;
  while(PMMODE & 0x8000); //Busy bit
}

void Write_Data_EpsonS1D13517(uint16_t _data) {
  Epson_HDC = 1;                               //RS = 1 = DATA   D/C = 1    SET RS LINE HIGH FOR DATA  ON EPSON CHIP
  PMDIN = _data;
  while(PMMODE & 0x8000);                      //Busy bit
}

//==============================================================

void Init_16Bit_PMP() {     // zero wait time is 8 ns strobe @224MHz   1=18.5ns  2=28ns

  PMAEN  = 0;               //  5=55ns @224MHz and sram corrupt   3=36.5 to 37ns =2.240 MHz   4 = 46ns
  PMMODE = 0;
 // PMCONBits.DUALBUF = 1;  //DUAL BUFFER FOR IN AND OUT  NOT AVAILABLE ON ECM
  PMMODEbits.MODE = 2;      //Master 2     Slave =1
  PMMODEbits.WAITB = 0;     //WAITB<1:0>: Data Setup before a Read/Write Strobe Wait States bits(1) 11 = Data wait of 4 TPB; multiplexed address phase of 4 TPB  10 = Data wait of 3 TPB; multiplexed address phase of 3 TPB 01 = Data wait of 2 TPB; multiplexed address phase of 2 TPB 00 = Data wait of 1 TPB; multiplexed address phase of 1 TPB (default)
  PMMODEbits.WAITM = 1;     //1111 = Wait of 16 TPB --0001 = Wait of 2 TPB-- 0000 = Wait of 1 TPB (default)STROBE PULSE WIDTH
  PMMODEbits.WAITE = 0;     //bit 1-0WAITE<1:0>: Data Hold After Read/Write Strobe Wait States bits(1)

  PMMODEbits.MODE16 = 1;    // 1 = 16-bit mode: a read or write to the data register invokes a single 16-bit transfer   For read operations  11 = Wait of 3 TPB  00 = Wait of 0 TPB (default)
  PMCONbits.CSF = 0;        //Chip Select Bit
  PMCONbits.PTRDEN = 1;     //READ STROBE
  PMCONbits.PTWREN = 1;     //WRITE STROBE
  PMCONbits.PMPEN = 1;      //PMP ENABLE
  PMCONbits.ON = 1;
}

//==============================================================

void Init_MCU() {

   ANSELA = 0;
   ANSELB = 0;
   ANSELC = 0;
   ANSELD = 0;
   ANSELE = 0;
   ANSELF = 0;
   ANSELG = 0;
   ANSELH = 0;
   ANSELJ = 0;

   TRISA = 0;
   TRISB = 0;
   TRISC = 0;
   TRISD = 0;
   TRISE = 0;
   TRISF = 0;
   TRISG = 0;
   TRISH = 0;
   TRISJ = 0;
   TRISK = 0;

   TRISD14_Bit = 1;
   SDI3R  = 0b1011; // = RPD14      PAGE 251     RD14 = SDI3    SPI3
   RPB10R = 0b0111; // = SDO3       PAGE 254     RB10 = SD03    SPI3

   PORTA=0;PORTB=0;PORTC=0;PORTD=0;PORTE=0;PORTF=0;PORTG=0; PORTH=0; PORTJ=0;  PORTK=0;

   //TRISA14_Bit = 1;
   //INT3R = 0b1101; // = RPA14   Clock In Pin RA14

   JTAGEN_bit = 0;

   LATC13_Bit = 1;  //RC13 = LCD DISPLAY RESET //NOT CONNECTED
   LATH15_bit = 1;  //PIN31 LCD DISPLAY (DISP)  DISPLAY ENABLE
   LATD0_bit = 1;   //EPSON CHIP RESET (WITH PULL-UP) NOT FITTED RESISTOR YET
   LATG15_bit = 1;   //EPSON CHIP SELECT (WITH PULL-UP) RESISTOR NOT FITTED YET
}

//==============================================================

void Initialise_EpsonS1D13517_5_Inch(){

    Epson_CS = 0;

    Write_Command_EpsonS1D13517(0x2A);
    Write_Data_EpsonS1D13517(0);         //Display Off

    /////////////////////////////////////////PAGE 129 FOR EXAMPLES //////////////////////////////////////////////////////////

    Write_Command_EpsonS1D13517(0x04);
    Write_Data_EpsonS1D13517(0x17);      //PLLCLK = 1MHz (=24MHz/24=CLKI/PLL_D)         (REG[04h] bit 7 = PLL ENABLE   PAGE 49
    Write_Command_EpsonS1D13517(0x06);
    Write_Data_EpsonS1D13517(0x51);      //VCO = 142-180MHz
    Write_Command_EpsonS1D13517(0x08);   //PLL Divide Select REG 8
    Write_Data_EpsonS1D13517(0x01);      //PLLCLK is divided by 2
    Write_Command_EpsonS1D13517(0x0C);   //PLL N Divider
    Write_Data_EpsonS1D13517(0x59);      //Target Frequency = 90MHz; NN = 180; CLKI = 24MHz; PLL_D = 24:1
    Write_Command_EpsonS1D13517(0x12);   //Clock Source Select Register
    Write_Data_EpsonS1D13517(0x01);
    Write_Command_EpsonS1D13517(0x04);   //Enable PLL
    Write_Data_EpsonS1D13517(0x97);      //was 9D bit 7 enables the ppl
    Write_Command_EpsonS1D13517(0x0E);   //Spread Spectrum modulation enabled with default spread of +/-0.25ns
    Write_Data_EpsonS1D13517(0x3F);

    Delay_ms(1);

    Write_Command_EpsonS1D13517(0x12);
    Write_Data_EpsonS1D13517(0x81);     //was 81h 0x92 = 36 MHz 0x81 = 24MHz   82 = 30 mhz and 90 mhz on ram  81 = 30 mhz pixel clock

    //////////////PANEL SETTINGS BELOW ///// REGISTERS AUTO-INCREMENT ///////////// MODE REGISTERS ON PAGE 52 /////////////////////////////////////////////////////////

    Write_Command_EpsonS1D13517(0x14);   //LCD Panel Type Register
    Write_Data_EpsonS1D13517(4);         //INPUT IMAGE FORMAT PAGE 61
    Write_Command_EpsonS1D13517(0x16);   //Horizontal Display Width Register (HDISP) PAGE 44
    Write_Data_EpsonS1D13517(0x63);      //800 + 1 PIXELS WIDE DIVIDE BY 8 = 100  = 100  HEX=64
    Write_Command_EpsonS1D13517(0x18);   //Horizontal Non-Display Period Register (HNDP)
    Write_Data_EpsonS1D13517(0x7F);      //WAS 0X26 FAST 65 HZ 7F = 55.5 HZ
    Write_Command_EpsonS1D13517(0x1A);   //Vertical Display Height Register 0 (VDISP)
    Write_Data_EpsonS1D13517(0xDF);      //LOW BYTE OF DISPLAY HEIGHT
    Write_Command_EpsonS1D13517(0x1C);
    Write_Data_EpsonS1D13517(0x01);      //HIGH BYTE OF DISPLAY HEIGHT  1DF = 479
    Write_Command_EpsonS1D13517(0x1E);   //Vertical Non-Display Period Register (VNDP)   PAGE 62
    Write_Data_EpsonS1D13517(0x25);      //DECIMAL 15 GAVE 65 HZ   hex16 54 hz but 2ms pulse width 0X25 = 51 HZ AND NEARLY 3ms vertical pulse width
    Write_Command_EpsonS1D13517(0x20);   //PHS Pulse Width Register (HSW)
    Write_Data_EpsonS1D13517(0x27);      //was 0x0f fast 65 hz 0x27 = same
    Write_Command_EpsonS1D13517(0x22);   //PHS Pulse Start Position Register (HPS)
    Write_Data_EpsonS1D13517(0x78);      //was 0x10 fast 65 hz  0x78 = same 54 hz
    Write_Command_EpsonS1D13517(0x24);   //PVS Pulse Width Register (VSW)
    Write_Data_EpsonS1D13517(0x0A);      // 5 = 1ms   0X0A = STILL 2ms
    Write_Command_EpsonS1D13517(0x26);   //PVS Pulse Start Position Register (VPS)     PAGE 64
    Write_Data_EpsonS1D13517(10);        //was 4 LINES
    Write_Command_EpsonS1D13517(0x28);   //PCLK Polarity Register
    Write_Data_EpsonS1D13517(0x80);      //PCLK Falling edgeSDCLK

    //////////////SDRAM SETTINGS BELOW //////////////////////////////

    Write_Command_EpsonS1D13517(0x82);
    Write_Data_EpsonS1D13517(0x03);       //SDRAM memory size = 128MBits page 84
    Write_Command_EpsonS1D13517(0x8C);
    Write_Data_EpsonS1D13517(0xFF);       //SDRAM Refresh Rate
    Write_Command_EpsonS1D13517(0x8E);
    Write_Data_EpsonS1D13517(0x03);       //SDRAM Refresh Counter
    Write_Command_EpsonS1D13517(0x90);    //REG[90h] SDRAM Write Buffer Memory Size Register 0 PAGE 86  & 87
    Write_Data_EpsonS1D13517(71);         //VGA 1M BYTE 40h --  71 * 16384 = 1,163,264 BYTES PER BUFFER    11 C000h 800x480 = 384'000 times 3 = 1,152,000 BYTES PER PIXEL
                                                                    //16k = 2^14
    Write_Command_EpsonS1D13517(0x84);
    Write_Data_EpsonS1D13517(0x82);       //SDRAM refresh page 84

    Write_Command_EpsonS1D13517(0x68);    //?? Software ResetREG[68h] = E8h => 00hPLL
    Write_Data_EpsonS1D13517(0xE8);

    Write_Command_EpsonS1D13517(0x68);
    Write_Data_EpsonS1D13517(0x01);       //Enable SDCLK page 51  When REG[68h] bit 0 = 1b, SDCLK is enabled and all internal clocks may be also enabled.

    /////////////////NORMAL OPERATION HERE ???????????????????

   /*Write_Command_EpsonS1D13517(0x54);   //IF ALL SET TO 255 / 0xFF IT WILL MAKE WHITE TRANSPARENT
    Write_Data_EpsonS1D13517(255);       //Transparency Key Color red Register
    Write_Command_EpsonS1D13517(0x56);
    Write_Data_EpsonS1D13517(255);       //Transparency Key Color green Register PAGE 74   WHITE
    Write_Command_EpsonS1D13517(0x58);
    Write_Data_EpsonS1D13517(255);       //Transparency Key Color blue Register PAGE 75    WHITE*/


  /*Write_Command_EpsonS1D13517(0x54);
    Write_Data_EpsonS1D13517(200);       //red Transparency black
    Write_Command_EpsonS1D13517(0x56);
    Write_Data_EpsonS1D13517(50);       //green Transparency black
    Write_Command_EpsonS1D13517(0x58);
    Write_Data_EpsonS1D13517(40);       //blue Transparency black*/

    Write_Command_EpsonS1D13517(0xB2);     //REG[B2h] Interrupt Control Register   page 92
    Write_Data_EpsonS1D13517(0b00010000);  //INTERRUPTS   alpha blend
    Write_Command_EpsonS1D13517(0xB6);
    Write_Data_EpsonS1D13517(0x00);      //INTERRUPTS        REG[6AH] NON-DISPLAY PERIOD CONTROL / STATUS REGISTER PAGE 79

  /*////PIP 1 ADDRESS
    Write_Command_EpsonS1D13517(0x2C);   //page 66
    Write_Data_EpsonS1D13517(0x00);
    Write_Command_EpsonS1D13517(0x2E);    //page 66
    Write_Data_EpsonS1D13517(0x00);
    Write_Command_EpsonS1D13517(0x30);    //page 66
    Write_Data_EpsonS1D13517(0x28);       //140000  BUFFER 2

    ///PIP 2 ADDRESS
    Write_Command_EpsonS1D13517(0x3E);   //page 66
    Write_Data_EpsonS1D13517(0x00);
    Write_Command_EpsonS1D13517(0x40);    //page 66
    Write_Data_EpsonS1D13517(0x00);
    Write_Command_EpsonS1D13517(0x42);    //page 66
    Write_Data_EpsonS1D13517(0x50);       //280000 BUFFER 3 00280000*/


    Write_Command_EpsonS1D13517(0x6A);    //REG[6Ah] Non-Display Period Control / Status Register PAGE 79
    Write_Data_EpsonS1D13517(0b00000011);  // 11b==INT     01b==Vertical Non-Display Period     00b==Horizontal Non-Display Period   10b==HDP OR’d with VDP

    Epson_CS = 1;
    Delay_ms(100); // <<< it does need this delay but not sure how long, MORE THAN ZERO
    //REG[6AH] NON-DISPLAY PERIOD CONTROL / STATUS REGISTER PAGE 79
}

//==============================================================


uint16_t background_Colour;
void Clear_Screen_S1D13517(uint16_t colour){

    uint8_t display_enable_bit = 0b0001;                                       //works with register 2A
    uint8_t write_Bit          = 0b0000;                                       //works with register Hex 52
    uint8_t sdram_Location_Number = 0;                                         //sdram_Location_Number = zero to 15
    uint32_t i;
    const uint16_t Number_Of_Pixels = 384000;
    background_Colour = colour;

    Epson_CS = 0;
    Write_Command_EpsonS1D13517(0x52);                                         //page 73 Input Mode Register  BITS 7,6,5,4 ARE INPUT BUFFER NUMBERS 1 TO 16
    Write_Data_EpsonS1D13517(sdram_Location_Number<<4 | write_Bit);            //BIT ZERO HERE MEANS THE MEMORY LOCATION (TOP 4 BITS) IS BEING "WRITTEN TO" Buffer 0  WORKS FOR MAIN WINDOW ONLY

    //REGISTERS AUTO-INCREMENT !
    Write_Command_EpsonS1D13517(0x5A);    //set window
    Write_Data_EpsonS1D13517(0);          //REG[5Ah] = 00h: Xstart = 0001
    Write_Data_EpsonS1D13517(0);          //REG[5Ch] = 00h, REG[5Eh] = 00h: Ystart = 0001
    Write_Data_EpsonS1D13517(0);          //REG[5Eh] = 00h: Ystart = 0001
    Write_Data_EpsonS1D13517(0xC6);       //REG[60h] = C6h: Xend = 800
    Write_Data_EpsonS1D13517(0x77);       //REG[62h] = 77h, REG[64h] = 03h: Yend = 480
    Write_Data_EpsonS1D13517(0x03);       //REG[64h] = 03h: Yend = 480

    switch(colour)  {

     case 1:     for(i=0;i<Number_Of_Pixels;i++){
                 black_Out;
                 background_Colour = 0x00;
                 } break;
     case 2:     for(i=0;i<Number_Of_Pixels;i++){
                 red_Out;
                 background_Colour = 0xF800;
                 } break;
     case 3:     for(i=0;i<Number_Of_Pixels;i++){
                 orange_Out;
                 background_Colour = 0xFCE1;
                 } break;
     case 4:     for(i=0;i<Number_Of_Pixels;i++){
                 yellow_Out;
                 background_Colour = 0xFFE0;
                 } break;
     case 5:     for(i=0;i<Number_Of_Pixels;i++){
                 green_Out;
                 background_Colour = 0x07E0;
                 } break;
     case 6:     for(i=0;i<Number_Of_Pixels;i++){
                 blue_Out;
                 background_Colour = 0x01F;
                 } break;
     case 7:     for(i=0;i<Number_Of_Pixels;i++){
                 violet_Out;
                 background_Colour = 0x891F;
                 } break;
     case 8:     for(i=0;i<Number_Of_Pixels;i++){
                 olive_Out;
                 background_Colour = 0x84A3;
                 } break;
     case 9:     for(i=0;i<Number_Of_Pixels;i++){
                 white_Out;
                 background_Colour = 0xFFFF;
                 } break;
     case 10:    for(i=0;i<Number_Of_Pixels;i++){
                 magenta_Out;
                 background_Colour = 0xF81F;
                 } break;
     case 11:    for(i=0;i<Number_Of_Pixels;i++){
                 lime_Out;
                 background_Colour = 0xAF20;
                 } break;
     case 12:    for(i=0;i<Number_Of_Pixels;i++){
                 babypowder_Out;
                 background_Colour = 0xEE8F;
                 } break;
     case 13:    for(i=0;i<Number_Of_Pixels;i++){
                 cyan_Out;
                 background_Colour = 0x07FF;
                 } break;
     case 14:    for(i=0;i<Number_Of_Pixels;i++){
                 lavenderblush_Out;
                 background_Colour = 0xFBC7;
                 } break;
     case 15:    for(i=0;i<Number_Of_Pixels;i++){
                 beige_Out;
                 background_Colour = 0xF4C7;
                 } break;
     default:    for(i=0;i<Number_Of_Pixels;i++){
                 Write_Data_EpsonS1D13517(0xFFFF);
                 } break;
    }

   Write_Command_EpsonS1D13517(0x2A);
   Write_Data_EpsonS1D13517(sdram_Location_Number<<4 | display_enable_bit);        //BIT ZERO HERE = Enable the display   Single buffer display (default) page 65  BITS 7,6,5,4 ARE INPUT BUFFER NUMBERS 1 TO 16   Buffer 9 = 1000
   Write_Command_EpsonS1D13517(0x50);                                          //REG[50h] Display Control Register PAGE 72
   Write_Data_EpsonS1D13517(0x80);                                             //Bit 7 must be set to update display 0b10000000 = HEX 80 OR 128 DECIMAL
   Epson_CS = 1;

}


//==============================================================

uint16_t Pixel;
void Get_Pixel_Colour(uint16_t colour){

    switch(colour)  {

     case 1:     Pixel = 0x00;//black
                 break;
     case 2:     Pixel = 0xF800;//red
                 break;
     case 3:     Pixel = 0xFCE1;//orange
                 break;
     case 4:     Pixel = 0xFFE0;//yellow
                 break;
     case 5:     Pixel = 0x07E0;//green
                 break;
     case 6:     Pixel = 0x01F;//blue
                 break;
     case 7:     Pixel = 0x891F;//violet
                 break;
     case 8:     Pixel = 0x84A3;//olive
                 break;
     case 9:     Pixel = 0xFFFF;//white
                 break;
     case 10:    Pixel = 0xF81F;//magenta
                 break;
     case 11:    Pixel = 0xAF20;//lime
                 break;
     case 12:    Pixel = 0xEE8F;//babyPowder
                 break;
     case 13:    Pixel = 0x07FF;//cyan
                 break;
     case 14:    Pixel = 0xFBC7;//lavenderblush
                 break;
     case 15:    Pixel = 0xF4C7;//beige
                 break;
     default:    Pixel = colour;
                 break;
    }
}

//==============================================================

void Set_Display_Letters_S1D13517(uint16_t x_position, uint16_t y_position){

     uint16_t Set_Start_Column = 0x01 | x_position/4;
     uint16_t Set_Start_Row = 0x00 | y_position/4;
     uint16_t Set_End_Column = Set_Start_Column-2 + Letter_Font_Width/4; //(bytes -1 bit) 8 pixels = 1 byte, 16 pixels = 2 bytes
     uint16_t Set_End_Row = Set_Start_Row + Letter_Font_Height/4;
     Epson_CS = 0;
     //REGISTERS AUTO-INCREMENT !
     Write_Command_EpsonS1D13517(0x5A);              //X START REGISTER
     Write_Data_EpsonS1D13517(Set_Start_Column);     //X START
     Write_Data_EpsonS1D13517(Set_Start_Row);        //Y START REGISTER ZER0
     Write_Data_EpsonS1D13517(1);                    //Y START REGISTER 1
     Write_Data_EpsonS1D13517(Set_End_Column);       //X END POSITION
     Write_Data_EpsonS1D13517(Set_End_Row);          //Y END POSITION REGISTER ZER0
     Write_Data_EpsonS1D13517(1);                    //Y END POSITION REGISTER 1
     Epson_CS = 1;
}

//==============================================================

void Write_Character(uint16_t Letter_Font_Length_Bytes_Start, uint16_t Letter_Font_Length_Bytes_End, uint16_t x_position, uint16_t y_position, uint16_t colour){
     uint8_t x=0;
     uint8_t dataout = 0;
     uint16_t i=1;
     uint16_t jj=0;
     Get_Pixel_Colour(colour);
     Set_Display_Letters_S1D13517(x_position,y_position);
     Epson_CS = 0;
     for(jj=Letter_Font_Length_Bytes_Start; jj<Letter_Font_Length_Bytes_End; jj++){
      for(x=0; x<8; x++){
          dataout = Letter_Font[jj] &i;
        if(dataout){
          Write_Data_EpsonS1D13517(Pixel);
         }else  {Write_Data_EpsonS1D13517(background_Colour);  }
          i=i<<1;
        if(i>128){
             i=1;}
       }
     }
     Epson_CS = 1;
}

void Write_Character_Dot(uint16_t x_position, uint16_t y_position, uint16_t colour){
     uint8_t x=0;
     uint8_t dataout = 0;
     uint16_t i=1;
     uint16_t jj=0;
     Get_Pixel_Colour(colour);
     Set_Display_Letters_S1D13517(x_position,y_position);
     Epson_CS = 0;
     for(jj=Letter_Font_Length_Bytes*36; jj<Letter_Font_Length_Bytes*37; jj++){
      for(x=0; x<8; x++){
          dataout = Letter_Font[jj] &i;
        if(dataout){
           Write_Data_EpsonS1D13517(Pixel);
         }else  {Write_Data_EpsonS1D13517(background_Colour);}
          i=i<<1;
        if (i>128){
              i=1;}
       }
     }
     Epson_CS = 1;
}

void Write_Character_Space(uint16_t x_position, uint16_t y_position, uint16_t colour){
     uint8_t x=0;
     uint8_t dataout = 0;
     uint16_t jj=0;
     Get_Pixel_Colour(colour);
     Set_Display_Letters_S1D13517(x_position,y_position);
     Epson_CS = 0;
     for(jj=0; jj<Letter_Font_Length_Bytes*10; jj++){    //Space
       Write_Data_EpsonS1D13517(background_Colour);
      }
      Epson_CS = 1;
}

//==============================================================

void switchCharacter(uint8_t Value, uint16_t x_position, uint16_t y_position, uint8_t colour){

     switch (Value)  {
     case 46:    Write_Character(Letter_Font_Length_Bytes*36,Letter_Font_Length_Bytes*37, x_position,y_position, colour);//DOT
                 break;
     case 48:    Write_Character(Letter_Font_Length_Bytes*0,Letter_Font_Length_Bytes*1, x_position,y_position, colour);//0
                 break;
     case 49:    Write_Character(Letter_Font_Length_Bytes*1,Letter_Font_Length_Bytes*2, x_position,y_position, colour);//1
                 break;
     case 50:    Write_Character(Letter_Font_Length_Bytes*2,Letter_Font_Length_Bytes*3, x_position,y_position, colour);//2
                 break;
     case 51:    Write_Character(Letter_Font_Length_Bytes*3,Letter_Font_Length_Bytes*4, x_position,y_position, colour);//3
                 break;
     case 52:    Write_Character(Letter_Font_Length_Bytes*4,Letter_Font_Length_Bytes*5, x_position,y_position, colour);//4
                 break;
     case 53:    Write_Character(Letter_Font_Length_Bytes*5,Letter_Font_Length_Bytes*6, x_position,y_position, colour);//5
                 break;
     case 54:    Write_Character(Letter_Font_Length_Bytes*6,Letter_Font_Length_Bytes*7, x_position,y_position, colour);//6
                 break;
     case 55:    Write_Character(Letter_Font_Length_Bytes*7,Letter_Font_Length_Bytes*8, x_position,y_position, colour);//7
                 break;
     case 56:    Write_Character(Letter_Font_Length_Bytes*8,Letter_Font_Length_Bytes*9, x_position,y_position, colour);//8
                 break;
     case 57:    Write_Character(Letter_Font_Length_Bytes*9,Letter_Font_Length_Bytes*10, x_position,y_position, colour);//9
                 break;
     case 65:    Write_Character(Letter_Font_Length_Bytes*10,Letter_Font_Length_Bytes*11, x_position,y_position, colour);//A
                 break;
     case 66:    Write_Character(Letter_Font_Length_Bytes*11,Letter_Font_Length_Bytes*12,x_position,y_position, colour); //B
                 break;
     case 67:    Write_Character(Letter_Font_Length_Bytes*12,Letter_Font_Length_Bytes*13,x_position,y_position, colour); //C
                 break;
     case 68:    Write_Character(Letter_Font_Length_Bytes*13,Letter_Font_Length_Bytes*14,x_position,y_position, colour); //D
                 break;
     case 69:    Write_Character(Letter_Font_Length_Bytes*14,Letter_Font_Length_Bytes*15,x_position,y_position, colour); //E
                 break;
     case 70:    Write_Character(Letter_Font_Length_Bytes*15,Letter_Font_Length_Bytes*16,x_position,y_position, colour); //F
                 break;
     case 71:    Write_Character(Letter_Font_Length_Bytes*16,Letter_Font_Length_Bytes*17,x_position,y_position, colour);//G
                 break;
     case 72:    Write_Character(Letter_Font_Length_Bytes*17,Letter_Font_Length_Bytes*18,x_position,y_position, colour);//H
                 break;
     case 73:    Write_Character(Letter_Font_Length_Bytes*18,Letter_Font_Length_Bytes*19,x_position,y_position, colour);//I
                 break;
     case 74:    Write_Character(Letter_Font_Length_Bytes*19,Letter_Font_Length_Bytes*20,x_position,y_position, colour);//J
                 break;
     case 75:    Write_Character(Letter_Font_Length_Bytes*20,Letter_Font_Length_Bytes*21,x_position,y_position, colour);//K
                 break;
     case 76:    Write_Character(Letter_Font_Length_Bytes*21,Letter_Font_Length_Bytes*22,x_position,y_position, colour);//L
                 break;
     case 77:    Write_Character(Letter_Font_Length_Bytes*22,Letter_Font_Length_Bytes*23,x_position,y_position, colour);//M
                 break;
     case 78:    Write_Character(Letter_Font_Length_Bytes*23,Letter_Font_Length_Bytes*24,x_position,y_position, colour);//N
                 break;
     case 79:    Write_Character(Letter_Font_Length_Bytes*24,Letter_Font_Length_Bytes*25,x_position,y_position, colour);//O
                 break;
     case 80:    Write_Character(Letter_Font_Length_Bytes*25,Letter_Font_Length_Bytes*26,x_position,y_position, colour);//P
                 break;
     case 81:    Write_Character(Letter_Font_Length_Bytes*26,Letter_Font_Length_Bytes*27,x_position,y_position, colour);//Q
                 break;
     case 82:    Write_Character(Letter_Font_Length_Bytes*27,Letter_Font_Length_Bytes*28,x_position,y_position, colour);//R
                 break;
     case 83:    Write_Character(Letter_Font_Length_Bytes*28,Letter_Font_Length_Bytes*29,x_position,y_position, colour);//S
                 break;
     case 84:    Write_Character(Letter_Font_Length_Bytes*29,Letter_Font_Length_Bytes*30,x_position,y_position, colour);//T
                 break;
     case 85:    Write_Character(Letter_Font_Length_Bytes*30,Letter_Font_Length_Bytes*31,x_position,y_position, colour);//U
                 break;
     case 86:    Write_Character(Letter_Font_Length_Bytes*31,Letter_Font_Length_Bytes*32,x_position,y_position, colour);//V
                 break;
     case 87:    Write_Character(Letter_Font_Length_Bytes*32,Letter_Font_Length_Bytes*33,x_position,y_position, colour);//W
                 break;
     case 88:    Write_Character(Letter_Font_Length_Bytes*33,Letter_Font_Length_Bytes*34,x_position,y_position, colour);//X
                 break;
     case 89:    Write_Character(Letter_Font_Length_Bytes*34,Letter_Font_Length_Bytes*35,x_position,y_position, colour);//Y
                 break;
     case 90:    Write_Character(Letter_Font_Length_Bytes*35,Letter_Font_Length_Bytes*36,x_position,y_position, colour);//Z
                 break;
     case 97:    Write_Character(Letter_Font_Length_Bytes*10,Letter_Font_Length_Bytes*11, x_position,y_position, colour); //A
                 break;
     case 98:    Write_Character(Letter_Font_Length_Bytes*11,Letter_Font_Length_Bytes*12,x_position,y_position, colour); //B
                 break;
     case 99:    Write_Character(Letter_Font_Length_Bytes*12,Letter_Font_Length_Bytes*13,x_position,y_position, colour); //C
                 break;
     case 100:   Write_Character(Letter_Font_Length_Bytes*13,Letter_Font_Length_Bytes*14,x_position,y_position, colour); //D
                 break;
     case 101:   Write_Character(Letter_Font_Length_Bytes*14,Letter_Font_Length_Bytes*15,x_position,y_position, colour); //E
                 break;
     case 102:   Write_Character(Letter_Font_Length_Bytes*15,Letter_Font_Length_Bytes*16,x_position,y_position, colour); //F
                 break;
     case 103:   Write_Character(Letter_Font_Length_Bytes*16,Letter_Font_Length_Bytes*17,x_position,y_position, colour);//G
                 break;
     case 104:   Write_Character(Letter_Font_Length_Bytes*17,Letter_Font_Length_Bytes*18,x_position,y_position, colour);//H
                 break;
     case 105:   Write_Character(Letter_Font_Length_Bytes*18,Letter_Font_Length_Bytes*19,x_position,y_position, colour);//I
                 break;
     case 106:   Write_Character(Letter_Font_Length_Bytes*19,Letter_Font_Length_Bytes*20,x_position,y_position, colour);//J
                 break;
     case 107:   Write_Character(Letter_Font_Length_Bytes*20,Letter_Font_Length_Bytes*21,x_position,y_position, colour);//K
                 break;
     case 108:   Write_Character(Letter_Font_Length_Bytes*21,Letter_Font_Length_Bytes*22,x_position,y_position, colour);//L
                 break;
     case 109:   Write_Character(Letter_Font_Length_Bytes*22,Letter_Font_Length_Bytes*23,x_position,y_position, colour);//M
                 break;
     case 110:   Write_Character(Letter_Font_Length_Bytes*23,Letter_Font_Length_Bytes*24,x_position,y_position, colour);//N
                 break;
     case 111:   Write_Character(Letter_Font_Length_Bytes*24,Letter_Font_Length_Bytes*25,x_position,y_position, colour);//O
                 break;
     case 112:   Write_Character(Letter_Font_Length_Bytes*25,Letter_Font_Length_Bytes*26,x_position,y_position, colour);//P
                 break;
     case 113:   Write_Character(Letter_Font_Length_Bytes*26,Letter_Font_Length_Bytes*27,x_position,y_position, colour);//Q
                 break;
     case 114:   Write_Character(Letter_Font_Length_Bytes*27,Letter_Font_Length_Bytes*28,x_position,y_position, colour);//R
                 break;
     case 115:   Write_Character(Letter_Font_Length_Bytes*28,Letter_Font_Length_Bytes*29,x_position,y_position, colour);//S
                 break;
     case 116:   Write_Character(Letter_Font_Length_Bytes*29,Letter_Font_Length_Bytes*30,x_position,y_position, colour);//T
                 break;
     case 117:   Write_Character(Letter_Font_Length_Bytes*30,Letter_Font_Length_Bytes*31,x_position,y_position, colour);//U
                 break;
     case 118:   Write_Character(Letter_Font_Length_Bytes*31,Letter_Font_Length_Bytes*32,x_position,y_position, colour);//V
                 break;
     case 119:   Write_Character(Letter_Font_Length_Bytes*32,Letter_Font_Length_Bytes*33,x_position,y_position, colour);//W
                 break;
     case 120:   Write_Character(Letter_Font_Length_Bytes*33,Letter_Font_Length_Bytes*34,x_position,y_position, colour);//X
                 break;
     case 121:   Write_Character(Letter_Font_Length_Bytes*34,Letter_Font_Length_Bytes*35,x_position,y_position, colour);//Y
                 break;
     case 122:   Write_Character(Letter_Font_Length_Bytes*35,Letter_Font_Length_Bytes*36,x_position,y_position, colour);//Z
                 break;
     default:    Write_Character_Space(x_position,y_position, colour);
                 break;
    }
}

//////////   “little-endian”   Least Significant Number first !!  ////////////////

//Offset |   Size    | Description           Implementing File I/O Functions Using Microchip’s Memory Disk Drive File System Library  AN1045
//  00h  |   3 Bytes | Jump Code + NOP
//  03h  |   8 Bytes | OEM Name
//  0Bh  |   1 Word  | Bytes per Sector ------ Sector size in bytes
//  0Dh  |   1 Byte  | Sectors per Cluster
//  0Eh  |   1 Word  | Start sector for FAT1 also known as Reserved Sectors
//  10h  |   1 Byte  | Number of Copies of FAT
//  11h  |   1 Word  | Number of Root Directory Entries 0x11 & 0x12    "Disk Parameter Block" (DPB).
//  13h  |   1 Word  | Number of Sectors in Partition Smaller than 32MB
//  15h  |   1 Byte  | Media Descriptor (F8h for Hard Disks)
//  16h  |   1 Word  | Sectors per FAT
//  18h  |   1 Word  | Sectors per Cluster   //Sectors per Track
//  1Ah  |   1 Word  | Number of Heads
//  1Ch  |   1 DWord | Number of Hidden Sectors in Partition
//  20h  |   1 DWord | Number of Sectors in Partition
//  24h  |   1 Word  | Logical Drive Number of Partition
//  26h  |   1 Byte  | Extended Signature (29h)
//  27h  |   1 DWord | Serial Number of Partition
//  2Bh  |  11 Bytes | Volume Name of Partition
//  36h  |   8 Bytes | FAT Name (FAT16)
//  3Eh  | 448 Bytes | Executable Code
//  1FEh |   2 Bytes | Executable Marker (55h AAh)

//==============================================================

//   Offset  |  Size     |  Description        Implementing File I/O Functions Using Microchip’s Memory Disk Drive File System Library  AN1045
//      00h  |  8 Bytes  |  Filename(1).
//      08h  |  3 bytes  |  File Extension.   //10  == zero
//      0Bh  |  1 Byte   |  File Attributes.
//      0Ch  |  1 Byte   |  Reserved.
//      0Dh  |  1 Byte   |  File Creation Time (ms portion).
//      0Eh  |  2 Bytes  |  File Creation Time (hours, minutes and seconds).
//      10h  |  2 bytes  |  File Creation Date.
//      12h  |  2 Bytes  |  Last Access Date.
//      14h  |  2 Bytes  |  Extended Address-Index.
//      16h  |  2 Bytes  |  Last Update Time (hours, minutes and seconds).
//      18h  |  2 Bytes  |  Last Update Date.
//      1Ah  |  2 Bytes  |  First Cluster of the File.
//      1Ch  |  4 Bytes  |  File Size. 4 bytes

uint8_t   Boot_Sector = 0;                    //Sector number of Boot Record
uint32_t  Root_Directory;                     //Sector number of Root Directory
uint16_t  First_File_Allocation_Table;        //Sector number of first FAT
uint16_t  Bytes_Per_Sector;
uint16_t  Sectors_Per_Cluster;                //Sectors per Track
uint16_t  Start_Sector_for_FAT1;              //Also known as Reserved_Sectors;  0Eh
uint8_t   Number_of_File_Allocation_Tables;
uint16_t  Number_of_Root_Directory_Entries;   //Number of Root Directory Entries
uint16_t  Sectors_Per_FAT;                    //Sectors per FAT
uint32_t  Number_of_Sectors;
uint32_t  Number_Of_Hidden_Sectors;
uint32_t  sector;
uint32_t  sectorb0;
uint32_t  sectorb1;
uint16_t  sectorb2;
uint8_t   sectorb3;
uint32_t  Cluster_Size;
uint8_t   bootSectorBuffer[512];
uint8_t   dataBuffer[512]; //SECTOR BUFFER
uint16_t  colour = white;

//==============================================================

void Get_Boot_Information(){

  Bytes_Per_Sector = bootSectorBuffer[0x0B] +256* bootSectorBuffer[0x0C];
  Sectors_Per_Cluster = bootSectorBuffer[0x0D];
  Start_Sector_for_FAT1 = bootSectorBuffer[0x0E] + (256)* bootSectorBuffer[0x0F];  //Reserved Sector
  Number_of_File_Allocation_Tables = bootSectorBuffer[0x10];
  Number_of_Root_Directory_Entries = bootSectorBuffer[0x11] + (256)* bootSectorBuffer[0x12];
  Sectors_Per_FAT = bootSectorBuffer[0x16] + (256)* bootSectorBuffer[0x17];
  sectorb0 =   bootSectorBuffer[0x23];
  sectorb1 =   bootSectorBuffer[0x22];
  sectorb2 =   bootSectorBuffer[0x21];
  sectorb3 =   bootSectorBuffer[0x20];
  Number_of_Sectors =  sectorb0<<24 | sectorb1<<16 | sectorb2<<8 | sectorb3;
  First_File_Allocation_Table = Boot_Sector + Start_Sector_for_FAT1;   //=6     233 * 2
  Root_Directory = First_File_Allocation_Table + (Sectors_Per_FAT * Number_of_File_Allocation_Tables);
  //Sectors_Smaller_Than_32MB = Boot_SectorBuffer[0x13];
}

//==============================================================

void Write_Text(const uint8_t *text, uint16_t x, uint16_t y, uint8_t colour)
{
    uint16_t i = 0;

    while (text[i] != '\0') {
        switchCharacter(text[i], x + (i * Letter_Font_Width), y, colour);
        i++;
    }
}

void Write_Number(uint32_t value, uint16_t x, uint16_t y, uint8_t colour)
{
    uint8_t buffer[12];
    int index = 0;

    do {
        buffer[index++] = '0' + (value % 10);
        value /= 10;
    } while (value > 0);

    while (index > 0) {
        index--;
        switchCharacter(buffer[index], x, y, colour);
        x += Letter_Font_Width;
    }
}

//==============================================================

void Show_Boot_information(){

    uint8_t xpos_Start = 120;
    uint8_t x = 0;
    uint8_t Font_Height = 34;
    Clear_Screen_S1D13517(black);
    colour = yellow;

    Write_Number(Number_of_Root_Directory_Entries,2,Font_Height, colour);
    //"Root_Entries   ="
    Write_Number(Sectors_Per_FAT,2,Font_Height*2, colour);
    //"Sectors_Per_FAT   ="
    Write_Number(Number_of_Sectors,2,Font_Height*3, colour);
    //"Number_of_Sectors   ="
    Write_Number(Sectors_Per_Cluster,2,Font_Height*4, colour);
    //"Sectors_Per_Cluster ="
    Write_Number(Start_Sector_for_FAT1,2,Font_Height*5, colour);
    //"Start_+_Reserved  ="
    Write_Number(Number_of_File_Allocation_Tables,2,Font_Height*6, colour);
    //"Number_of_FATs   ="
    Write_Number(Bytes_Per_Sector,2,Font_Height*7, colour);
    //"Bytes_Per_Sector   ="
    Cluster_Size = Bytes_Per_Sector * Sectors_Per_Cluster;
    Write_Number(Cluster_Size,2,Font_Height*8, colour);
    //"Cluster Size   ="
    Write_Number(Root_Directory,2,Font_Height*9, colour);

    Write_Text("ROOT DIRECTORY",200, Font_Height * 9+8, green);

    Delay_ms(800);
 }

//==============================================================

void Set_Bus_Speeds(){

      /* unlock system for clock configuration */
    SYSKEY = 0x00000000;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    PB1DIVbits.PBDIV = 1; // Peripheral Bus 1 Clock Divisor Control (PBCLK1 is SYSCLK divided by 2)
    PB2DIVbits.ON = 1; // Peripheral Bus 2 Output Clock Enable (Output clock is enabled)
    PB2DIVbits.PBDIV = 1; // Peripheral Bus 2 Clock Divisor Control (PBCLK2 is SYSCLK divided by 2)  Peripheral Bus 2 Clock drives i2C, spi, PMP
    PB3DIVbits.ON = 1; // Peripheral Bus 3 Output Clock Enable (Output clock is enabled)
    PB3DIVbits.PBDIV = 1; // Peripheral Bus 3 Clock Divisor Control (PBCLK3 is SYSCLK divided by 2)
    PB4DIVbits.ON = 1; // Peripheral Bus 4 Output Clock Enable (Output clock is enabled)
    while (!PB4DIVbits.PBDIVRDY); // Wait until it is ready to write to
    PB4DIVbits.PBDIV = 1; // Peripheral Bus 4 Clock Divisor Control (PBCLK4 is SYSCLK divided by 1)
    PB5DIVbits.ON = 1; // Peripheral Bus 5 Output Clock Enable (Output clock is enabled)
    PB5DIVbits.PBDIV = 1; // Peripheral Bus 5 Clock Divisor Control (PBCLK5 is SYSCLK divided by 2)
    PB7DIVbits.ON = 1; // Peripheral Bus 7 Output Clock Enable (Output clock is enabled)
    PB7DIVbits.PBDIV = 1; // Peripheral Bus 7 Clock Divisor Control (PBCLK7 is SYSCLK divided by 1)
    PB8DIVbits.ON = 1; // Peripheral Bus 8 Output Clock Enable (Output clock is enabled)
    PB8DIVbits.PBDIV = 1; // Peripheral Bus 8 Clock Divisor Control (PBCLK8 is SYSCLK divided by 2)
    PRECONbits.PFMSECEN = 0;  // Flash SEC Interrupt Enable (Do not generate an interrupt when the PFMSEC bit is set)
    PRECONbits.PREFEN = 0b11; // Predictive Prefetch Enable (Enable predictive prefetch for any address)  bit 5-4 PREFEN<1:0>: Predictive Prefetch Enable bits
    PRECONbits.PFMWS = 0b10;  // PFM Access Time Defined in Terms of SYSCLK Wait States (Two wait states)
    CFGCONbits.ECCCON = 3;
    SYSKEY = 0x00;
}

//==============================================================

void InitialiseSlowSPI(uint16_t Speed){
  SPI3_Init_Advanced(_SPI_MASTER, _SPI_8_BIT, Speed, _SPI_SS_DISABLE, _SPI_DATA_SAMPLE_MIDDLE, _SPI_CLK_IDLE_HIGH, _SPI_ACTIVE_2_IDLE);
}
void InitialiseFastSPI(uint8_t Speed){
  SPI3_Init_Advanced(_SPI_MASTER, _SPI_8_BIT, Speed, _SPI_SS_DISABLE, _SPI_DATA_SAMPLE_MIDDLE, _SPI_CLK_IDLE_HIGH, _SPI_ACTIVE_2_IDLE);
}

//==============================================================
                                           // DEFINITIONS FOR MMC/SD CARD COMMANDS
#define CMD0   (64 + 0)                    // Software Reset Command
#define CMD1   (64 + 1)                    // Initiate initialization process.
#define ACMD41 (64 + 41)                   // SEND_OP_COND (SDC)
#define CMD8   (64 + 8)                    // COMMAND  8  VERSION CHECK  For only SDC V2. Check voltage range.
#define CMD9   (64 + 9)                    // SEND_CSD  Read CSD register.
#define CMD10  (64 + 10)                   // SEND_CID  Read CID register.
#define CMD12  (64 + 12)                   // STOP_TRANSMISSION  Stop to read data.
#define ACMD13 (64 + 13)                   // SD_STATUS (SDC)
#define CMD16  (64 + 16)                   // SET SECTOR LENGTH OF BYTES YOU WANT TO READ Change R/W block size.
#define CMD17  (64 + 17)                   // READ SINGLE SECTOR
#define CMD18  (64 + 18)                   // READ MULTIPLE SECTORS UNTIL INTERRUPTED BY A 'STOP TRANSMISSION' COMMAND
#define CMD23  (64 + 23)                   // SET SECTOR COUNT / NUMBER OF BLOCKS TO READ FOR CMD18 & CMD25
#define ACMD23 (64 + 23)                   // SET_WRITE SECTOR ERASE COUNT (SDC) For only SDC. Define number of blocks to pre-erase with next multi-block write command.
#define CMD24  (64 + 24)                   // SET WRITE ADDRESS FOR SINGLE SECTOR
#define CMD25  (64 + 25)                   // SET FIRST WRITE ADDRESS FOR MULTIPLE SECTORS
#define CMD41  (64 + 41)                   // SEND_OP_COND (ACMD)
#define CMD55  (64 + 55)                   // APP_CMD  Leading command before ACMD command.
#define CMD58  (64 + 58)                   // READ_OCR


void Write_HexByte(uint8_t b, uint16_t x, uint16_t y, uint16_t colour){

    uint8_t hex[3];
    uint8_t hi;
    uint8_t lo;

    hi = (b >> 4) & 0x0F;
    lo = b & 0x0F;

    hex[0] = (hi < 10) ? ('0' + hi) : ('A' + (hi - 10));
    hex[1] = (lo < 10) ? ('0' + lo) : ('A' + (lo - 10));
    hex[2] = 0;

    Write_Text(hex, x, y, colour);
}

//==============================================================

void Initialise_SDCARD_New(){

    uint16_t  x;
    uint16_t Counter = 0;
    uint8_t responseBuffer[5];
    uint8_t response1;
    uint8_t loop0;
    uint8_t loop8;
    uint8_t loop55;
    uint8_t loop58;
    uint8_t loop16;
    uint8_t read_again;
    uint8_t token;
    uint8_t Bit31;
    uint8_t Bit30;
    uint8_t Bits23_16;
    uint16_t Speed;

    Clear_Screen_S1D13517(black);
    loop0:
    InitialiseSlowSPI(240);
    Delay_ms(1200);      //SD Card Power-Up Time.

    LATB10_bit = 1;     // RB10 = SERIAL DATA OUT SPI3
    LATB14_bit = 1;     // RB14 = CLOCK SPI 3

    Write_Text("START OF SD CARD INITIALISATION", 10,10,yellow);  //debug

    for(x = 0; x <10; x++){    // DUMMY CLOCKS  74 ARE REQUIRED.
     SPI3_Write(0xff);
    }

    SD_Card_Chip_Select = 0;
    SPI3_Write(CMD0);       //Software Reset Command
    SPI3_Write(0x00);
    SPI3_Write(0x00);
    SPI3_Write(0x00);
    SPI3_Write(0x00);
    SPI3_Write(0x95);       //0x95 Is Checksum For Software Reset

    Delay_ms(1);
    do {
    response1 = SPI3_Read(0xFF);
    Counter++;
    } while(response1 ==0xFF);

    SD_Card_Chip_Select = 1;
    SPI3_Write(0xFF);
    Delay_ms(2);

    if(response1 != 1 && response1 != 0){
    Clear_Screen_S1D13517(red);
    Write_Number(response1,30,70,blue);
    Write_Number(counter,  30,110,blue);
    }

    Delay_ms(20);           //TIME FOR SD CARD
    Counter = 0;

    Write_Text("ROUTINE CMD0  COMPLETE", 10,42,white);  //debug

    loop8:
    SPI3_Write(0xFF);
    SD_Card_Chip_Select = 0;
    SPI3_Write(CMD8);
    SPI3_Write(0x00);
    SPI3_Write(0x00);
    SPI3_Write(0x01);
    SPI3_Write(0xAA);
    SPI3_Write(0x87);        //Checksum
    Delay_us(2);

    do {
    response1 = SPI3_Read(0xFF);
    Delay_us(2);
    } while(response1 != 0);

    Delay_ms(1);

    SD_Card_Chip_Select = 0;
    for(x = 0; x <4; x++){
    delay_ms(1);
    responseBuffer[x] = SPI3_Read(255);
    }

    SD_Card_Chip_Select = 1;
    SPI3_Write(0xFF);

    if(responseBuffer[0] !=0 && responseBuffer[1] !=0 && responseBuffer[2] !=1 && responseBuffer[3] !=170  ){
     Counter++;
    if(Counter >5){
       Clear_Screen_S1D13517(red);
       Write_Text("CMD8 ERROR SD CARD INIT",100,30,white);
       Write_Number(response1,30,70,blue);
       Write_Number(responseBuffer[0],30,100,blue);
       Write_Number(responseBuffer[1],30,130,blue);
       Write_Number(responseBuffer[2],30,160,blue);
       goto loop8;
     }
    }

    Write_Text("ROUTINE CMD8  COMPLETE", 10,74,white);  //debug

    Counter = 0;
    loop55:

    SD_Card_Chip_Select = 0;
    SPI3_Write(CMD55);  //     PAGE 59 OF SD CARD ASSOCIATION STATES THAT COMMAND 55 SHALL ALWAYS PRECEDE AMCD41
    SPI3_Write(0x00);
    SPI3_Write(0x00);
    SPI3_Write(0x00);
    SPI3_Write(0x00);
    SPI3_Write(0x87);         // Checksum

    do {
    response1 = SPI3_Read(0xFF);
    counter++;
    } while(response1 !=1);

    SD_Card_Chip_Select = 1;
    SPI3_Write(0xFF);
    Delay_ms(2);
    Counter = 0;

    Write_Text("ROUTINE CMD55 COMPLETE", 10,106,white);  //debug

    Delay_ms(10);

    SD_Card_Chip_Select = 0;
    SPI3_Write(CMD41);  //CMD41
    SPI3_Write(0x40);   //send 0x40... when card_version == 2 (SD v2). send 0x00... when card_version == 1 (SD v1).
    SPI3_Write(0x00);
    SPI3_Write(0x00);
    SPI3_Write(0x00);
    SPI3_Write(0x87);   // Checksum was 0x87

    delay_us(2);
    do {
    response1 = SPI3_Read(0xFF);
    delay_us(2);
    } while(response1 ==0xFF);

    SD_Card_Chip_Select = 1;
    SPI3_Write(0xFF);
    Delay_ms(2);

    if(response1 !=0){

    Counter++;
    delay_us(500);

    if(Counter >10){
     Clear_Screen_S1D13517(red);
     Write_Text("CMD41 ERROR SD CARD INIT", 100, 30, white);
     Write_Text("SD CARD V1 MAYBE", 100, 60, white);
     Write_Number(response1,30,100,white);
     Write_Number(counter,  130,100,red);
    }
    goto loop55;
    }

    Write_Text("ROUTINE CMD41 COMPLETE", 10, 138, white);  //debug

    Counter = 0;
    loop58:

    SD_Card_Chip_Select = 0;
    SPI3_Write(CMD58);       //OCR register (big-endian, MSB first)
    SPI3_Write(0x00);
    SPI3_Write(0x00);
    SPI3_Write(0x00);
    SPI3_Write(0x00);
    SPI3_Write(0xFF);        //Checksum

    delay_ms(2);
    do{
     response1 = SPI3_Read(0xFF);

    }while(response1 !=0xFF);

    for(x = 0; x <4; x++){

    delay_us(200);
    responseBuffer[x] = SPI3_Read(0xFF);
    }
    SD_Card_Chip_Select = 1;
    SPI3_Write(0xFF);
    Counter = 0;
    /*|------------------------------------------------------------------------------|
    |   31 = card power up complete and read                                       |
    |   30 = SDHC or SDXC                                                          |
    |   23 to 16 = if all bits set, voltage rand full from 2.7 volts to 3.6 volts  |
    |   15 - 8 voltage windows = 2 volts to 2.7 volts                              |
    |   bit 7 of last byte = voltage window of 1.7 volts to 2 volts                |
    |   bits 6 to zero = reserved                                                  |
    |                                                                              |
    |           192          255           128          65                         |
    |                                                                              |
    |         11000000     11111111      10000000      01000001                    |
    |______________________________________________________________________________|*/



    Write_Text("ROUTINE CMD58 OCR COMPLETE ", 10, 170, white);  //debug


    Bit31 = responseBuffer[1] & 128;
    if(Bit31){

    Write_Text("POWER-UP COMPLETE", 10, 234, green);  //debug

    }
    if( Bit31 ==0){

    Write_Text("POWER-UP FAIL", 10, 234, red);  //debug

    }

    Bit30 = responseBuffer[1] & 64;
    if(Bit30){

    Write_Text("SDHC CARD", 10, 266, green);  //debug

    }
    if(Bit30 ==0){

    Write_Text("SDSC CARD", 10, 266, red);  //debug

    }

    Bits23_16 = responseBuffer[2] & 0xFF;
    if(Bits23_16){

    Write_Text("Voltage Window 2.7 to 3.6", 10, 298, green);  //debug

    }

    if(Bit31 ==0){
    Counter++;
    Delay_ms(1);
    if(Counter >5){
     Clear_Screen_S1D13517(red);
      Write_Text("CMD58 ERROR POWER FAIL", 30, 50, white);
     Delay_ms(300);
    }
    goto loop58;
    }

    Delay_ms(2000);

    loop16:
    speed = 14;
    InitialiseFastSPI(Speed); //<<<<<<<<<<<<<<<<<
    Delay_ms(100);
    Counter = 0;

    SPI3_Write(0xFF);
    SD_Card_Chip_Select = 0;
    SPI3_Write(CMD16);
    SPI3_Write(0x00);
    SPI3_Write(0x00);
    SPI3_Write(0x02);
    SPI3_Write(0x00);
    SPI3_Write(0x87);      // Checksum

    // delay_ms(2);
    do{
     responseBuffer[5] = SPI3_Read(0xFF);

    }while(responseBuffer[5] ==0xFF);
    SD_Card_Chip_Select = 1;
    SPI3_Write(0xFF);

    Write_Text("ROUTINE CMD16 Complete ", 10, 202, white);  //debug

    Counter = 0;
    read_again:
    SD_Card_Chip_Select = 0;
    SPI3_Write(CMD17);
    SPI3_Write(0x00);
    SPI3_Write(0x00);
    SPI3_Write(0x00);
    SPI3_Write(0x00);
    SPI3_Write(0x87);      // Checksum
    Delay_us(2);

    do {
    responseBuffer[1] = SPI3_Read(0xFF);
    Delay_us(2);
    Counter++;
    } while(responseBuffer[1] ==0xFF);

    asm nop;
    SD_Card_Chip_Select = 1;
    SPI3_Write(0xFF);
    Counter = 0;

    SD_Card_Chip_Select = 0;
    do {
    token = SPI3_Read(0xFF);
    Delay_us(40);
    Counter++;
    if(Counter >10)
    {
     goto read_again;
    }

    } while(token !=0xFE);

    if(token !=0xFE){

    Clear_Screen_S1D13517(red);
    Write_HexByte(token,300,30,white);
    while(1);

    }

    for(x = 0; x <512; x++){
    asm nop; asm nop;
    bootSectorBuffer[x] = SPI3_Read(255);
    }

    for(x = 0; x < 2; x++)
    {
    responseBuffer[0] = SPI3_Read(255);
    }
    SD_Card_Chip_Select = 1;
    SPI3_Write(0xFF);

    Delay_ms(1500);

    if(bootSectorBuffer[54] ==70 && bootSectorBuffer[58] == 54 && bootSectorBuffer[510] ==0x55 && bootSectorBuffer[511] ==0xAA){
     Clear_Screen_S1D13517(lavenderblush);
     colour = blue;
     Write_Text("FAT16 INITIALISED", 185, 30, white);
     switchCharacter(bootSectorBuffer[54], 300,100,colour);
     switchCharacter(bootSectorBuffer[55], 330,100,colour);
     switchCharacter(bootSectorBuffer[56], 360,100,colour);
     switchCharacter(bootSectorBuffer[57], 390,100,colour);
     switchCharacter(bootSectorBuffer[58], 420,100,colour);
     Write_Text("CMD17 TOKEN = ", 200, 160, white);
     Write_Text("SPEED", 200, 200, green);
     Write_HexByte(token,500,160,green);
     Write_Number(Speed, 360, 200, yellow);
     Speed +=4;
     InitialiseSlowSPI(Speed);
     Delay_ms(500);
    }


    if(bootSectorBuffer[54] != 70 && bootSectorBuffer[58] != 54 && bootSectorBuffer[0]==0 && bootSectorBuffer[2]==0){
     Clear_Screen_S1D13517(blue);
     Write_Text("POSSIBLE MBR FOUND NOT FAT16", 60, 30, white);
     Write_HexByte(bootSectorBuffer[0],30,70,red);
     Write_HexByte(bootSectorBuffer[1],30,100,red);
     Write_HexByte(bootSectorBuffer[2],30,130,red);
     Write_HexByte(bootSectorBuffer[510],30,160,red);
     Write_HexByte(bootSectorBuffer[511],90,160,red);
     while(1);
    }


    if(bootSectorBuffer[510] !=0x55 && bootSectorBuffer[511] !=0xAA){
     Clear_Screen_S1D13517(red);
     colour = white;
     Write_Text("BOOT SIGNATURE ERROR", 160, 30,colour);
     Write_HexByte(bootSectorBuffer[0],30,60,colour);
     Write_HexByte(bootSectorBuffer[1],30,90,colour);
     Write_HexByte(bootSectorBuffer[2],30,120,colour);
     Write_HexByte(bootSectorBuffer[510],30,150,colour);
     Write_HexByte(bootSectorBuffer[511],120,150,colour);
     Clear_Screen_S1D13517(blue);
     Write_HexByte(bootSectorBuffer[510],30,150,red);
     Write_HexByte(bootSectorBuffer[511],100,150,red);
     Delay_ms(20);
     Speed+=4;
     Counter++;;
     Write_Number(Counter, 500, 300, white);
     while(bootSectorBuffer[511] !=0xAA){
       goto read_again;

     }
    }

         //debug tool below
    /*Write_Number(responseBuffer[1],108,400,magenta);
    Write_Number(responseBuffer[2],190,350,white);
    Write_Number(responseBuffer[3],268,350,yellow);
    Write_Number(responseBuffer[4],346,350,blue);
    Write_Number(counter, 500, 400, white);
    //jump instructions, start of card
    Write_HexByte(bootSectorBuffer[0],30,30,red);
    Write_HexByte(bootSectorBuffer[1],30,60,red);
    Write_HexByte(bootSectorBuffer[2],30,90,red);
    //boot signature below
    Write_HexByte(bootSectorBuffer[510],30,290,red);
    Write_HexByte(bootSectorBuffer[511],30,330,red);
    //text letters below
    Switch_Character(bootSectorBuffer[54], 500,50,yellow);
    Switch_Character(bootSectorBuffer[55], 500,90,yellow);
    Switch_Character(bootSectorBuffer[56], 500,130,yellow);
    Switch_Character(bootSectorBuffer[57], 500,170,yellow);
    switch_Character(bootSectorBuffer[58], 500,210,yellow);*/

    Delay_ms(2000);
}


//====================================================

void Read_Sector(uint32_t address, uint8_t *buffer){

    uint16_t  ypos = 50;
    uint16_t  xpos = 20;
    uint16_t  x;
    uint16_t  Counter = 0;
    uint8_t   loop1;
    uint8_t   responseBuffer[4];

    loop1:
    SD_Card_Chip_Select = 0;
    SPI3_Write(CMD17);        //Command 17  Read Sector
    SPI3_Write(Address>>24);
    SPI3_Write(Address>>16);
    SPI3_Write(Address>>8);
    SPI3_Write(Address);
    SPI3_Write(0x87);
    SD_Card_Chip_Select = 1;
    //SPI3_Write(0xFF);
    SD_Card_Chip_Select = 0;

    responseBuffer[0] = SPI3_Read(0xFF);   //Response 1   THIS WORKS BY ITSELF, IGNORE IT, IT'S USUALLY 0xFF

    do {
        responseBuffer[0] = SPI3_Read(0xFF);
        Delay_us(2);
    }   while (responseBuffer[0] !=0xFE);

    for(x = 0; x <512; x++){

     buffer[x] = SPI3_Read(255);     //<<<<<<DATA BUFFER HERE
     }

    for(x = 0; x < 2; x++){

       responseBuffer[0] = SPI3_Read(255);
     }
      SD_Card_Chip_Select = 1;
      SPI3_Write(0xFF);
}

//=============================================================================

struct File_Details{
    uint16_t Location[15];
    uint32_t TotalFileSize;
    uint32_t Starting_Cluster[15];
}File;

uint16_t Max_Bytes = 512;
uint16_t Bytes_Left_To_Read;
uint16_t Image_Data_Starts_At;
uint16_t Location = 8;

uint8_t  File_Number = 0;
uint32_t SizeData31 = 0;
uint32_t SizeData30 = 0;
uint16_t SizeData29 = 0;
uint8_t  SizeData28 = 0;
uint16_t StartingClusterData27 = 0;
uint8_t  StartingClusterData26 = 0;

uint8_t  FileCount = 0;
uint8_t  xpos_4_FileNumber;
uint8_t  xpos_4_Location;
uint16_t xpos_4_Actual_Start_Sector;
uint16_t xpos_4_Start_Sector;
uint32_t Root_Directory_In_Bytes;
uint16_t Sum0;
uint32_t Sum1;
uint32_t x = 0;
uint32_t i = 0;
uint32_t j = 0;
uint8_t  k = 10;
uint32_t Actual_Sector[15];
uint8_t  Byte2;
uint16_t Byte3;
uint32_t Byte4;
uint32_t Byte5;
uint8_t  Byte10;
uint16_t Byte11;
uint32_t Byte12;
uint32_t Byte13;
uint8_t  Byte18;
uint16_t Byte19;
uint16_t Image_Width;
uint16_t Sectors_To_Read = 0;

void Get_Files(){ // now counting to five

    uint8_t x = 0;
    uint16_t  ypos = 10;
    uint16_t  xpos = 240;
    uint32_t Sector;
    colour = white;

    Sector = Root_Directory * 512;
    Read_Sector(Sector, dataBuffer);  //<<<<READ ROOT DIRECTORY TO VIEW FILES<<<<<<<<<

    Clear_Screen_S1D13517(lavenderblush);

    for(x = 0; x <12; x++){
    switchCharacter(dataBuffer[x], xpos + Letter_Font_Width * x, ypos, colour);   //Display Sdcard Name
    }

    Delay_ms(300);

    Clear_Screen_S1D13517(lavenderblush);

    Write_Text("Sector", 500, ypos, green);   //SECTOR TEXT

    Write_Number(Sector/512, 660, ypos, red); //SECTOR NUMBER

    xpos = 20;          //BMP NAME XPOS START RESET AFTER SECTOR NUMBER AND TEXT DISPLAYED
    ypos       = 20;    //BMP FILE NAME YPOSITION, THIS SHOULD AUTO INCREMENT WITH FILE COUNT
    Location   = 128;   //Jumps Over System Info

    while(Location <512){

      if(dataBuffer[Location] >=65 && dataBuffer[Location] <=90){

       if(dataBuffer[Location+8] ==66 && dataBuffer[Location+9] ==77){

         Write_Number(Location,340,ypos,blue); //Bytes In From That Sector Start, Like 472 + 16 Bytes.

         for(x=0; x<12; x++, colour++){
           if(colour> 13){ colour = 1; }
           switchCharacter(dataBuffer[Location+x],xpos +Letter_Font_Width*x,ypos,colour);   //SHORT NAMES ARE ALWAYS CONVERTED TO UPPER CASE
          }

          ypos +=28;
          File_Number++;
         if(dataBuffer[Location+10] ==80) {  //P
           File.Location[File_Number] = Location;
           SizeData31 =  dataBuffer[File.Location[File_Number]+31];
           SizeData30 =  dataBuffer[File.Location[File_Number]+30];
           SizeData29 =  dataBuffer[File.Location[File_Number]+29];
           SizeData28 =  dataBuffer[File.Location[File_Number]+28];
           File.TotalFileSize =  ((SizeData31<<24) |  (SizeData30<<16) |  (SizeData29<<8) | (SizeData28));
           StartingClusterData27 = dataBuffer[File.Location[File_Number]+27];
           StartingClusterData26 = dataBuffer[File.Location[File_Number]+26];
           File.Starting_Cluster[File_Number] = (StartingClusterData27<<8) | StartingClusterData26;
          }
        }
      }
      Location += 8;
    }

    //---------------------------------------READ SECOND SECTOR OF ROOT DIRECTORY--------------------------------------
    Sector = (512)*(Root_Directory +1);
    Read_Sector(Sector, dataBuffer);
    //------------------------------------------------------------------------------------------------------------------
    Location   = 0;

    Write_Text("Sector", 500, ypos, green);   //SECTOR  TEXT

    Write_Number(Sector/512, 660, ypos, red);           //SECTOR NUMBER

    xpos = 20;            //SECTOR TEXT AND SECTOR NUMBER XPOS FIRST

    while(Location <512){

      if(dataBuffer[Location] >=65 && dataBuffer[Location] <=90){

       if(dataBuffer[Location+8] ==66 && dataBuffer[Location+9] ==77){

         Write_Number(Location,340,ypos,blue); //Bytes In From That Sector Start, Like 472 + 16 Bytes.

         for(x=0; x<12; x++, colour++){
           if(colour> 13){ colour = 1; }
           switchCharacter(dataBuffer[Location+x],xpos +Letter_Font_Width*x,ypos,colour);   //SHORT NAMES ARE ALWAYS CONVERTED TO UPPER CASE
          }

         ypos +=28;
         File_Number++;
         if(dataBuffer[Location+10] ==80){
           File.Location[File_Number] = Location;
           SizeData31 =  dataBuffer[File.Location[File_Number]+31];
           SizeData30 =  dataBuffer[File.Location[File_Number]+30];
           SizeData29 =  dataBuffer[File.Location[File_Number]+29];
           SizeData28 =  dataBuffer[File.Location[File_Number]+28];
           File.TotalFileSize =  ((SizeData31<<24) |  (SizeData30<<16) |  (SizeData29<<8) | (SizeData28));
           StartingClusterData27 = dataBuffer[File.Location[File_Number]+27];
           StartingClusterData26 = dataBuffer[File.Location[File_Number]+26];
           File.Starting_Cluster[File_Number] = (StartingClusterData27<<8) | StartingClusterData26;
          }
        }
      }
      Location +=8;
    }

    //---------------------------------------READ THIRD SECTOR OF ROOT DIRECTORY--------------------------------------
    Sector = (512)*(Root_Directory+2);
    Read_Sector(Sector, dataBuffer);
    //------------------------------------------------------------------------------------------------------------------
    Location = 0;

    Write_Text("Sector", 500, ypos, green);   //SECTOR WORD

    Write_Number(Sector/512, 660, ypos, red); //SECTOR NUMBER

    xpos = 20;    //SECTOR TEXT AND SECTOR NUMBER XPOS FIRST

    while(Location <512){

      if(dataBuffer[Location] >=65 && dataBuffer[Location] <=90){

       if(dataBuffer[Location+8] ==66 && dataBuffer[Location+9] ==77){

         Write_Number(Location,340,ypos,blue); //Bytes In From That Sector Start, Like 472 + 16 Bytes.

         for(x=0; x<12; x++, colour++){
           if(colour> 13){ colour = 1; }
           switchCharacter(dataBuffer[Location+x],xpos +Letter_Font_Width*x,ypos,colour);   //SHORT NAMES ARE ALWAYS CONVERTED TO UPPER CASE
          }

         ypos +=28;
         File_Number++;
         if(dataBuffer[Location+10] ==80){
           File.Location[File_Number] = Location;
           SizeData31 =  dataBuffer[File.Location[File_Number]+31];
           SizeData30 =  dataBuffer[File.Location[File_Number]+30];
           SizeData29 =  dataBuffer[File.Location[File_Number]+29];
           SizeData28 =  dataBuffer[File.Location[File_Number]+28];
           File.TotalFileSize =  ((SizeData31<<24) |  (SizeData30<<16) |  (SizeData29<<8) | (SizeData28));
           StartingClusterData27 = dataBuffer[File.Location[File_Number]+27];
           StartingClusterData26 = dataBuffer[File.Location[File_Number]+26];
           File.Starting_Cluster[File_Number] = (StartingClusterData27<<8) | StartingClusterData26;
          }
        }
      }
      Location +=8;
    }

    ypos +=12;   //SECTOR TEXT AND SECTOR NUMBER ypos

    Write_Text("FILE COUNT", 50, ypos, colour);   //FILE COUNT TEXT

    FileCount = File_Number;
    Write_Number(File_Number, 340, ypos, yellow);
    ypos +=32;

    Write_Text("FILE SIZE", 50, ypos, colour);    //FILE SIZE TEXT

    Write_Number(File.TotalFileSize, 340, ypos, magenta);  //FILE SIZE NUMBER
    Delay_ms(2000);
    while(FileCount ==0);
    //////////////////////////////////////
    xpos_4_FileNumber          = 10;
    xpos_4_Location            = 100;
    xpos_4_Start_Sector        = 300;
    xpos_4_Actual_Start_Sector = 500;
    File_Number = 1;
    ypos = 2;
    xpos = 70;

    Clear_Screen_S1D13517(black);

    Write_Text("ACTUAL SECTOR LOCATION", 120, ypos, orange);   //ACTUAL SECTOR LOCATION CALCULATOR

    ypos +=31;

    for(x=0; x <FileCount; x++){
     Root_Directory_In_Bytes = (Root_Directory)*512;
     Sum0 = Number_of_Root_Directory_Entries * 32;
     Sum1 = (File.Starting_Cluster[File_Number] -2) *(Sectors_Per_Cluster * 512);
     Root_Directory_In_Bytes += Sum0;
     Sum1 += Root_Directory_In_Bytes;
     Actual_Sector[File_Number] = Sum1/512;
     Write_Number(File_Number,xpos_4_FileNumber, ypos, yellow);
     Write_Number(File.Location[File_Number], xpos_4_Location, ypos, green); //BYTES IN FROM BEGINNING OF SECTOR
     Write_Number(File.Starting_Cluster[File_Number], xpos_4_Start_Sector, ypos, blue); //STARTING CLUSTER
     Write_Number(Actual_Sector[File_Number], xpos_4_Actual_Start_Sector, ypos, yellow); //ACTUAL SECTOR HERE
     ypos +=31;
     File_Number++;
    }

    Delay_ms(600);
    File_Number = 1;  //<<<<<<<<<<<<<<<<<<<<<<<<< Reset File Number To 1
}

//=================================================================

void get_FilesBACKUPCOPY1(){

    uint8_t x = 0;
    uint16_t  ypos = 20;
    uint16_t  xpos = 240;
    uint32_t Sector;
    colour = white;

    Sector = Root_Directory * 512;
    Read_Sector(Sector, dataBuffer);  //<<<<READ ROOT DIRECTORY TO VIEW FILES<<<<<<<<<

    Clear_Screen_S1D13517(lavenderblush);

    for(x = 0; x <12; x++){
    switchCharacter(dataBuffer[x], xpos + Letter_Font_Width * x, ypos, colour);   //Display Sdcard Name
    }

    Delay_ms(300);

    Clear_Screen_S1D13517(lavenderblush);

    Write_Text("Sector", 500, ypos, green);   //SECTOR TEXT

    Write_Number(Sector/512, 660, ypos, red); //SECTOR NUMBER

    xpos = 20;          //BMP NAME XPOS START RESET AFTER SECTOR NUMBER AND TEXT DISPLAYED
    ypos       = 20;    //BMP FILE NAME YPOSITION, THIS SHOULD AUTO INCREMENT WITH FILE COUNT
    Location   = 128;   //Jumps Over System Info

    while(Location <512){

      if(dataBuffer[Location] >=65 && dataBuffer[Location] <=90){

       if(dataBuffer[Location+8] ==66 && dataBuffer[Location+9] ==77){

         Write_Number(Location,340,ypos,blue); //Bytes In From That Sector Start, Like 472 + 16 Bytes.

         for(x=0; x<12; x++, colour++){
           if(colour> 13){ colour = 1; }
           switchCharacter(dataBuffer[Location+x],xpos +Letter_Font_Width*x,ypos,colour);   //SHORT NAMES ARE ALWAYS CONVERTED TO UPPER CASE
          }

          ypos +=28;
          File_Number++;
         if(dataBuffer[Location+10] ==80) {  //P
           File.Location[File_Number] = Location;
           SizeData31 =  dataBuffer[File.Location[File_Number]+31];
           SizeData30 =  dataBuffer[File.Location[File_Number]+30];
           SizeData29 =  dataBuffer[File.Location[File_Number]+29];
           SizeData28 =  dataBuffer[File.Location[File_Number]+28];
           File.TotalFileSize =  ((SizeData31<<24) |  (SizeData30<<16) |  (SizeData29<<8) | (SizeData28));
           StartingClusterData27 = dataBuffer[File.Location[File_Number]+27];
           StartingClusterData26 = dataBuffer[File.Location[File_Number]+26];
           File.Starting_Cluster[File_Number] = (StartingClusterData27<<8) | StartingClusterData26;
          }
        }
      }
      Location += 8;
    }

    //---------------------------------------READ SECOND SECTOR OF ROOT DIRECTORY--------------------------------------
    Sector = (512)*(Root_Directory+1);
    Read_Sector(Sector, dataBuffer);
    //------------------------------------------------------------------------------------------------------------------
    Location   = 0;

    Write_Text("Sector", 500, ypos, green);   //SECTOR  TEXT

    Write_Number(Sector/512, 660, ypos, red);           //SECTOR NUMBER

    xpos = 20;            //SECTOR TEXT AND SECTOR NUMBER XPOS FIRST


    while(Location <512){

      if(dataBuffer[Location] >=65 && dataBuffer[Location] <=90){

       if(dataBuffer[Location+8] ==66 && dataBuffer[Location+9] ==77){

         Write_Number(Location,340,ypos,blue); //Bytes In From That Sector Start, Like 472 + 16 Bytes.

         for(x=0; x<12; x++, colour++){
           if(colour> 13){ colour = 1; }
           switchCharacter(dataBuffer[Location+x],xpos +Letter_Font_Width*x,ypos,colour);   //SHORT NAMES ARE ALWAYS CONVERTED TO UPPER CASE
          }

         ypos +=28;
         File_Number++;
         if(dataBuffer[Location+10] ==80){
           File.Location[File_Number] = Location;
           SizeData31 =  dataBuffer[File.Location[File_Number]+31];
           SizeData30 =  dataBuffer[File.Location[File_Number]+30];
           SizeData29 =  dataBuffer[File.Location[File_Number]+29];
           SizeData28 =  dataBuffer[File.Location[File_Number]+28];
           File.TotalFileSize =  ((SizeData31<<24) |  (SizeData30<<16) |  (SizeData29<<8) | (SizeData28));
           StartingClusterData27 = dataBuffer[File.Location[File_Number]+27];
           StartingClusterData26 = dataBuffer[File.Location[File_Number]+26];
           File.Starting_Cluster[File_Number] = (StartingClusterData27<<8) | StartingClusterData26;
          }
        }
      }
      Location +=8;
    }

    //---------------------------------------READ THIRD SECTOR OF ROOT DIRECTORY--------------------------------------
    Sector = (512)*(Root_Directory+2);
    Read_Sector(Sector, dataBuffer);
    //------------------------------------------------------------------------------------------------------------------
    Location = 0;

    Write_Text("Sector", 500, ypos, green);   //SECTOR WORD

    Write_Number(Sector/512, 660, ypos, red); //SECTOR NUMBER

    xpos = 20;    //SECTOR TEXT AND SECTOR NUMBER XPOS FIRST

    while(Location <512){

      if(dataBuffer[Location] >=65 && dataBuffer[Location] <=90){

       if(dataBuffer[Location+8] ==66 && dataBuffer[Location+9] ==77){

         Write_Number(Location,340,ypos,blue); //Bytes In From That Sector Start, Like 472 + 16 Bytes.

         for(x=0; x<12; x++, colour++){
           if(colour> 13){ colour = 1; }
           switchCharacter(dataBuffer[Location+x],xpos +Letter_Font_Width*x,ypos,colour);   //SHORT NAMES ARE ALWAYS CONVERTED TO UPPER CASE
          }

         ypos +=28;
         File_Number++;
         if(dataBuffer[Location+10] ==80){
           File.Location[File_Number] = Location;
           SizeData31 =  dataBuffer[File.Location[File_Number]+31];
           SizeData30 =  dataBuffer[File.Location[File_Number]+30];
           SizeData29 =  dataBuffer[File.Location[File_Number]+29];
           SizeData28 =  dataBuffer[File.Location[File_Number]+28];
           File.TotalFileSize =  ((SizeData31<<24) |  (SizeData30<<16) |  (SizeData29<<8) | (SizeData28));
           StartingClusterData27 = dataBuffer[File.Location[File_Number]+27];
           StartingClusterData26 = dataBuffer[File.Location[File_Number]+26];
           File.Starting_Cluster[File_Number] = (StartingClusterData27<<8) | StartingClusterData26;
          }
        }
      }
      Location +=8;
    }

    ypos +=20;   //SECTOR TEXT AND SECTOR NUMBER ypos

    Write_Text("FILE COUNT", 50, ypos, colour);   //FILE COUNT TEXT

    FileCount = File_Number;
    Write_Number(File_Number, 340, ypos, yellow);
    ypos +=32;

    Write_Text("FILE SIZE", 50, ypos, colour);    //FILE SIZE TEXT

    Write_Number(File.TotalFileSize, 340, ypos, magenta);  //FILE SIZE NUMBER
    Delay_ms(2000);
    while(FileCount ==0);
    //////////////////////////////////////
    xpos_4_FileNumber          = 10;
    xpos_4_Location            = 100;
    xpos_4_Start_Sector        = 300;
    xpos_4_Actual_Start_Sector = 500;
    File_Number = 1;
    ypos = 2;
    xpos = 70;

    Clear_Screen_S1D13517(black);

    Write_Text("ACTUAL SECTOR LOCATION", 120, ypos, orange);   //ACTUAL SECTOR LOCATION CALCULATOR

    ypos +=32;

    for(x=0; x <FileCount; x++){
     Root_Directory_In_Bytes = (Root_Directory)*512;
     Sum0 = Number_of_Root_Directory_Entries * 32;
     Sum1 = (File.Starting_Cluster[File_Number] -2) *(Sectors_Per_Cluster * 512);
     Root_Directory_In_Bytes += Sum0;
     Sum1 += Root_Directory_In_Bytes;
     Actual_Sector[File_Number] = Sum1/512;
     Write_Number(File_Number,xpos_4_FileNumber, ypos, yellow);
     Write_Number(File.Location[File_Number], xpos_4_Location, ypos, green); //BYTES IN FROM BEGINNING OF SECTOR
     Write_Number(File.Starting_Cluster[File_Number], xpos_4_Start_Sector, ypos, blue); //STARTING CLUSTER
     Write_Number(Actual_Sector[File_Number], xpos_4_Actual_Start_Sector, ypos, yellow); //ACTUAL SECTOR HERE
     ypos +=31;
     File_Number++;
    }

    Delay_ms(600);
    File_Number = 1;  //<<<<<<<<<<<<<<<<<<<<<<<<< Reset File Number To 1
}

//===========================================================

void Write_Picture(uint32_t Actual_Sector, uint8_t Memory_Buffer_Number){

    uint16_t xpos_Start = 50;
    uint16_t ypos = 14;
    Max_Bytes = 512;

    Read_Sector(512 * Actual_Sector, dataBuffer);  //ACTUAL SECTOR (uint32_t) WHERE PICTURE STARTS, NOT THE SAME AS START OF FILE. THIS IS READING THE BITMAP HEADER

    if(dataBuffer[0] ==66){            //CONFIRMS BIT ZERO AND BIT 1 = BM FOR BITMAP
     if(dataBuffer[1] ==77){
    }}else { Clear_Screen_S1D13517(red);
             Delay_ms(300);

             Write_Text("NOT A BITMAP",xpos_Start+Letter_Font_Width*x,ypos,colour);  //NOT A BITMAP

            }

    Byte2 = dataBuffer[2];
    Byte3 = dataBuffer[3];
    Byte3 = Byte3<<8;
    Byte4 = dataBuffer[4];
    Byte4 = Byte4<<16;
    Byte5 = dataBuffer[5];
    Byte5 = Byte5<<24;
    File.TotalFileSize = Byte5 + Byte4 + Byte3 + Byte2;        //Does what it says
    Byte10 = dataBuffer[10];
    Byte11 = dataBuffer[11];
    Byte11 = Byte11<<8;
    Byte12 = dataBuffer[12];
    Byte12 = Byte12<<16;
    Byte13 = dataBuffer[13];
    Byte13 = Byte13<<24;
    Image_Data_Starts_At = Byte13 + Byte12 + Byte11 + Byte10;  //Does what it says
    Byte18 = dataBuffer[18];
    Byte19 = dataBuffer[19];
    Byte19 = Byte19<<8;
    Image_Width = Byte19 + Byte18;

    Sectors_To_Read = File.TotalFileSize / 512;
    Bytes_Left_To_Read = File.TotalFileSize %512;

    if(Bytes_Left_To_Read>0){
      Sectors_To_Read +=1;  //   Sectors_To_Read = Sectors_To_Read+1;
    }

    Epson_CS = 0;
    Write_Command_EpsonS1D13517(0x52);    //page 73 Input Mode Register
    Write_Data_EpsonS1D13517(Memory_Buffer_Number<<4 | 0b0000);  //Memory Buffer Is The SDRAM Buffer Number 0 To 13 Works For Single Buffers Not Pip  Bit 3 Is Transparency
    //REGISTERS AUTO-INCREMENT !
    Write_Command_EpsonS1D13517(0x5A);    //set window for x start
    Write_Data_EpsonS1D13517(0);          //X START REGISTER
    Write_Data_EpsonS1D13517(0);          //Y START REGISTER ZER0
    Write_Data_EpsonS1D13517(0);          //Y START REGISTER 1
    Write_Data_EpsonS1D13517(0xC6);       //X END POSITION
    Write_Data_EpsonS1D13517(0x77);       //Y END POSITION REGISTER ZER0
    Write_Data_EpsonS1D13517(0x03);       //Y END POSITION REGISTER 1

    for(i=0; i<Sectors_To_Read; i++){
     Read_Sector(512 * Actual_Sector, dataBuffer);

     if(i==Sectors_To_Read-1){
       Max_Bytes = Bytes_Left_To_Read-2;
      }

     for(x = Image_Data_Starts_At; x<Max_Bytes; x = x+2){
       PMDIN = dataBuffer[x] | dataBuffer[x+1]<<8;
      }
      Actual_Sector++;
      Image_Data_Starts_At = 0;
    }
    Epson_CS = 1;
}

//==============================================================

void Write_PictureBACKUP1(uint32_t Actual_Sector, uint8_t Memory_Buffer_Number){ //ORIGINAL DO NOT TOUCH.

    uint16_t xpos_Start = 50;
    uint16_t ypos = 14;
    Max_Bytes = 512;

    Read_Sector(512 * Actual_Sector, dataBuffer);  //ACTUAL SECTOR (uint32_t) WHERE PICTURE STARTS, NOT THE SAME AS START OF FILE. THIS IS READING THE BITMAP HEADER

    if(dataBuffer[0] ==66){            //CONFIRMS BIT ZERO AND BIT 1 = BM FOR BITMAP
     if(dataBuffer[1] ==77){
    }}else { Clear_Screen_S1D13517(red);
             Delay_ms(300);

             Write_Text("NOT A BITMAP ",xpos_Start+Letter_Font_Width*x,ypos,colour);  //NOT A BITMAP

            }

    Byte2 = dataBuffer[2];
    Byte3 = dataBuffer[3];
    Byte3 = Byte3<<8;
    Byte4 = dataBuffer[4];
    Byte4 = Byte4<<16;
    Byte5 = dataBuffer[5];
    Byte5 = Byte5<<24;
    File.TotalFileSize = Byte5 + Byte4 + Byte3 + Byte2;        //Does what it says
    Byte10 = dataBuffer[10];
    Byte11 = dataBuffer[11];
    Byte11 = Byte11<<8;
    Byte12 = dataBuffer[12];
    Byte12 = Byte12<<16;
    Byte13 = dataBuffer[13];
    Byte13 = Byte13<<24;
    Image_Data_Starts_At = Byte13 + Byte12 + Byte11 + Byte10;  //Does what it says
    Byte18 = dataBuffer[18];
    Byte19 = dataBuffer[19];
    Byte19 = Byte19<<8;
    Image_Width = Byte19 + Byte18;

    Sectors_To_Read = File.TotalFileSize / 512;
    Bytes_Left_To_Read = File.TotalFileSize %512;

    if(Bytes_Left_To_Read>0){
      Sectors_To_Read +=1;  //   Sectors_To_Read = Sectors_To_Read+1;
    }

    Epson_CS = 0;
    Write_Command_EpsonS1D13517(0x52);    //page 73 Input Mode Register
    Write_Data_EpsonS1D13517(Memory_Buffer_Number<<4 | 0b0000);  //Memory Buffer Is The SDRAM Buffer Number 0 To 13 Works For Single Buffers Not Pip  Bit 3 Is Transparency
    //REGISTERS AUTO-INCREMENT !
    Write_Command_EpsonS1D13517(0x5A);    //set window for x start
    Write_Data_EpsonS1D13517(0);          //X START REGISTER
    Write_Data_EpsonS1D13517(0);          //Y START REGISTER ZER0
    Write_Data_EpsonS1D13517(0);          //Y START REGISTER 1
    Write_Data_EpsonS1D13517(0xC6);       //X END POSITION
    Write_Data_EpsonS1D13517(0x77);       //Y END POSITION REGISTER ZER0
    Write_Data_EpsonS1D13517(0x03);       //Y END POSITION REGISTER 1

    for(i=0; i<Sectors_To_Read; i++){
     Read_Sector(512 * Actual_Sector, dataBuffer);

     if(i==Sectors_To_Read-1){
       Max_Bytes = Bytes_Left_To_Read-2;
      }

     for(x = Image_Data_Starts_At; x<Max_Bytes; x = x+2){
       PMDIN = dataBuffer[x] | dataBuffer[x+1]<<8;
      }
      Actual_Sector++;
      Image_Data_Starts_At = 0;
    }
    Epson_CS = 1;
}

uint8_t Ready = 0;
void Interrupt() iv IVT_EXTERNAL_1 ilevel 7 ics ICS_SRS {    // AN25/RPE8/RE8   Interrupts PAGE 116      INTCON: INTERRUPT CONTROL REGISTER page 141

        IFS0bits.INT1IF = 0;
        Ready = 1;
}

void main() {

    uint8_t   Memory_buffer = 0;
    uint16_t  PointerToSector;
    uint32_t  Memory_Address0;
    uint32_t  Memory_Address1;
    uint32_t  Memory_Address2;
    uint8_t   link;
    uint8_t   alphaValue = 0;
    uint32_t  Buffer[14];
    uint16_t  Random = 0;
    uint8_t   OneImage = 0xC0;
    uint8_t   TwoImage = 0x80;

//=============================================================================

 // The 16MB SDRAM Must Be Set Using Multiples Of 16k Which Equals 16384 Bytes.
 // 800x480 screen =  384000 * 3 for 24 bit = 1152000 bytes.
 // Only Whole Numbers Are Permitted, i.e.Integers.
 // 16k or 16384 Multiplied By 64 = 1,048,576 Bytes. Too Small.
 //        16384 Multiplied By 71 = 1'16'3264

//=============================================================================

    Buffer[0]  = 0x00;
    Buffer[1]  = 0x11C000; //1 OK
    Buffer[2]  = 0x238000; //2 OK
    Buffer[3]  = 0x354000; //3 OK
    Buffer[4]  = 0x470000; //4 OK
    Buffer[5]  = 0x58C000; //5 OK
    Buffer[6]  = 0x6A8000; //6 OK
    Buffer[7]  = 0x7C4000; //7 OK
    Buffer[8]  = 0x8E0000; //8 OK
    Buffer[9]  = 0x9FC000; //9 OK
    Buffer[10] = 0xB18000; //10 OK
    Buffer[11] = 0xC34000; //11 OK
    Buffer[12] = 0xD50000; //12 OK
    Buffer[13] = 0xE6C000; //13 OK


//=============================================================================

    Init_16Bit_PMP();

    Init_MCU();

    Set_Bus_Speeds();

    Initialise_EpsonS1D13517_5_Inch();

    Initialise_SDCARD_New();

    Get_Boot_Information();

    Show_Boot_information();

    Get_Files();

    LATA1_bit = 0;
    TRISE8_bit = 1;        //Tear Link For Display
    INT1R = 1101;          // = RPE8  INTERRUPT FOR BLANKING PERIOD & OR ALPHA BLEND

    EnableInterrupts();
    INT1IE_bit = 1;
    INT1IP0_bit = 1;       //required priority bits
    INT1IP1_bit = 1;       //required
    INT1IP2_bit = 1;       //required
    INTCONbits.INT1EP = 1; //required INT1EP: External Interrupt 1 Edge Polarity Control bit 1 = Rising edge

    Memory_buffer=0;       //zero the buffer to start at zero first.

    while(Memory_buffer < FileCount-1){

    PointerToSector = Actual_Sector[File_Number];

    Epson_CS = 0;
    Write_Command_EpsonS1D13517(0x2A);
    Write_Data_EpsonS1D13517(Memory_buffer<<4 | 0b0001); //Enable the display   Single buffer display (default) page 65
    Write_Command_EpsonS1D13517(0x50);                   //REG[50h] Display Control Register PAGE 72
    Write_Data_EpsonS1D13517(0x80);                      //bit 7 must be set to update display
    Epson_CS = 1;

    Write_Picture(PointerToSector, Memory_buffer);

    File_Number+=1;
    Memory_buffer+=1;
    }

    Memory_Address1 = Buffer[1];
    Memory_Address2 = Buffer[2];

    link:
    Epson_CS = 0;
    Write_Command_EpsonS1D13517(0x98);                    //Set Horizontal Size  REG[98h] Alpha-Blend Horizontal Size Register PAGE 89
    Write_Data_EpsonS1D13517(0x63);                       //63 800 wide
    Write_Data_EpsonS1D13517(0xDF);                       //DF 01
    Write_Data_EpsonS1D13517(0x01);                       //Set Vertical Size Register Register 1
    Write_Data_EpsonS1D13517(TwoImage | alphaValue);      //Number of Images = 1;     6REG[9Eh] bits 5-0 bits 5 to zero is blend value   1 image: REG[9Eh] bits 7-6 = 11b   2 image: REG[9Eh] bits 7-6 = 10b

    Write_Data_EpsonS1D13517(Memory_Address1&0xFF);       //Alpha-Blend Input Image 1 Start Address bits 7-3
    Write_Data_EpsonS1D13517(Memory_Address1>>8&0xFF);    //Alpha-Blend Input Image 1 Start Address bits 15-8
    Write_Data_EpsonS1D13517(Memory_Address1>>16&0xFF);   //Alpha-Blend Input Image Start Address bits 23-16      71 * 16384 = 1,163,264 BYTES PER BUFFER

    Write_Data_EpsonS1D13517(Memory_Address2&0xFF);       //Alpha-Blend Input Image 2 Start Address bits 7-3
    Write_Data_EpsonS1D13517(Memory_Address2>>8&0xFF);    //Alpha-Blend Input Image 2 Start Address bits 15-8
    Write_Data_EpsonS1D13517(Memory_Address2>>16&0xFF);   //Alpha-Blend Input Image 2 Start Address bits 23-16

    Memory_Address0 = Buffer[13]; //OUTPUT BUFFER 13 Is Actually The 14th Buffer Zero To 13 = 14

    Write_Data_EpsonS1D13517(Memory_Address0&0xFF);       //Alpha-Blend Output Image Start Address bits 7-3
    Write_Data_EpsonS1D13517(Memory_Address0>>8&0xFF);    //Alpha-Blend Output Image Start Address bits 15-8
    Write_Data_EpsonS1D13517(Memory_Address0>>16&0xFF);   //Alpha-Blend Output Image Start Address bits 23-16

    Write_Data_EpsonS1D13517(0b00010000);                 //Disable Interrupt MasK PAGE 92     SHOULD BE NO INTERRUPT
    Write_Command_EpsonS1D13517(0xB2);
    Write_Data_EpsonS1D13517(0b00000001);                 //ENABLE Interrupt        REG[B2h] bit 0 = 1b

    Write_Command_EpsonS1D13517(0x94);                    //Start Alpha Blend  Alpha-Blend Control Register page 88
    Write_Data_EpsonS1D13517(0b00000001);                 //REG[94h] bit 0 = 1b then 0b
    Write_Command_EpsonS1D13517(0x94);
    Write_Data_EpsonS1D13517(0b00000000);                 //REG[94h] bit 0 = 1b then 0b

    //Wait for Interrupt

    if(Ready){
    Ready = 0;
    Write_Command_EpsonS1D13517(0xB6);                   //REG[B6h] bit 0 = 1b then 0b    Clear Interrupt Status
    Write_Data_EpsonS1D13517(1);
    Write_Command_EpsonS1D13517(0xB6);
    Write_Data_EpsonS1D13517(0);

    Write_Command_EpsonS1D13517(0x2A);
    Write_Data_EpsonS1D13517(Memory_buffer<<4 | 0b0001); //Enable The Display   Single Buffer Display (Default) Page 65
    Write_Command_EpsonS1D13517(0x50);                     //REG[50h] Display Control Register PAGE 72
    Write_Data_EpsonS1D13517(0x80);                        //bit 7 must be set to update display
    Epson_CS = 1;
    LATA1_bit = 1;
    Delay_ms(90);

    alphaValue ++;

    if(alphaValue>32){
     Memory_Address2 = Buffer[Random];
     Random = rand()%13;
     Memory_Address1 = Buffer[Random];
     alphaValue = 0;
    }
    LATA1_bit = 0;
    goto link;
   }

}

