.global grayFP
.type grayFP, %function
grayFP:
  sub sp, sp, #16
  str lr, [sp]

  // FIΧМЕ: implement the void grayFP(char* pixelsStart, int numPixels)
  // function to convert numPixels pixels starting at pixelsStart to
  // grayscale. Do this by calculating the value:
  //   grayscale_value = 0.2126*red + 0.7152*green + 0.0722*blue
  // and rounding the result to the nearest whole number. Use double
  // precision floating point numbers in all your calculations. Change
  // the red, green, and blue channels of the original pixel all to
  // grayscale_value.

  // Remember that FP assembly is *not* SIMD--you can't work on multiple pixels at a time
  // Hint 1: The colors are in ***blue green red*** order, *not* red green blue
  // Hint 2: Read a single color at a time for a single pixel with ldrb
  // Hint 3: Put that color in a 64-bit FP register with ucvtf
  // Hint 4: Use the fcvtau instruction to do the rounding and conversion to a 32-bit int

  ldr lr, [sp]
  add sp, sp, #16
  ret
