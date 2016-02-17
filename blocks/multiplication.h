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

struct multiplication_options {};

void multiplication(struct multiplication_options *options, int *in0, int *in1, int *out0){
  *out0 = *in0 * *in1;
}
