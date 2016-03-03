/*
 * =====================================================================================
 *
 *       Filename:  peak.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/17/2016 06:15:55 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Josh Tang
 *   Organization:  SignalCraft
 *
 * =====================================================================================
 */
struct peak_options_int {};

struct peak_options_afp {};

struct peak_options_float {};

int peak_max_int = 0;

int peak_max_afp = 0;

float peak_max_float = 0;

void peak_int(struct peak_options_int *options, int *in, int *out){
  if(*in > peak_max_int){
    peak_max_int = *in;
  }
  *out = peak_max_int;
}

void peak_afp(struct peak_options_afp *options, int *in, int *out){
  if(*in > peak_max_afp){
    peak_max_afp = *in;
  }
  *out = peak_max_afp;
}

void peak_float(struct peak_options_float *options, float *in, float *out){
  if(*in > peak_max_float){
    peak_max_float = *in;
  }
  *out = peak_max_float;
}
