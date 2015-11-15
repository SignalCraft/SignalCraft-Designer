void saturation(int *in0, int *out0) {
	if (*in0 > 10) {
		*out0 = 10;
	} else if (*in0 < -10) {
		*out0 = -10;
	} else {
		*out0 = *in0;
	}
}