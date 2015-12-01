struct addition_options { };

void addition(struct addition_options *options, int *in0, int *in1, int *out0) {
	*out0 = *in0 + *in1;
}