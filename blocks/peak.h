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
struct peak_options {}

int peak_max = 0;

void peak(struct peak_options *options, int *in, int *out){
  if(*in > peak_max){
    peak_max = *in;
  }
  *out = peak_max;
}
