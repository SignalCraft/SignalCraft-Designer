struct addition_options_int { };

struct addition_options_afp { };

struct addition_options_float { };

void addition_int(struct addition_options_int *options, int *in0, int *in1, int *out0) {
	*out0 = *in0 + *in1;
}

void addition_afp(struct addition_options_afp *options, int *in0, int *in1, int *out0) {
	*out0 = (*in0 >> 1) + (*in1 >> 1);
}

void addition_float(struct addition_options_float *options, float *in0, float *in1, float *out0) {
	*out0 = *in0 + *in1;
}