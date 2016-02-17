struct addition_options { };

void addition(struct addition_options *options, int16_t *in0, int16_t *in1, int16_t *out0) {
	*out0 = *in0 + *in1;
}