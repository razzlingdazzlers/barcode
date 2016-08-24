/*
  Convert text to bar code 128
  Released under MIT license

  Copyright (c) 2016 razzling.dazzlers@gmail.com

  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 */

#define BAR_CODE_ASCII_START 32
#define BAR_CODE_ASCII_ZERO  48
static Barcode:BAR_CODE_128[] = {
    212222, 222122, 222221, 121223, 121322, 131222, 122213, 122312, 132212,
    221213, 221312, 231212, 112232, 122132, 122231, 113222, 123122, 123221,
    223211, 221132, 221231, 213212, 223112, 312131, 311222, 321122, 321221,
    312212, 322112, 322211, 212123, 212321, 232121, 111323, 131123, 131321,
    112313, 132113, 132311, 211313, 231113, 231311, 112133, 112331, 132131,
    113123, 113321, 133121, 313121, 211331, 231131, 213113, 213311, 213131,
    311123, 311321, 331121, 312113, 312311, 332111, 314111, 221411, 431111,
    111224, 111422, 121124, 121421, 141122, 141221, 112214, 112412, 122114,
    122411, 142112, 142211, 241211, 221114, 413111, 241112, 134111, 111242,
    121142, 121241, 114212, 124112, 124211, 411212, 421112, 421211, 212141,
    214121, 412121, 111143, 111341, 131141, 114113, 114311, 411113, 411311,
    113141, 114131, 311141, 411131, 211412, 211214, 211232, 2331112,
  };

#define START_A 103
#define STOP    106
/*
  START_A = 103
  START_B = 104
  START_C = 105
  SHIFT   = 98
  CODE_A  = 101
  CODE_B  = 100
  CODE_C  = 99
  STOP    = 106
  FNC_1   = 102
  FNC_2   = 97
  FNC_3   = 96
 */

stock barcode(string[], Barcode:widths[], max_barcode = sizeof widths) {
    new sum = 0, i = 0, len;
    widths[0] = BAR_CODE_128[START_A];
    for(len = strlen(string); i < len; i++) {
        sum += (i + 1) * string[i];
        widths[i + 1] = BAR_CODE_128[string[i] - BAR_CODE_ASCII_START];
    }
    widths[i++] = BAR_CODE_128[sum % 103];
    widths[i++] = BAR_CODE_128[STOP];
    for(; i < max_barcode; i++) widths[i] = 0;
}

stock barcode_to_bool(
    Barcode:widths[], bool:black_is_true[], max_bools = sizeof black_is_true) {
    new w = 0, b = 0, bool:black = true, t, l, count, tmpval[8];
    while(widths[w]) {
        valstr(tmpval, widths[w]);
        for(t = 0; t < sizeof(tmpval); t++) {
            if(tmpval[t] == 0) break;
            count = tmpval[t] - BAR_CODE_ASCII_ZERO;
            for(l = 0; l < count; l++) {
                black_is_true[b] = black;
                b++;
            }
            black = !black;
        }
        w++;
    }
    for(; b < max_bools; b++) black_is_true[b] = false;
}
