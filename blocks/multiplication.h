/*
 * =====================================================================================
 *
 *       Filename:  multiplication.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/17/2016 06:05:53 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Joshua Tang
 *   Organization:  SignalCraft
 *
 * =====================================================================================
 */

struct multiplication_options_int {};

struct multiplication_options_afp {};

struct multiplication_options_float {};

void multiplication_int(struct multiplication_options_int *options, int *in0, int *in1, int *out0){
  *out0 = *in0 * *in1;
}

void multiplication_afp(struct multiplication_options_afp *options, int *in0, int *in1, int *out0){
  *out0 = (int64_t)(*in0) * *in1;
}

void multiplication_float(struct multiplication_options_float *options, float *in0, float *in1, float *out0){
  *out0 = *in0 * *in1;
}
