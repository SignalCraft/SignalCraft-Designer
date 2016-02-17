/*
 * =====================================================================================
 *
 *       Filename:  low_pass_filter.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/17/2016 02:12:01 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author: Josh Tang
 *   Organization: SignalCraft 
 *
 * =====================================================================================
 */

struct low_pass_filter_options {
  int threshold;
}

void low_pass_filter(struct low_pass_filter_options *options, int *in0, int *out0){
  int Beta = threshold;//4;
  *in0 <<= FP_Shift;
  *out0 = (*out0 << Beta) - *out0;
  *out0 += *in0;
  *out0 >>= Beta;
  *out0 >>= FP_Shift;
}

